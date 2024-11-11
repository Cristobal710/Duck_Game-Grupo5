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
        case TOMAR_ARMA:
            // llamar a un metodo que recorra el array de armas y devuelva la cercana al pato
            // pato.tomar_arma();
            break;
        default:
            // hacer metodo que ponga quieto al pato
            pato.estado.set_dejar_de_moverse();
            pato.levantarse_del_piso();
            break;

    }
}

void GameLoop::enviar_estado_juego_si_cambio(Pato& pato, EstadoJuego& estado_anterior) {
    if (pato.estado.get_estado_agachado() != estado_anterior.patos.front().estado.get_estado_agachado() || pato.estado.get_estado_movimiento() != estado_anterior.patos.front().estado.get_estado_movimiento()) {
        std::cout << "cambio" << std::endl;
        cola_estados_juego.push(ultimo_estado);
    }
}

void GameLoop::terminar_acciones_patos() {
    for (Pato& pato: ultimo_estado.patos) {
        pato.estado.set_dejar_de_moverse();
        pato.estado.set_dejar_de_agacharse();
        pato.levantarse_del_piso();
        pato.dejar_de_apuntar_arriba();
        // dejar de disparar
    }
}

void GameLoop::drop_and_rest(float tiempo_ultimo_frame){
    Uint32 tiempo_actual = SDL_GetTicks();
    int32_t descansar = RATE - (tiempo_actual - tiempo_ultimo_frame);

    if (descansar < 0){ //entonces nos atrasamos, tenemos que esperar a la siguiente iteracion, drop & rest.
        int32_t tiempo_atrasado = -descansar;
        descansar = RATE - (tiempo_atrasado % RATE);
        int32_t tiempo_perdido = tiempo_atrasado + descansar;

        tiempo_ultimo_frame += tiempo_perdido;
    }

    SDL_Delay(descansar);
    tiempo_ultimo_frame += RATE;
}

 
void GameLoop::run() {
    Pato pato(3, 0, 0, 0);
    ultimo_estado.patos.emplace_back(pato);
    
    
    //lector de un mapa desde un archivo json guardado en la carpeta de mapas
    LectorJson lector_mapa = LectorJson();

    Mapa mapa = lector_mapa.procesar_mapa("../resources/maps/mapa1");
    //aca esta el mapa, las colisiones estan guardadas en la clase (tiles).
    //hay que enviar toda esta informacion a cada cliente una vez antes de empezar la partida
    //para que el cliente grafico puede mostrar correctamente el mapa, hacer que de el lado del
    //cliente se reciba este objeto nuevamente, es decir, serializarlo en un objeto mapa igual al que 
    //hay aca. Supongo que hay que mover la definicion del mapa a common y no solo a servidor.
    //una vez que recibamos del socket este objeto mapa podemos mostrarlo en el juego a traves de la interfaz.

    std::cout << mapa.getFondo() << std::endl;
    std::map<std::string, std::vector<SDL_Point>> tiles = mapa.getTiles();
    std::vector<SDL_Point> posiciones_tiles = tiles.at(("../resources/TileSets/greyBlock.png"));
    for (SDL_Point punto : posiciones_tiles){
        std::cout << "x: " << punto.x << " y: " << punto.y  << std::endl;
    }
    float tiempo_ultimo_frame = SDL_GetTicks();

    while (!(*esta_cerrado)) {
        //eliminar_clientes_cerrados();

        while (true) {
            EstadoJuego estado_anterior = ultimo_estado;
            std::vector<EventoServer> eventos = clientes.recibir_mensajes_clientes();
            
           if (eventos.empty()) {
                terminar_acciones_patos();
            }
            for(EventoServer evento : eventos){
                procesar_evento(evento, ultimo_estado);
                cola_estados_juego.push(ultimo_estado);
            }
            for (Pato& pato: ultimo_estado.patos) {
                if (pato.estado.get_estado_salto() == SALTAR_ALETEAR) {
                    pato.saltar();
                    // cola_estados_juego.push(ultimo_estado);
                }
            }
            // aplicar logica del juego, balas, gravedad, etc
            // pushear
            enviar_estado_juego_si_cambio(pato, estado_anterior);
            drop_and_rest(tiempo_ultimo_frame);
        }
    }

    //cerrar_gameloop();
}


    //cerrar_gameloop();

