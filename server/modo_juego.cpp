#include "modo_juego.h"
#include "server_gameloop.h"
#define RATE 1000 / 30

ModoJuego::ModoJuego(ServerClient& cliente, Queue<EventoServer>& cola_cliente, Queue<EstadoJuego>& recibidos):
cliente(cliente), queue_cliente(cola_cliente), broadcast(recibidos), ultimo_estado() 
{}

void ModoJuego::run() {
    bool cerrado = false;
    float tiempo_ultimo_frame = SDL_GetTicks();
    bool iniciar_partida = false; 
    bool partida_nueva = false;
    ultimo_estado.id_ultimo_jugador = cliente.get_id();
    broadcast.push(ultimo_estado);
    while (!iniciar_partida){
        std::vector<EventoServer> eventos;

        EventoServer evento;
        while(queue_cliente.try_pop(evento)){
            eventos.push_back(evento);
        }
        for(EventoServer evento : eventos){
            procesar_evento_lobby(evento, iniciar_partida, partida_nueva);
        }
        broadcast.push(ultimo_estado);
        drop_and_rest(tiempo_ultimo_frame);
    }

    if (partida_nueva){
        auto* gameloop = new GameLoop(broadcast, &cerrado);
        gameloop->start();
        gameloop->agregar_cliente(cliente, queue_cliente);
    }
    while (not cerrado){
        drop_and_rest(tiempo_ultimo_frame);
    }
}


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


void ModoJuego::procesar_evento_lobby(EventoServer& evento, bool& iniciar_partida, bool& partida_nueva) {
    PedidoJugador pedido_cliente = evento.pedido;
    ejecutar_accion_lobby(pedido_cliente, evento.jugador_id, iniciar_partida, partida_nueva);
}

void ModoJuego::ejecutar_accion_lobby(PedidoJugador& pedido, uint16_t id_jugador, bool& iniciar_partida, bool& partida_nueva) {
    if (pedido.crear_partida == 0x01){
        ultimo_estado.lobby_data.agregar_partida(id_jugador);
        partida_nueva = true;
        //crear una partida
        return;
    }
    if (pedido.unirse_a_partida == 0x01){
        ultimo_estado.lobby_data.unirse_a_partida(pedido.id_partida_a_unirse, id_jugador);
        //unirse a partida con id que esta en el pedido 
        return;
    }
    if (pedido.un_jugador == 0x01){
        //crear un pato?
        std::cout << "hay un jugador" << std::endl;
        return;
    }
    if (pedido.dos_jugadores == 0x01){
        //crear dos patos?
        //mandar_id_cliente(cliente.get_id());
        // mandar_id_cliente(cliente.get_id() + 1);
        ultimo_estado.id_ultimo_jugador = cliente.get_id() + 1;
        std::cout << "hay dos jugadores" << std::endl;
        return;
    }
    if(pedido.empezar == 0x01){
        ultimo_estado.lobby_data.empezar_partida(0);
        iniciar_partida = true;
        return;
    }
}


