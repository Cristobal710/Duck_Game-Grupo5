#include "server_recibir.h"


ServerRecibir::ServerRecibir(Socket& skt, Queue<EventoServer>& cola_eventos):
        skt(skt), cola_eventos(cola_eventos) {}

void ServerRecibir::run() {
    ServerProtocolo protocolo(skt);
    while (_keep_running) {
        try {
            EventoServer evento = protocolo.recibir_evento();
            cola_eventos.push(evento);
        } catch (ClosedQueue& e) {
            break;
        } catch (...) {
            break;
        }
    }
}
