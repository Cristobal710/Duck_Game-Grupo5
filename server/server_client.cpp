#include "server_client.h"

ServerClient::ServerClient(uint16_t id, Socket skt, Queue<EstadoJuego>& recibidos, Queue<EventoServer>& enviados):
        id(id),
        conexion_socket(std::move(skt)),
        esta_cerrado(false),
        estados_juego(recibidos),
        eventos(enviados) {}

void ServerClient::cerrar(ServerEnviar& enviar) {
    esta_cerrado = true;
    _is_alive = false;

    try {
        conexion_socket.shutdown(2);
    } catch (...) {}

    enviar.join();
}

void ServerClient::run() {

    ServerEnviar enviar(conexion_socket, estados_juego);
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
