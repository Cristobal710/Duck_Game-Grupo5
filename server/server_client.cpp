#include "server_client.h"

ServerClient::ServerClient(Socket skt, Queue<EstadoJuego>& recibidos, Queue<EventoServer>& enviados):
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

    // ServerEnviar enviar(conexion_socket, enviados);
    // enviar.start();

    // ServerProtocolo protocolo(conexion_socket);

    // while (enviar.is_alive() && (!esta_cerrado)) {
    //     try {
    //         protocolo.recibir_comando();
    //     } catch (...) {
    //         break;
    //     }
    // }

    // cerrar(enviar);
    // cerrar(enviar);
}
