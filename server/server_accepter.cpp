#include "server_accepter.h"
#include "modo_juego.h"

Accepter::Accepter(Socket& socket, bool* conexion):
        socket_aceptador(socket), esta_cerrado(conexion), recibidos(), ultimo_id(1) {}

void Accepter::run() {
    
    std::list<ModoJuego*> partidas_distintas;

    while (!(*esta_cerrado)) {
        try {
            auto* recibido2 = new Queue<EstadoJuego>() ;
            auto skt_nuevo_cliente = socket_aceptador.accept();
            auto* enviados = new Queue<EventoServer>();
            auto* cliente = new ServerClient(ultimo_id, std::move(skt_nuevo_cliente), *recibido2, *enviados);
            ultimo_id += 2;
            
            auto* modo_juego = new ModoJuego(*cliente, *enviados, *recibido2, partidas_distintas.size() + 1, partidas_distintas); 
            partidas_distintas.emplace_back(modo_juego);
            modo_juego->start();

            
            cliente->start();
        } catch (...) {
            // gameloop.join();
            break;
        }
    }
}
