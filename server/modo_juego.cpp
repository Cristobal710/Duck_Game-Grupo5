#include "modo_juego.h"
#include "server_gameloop.h"
#define LOBBY_REQUEST 0x01
#define RATE 1000 / 30

ModoJuego::ModoJuego(ServerClient& cliente, Queue<EventoServer>& cola_cliente, Queue<EstadoJuego>& recibidos, uint8_t id,
std::list<ModoJuego*>& partidas_distintas):
cliente(cliente), queue_cliente(cola_cliente), broadcast(recibidos), ultimo_estado(), id_partida(id),
partidas_distintas(partidas_distintas), partida_nueva(false) 
{}

void ModoJuego::run() {

    bool cerrado = false;
    float tiempo_ultimo_frame = SDL_GetTicks();
    bool iniciar_partida = false; 

    std::list<uint16_t> ids_tomados;
    for (uint16_t i = cliente.get_id(); i > 0; i--){
        ids_tomados.emplace_front(i);
    }

    ultimo_estado.ids_tomados = ids_tomados;
    ultimo_estado.id_partida = id_partida;

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
        broadcast.enviar_mensaje(ultimo_estado);
        drop_and_rest(tiempo_ultimo_frame);
    }

    if (partida_nueva){
        auto* gameloop = new GameLoop(broadcast.conseguir_cola(), &cerrado, id_partida);
        gameloop->start();
        gameloop->agregar_cliente(cliente, queue_cliente);
    }
    while (not cerrado){
        drop_and_rest(tiempo_ultimo_frame);
    }
}

bool ModoJuego::tiene_partida() { return partida_nueva; }

uint8_t ModoJuego::obtener_id_partida() { return id_partida; }


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
    std::cout << "tamanio de partidas --> " << partidas_distintas.size() << std::endl;
    if (pedido.crear_partida == LOBBY_REQUEST){
        partida_nueva = true;
        return;
        } 
    if (pedido.unirse_a_partida == LOBBY_REQUEST){
        //ultimo_estado.lobby_data.unirse_a_partida(pedido.id_partida_a_unirse, id_jugador);
        
        //unirse a partida con id que esta en el pedido 
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
