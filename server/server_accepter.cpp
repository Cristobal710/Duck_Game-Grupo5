#include "server_accepter.h"
#include "modo_juego.h"

Accepter::Accepter(Socket& socket, bool* conexion):
        socket_aceptador(socket), esta_cerrado(conexion), recibidos(), ultimo_id(1) {}

void Accepter::run() {
    
    std::list<ModoJuego*> partidas_distintas;

    while (!(*esta_cerrado)) {
        try {
            auto skt_nuevo_cliente = socket_aceptador.accept();
            auto* enviados = new Queue<EventoServer>();
            auto* cliente = new ServerClient(ultimo_id, std::move(skt_nuevo_cliente), recibidos, *enviados);
            ultimo_id++;
            
            auto* modo_juego = new ModoJuego(*cliente, *enviados, recibidos, partidas_distintas.size() + 1); 
            partidas_distintas.emplace_back(modo_juego);
            modo_juego->start();

            
            cliente->start();
        } catch (...) {
            // gameloop.join();
            break;
        }
    }
}
