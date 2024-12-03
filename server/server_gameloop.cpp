#include "server_gameloop.h"

#include "../common/common_constantes.h"
#include <SDL2/SDL.h>
#include <random>

#define RATE 1000 / 30
#define BAZOOKA "Bazooka"
#define CHAINSAW "Chainsaw"
#define DEATH_RAY "Death ray"
#define SHOTGUN "Shotgun"
#define DISTANCIA_ARMA 4

#define ALTO_TILE 32
#define ANCHO_TILE 24

GameLoop::GameLoop(std::map<uint16_t, Queue<EstadoJuego>*>* mapa_jugadores,
        bool* conexion, uint8_t id, std::string mapa_seleccionado, std::vector<Puntaje>& puntaje_jugadores):
        clientes(),
        esta_cerrado(conexion),
        id_ultimo_jugador(0), id_partida(id), mapa_jugadores(mapa_jugadores), 
        mapa_a_jugar(mapa_seleccionado), puntaje_jugadores(puntaje_jugadores)
        {
        ultimo_estado = EstadoJuego();
        }


// void GameLoop::cerrar_gameloop() {
//     cola_eventos.close();
//     clientes.cerrar_gameloop();
//     _is_alive = false;
// }

// void GameLoop::eliminar_clientes_cerrados() {
//     clientes.eliminar_clientes_cerrados();
// }

void GameLoop::agregar_cliente(ServerClient& cliente, Queue<EventoServer>& cola_cliente) {
    clientes.agregar_cliente(cliente, cola_cliente);
    // if(cliente.get_id() == id_ultimo_jugador){
    //     uint16_t id_nuevo = id_ultimo_jugador + 1;
    //     mandar_id_cliente(id_nuevo);
    //     id_ultimo_jugador = id_nuevo;
    //     return;
    // }
    // mandar_id_cliente(cliente.get_id());
    // id_ultimo_jugador = cliente.get_id();
}

void GameLoop::procesar_evento(EventoServer& evento, EstadoJuego& estado_juego) {
    for (Pato& pato: estado_juego.patos) {
        if (pato.get_id() == evento.jugador_id) {
            ejecutar_accion(evento.accion, pato);
        }

    }
}

void GameLoop::ejecutar_accion(uint8_t accion, Pato& pato) {
    Bala bala;
    Caja caja;
    bool puede_disparar = false;
    switch (accion) {
        case MOVER_IZQUIERDA:
            pato.estado.set_moviendo_izquierda();
            break;
        case MOVER_DERECHA:
            pato.estado.set_moviendo_derecha();
            break;
        case TIRAR_PISO:
            if (pato.estado.get_estado_salto() == BYTE_NULO) {
                pato.estado.set_agacharse();
            }
            break;
        case APUNTAR_ARRIBA:
            pato.apuntar_arriba();
            // pato.saltar();
            break;
        case SALTAR:
            if (pato.estado.get_estado_salto() == BYTE_NULO) {
                pato.levantarse_del_piso();
                pato.saltar();
            }
            if (pato.estado.get_estado_salto() == CAER) {
                pato.estado.set_aletear();
            }
            break;
        case AGARRAR_RECOMPENSA:
            //pato.saltar();
            agarrar_recompensa(pato);
            break;
        case DEJAR_MOVER_IZQUIERDA:
            pato.estado.set_dejar_de_moverse();
            break;
        case DEJAR_MOVER_DERECHA:
            pato.estado.set_dejar_de_moverse();
            break;
        case DEJAR_APUNTAR_ARRIBA:
            pato.dejar_de_apuntar_arriba();
            break;
        case DEJAR_SALTAR:
            if (pato.contador_salto == 5) {
                pato.estado.set_dejar_de_saltar();
                pato.estado.set_caer();
                pato.contador_salto = 0;
            }
            if (pato.estado.get_estado_salto() == ALETEAR) {
                pato.estado.set_dejar_de_aletear();
                pato.estado.set_caer();
            }
            // pato.estado.set_dejar_de_saltar();
            break;
        case DEJAR_TIRAR_PISO:
            pato.levantarse_del_piso();
            break;
        case TOMAR_ARMA:
            //pato.saltar();
            // llamar a un metodo que recorra el array de armas y devuelva la cercana al pato
            //pato.tomar_arma();
            break;
        case DISPARAR:
            puede_disparar = pato.disparar();
            if (puede_disparar){
                crear_bala(pato);
                if (pato.estado.get_estado_agachado() == TIRAR_PISO) {
                    pato.estado.set_dejar_de_agacharse();
                }
            }
            break;
        default:
            break;

    }
}

