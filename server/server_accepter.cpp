#include "server_accepter.h"

Accepter::Accepter(Socket& socket, bool* conexion):
        socket_aceptador(socket), esta_cerrado(conexion), recibidos(), ultimo_id(1) {}

void Accepter::run() {

    GameLoop gameloop(recibidos, esta_cerrado);
    gameloop.start();
    while (!(*esta_cerrado)) {
        try {
            auto skt_nuevo_cliente = socket_aceptador.accept();
            auto* enviados = new Queue<EventoServer>();
            auto* cliente = new ServerClient(ultimo_id, std::move(skt_nuevo_cliente), recibidos, *enviados);
            gameloop.agregar_cliente(*cliente, *enviados);
            ultimo_id++;
            cliente->start();
        } catch (...) {
            // gameloop.join();
            break;
        }
    }
}
