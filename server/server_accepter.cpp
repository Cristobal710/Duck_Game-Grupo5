#include "server_accepter.h"
#include "modo_juego.h"

Accepter::Accepter(Socket& socket, bool* conexion):
        socket_aceptador(socket), esta_cerrado(conexion), ultimo_id(1) {}

void Accepter::run() {

    std::list<ModoJuego*> partidas_distintas;
    std::list<Queue<EstadoJuego>*> queues_estado_juego;
    std::list<Queue<EventoServer>*>queues_estado_server;

    while (!(*esta_cerrado)) {
        std::atomic_bool cerrar_servidor = false;
        try {
            auto skt_nuevo_cliente = socket_aceptador.accept();
            auto* recibido = new Queue<EstadoJuego>() ;
            queues_estado_juego.emplace_back(recibido);
            auto* enviados = new Queue<EventoServer>();
            queues_estado_server.emplace_back(enviados);
            auto* cliente = new ServerClient(ultimo_id, std::move(skt_nuevo_cliente), *recibido, *enviados);
            ultimo_id += 2;
            
            auto* modo_juego = new ModoJuego(*cliente, *enviados, *recibido, partidas_distintas.size() + 1,
            partidas_distintas, cerrar_servidor); 
            partidas_distintas.emplace_back(modo_juego);
            
            modo_juego->start();
            cliente->start();
        } catch (...) {
            cerrar_servidor = true;
            for (ModoJuego* partida : partidas_distintas){
                partida->join();
                delete partida;
            }
            for (Queue<EstadoJuego>* queue : queues_estado_juego){
                delete queue;
            }
            for (Queue<EventoServer>* queue : queues_estado_server){
                delete queue;
            }
            break;
        }
    }
}