void GameLoop::agarrar_recompensa(Pato& pato){
    for (Proteccion& proteccion : ultimo_estado.armaduras){
        if(pato.colisiona_con_recompensa(proteccion.get_hitbox()) == Recompensas){
            if(!proteccion.get_se_agarro()){
                if (proteccion.get_tipo() == CASCO_ENUM) {
                    if (!pato.get_casco_equipado()) {
                        pato.equipar_casco();
                        proteccion.set_se_agarro(true);
                    }
                }else{
                    if (!pato.get_armadura_equipada()) {
                        pato.equipar_armadura();
                        proteccion.set_se_agarro(true);
                    }
                }
                return;
            }
        }
    }
    if (pato.tiene_arma()) {
        Arma arma_pato = pato.get_arma();
        pato.soltar_arma();
        for (Arma& arma : ultimo_estado.armas){
            if (arma.get_id() == arma_pato.get_id()){
                arma.set_se_agarro(false);
                arma.set_pos_x(pato.get_pos_x());
                arma.set_pos_y(pato.get_pos_y());
                arma.set_municion_disponible(arma_pato.get_municion_disponible());
                return;
            }
        }
        return;
    }
    for(Caja& caja : ultimo_estado.cajas){
        if(pato.colisiona_con_recompensa(caja.get_hitbox()) == Recompensas){
            if (!caja.get_esta_vacia()) {
                Arma arma = caja.get_arma();
                pato.tomar_arma(arma);
                caja.set_esta_vacia(true);
                return;
            }
        }
    }
    for(Arma& arma : ultimo_estado.armas){
        if(pato.colisiona_con_recompensa(arma.get_hitbox()) == Recompensas){
            if(!arma.get_se_agarro()){
                arma.set_se_agarro(true);
                pato.tomar_arma(arma);
                return;
            }
        }
    }
}

bool GameLoop::validar_movimiento(Pato& pato, TipoColision colision){
    bool colisiona = false;
    for (Tile& tile: colisiones) {
        if (pato.colisiona_con_tile(tile.get_hitbox()) == colision) {
            colisiona = true;
            break;
        }
    }
    return colisiona;
}

void GameLoop::aplicar_estados(){
    for(Pato& pato : ultimo_estado.patos){
        if(pato.estado.get_estado_movimiento() == MOVER_DERECHA){
            bool colisiona = validar_movimiento(pato, ParedIzquierda);
            if (!colisiona) {
                pato.moverse_derecha();
                pato.levantarse_del_piso();
            }
        }else if(pato.estado.get_estado_movimiento() == MOVER_IZQUIERDA){
            bool colisiona = validar_movimiento(pato, ParedDerecha);
            if (!colisiona) {
                pato.moverse_izquierda();
                pato.levantarse_del_piso();
            }
        }
        if(pato.estado.get_estado_agachado() == TIRAR_PISO ){
            pato.tirarse_al_piso();
        }
        if(pato.estado.get_estado_salto() == ALETEAR){
            pato.aletear();
            for (Tile& tile: colisiones) {
                if (pato.colisiona_con_tile(tile.get_hitbox()) == Piso) {
                    pato.estado.set_dejar_de_aletear();
                    pato.ajustar_sobre_tile(tile.get_hitbox());
                    break;
                }
            }
        }
    }
}

void GameLoop::crear_bala(Pato& pato){  
    if (!pato.esta_apuntando_arriba()){
        if (pato.get_direccion() == DIRECCION_DERECHA) {
            Bala bala(ultimo_estado.balas.size() + 1, pato.get_pos_x(), pato.get_pos_y() + DISTANCIA_ARMA, pato.get_pos_x() + pato.get_arma().get_alcance(), pato.get_pos_y() + DISTANCIA_ARMA, pato.get_direccion(), pato.get_arma().get_tipo_arma(), pato.get_id());
            // std::cout << "cree bala "<< static_cast<int>(bala.get_id()) <<" pos x bala: " << static_cast<int>(bala.get_pos_x()) << std::endl;
            ultimo_estado.balas.push_back(bala);
        } else {
            bool fuera_rango = pato.get_pos_x() < pato.get_arma().get_alcance();
            uint16_t pos_final_x = fuera_rango ? 0 : pato.get_pos_x() - pato.get_arma().get_alcance();
            Bala bala(ultimo_estado.balas.size() + 1, pato.get_pos_x(), pato.get_pos_y() + DISTANCIA_ARMA, pos_final_x, pato.get_pos_y() + DISTANCIA_ARMA, pato.get_direccion(), pato.get_arma().get_tipo_arma(), pato.get_id());
            // std::cout << "cree bala "<< static_cast<int>(bala.get_id()) <<"pos x bala: " << static_cast<int>(bala.get_pos_x()) << std::endl;
            ultimo_estado.balas.push_back(bala);
        }
    } else {
        Bala bala(ultimo_estado.balas.size() + 1, pato.get_pos_x(), pato.get_pos_y(), pato.get_pos_x(), pato.get_pos_y() - pato.get_arma().get_alcance(), pato.get_direccion(), pato.get_arma().get_tipo_arma(), pato.get_id());
        ultimo_estado.balas.push_back(bala);
    }
}

