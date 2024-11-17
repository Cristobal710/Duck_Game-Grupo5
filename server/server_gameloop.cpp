#include "server_gameloop.h"

#include "../common/common_constantes.h"
#include <SDL2/SDL.h>

#define RATE 1000 / 30
#define BAZOOKA "Bazooka"
#define CHAINSAW "Chainsaw"
#define DEATH_RAY "Death ray"
#define SHOTGUN "Shotgun"

#define ALTO_TILE 16
#define ANCHO_TILE 16

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
    switch (accion) {
        case MOVER_IZQUIERDA:
            pato.estado.set_moviendo_izquierda();
            break;
        case MOVER_DERECHA:
            pato.estado.set_moviendo_derecha();
            break;
        case TIRAR_PISO:
            pato.estado.set_agacharse();
            break;
        case APUNTAR_ARRIBA:
            pato.apuntar_arriba();
            break;
        case SALTAR_ALETEAR:
            // std::cout << "entre al case de saltar" << std::endl;
            if (pato.estado.get_estado_salto() == BYTE_NULO) {
                pato.saltar();
            }
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
        case DEJAR_SALTAR_ALETEAR:
            if (pato.contador_salto == 5) {
                pato.estado.set_dejar_de_saltar();
                pato.estado.set_caer();
                pato.contador_salto = 0;
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
            pato.disparar();
            crear_bala(pato);
            break;
        default:
            break;

    }
}

void GameLoop::aplicar_estados(){
    for(Pato& pato : ultimo_estado.patos){
        if(pato.estado.get_estado_movimiento() == MOVER_DERECHA){
            pato.moverse_derecha();
        }else if(pato.estado.get_estado_movimiento() == MOVER_IZQUIERDA){
            pato.moverse_izquierda();
        }
        if(pato.estado.get_estado_agachado() == TIRAR_PISO ){
            pato.tirarse_al_piso();
        }
       
    }
}









void GameLoop::crear_bala(Pato& pato){
    if (pato.tiene_arma()) {    
        if (!pato.esta_apuntando_arriba()){
            if (pato.get_direccion() == DIRECCION_DERECHA) {
                Bala bala(ultimo_estado.balas.size() + 1, pato.get_pos_x(), pato.get_pos_y(), pato.get_pos_x() + pato.get_arma()->get_alcance(), pato.get_pos_y(), pato.get_direccion(), pato.get_id());
                ultimo_estado.balas.push_back(bala);
            } else {
                Bala bala(ultimo_estado.balas.size() + 1, pato.get_pos_x(), pato.get_pos_y(), pato.get_pos_x() - pato.get_arma()->get_alcance(), pato.get_pos_y(), pato.get_direccion(), pato.get_id());
                ultimo_estado.balas.push_back(bala);
            }
        } else {
            Bala bala(ultimo_estado.balas.size() + 1, pato.get_pos_x(), pato.get_pos_y(), pato.get_pos_x(), pato.get_pos_y() - pato.get_arma()->get_alcance(), pato.get_direccion(), pato.get_id());
            ultimo_estado.balas.push_back(bala);
        }
    }
}

