#include "modo_juego.h"
#include "server_gameloop.h"
#define LOBBY_REQUEST 0x01
#define RATE 1000 / 30

#define ALTO_TILE 32
#define ANCHO_TILE 24

ModoJuego::ModoJuego(ServerClient& cliente, Queue<EventoServer>& cola_cliente, Queue<EstadoJuego>& recibidos, uint8_t id,
std::list<ModoJuego*>& partidas_distintas):
cliente(cliente), queue_cliente(cola_cliente), broadcast(recibidos), ultimo_estado(), id_partida(id),
partidas_distintas(partidas_distintas), partida_nueva(false), clientes() 
{}

void ModoJuego::run() {
    clientes.emplace_back(&cliente);

    bool cerrado = false;
    float tiempo_ultimo_frame = SDL_GetTicks();
    bool iniciar_partida = false; 

    ultimo_estado.id_jugador = cliente.get_id();
    ultimo_estado.id_partida = id_partida;
    ultimo_estado.partida_iniciada = 0x00;
    ultimo_estado.informacion_enviada = ESTADO_LOBBY;

    broadcast.enviar_mensaje(ultimo_estado);
    
    while (!iniciar_partida){
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

    if (partida_nueva){
        
        LectorJson lector_mapa = LectorJson();
        Mapa mapa = lector_mapa.procesar_mapa("../resources/maps/mapa5");
        EstadoJuego estado_inicial;
        
        estado_inicial.id_partida = id_partida;
        estado_inicial.partida_iniciada = 0x01;
        estado_inicial.mapa = mapa;
        estado_inicial.informacion_enviada = ENVIAR_MAPA;
        leer_configuracion(RUTA_CONFIGURACION);
        inicializar_patos(estado_inicial);
        inicializar_cajas(estado_inicial);
        inicializar_armas(estado_inicial);

        // QueueProtegida queue_nueva(broadcast.conseguir_cola());
        auto* jugadores = new std::map<uint16_t, Queue<EstadoJuego>*>();
        for (ServerClient* client : clientes){
            auto* queue = new Queue<EstadoJuego>();
            jugadores->emplace(client->get_id(), queue);
            client->cambiar_queue(jugadores->at(client->get_id()));
        }


        auto* gameloop = new GameLoop(jugadores, &cerrado, id_partida);
        for (ServerClient* client : clientes){
            client->iniciar_partida(estado_inicial);
            gameloop->agregar_cliente(*client, client->get_queue());
        }
        gameloop->start();
    }
    while (not cerrado){
        drop_and_rest(tiempo_ultimo_frame);
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
        std::cout << "hay dos jugadores" << std::endl;
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