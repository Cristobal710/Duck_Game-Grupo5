#include "server_client.h"

ServerClient::ServerClient(uint16_t id, Socket skt, Queue<EstadoJuego>& recibidos, Queue<EventoServer>& enviados):
        id(id),
        conexion_socket(std::move(skt)),
        esta_cerrado(false),
        estados_juego(recibidos),
        eventos(enviados), dos_jugadores(false), enviar(conexion_socket, &estados_juego, esta_cerrado) {}

void ServerClient::cerrar(ServerEnviar& enviar) {
    esta_cerrado = true;
    _is_alive = false;

    try {
        conexion_socket.shutdown(2);
    } catch (...) {}
    enviar.cerrar_queue();
    enviar.join();
}

void ServerClient::run() {

    enviar.start();

    ServerProtocolo protocolo(conexion_socket);

    while (_keep_running) {
        try {
            EventoServer evento = protocolo.recibir_evento();
            eventos.push(evento);

        } catch (ClosedQueue& e) {
            break;
        } catch (...) {
            break;
        }
    }

    cerrar(enviar);
}

uint16_t& ServerClient::get_id() { return id; }

void ServerClient::juegan_2_personas() {
    dos_jugadores = true;
}

bool ServerClient::juegan_dos() { return dos_jugadores; }

Queue<EventoServer>& ServerClient::get_queue() {
    return eventos;
}

void ServerClient::enviar_estado(EstadoJuego& estado) {
    enviar.enviar_estado(estado);
}

void ServerClient::cambiar_queue(Queue<EstadoJuego>* nueva_queue) {
    enviar.cambiar_queue(nueva_queue);
}
