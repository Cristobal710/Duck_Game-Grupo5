#include "server_gameloop.h"

#include "../common/common_constantes.h"
#include <SDL2/SDL.h>

#define RATE 1000 / 30
#define BAZOOKA "Bazooka"
#define CHAINSAW "Chainsaw"
#define DEATH_RAY "Death ray"
#define SHOTGUN "Shotgun"
#define DISTANCIA_ARMA 4

#define ALTO_TILE 32
#define ANCHO_TILE 24

GameLoop::GameLoop(Queue<EstadoJuego>& cola_estados_juego,
        bool* conexion):
        mapa_clientes(),
        clientes(mapa_clientes),
        cola_estados_juego(cola_estados_juego),
        esta_cerrado(conexion) {
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
            pato.saltar();
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
            if (pato.tiene_arma()) {
                pato.soltar_arma();
                break;
            }
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
            pato.saltar();
            // llamar a un metodo que recorra el array de armas y devuelva la cercana al pato
            // pato.tomar_arma();
            break;
        case DISPARAR:
            if (!pato.tiene_arma()) { 
                break;
            } 
            if (pato.estado.get_estado_agachado() == TIRAR_PISO) {
                pato.estado.set_dejar_de_agacharse();
            }
            pato.disparar();
            crear_bala(pato);
            break;
        default:
            break;

    }
}