// void GameLoop::enviar_estado_juego_si_cambio( EstadoJuego& estado_anterior) {
//     for(Pato& pato :ultimo_estado.patos){
//         if (pato.estado.get_estado_agachado() != estado_anterior.patos.front().estado.get_estado_agachado() || pato.estado.get_estado_movimiento() != estado_anterior.patos.front().estado.get_estado_movimiento() || pato.estado.get_estado_salto() != estado_anterior.patos.front().estado.get_estado_salto() || pato.estado.get_estado_disparo() != estado_anterior.patos.front().estado.get_estado_disparo() || pato.esta_apuntando_arriba() != estado_anterior.patos.front().esta_apuntando_arriba()) {
//             cola_estados_juego.enviar_mensaje(ultimo_estado);
//         }
//         if (pato.get_pos_x() != estado_anterior.patos.front().get_pos_x() || pato.get_pos_y() != estado_anterior.patos.front().get_pos_y()) {            
//             cola_estados_juego.enviar_mensaje(ultimo_estado);
//         }
//     }
//     bool cambio = false;
//     for (Bala& bala: ultimo_estado.balas) {
//         if (bala.get_pos_x() != estado_anterior.balas.front().get_pos_x() || bala.get_pos_y() != estado_anterior.balas.front().get_pos_y()) {
//             cambio = true;
//         }
//     }
//     if (cambio) {
//         cola_estados_juego.enviar_mensaje(ultimo_estado);
//     }
// }

void GameLoop::avanzar_balas_direccion_izquierda(std::__cxx11::list<Bala>::iterator& it){
    if (it->get_direccion() == DIRECCION_IZQUIERDA) {
        // std::cout << "pos x bala " << it->get_id() << " antes de avance: " << static_cast<int>(it->get_pos_x()) << std::endl;
        if (it->get_pos_x() < 5) {
            it->set_pos_x(0);
        } else {
            it->set_pos_x(it->get_pos_x() - 5);
        }
        //it->set_pos_x(it->get_pos_x() - 5);
        // std::cout << "pos x bala " << it->get_id() << " despues de avance: " << static_cast<int>(it->get_pos_x()) << std::endl;
    }
}

void GameLoop::avanzar_balas_direccion_derecha(std::__cxx11::list<Bala>::iterator& it){
    if (it->get_direccion() == DIRECCION_DERECHA) {
        // std::cout << "pos x bala " << it->get_id() << " antes de avance: " << static_cast<int>(it->get_pos_x()) << std::endl;
        it->set_pos_x(it->get_pos_x() + 5);
        // std::cout << "pos x bala " << it->get_id() << " despues de avance: " << static_cast<int>(it->get_pos_x()) << std::endl;
    }
}

void GameLoop::avanzar_balas_direccion_arriba(std::__cxx11::list<Bala>::iterator& it){
    if (it->get_direccion() == DIRECCION_ARRIBA) {
        it->set_pos_y(it->get_pos_y() - 5);
        // std::cout << "pos y bala avance :" << static_cast<int>(it->get_pos_y()) << std::endl;
    }
}

void GameLoop::eliminar_balas_fuera_de_alcance(std::__cxx11::list<Bala>::iterator& it){
    if ((it->get_pos_x() >= it->get_pos_x_final() && it->get_direccion() == DIRECCION_DERECHA)) {
        // std::cout << "se elimina la bala que va a la derecha" << std::endl;
        it = ultimo_estado.balas.erase(it);
    } else if ((it->get_pos_x() <= it->get_pos_x_final() && it->get_direccion() == DIRECCION_IZQUIERDA)) {
        // std::cout << "se elimina la bala que va a la izquierda" << std::endl;
        it = ultimo_estado.balas.erase(it);
    } else if (it->get_pos_y() <= it->get_pos_y_final() && it->get_direccion() == DIRECCION_ARRIBA) {
        // std::cout << "se elimina la bala que va arriba" << std::endl;
        it = ultimo_estado.balas.erase(it);
    } else {
        ++it;
    }
}