void GameLoop::enviar_estado_juego_si_cambio(Pato& pato, EstadoJuego& estado_anterior) {
    pato = pato;
    for(Pato& pato :ultimo_estado.patos){
        if (pato.estado.get_estado_agachado() != estado_anterior.patos.front().estado.get_estado_agachado() || pato.estado.get_estado_movimiento() != estado_anterior.patos.front().estado.get_estado_movimiento() || pato.estado.get_estado_salto() != estado_anterior.patos.front().estado.get_estado_salto() || pato.estado.get_estado_disparo() != estado_anterior.patos.front().estado.get_estado_disparo()) {
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
        // std::cout << "pos x bala:" << static_cast<int>(it->get_pos_x()) << std::endl;
    }
}

void GameLoop::avanzar_balas_direccion_derecha(std::__cxx11::list<Bala>::iterator& it){
    if (it->get_direccion() == DIRECCION_DERECHA) {
        it->set_pos_x(it->get_pos_x() + 5);
        // std::cout << "pos x bala:" << static_cast<int>(it->get_pos_x()) << std::endl;
    }
}

void GameLoop::avanzar_balas_direccion_arriba(std::__cxx11::list<Bala>::iterator& it){
    if (it->get_direccion() == DIRECCION_ARRIBA) {
        it->set_pos_y(it->get_pos_y() - 5);
        // std::cout << "pos y bala:" << static_cast<int>(it->get_pos_y()) << std::endl;
    }
}

void GameLoop::eliminar_balas_fuera_de_alcance(std::__cxx11::list<Bala>::iterator& it){
    if (it->get_pos_x() >= it->get_pos_x_final() && it->get_pos_y() >= it->get_pos_y_final() && it->get_direccion() == DIRECCION_DERECHA) {
        // std::cout << "se elimina la bala que va a la derecha" << std::endl;
        it = ultimo_estado.balas.erase(it);
    } else if (it->get_pos_x() <= it->get_pos_x_final() && it->get_pos_y() <= it->get_pos_y_final() && it->get_direccion() == DIRECCION_IZQUIERDA) {
        // std::cout << "se elimina la bala que va a la izquierda" << std::endl;
        it = ultimo_estado.balas.erase(it);
    } else if (it->get_pos_y() <= it->get_pos_y_final() && it->get_direccion() == DIRECCION_ARRIBA) {
        // std::cout << "se elimina la bala que va arriba" << std::endl;
        it = ultimo_estado.balas.erase(it);
    } else {
        ++it;
    }
}

void GameLoop::avanzar_balas(){
    for (auto it = ultimo_estado.balas.begin(); it != ultimo_estado.balas.end(); ) {
        avanzar_balas_direccion_izquierda(it);
        avanzar_balas_direccion_derecha(it);    
        avanzar_balas_direccion_arriba(it);
        eliminar_balas_fuera_de_alcance(it);
    }
}

void GameLoop::continuar_saltando_patos() {
    for (Pato& pato: ultimo_estado.patos) {
        if (pato.estado.get_estado_salto() == SALTAR_ALETEAR) {
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
                // std::cout << "frene el salto" << std::endl;
                break;
            }
            // if (pato.colisiona_con_tile(tile.get_hitbox()) == Pared){
            //     pato.estado.set_dejar_de_moverse();
            //     std::cout<<"entre a frenar pato pared"<<std::endl;
            //     break;
            // }
        }
    }
}

void GameLoop::aplicar_gravedad(){
    for (Pato& pato: ultimo_estado.patos) {
        for (Tile& tile: colisiones) {
            if (pato.colisiona_con_tile(tile.get_hitbox()) == Piso) {
                    pato.estado.set_dejar_de_caer();
                break;
            } else {
                if (pato.estado.get_estado_salto() != SALTAR_ALETEAR) {
                    pato.estado.set_caer();
                }
            }
        }
        if (pato.estado.get_estado_salto() == CAER) {
            pato.caer();
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


void GameLoop::calcular_colisiones_balas(EstadoJuego estado_juego){
    for(Pato& pato : estado_juego.patos){
        for (auto it = ultimo_estado.balas.begin(); it != ultimo_estado.balas.end(); ) {
            if(pato.colisiona_con_bala(*it) == Balas && (it->get_id_origen() != pato.get_id())){

                std::cout<<"===BALA COLISIONA CON PATO==="<<std::endl;
                it = ultimo_estado.balas.erase(it);  
            }else{
                it++;
            }
            //if(pato.get_hitbox().colisiona_izquierda_con(bala.get_hitbox().get_hitbox_rect())){
            //    std::cout<<pato.get_pos_x()<<" ==== "<<pato.get_pos_y() <<std::endl;
//
            //    
            //}
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
}

void GameLoop::run() {
    int pos_x = 0;
    int pos_y = 0;
    LectorJson lector_mapa = LectorJson();
    Mapa mapa = lector_mapa.procesar_mapa("../resources/maps/mapa1");
    ultimo_estado.mapa = mapa;
    //cola_estados_juego.push(ultimo_estado);

    std::map<std::string, std::vector<SDL_Point>> spawns = ultimo_estado.mapa.getSpawns();
    for (const auto& id_posicion : spawns) {        
        std::string id_jugador = id_posicion.first;
        std::vector<SDL_Point> posicion = id_posicion.second;
        pos_x = posicion.front().x;
        pos_y = posicion.front().y;
    }
    Pato pato(3, pos_x, pos_y, 0);
    Arma* arma = new Arma(1, pos_x, pos_y, 15, 300);
    pato.tomar_arma(arma);
    ultimo_estado.patos.emplace_back(pato);
    // Pato pato_dos(4, pos_x +20, pos_y, 0);
    // std::cout<<static_cast<int>(pato_dos.get_id())<<std::endl;
    // Arma* arma_dos = new Arma(1, pos_x+20, pos_y, 15, 300);
    // pato_dos.tomar_arma(arma_dos);
    ultimo_estado.patos.emplace_back(pato_dos);
    cola_estados_juego.push(ultimo_estado);
    float tiempo_ultimo_frame = SDL_GetTicks();
    calcular_colisiones_tiles(mapa);

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
            actualizar_hitbox_entidades();
            aplicar_logica();
            calcular_colisiones_balas(ultimo_estado);
            enviar_estado_juego_si_cambio(pato, estado_anterior);
            drop_and_rest(tiempo_ultimo_frame);
        }
    }
    //cerrar_gameloop();
}