void GameLoop::agarrar_recompensa(Pato& pato){
    for(Caja& caja : ultimo_estado.cajas){
        if(pato.colisiona_con_recompensa(caja.get_hitbox()) == Recompensas){
            if (!caja.get_esta_vacia()) {
                Arma* arma = caja.get_arma();
                pato.tomar_arma(arma);
                arma->set_se_agarro(true);
                std::cout << ultimo_estado.cajas.size() << std::endl;
                std::cout << ultimo_estado.cajas.size() << std::endl;
                caja.set_esta_vacia(true);
                return;          
            }
        }
    }
    for(Arma& arma : ultimo_estado.armas){
        if(pato.colisiona_con_recompensa(arma.get_hitbox()) == Recompensas){
            if(!arma.get_se_agarro()){
                arma.set_se_agarro(true);
                pato.tomar_arma(&arma);
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
            Bala bala(ultimo_estado.balas.size() + 1, pato.get_pos_x(), pato.get_pos_y() + DISTANCIA_ARMA, pato.get_pos_x() + pato.get_arma()->get_alcance(), pato.get_pos_y() + DISTANCIA_ARMA, pato.get_direccion(), pato.get_arma()->get_tipo_arma(), pato.get_id());
            ultimo_estado.balas.push_back(bala);
        } else {
            Bala bala(ultimo_estado.balas.size() + 1, pato.get_pos_x(), pato.get_pos_y() + DISTANCIA_ARMA, pato.get_pos_x() - pato.get_arma()->get_alcance(), pato.get_pos_y() + DISTANCIA_ARMA, pato.get_direccion(), pato.get_arma()->get_tipo_arma(), pato.get_id());
            ultimo_estado.balas.push_back(bala);
        }
    } else {
        Bala bala(ultimo_estado.balas.size() + 1, pato.get_pos_x(), pato.get_pos_y(), pato.get_pos_x(), pato.get_pos_y() - pato.get_arma()->get_alcance(), pato.get_direccion(), pato.get_arma()->get_tipo_arma(), pato.get_id());
        ultimo_estado.balas.push_back(bala);
    }
}

void GameLoop::enviar_estado_juego_si_cambio( EstadoJuego& estado_anterior) {
    for(Pato& pato :ultimo_estado.patos){
        if (pato.estado.get_estado_agachado() != estado_anterior.patos.front().estado.get_estado_agachado() || pato.estado.get_estado_movimiento() != estado_anterior.patos.front().estado.get_estado_movimiento() || pato.estado.get_estado_salto() != estado_anterior.patos.front().estado.get_estado_salto() || pato.estado.get_estado_disparo() != estado_anterior.patos.front().estado.get_estado_disparo() || pato.esta_apuntando_arriba() != estado_anterior.patos.front().esta_apuntando_arriba()) {
            cola_estados_juego.push(ultimo_estado);
        }
        if (pato.get_pos_x() != estado_anterior.patos.front().get_pos_x() || pato.get_pos_y() != estado_anterior.patos.front().get_pos_y()) {            
            cola_estados_juego.push(ultimo_estado);
        }
    }
    bool cambio = false;
    for (Bala& bala: ultimo_estado.balas) {
        if (bala.get_pos_x() != estado_anterior.balas.front().get_pos_x() || bala.get_pos_y() != estado_anterior.balas.front().get_pos_y()) {
            cambio = true;
        }
    }
    if (cambio) {
        cola_estados_juego.push(ultimo_estado);
    }
}

void GameLoop::avanzar_balas_direccion_izquierda(std::__cxx11::list<Bala>::iterator& it){
    if (it->get_direccion() == DIRECCION_IZQUIERDA) {
        it->set_pos_x(it->get_pos_x() - 5);
        //std::cout << "pos x bala avance:" << static_cast<int>(it->get_pos_x()) << std::endl;
    }
}

void GameLoop::avanzar_balas_direccion_derecha(std::__cxx11::list<Bala>::iterator& it){
    if (it->get_direccion() == DIRECCION_DERECHA) {
        it->set_pos_x(it->get_pos_x() + 5);
        //std::cout << "pos x bala avance :" << static_cast<int>(it->get_pos_x()) << std::endl;
    }
}

void GameLoop::avanzar_balas_direccion_arriba(std::__cxx11::list<Bala>::iterator& it){
    if (it->get_direccion() == DIRECCION_ARRIBA) {
        it->set_pos_y(it->get_pos_y() - 5);
        //std::cout << "pos y bala avance :" << static_cast<int>(it->get_pos_y()) << std::endl;
    }
}

void GameLoop::eliminar_balas_fuera_de_alcance(std::__cxx11::list<Bala>::iterator& it){
    if ((it->get_pos_x() >= it->get_pos_x_final() && it->get_direccion() == DIRECCION_DERECHA) || (it->get_pos_x() == 1280 && it->get_direccion() == DIRECCION_IZQUIERDA)) {
        //std::cout << "se elimina la bala que va a la derecha" << std::endl;
        it = ultimo_estado.balas.erase(it);
    } else if ((it->get_pos_x() <= it->get_pos_x_final() && it->get_direccion() == DIRECCION_IZQUIERDA) || (it->get_pos_x() == 0 && it->get_direccion() == DIRECCION_IZQUIERDA)) {
        //std::cout << "se elimina la bala que va a la izquierda" << std::endl;
        it = ultimo_estado.balas.erase(it);
    } else if (it->get_pos_y() <= it->get_pos_y_final() && it->get_direccion() == DIRECCION_ARRIBA) {
        //std::cout << "se elimina la bala que va arriba" << std::endl;
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
                        std::cout << "ajustar tile" << std::endl;
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

// void GameLoop::calcular_colisiones_cajas(){
//     for(Pato& pato : ultimo_estado.patos){
//         for(Caja& caja : ultimo_estado.cajas){
//             if(pato.colisiona_con_caja(caja.get_hitbox()) == Cajas){
//                 //std::cout<<"ESTOY COLISIONANDO CON UNA CAJARDA"<<std::endl;
//             }
//         }
//     }
    
// }

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
    int id = 3;
    std::map<std::string, std::vector<SDL_Point>> spawns = ultimo_estado.mapa.getSpawns();
    for (const auto& id_posicion : spawns) {        
        std::string id_jugador = id_posicion.first;
        std::vector<SDL_Point> posicion = id_posicion.second;
        for(SDL_Point coord : posicion){
            pos_x = coord.x;
            pos_y = coord.y;
            Pato pato(id, pos_x, pos_y, 0);
            id++;
            // Arma* arma = new Arma(1, pos_x, pos_y, 15, 200, PEW_PEW_LASER);
            // pato.tomar_arma(arma);
            
            // pato.tomar_armadura();
            // pato.equipar_armadura();
            // pato.tomar_casco();
            // pato.equipar_casco();
            ultimo_estado.patos.emplace_back(pato);
        }
    }

}

void GameLoop::inicializar_cajas(){
    for (const auto& cajas : ultimo_estado.mapa.getCajas()) {
        for (SDL_Point posicion_caja : cajas.second) {
            Arma arma(ultimo_estado.armas.size()+1, posicion_caja.x, posicion_caja.y, 30, 30, AK_47);
            arma.set_se_agarro(true);
            Caja caja(ultimo_estado.cajas.size() + 1, posicion_caja.x, posicion_caja.y, AK_47, &arma);
            ultimo_estado.armas.push_back(arma);
            ultimo_estado.cajas.push_back(caja);
        }
    }

}
void GameLoop::inicializar_armas(){
    for (const auto& armas : ultimo_estado.mapa.getEquipamiento()) {
        for (SDL_Point posicion_arma : armas.second) {
            Arma arma(ultimo_estado.armas.size() + 1, posicion_arma.x, posicion_arma.y, 15, 300, AK_47);
            ultimo_estado.armas.push_back(arma);
        }
    }
}

void GameLoop::inicializar_juego(){
    inicializar_patos();
    inicializar_cajas();
    inicializar_armas();
    cola_estados_juego.push(ultimo_estado);
}


void GameLoop::run() {
    LectorJson lector_mapa = LectorJson();
    Mapa mapa = lector_mapa.procesar_mapa("../resources/maps/mapa5");
    ultimo_estado.mapa = mapa;
    inicializar_juego();
    calcular_colisiones_tiles(mapa);

    float tiempo_ultimo_frame = SDL_GetTicks();
    while (!(*esta_cerrado)) {
        //eliminar_clientes_cerrados();
        // ultimo_estado.mapa = Mapa();
        while (true) {
            EstadoJuego estado_anterior = ultimo_estado;
            std::vector<EventoServer> eventos = clientes.recibir_mensajes_clientes();
            for(EventoServer evento : eventos){
                procesar_evento(evento, ultimo_estado);
                cola_estados_juego.push(ultimo_estado);
            }
            eliminar_patos_muertos();
            actualizar_hitbox_entidades();
            aplicar_logica();
            calcular_colisiones_balas();
            enviar_estado_juego_si_cambio(estado_anterior);
            drop_and_rest(tiempo_ultimo_frame);
        }
    }
    //cerrar_gameloop();
}