void GameLoop::eliminar_balas_si_colisionan(std::__cxx11::list<Bala>::iterator& it){
    for (Tile& tile: colisiones) {
        if (it->colisiona_con_tile(tile.get_hitbox()) != Nada) {
            it = ultimo_estado.balas.erase(it);
            break;
        }
    }
}

void GameLoop::avanzar_balas(){
    for (auto it = ultimo_estado.balas.begin(); it != ultimo_estado.balas.end(); ) {
        eliminar_balas_si_colisionan(it);
        avanzar_balas_direccion_izquierda(it);
        avanzar_balas_direccion_derecha(it);
        avanzar_balas_direccion_arriba(it);
        eliminar_balas_fuera_de_alcance(it);
    }
}

void GameLoop::continuar_saltando_patos() {
    for (Pato& pato: ultimo_estado.patos) {
        if (pato.estado.get_estado_salto() == SALTAR) {
            //std::cout << "entre al if de saltar y el contador es de " << static_cast<int>(pato.contador_salto) << std::endl;
            pato.saltar();
        }
    }
}

void GameLoop::frenar_saltos_patos_si_colisionan(){
    for (Pato& pato: ultimo_estado.patos) {
        for (Tile& tile: colisiones) {
            if (pato.colisiona_con_tile(tile.get_hitbox()) == Techo) {
                pato.estado.set_dejar_de_saltar();
                pato.contador_salto = 0;
                break;
            }
        }
    }
}

void GameLoop::aplicar_gravedad() {
    for (Pato& pato : ultimo_estado.patos) {
        bool colision_detectada = false;

        for (Tile& tile : colisiones) {
            if (pato.colisiona_con_tile(tile.get_hitbox()) == Piso) {
                pato.estado.set_dejar_de_caer();
                colision_detectada = true;
                break;
            }
        }

        if (!colision_detectada && pato.estado.get_estado_salto() != SALTAR && pato.estado.get_estado_salto() != ALETEAR) {
            pato.estado.set_caer();
        }

        if (pato.estado.get_estado_salto() == CAER) {
            for (int i = 0; i < pato.velocidad_caida; ++i) {
                colision_detectada = false;
                //std::cout << i << std::endl;
                pato.caer();
                actualizar_hitbox_entidades();
                for (Tile& tile : colisiones) {
                    //std::cout << "colisionando con tile" << std::endl;
                    if (pato.colisiona_con_tile(tile.get_hitbox()) == Piso) {
                        //std::cout << "ajustar tile" << std::endl;
                        pato.estado.set_dejar_de_caer();
                        pato.ajustar_sobre_tile(tile.get_hitbox());
                        colision_detectada = true;
                        break;
                    }
                }
                if (colision_detectada) {
                    break;
                }
            }
        }
    }
}

void GameLoop::aplicar_logica(){
    aplicar_estados();
    frenar_saltos_patos_si_colisionan();
    continuar_saltando_patos();
    avanzar_balas();
    aplicar_gravedad();
}

void GameLoop::drop_and_rest(float& tiempo_ultimo_frame){
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

void GameLoop::calcular_colisiones_tiles(Mapa mapa){
    std::map<std::string,std::vector<SDL_Point>> tiles = mapa.getTiles();
    for (auto& key : tiles) {
        for(SDL_Point p : tiles.at(key.first)){
            SDL2pp::Rect hitbox(p.x, p.y, ANCHO_TILE, ALTO_TILE);
            Tile tile(p.x, p.y, hitbox);
            colisiones.push_back(tile);
        }
    }
}

void GameLoop::calcular_colisiones_balas(){
    for(Pato& pato : ultimo_estado.patos){
        for (auto it = ultimo_estado.balas.begin(); it != ultimo_estado.balas.end();) {
            if(pato.colisiona_con_bala(*it) == Balas){
                it = ultimo_estado.balas.erase(it);
                pato.recibir_danio();
            }else {
                it++;
            }
        }
    }
}

void GameLoop::actualizar_hitbox_entidades(){
    for (Pato& pato: ultimo_estado.patos) {
        pato.calcular_hitbox();
    }
    for (Bala& bala: ultimo_estado.balas) {
        bala.calcular_hitbox();
    }
    for (Arma& arma : ultimo_estado.armas){
        arma.calcular_hitbox();
    }
}

void GameLoop::eliminar_patos_muertos(){
    for (auto it=ultimo_estado.patos.begin(); it!=ultimo_estado.patos.end();){
        if(!it->esta_vivo()){
            it = ultimo_estado.patos.erase(it);
        }else{
            it++;
        }
    }
}

void GameLoop::inicializar_patos(){
    int pos_x = 0;
    int pos_y = 0;
    std::vector<uint16_t> id_jugadores = clientes.obtener_ids();
    int contador = 0;
    std::map<std::string, std::vector<SDL_Point>> spawns = ultimo_estado.mapa.getSpawns();
    std::vector<SDL_Point> posicion = spawns.at("default");
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
            ultimo_estado.patos.emplace_back(pato);
            contador++;
        } else {
            return;
        }
    }
}

