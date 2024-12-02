#include "queue_protegida.h"


QueueProtegida::QueueProtegida(Queue<EstadoJuego>& recibidos):
recibidos(recibidos) {}

void QueueProtegida::enviar_mensaje(EstadoJuego& ultimo_estado) {
    std::lock_guard<std::mutex> lock(mutex);
    //try{
    recibidos.push(ultimo_estado);
    // } catch (ClosedQueue& e){
    //     return;
    // }
}

Queue<EstadoJuego>& QueueProtegida::conseguir_cola() {
    return recibidos;
}
