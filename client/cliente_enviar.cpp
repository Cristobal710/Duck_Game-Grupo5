#include "cliente_enviar.h"

ClientEnviar::ClientEnviar(Socket& socket): protocolo(socket), eventos() {}

void ClientEnviar::enviar_comando() {
    ComandoGrafica comando_grafica = eventos.pop();
    protocolo.enviar_comando(comando_grafica);
}

void ClientEnviar::run() {
    while (true) {
        try {
            enviar_comando();
        } catch (ClosedQueue& e) {
            break;
        } catch (...) {
            break;
        }
    }
}