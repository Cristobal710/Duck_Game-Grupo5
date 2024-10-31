#include "cliente_recibir.h"

ClienteRecibir::ClienteRecibir(Socket& socket, Queue<EstadoJuego>& cola_estados_juego):
        protocolo(socket), cola_estados_juego(cola_estados_juego) {}

void ClienteRecibir::run() {
    while (_keep_running) {
        try {
            EstadoJuego estado_del_juego = protocolo.recibir_estado_juego();
            cola_estados_juego.push(estado_del_juego);
        } catch (ClosedQueue& e) {
            break;
        } catch (...) {
            break;
        }
    }
}
