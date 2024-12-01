#include "queue_protegida.h"


QueueProtegida::QueueProtegida(Queue<EstadoJuego>& recibidos):
recibidos(recibidos) {}

void QueueProtegida::enviar_mensaje(EstadoJuego& ultimo_estado) {
    std::lock_guard<std::mutex> lock(mutex);
    recibidos.push(ultimo_estado);
}

Queue<EstadoJuego>& QueueProtegida::conseguir_cola() {
    return recibidos;
}
