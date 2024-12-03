#include "modo_juego.h"
#include "server_gameloop.h"
#define LOBBY_REQUEST 0x01
#define RATE 1000 / 30

#define ALTO_TILE 32
#define ANCHO_TILE 24

ModoJuego::ModoJuego(ServerClient& cliente, Queue<EventoServer>& cola_cliente, Queue<EstadoJuego>& recibidos, uint8_t id,
std::list<ModoJuego*>& partidas_distintas, std::atomic_bool& cerrar_servidor):
cliente(cliente), queue_cliente(cola_cliente), broadcast(recibidos), ultimo_estado(), id_partida(id),
partidas_distintas(partidas_distintas), partida_nueva(false), clientes(), cerrar_servidor(cerrar_servidor) 
{
    mapas_disponibles = {
        "../resources/maps/mapa-con-4-spawns-1",
        "../resources/maps/mapa-con-4-spawns-2",
        "../resources/maps/mapa-con-4-spawns-3",
        "../resources/maps/mapa-con-4-spawns-4",
        "../resources/maps/mapa-con-4-spawns-5"
    };
}

void ModoJuego::run() {
    clientes.emplace_back(&cliente);

    float tiempo_ultimo_frame = SDL_GetTicks();
    bool iniciar_partida = false; 

    ultimo_estado.id_jugador = cliente.get_id();
    ultimo_estado.id_partida = id_partida;
    ultimo_estado.partida_iniciada = 0x00;
    ultimo_estado.informacion_enviada = ESTADO_LOBBY;

    broadcast.enviar_mensaje(ultimo_estado);
    
    while (!iniciar_partida && !cerrar_servidor){
        std::vector<EventoServer> eventos;

        EventoServer evento;
            while(queue_cliente.try_pop(evento)){
            eventos.push_back(evento);
        } 
        for(EventoServer evento : eventos){
            procesar_evento_lobby(evento, iniciar_partida);
        }
        buscar_partidas();
        ultimo_estado.informacion_enviada = ESTADO_LOBBY;
        broadcast.enviar_mensaje(ultimo_estado);
        drop_and_rest(tiempo_ultimo_frame);
    }

    if (cerrar_servidor){
        for (ServerClient* client : clientes){
            if (client->get_id() == cliente.get_id()){
                client->get_queue().close();
                client->join();
                delete client;
            }
        }
        return;
    }
    
    
    std::vector<Puntaje> puntaje_jugadores;
    for (ServerClient* client : clientes){
        Puntaje jugador(client->get_id());
        puntaje_jugadores.emplace_back(std::move(jugador));
        if (client->juegan_dos()){
            Puntaje jugador2(client->get_id() + 1);
            puntaje_jugadores.emplace_back(std::move(jugador2));
        }
    }

    auto* jugadores = new std::map<uint16_t, Queue<EstadoJuego>*>();
    for (ServerClient* client : clientes){
        auto* queue = new Queue<EstadoJuego>();
        jugadores->emplace(client->get_id(), queue);
        client->cambiar_queue(jugadores->at(client->get_id()));
    }

    if (partida_nueva){
        
        while (no_hay_ganador(puntaje_jugadores) && !cerrar_servidor) {
            LectorJson lector_mapa = LectorJson();
            std::string mapa_seleccionado = sortear_mapa();
            Mapa mapa = lector_mapa.procesar_mapa(mapa_seleccionado);
            EstadoJuego estado_inicial;
            
            estado_inicial.id_partida = id_partida;
            estado_inicial.partida_iniciada = 0x01;
            estado_inicial.mapa = mapa;
            estado_inicial.informacion_enviada = ENVIAR_MAPA;
            leer_configuracion(RUTA_CONFIGURACION);
            inicializar_patos(estado_inicial);
            inicializar_cajas(estado_inicial);
            inicializar_armas(estado_inicial);
            
            bool ronda_finalizada = false;
            auto* gameloop = new GameLoop(jugadores, &ronda_finalizada, id_partida, mapa_seleccionado, puntaje_jugadores);
            for (ServerClient* client : clientes){
                client->enviar_estado(estado_inicial);
                gameloop->agregar_cliente(*client, client->get_queue());
            }

            gameloop->start();
            while (!ronda_finalizada && !cerrar_servidor){
                drop_and_rest(tiempo_ultimo_frame);
            }

            //el gameloop siempre termina cuando termina la partida o se cierra la conexion, cualquiera de las 2
            //alcanza, solo hay que liberarlo
            gameloop->join();
            delete gameloop;
            if (no_hay_ganador(puntaje_jugadores)){
                EstadoJuego estado_final;
                estado_final.id_partida = id_partida;
                estado_final.informacion_enviada = PARTIDA_TERMINADA;
                estado_final.partida_iniciada = 0x00;
                for (ServerClient* client : clientes){
                    client->enviar_estado(estado_final);
                }
            }
        }
    } else {
        //joinee la partida de alguien, tengo que esperar simplemente
        drop_and_rest(tiempo_ultimo_frame);
    }
    
    //enviar ganador de la partida
    EstadoJuego ultimo_estado;
            
    ultimo_estado.id_partida = id_partida;
    ultimo_estado.informacion_enviada = ENVIAR_RESULTADO_PARTIDA;
    ultimo_estado.ganador_partida = conseguir_ganador(puntaje_jugadores);
    for (ServerClient* client : clientes){
        client->enviar_estado(ultimo_estado);
    }

    delete jugadores;
    for (ServerClient* client : clientes){
        if (client->get_id() == cliente.get_id()){
            client->get_queue().close();
            client->join();
            delete client;
            break;
        }
    }
}

