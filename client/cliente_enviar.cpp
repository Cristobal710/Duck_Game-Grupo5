#include "cliente_enviar.h"

ClientEnviar::ClientEnviar(Socket& socket, Queue<ComandoGrafica>& cola_eventos): protocolo(socket), eventos(cola_eventos) {}

void ClientEnviar::enviar_comando() {
    ComandoGrafica comando_grafica = eventos.pop();
    std::cout << comando_grafica.tecla << std::endl;
    protocolo.enviar_comando(comando_grafica);
}

void ClientEnviar::run() {
    while (_keep_running) {
        try {
            enviar_comando();
        } catch (ClosedQueue& e) {
            break;
        } catch (...) {
            break;
        }
    }
}
