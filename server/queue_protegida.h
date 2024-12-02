#ifndef QUEUE_PROTEGIDA_H
#define QUEUE_PROTEGIDA_H
#include "../common/common_queue.h"
#include "../common/common_estado_juego.h"
#include <mutex>


class QueueProtegida {
    private:
    Queue<EstadoJuego>& recibidos;
    std::mutex mutex;


    public:
    QueueProtegida(Queue<EstadoJuego>& recibidos);
    void enviar_mensaje(EstadoJuego& ultimo_estado);
    Queue<EstadoJuego>& conseguir_cola();
};


#endif