bool ModoJuego::tiene_partida() { return partida_nueva; }

uint8_t ModoJuego::obtener_id_partida() { return id_partida; }

bool ModoJuego::tiene_id(uint8_t un_id) { return (un_id == id_partida); }


void ModoJuego::drop_and_rest(float& tiempo_ultimo_frame){
    Uint32 tiempo_actual = SDL_GetTicks();
    int32_t descansar = RATE - (tiempo_actual - tiempo_ultimo_frame);

    if (descansar < 0) {
        int32_t tiempo_atrasado = -descansar;
        descansar = RATE - (tiempo_atrasado % RATE);
        int32_t tiempo_perdido = tiempo_atrasado + descansar;

        tiempo_ultimo_frame += tiempo_perdido;
    }

    SDL_Delay(descansar);
    tiempo_ultimo_frame += RATE;
}


void ModoJuego::procesar_evento_lobby(EventoServer& evento, bool& iniciar_partida) {
    PedidoJugador pedido_cliente = evento.pedido;
    ejecutar_accion_lobby(pedido_cliente, evento.jugador_id, iniciar_partida);
}

void ModoJuego::ejecutar_accion_lobby(PedidoJugador& pedido, uint16_t id_jugador, bool& iniciar_partida) {
    id_jugador = id_jugador;
    if (pedido.crear_partida == LOBBY_REQUEST){
        partida_nueva = true;
        return;
        } 
    if (pedido.unirse_a_partida == LOBBY_REQUEST){
        for (ModoJuego* partida_posible : partidas_distintas){
            if (partida_posible->tiene_id(pedido.id_partida_a_unirse)){
                partida_posible->nuevo_jugador(&cliente);   
                ultimo_estado.id_partida =  pedido.id_partida_a_unirse;
            }
        }
        return;
    }
    if (pedido.un_jugador == LOBBY_REQUEST){
        //por default es uno solo
        return;
    }
    if (pedido.dos_jugadores == LOBBY_REQUEST){
        cliente.juegan_2_personas();
        return;
    }
    if(pedido.empezar == LOBBY_REQUEST){
        //ultimo_estado.lobby_data.empezar_partida(0);
        iniciar_partida = true;
        return;
    }
}

void ModoJuego::buscar_partidas() {
    std::list<uint8_t> partidas;
        for (ModoJuego* cliente_nuevo : partidas_distintas){
            if (cliente_nuevo->tiene_partida()){
                partidas.emplace_front(cliente_nuevo->obtener_id_partida());
            }
        }
    ultimo_estado.partidas = partidas;
}

std::string ModoJuego::sortear_mapa() {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, mapas_disponibles.size() - 1);

    int indice_aleatorio = dis(gen);
    return mapas_disponibles[indice_aleatorio];
}

void ModoJuego::leer_configuracion(const std::string& archivo_yaml){
    YAML::Node config = YAML::LoadFile(archivo_yaml);

    for (const auto& arma : config["armas"]) {
        ArmaConfig config_arma;
        
        config_arma.nombre = arma.first.as<std::string>();
        config_arma.alcance = arma.second["alcance"].as<int>();
        config_arma.municiones = arma.second["municiones"].as<int>();
        std::string path = arma.second["path"].as<std::string>();

        armamento_config[path] = config_arma;
        if (config_arma.nombre != "armadura" && config_arma.nombre != "casco") {
            armas_posibles.push_back(config_arma);
        }
    }
}

void ModoJuego::inicializar_patos(EstadoJuego& estado) {
    int pos_x = 0;
    int pos_y = 0;
    std::vector<uint16_t> id_jugadores;
    for (ServerClient* client : clientes){
        id_jugadores.emplace_back(client->get_id());
        if (client->juegan_dos()){
            id_jugadores.emplace_back(client->get_id() + 1);
        }
    }
    int contador = 0;
    std::map<std::string, std::vector<SDL_Point>> spawns = estado.mapa.getSpawns();
        //std::cout << "agarro spawns" << std::endl;
        std::vector<SDL_Point> posicion = spawns["default"];
    
        for(SDL_Point coord : posicion){
            pos_x = coord.x;
            pos_y = coord.y;
            // for (Pato pato : ultimo_estado.patos){
            //     if (pato.get_pos_x() != pos_x && pato.get_pos_y() != pos_y){
                    
            //     }
            // }
            if (static_cast<int>(id_jugadores.size()) > contador){
                Pato pato(id_jugadores.at(contador), pos_x, pos_y, 0);
                // pato.tomar_armadura();
                // pato.equipar_armadura();
                // pato.tomar_casco();
                // pato.equipar_casco();
                estado.patos.emplace_back(pato);
                contador++;
            } else {
                return;
            }
        }
}

