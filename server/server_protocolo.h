#ifndef SERVER_PROTOCOLO_H
#define SERVER_PROTOCOLO_H

#include <cstdint>
#include <iostream>
#include <string>
#include <list>

#include "../common/common_protocolo.h"
#include "../common/common_queue.h"
#include "../common/common_socket.h"

#include "../common/common_pato.h"
#include "../common/common_arma.h"
#include "../common/common_bala.h"
#include "../common/common_caja.h"
#include "../common/common_entidad.h"
#include "../common/common_estado_juego.h"
#include "../common/common_granada.h"

#include "server_evento.h"

struct Comando {
    uint8_t comando;
    uint8_t accion;
    uint8_t jugador_id;
};

class ServerProtocolo: public Protocolo {
private:
    Comando recibir_nombre();
    uint8_t recibir_caja();
    void enviar_pato(Pato& pato);
    void enviar_caja(Caja& caja);
    void enviar_arma(Arma& arma);
    void enviar_bala(Bala& bala);
    void enviar_granada(Granada& granada);
    void enviar_patos(std::list<Pato>& patos);
    void enviar_cajas(std::list<Caja>& cajas);
    void enviar_armas(std::list<Arma>& armas);
    void enviar_balas(std::list<Bala>& balas);
    void enviar_granadas(std::list<Granada>& granadas);
    std::list<uint8_t> serializar_pato(Pato& pato);

public:
    explicit ServerProtocolo(Socket& socket);
    EventoServer recibir_evento();
    void enviar_estado_juego(EstadoJuego& estado);

};

#endif