Arma GameLoop::elegir_arma_aleatoria(SDL_Point posicion_caja){
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> distrib(0, armas_posibles.size() - 1);
    int indice_aleatorio = distrib(gen);
    ArmaConfig elemento_aleatorio = armas_posibles[indice_aleatorio];
    Arma arma = mapear_armas(elemento_aleatorio, posicion_caja);
    return arma;
}

void GameLoop::inicializar_cajas(){
    for (const auto& cajas : ultimo_estado.mapa.getCajas()) {
        for (SDL_Point posicion_caja : cajas.second) {
            Arma arma = elegir_arma_aleatoria(posicion_caja);
            arma.set_se_agarro(true);
            Caja caja(ultimo_estado.cajas.size() + 1, posicion_caja.x, posicion_caja.y, arma);
            ultimo_estado.armas.push_back(arma);
            ultimo_estado.cajas.push_back(caja);
        }
    }
}

Arma GameLoop::mapear_armas(ArmaConfig armamento, SDL_Point posicion_arma){
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

void GameLoop::inicializar_armas(){
    for (const auto& armas : ultimo_estado.mapa.getEquipamiento()) {
        for (SDL_Point posicion_arma : armas.second) {
            ArmaConfig armamento = armamento_config[armas.first];
            if(armamento.nombre == "armadura"){
                Proteccion proteccion(ultimo_estado.armaduras.size()+1, posicion_arma.x, posicion_arma.y, ARMADURA_ENUM, false);
                ultimo_estado.armaduras.push_back(proteccion);
                continue;
            }else if(armamento.nombre == "casco"){
                Proteccion proteccion(ultimo_estado.armaduras.size()+1, posicion_arma.x, posicion_arma.y, CASCO_ENUM, false);
                ultimo_estado.armaduras.push_back(proteccion);
                continue;
            }
            Arma arma = mapear_armas(armamento, posicion_arma);
            ultimo_estado.armas.push_back(arma);
        }
    }
}


void GameLoop::leer_configuracion(const std::string& archivo_yaml){
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

void GameLoop::inicializar_juego(){
    leer_configuracion(RUTA_CONFIGURACION);
    inicializar_patos();
    inicializar_cajas();
    inicializar_armas();
}


void GameLoop::run() {
    float tiempo_ultimo_frame = SDL_GetTicks();

    LectorJson lector_mapa = LectorJson();
    Mapa mapa = lector_mapa.procesar_mapa(mapa_a_jugar);
    ultimo_estado.mapa = mapa;
    ultimo_estado.id_partida = id_partida;
    inicializar_juego();
    calcular_colisiones_tiles(mapa);

    tiempo_ultimo_frame = SDL_GetTicks();
        //eliminar_clientes_cerrados();
        // ultimo_estado.mapa = Mapa();
        while (!partida_terminada() && !(*esta_cerrado)) {
            EstadoJuego estado_anterior = ultimo_estado;
            std::vector<EventoServer> eventos = clientes.recibir_mensajes_clientes();
            for(EventoServer evento : eventos){
                procesar_evento(evento, ultimo_estado);
                for (auto it = mapa_jugadores->begin(); it != mapa_jugadores->end(); ++it) {
                    Queue<EstadoJuego>* queue = it->second;
                    queue->push(ultimo_estado);
                }
            }
            eliminar_patos_muertos();
            actualizar_hitbox_entidades();
            aplicar_logica();
            calcular_colisiones_balas();
            ultimo_estado.informacion_enviada = ENVIAR_ESTADO_JUEGO;
            for (auto it = mapa_jugadores->begin(); it != mapa_jugadores->end(); ++it) {
                Queue<EstadoJuego>* queue = it->second;
                queue->push(ultimo_estado);
            }
            drop_and_rest(tiempo_ultimo_frame);
        }
    //cerrar_gameloop();
    for (Puntaje& puntaje : puntaje_jugadores){
        if (puntaje.tengo_id(ultimo_estado.patos.front().get_id())){
            puntaje.gana_una_ronda();
        }
    }
}


bool GameLoop::partida_terminada(){
    if (ultimo_estado.patos.size() > 1){
        return false;
    }
    return true;
}