void ModoJuego::inicializar_cajas(EstadoJuego& estado) {
    for (const auto& cajas : estado.mapa.getCajas()) {
        for (SDL_Point posicion_caja : cajas.second) {
            Arma arma = elegir_arma_aleatoria(posicion_caja);
            arma.set_se_agarro(true);
            Caja caja(estado.cajas.size() + 1, posicion_caja.x, posicion_caja.y, arma);
            estado.armas.push_back(arma);
            estado.cajas.push_back(caja);
        }
    }
}

Arma ModoJuego::elegir_arma_aleatoria(SDL_Point posicion_caja){
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> distrib(0, armas_posibles.size() - 1);
    int indice_aleatorio = distrib(gen);
    ArmaConfig elemento_aleatorio = armas_posibles[indice_aleatorio];
    Arma arma = mapear_armas(elemento_aleatorio, posicion_caja);
    return arma;
}

Arma ModoJuego::mapear_armas(ArmaConfig armamento, SDL_Point posicion_arma){
    if (armamento.nombre == "ak47") {
        return AK47(ultimo_estado.armas.size() + 1, posicion_arma.x, posicion_arma.y, armamento.municiones, armamento.alcance * ANCHO_TILE);
    } else if (armamento.nombre == "escopeta") {
        return Escopeta(ultimo_estado.armas.size() + 1, posicion_arma.x, posicion_arma.y, armamento.municiones, armamento.alcance * ANCHO_TILE);
    } else if (armamento.nombre == "laserRifle") {
        return LaserRifle(ultimo_estado.armas.size() + 1, posicion_arma.x, posicion_arma.y, armamento.municiones, armamento.alcance * ANCHO_TILE);
    } else if (armamento.nombre == "magnum") {
        return Magnum(ultimo_estado.armas.size() + 1, posicion_arma.x, posicion_arma.y, armamento.municiones, armamento.alcance * ANCHO_TILE);
    } else if (armamento.nombre == "pewpewLaser") {
        return PewPewLaser(ultimo_estado.armas.size() + 1, posicion_arma.x, posicion_arma.y, armamento.municiones, armamento.alcance * ANCHO_TILE);
    } else if (armamento.nombre == "pistolaCowboy") {
        return PistolaCowboy(ultimo_estado.armas.size() + 1, posicion_arma.x, posicion_arma.y, armamento.municiones, armamento.alcance * ANCHO_TILE);
    } else if (armamento.nombre == "pistolaDuelos") {
        return PistolaDuelos(ultimo_estado.armas.size() + 1, posicion_arma.x, posicion_arma.y, armamento.municiones, armamento.alcance * ANCHO_TILE);
    } else if (armamento.nombre == "sniper") {
        return Sniper(ultimo_estado.armas.size() + 1, posicion_arma.x, posicion_arma.y, armamento.municiones, armamento.alcance * ANCHO_TILE);
    } else {
        return Arma();
    }
}

void ModoJuego::inicializar_armas(EstadoJuego& estado) {
for (const auto& armas : estado.mapa.getEquipamiento()) {
        for (SDL_Point posicion_arma : armas.second) {
            ArmaConfig armamento = armamento_config[armas.first];
            if(armamento.nombre == "armadura"){
                Proteccion proteccion(ultimo_estado.armaduras.size()+1, posicion_arma.x, posicion_arma.y, ARMADURA_ENUM, false);
                estado.armaduras.push_back(proteccion);
                continue;
            }else if(armamento.nombre == "casco"){
                Proteccion proteccion(estado.armaduras.size()+1, posicion_arma.x, posicion_arma.y, CASCO_ENUM, false);
                estado.armaduras.push_back(proteccion);
                continue;
            }
            Arma arma = mapear_armas(armamento, posicion_arma);
            estado.armas.push_back(arma);
        }
    }
}

void ModoJuego::nuevo_jugador(ServerClient* client){
    clientes.emplace_back(client);
}

bool ModoJuego::no_hay_ganador(std::vector<Puntaje>& puntaje_jugadores) {
    for (Puntaje& jugador : puntaje_jugadores){
        if (jugador.gano_la_partida()){
            return false;
        }
    }
    return true;
}
uint16_t ModoJuego::conseguir_ganador(std::vector<Puntaje>& puntaje_jugadores) {
    uint16_t ganador = 0;
    for (Puntaje& jugador : puntaje_jugadores){
        if (jugador.gano_la_partida()){
            ganador = jugador.get_id();
        }
    }
    return ganador;
}
