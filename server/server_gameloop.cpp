#include "server_gameloop.h"

#include "../common/common_constantes.h"
#include <SDL2/SDL.h>

#define RATE 1000 / 30
#define BAZOOKA "Bazooka"
#define CHAINSAW "Chainsaw"
#define DEATH_RAY "Death ray"
#define SHOTGUN "Shotgun"

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
            pato.moverse_izquierda();
            break;
        case MOVER_DERECHA:
            pato.moverse_derecha();
            break;
        case TIRAR_PISO:
            pato.tirarse_al_piso();
            break;
        case APUNTAR_ARRIBA:
            pato.apuntar_arriba();
            break;
        case SALTAR_ALETEAR:
            pato.saltar();
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
            pato.estado.set_dejar_de_saltar();
            break;
        case DEJAR_TIRAR_PISO:
            pato.levantarse_del_piso();
            break;
        case TOMAR_ARMA:
            // llamar a un metodo que recorra el array de armas y devuelva la cercana al pato
            // pato.tomar_arma();
            break;
        case DISPARAR:
            pato.disparar();
            if (pato.tiene_arma()) {    
                if (!pato.esta_apuntando_arriba()){
                    Bala bala(ultimo_estado.balas.size() + 1, pato.get_pos_x(), pato.get_pos_y(), pato.get_direccion(), pato.get_pos_x() + pato.get_arma()->get_alcance(), pato.get_pos_y());
                    ultimo_estado.balas.push_back(bala);
                } else {
                    Bala bala(ultimo_estado.balas.size() + 1, pato.get_pos_x(), pato.get_pos_y(), pato.get_direccion(), pato.get_pos_x(), pato.get_pos_y() - pato.get_arma()->get_alcance());
                    ultimo_estado.balas.push_back(bala);
                }
            }
            break;
        default:
            // hacer metodo que ponga quieto al pato
            break;

    }
}

void GameLoop::enviar_estado_juego_si_cambio(Pato& pato, EstadoJuego& estado_anterior) {
    if (pato.estado.get_estado_agachado() != estado_anterior.patos.front().estado.get_estado_agachado() || pato.estado.get_estado_movimiento() != estado_anterior.patos.front().estado.get_estado_movimiento() || pato.estado.get_estado_salto() != estado_anterior.patos.front().estado.get_estado_salto() || pato.estado.get_estado_disparo() != estado_anterior.patos.front().estado.get_estado_disparo()) {
        cola_estados_juego.push(ultimo_estado);
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

void GameLoop::terminar_acciones_patos() {
    for (Pato& pato: ultimo_estado.patos) {
        pato.estado.set_dejar_de_moverse();
        pato.estado.set_dejar_de_agacharse();
        pato.estado.set_dejar_de_disparar();
        pato.levantarse_del_piso();
        pato.dejar_de_apuntar_arriba();
    }
}

void GameLoop::aplicar_logica(){
    for (Pato& pato: ultimo_estado.patos) {
        if (pato.estado.get_estado_salto() == SALTAR_ALETEAR) {
            pato.saltar();
        }
    }
    for (auto it = ultimo_estado.balas.begin(); it != ultimo_estado.balas.end(); ) {
        if (it->get_direccion() == DIRECCION_IZQUIERDA) {
            it->set_pos_x(it->get_pos_x() - 3);
        }
        if (it->get_direccion() == DIRECCION_DERECHA) {
            it->set_pos_x(it->get_pos_x() + 3);
        }
        if (it->get_direccion() == DIRECCION_ARRIBA) {
            it->set_pos_y(it->get_pos_y() - 3);
        }

        if (it->get_pos_x() == it->get_pos_x_final() && it->get_pos_y() == it->get_pos_y_final()) {
            it = ultimo_estado.balas.erase(it);
        } else {
            ++it;
        }
    }
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

 
void GameLoop::run() {
    Pato pato(3, 0, 300, 0);
    Arma* arma = new Arma(1, 0, 255, 15, 30);
    pato.tomar_arma(arma);
    ultimo_estado.patos.emplace_back(pato);
    LectorJson lector_mapa = LectorJson();
    Mapa mapa = lector_mapa.procesar_mapa("../resources/maps/mapa1");
    ultimo_estado.mapa = mapa;
    cola_estados_juego.push(ultimo_estado);

    float tiempo_ultimo_frame = SDL_GetTicks();

    while (!(*esta_cerrado)) {
        //eliminar_clientes_cerrados();
        // ultimo_estado.mapa = Mapa();
        while (true) {
            EstadoJuego estado_anterior = ultimo_estado;
            std::vector<EventoServer> eventos = clientes.recibir_mensajes_clientes();
            
            if (eventos.empty()) {
                //terminar_acciones_patos();
            }
            for(EventoServer evento : eventos){
                procesar_evento(evento, ultimo_estado);
                cola_estados_juego.push(ultimo_estado);
            }
            // aplicar logica del juego, balas, gravedad, etc
            // pushear
            aplicar_logica();
            enviar_estado_juego_si_cambio(pato, estado_anterior);
            drop_and_rest(tiempo_ultimo_frame);
        }
    }
    //cerrar_gameloop();
}
