#ifndef CLIENT_PROTOCOL_H
#define CLIENT_PROTOCOL_H

#include <map>
#include <string>
#include <list>

#include "../common/common_protocolo.h"
#include "../common/common_socket.h"
#include "../common/common_pato.h"
#include "../common/common_caja.h"
#include "../common/common_arma.h"
#include "../common/common_bala.h"
#include "../common/common_granada.h"


#include "cliente_comando.h"

/*
 * Clase para encapsular el protocolo de comunicacion con el servidor
 * */
class ClienteProtocolo: public Protocolo {

public:
    explicit ClienteProtocolo(Socket& socket);

    void enviar_comando(ComandoGrafica comando);

    void recibir_pato(std::list<Pato>& patos);
    std::list<Pato> recibir_patos();
    //std::vector<Pato> deserializar_patos(std::vector<uint8_t>& patos);

    void recibir_caja(std::list<Caja>& cajas);
    std::list<Caja> recibir_cajas();

    void recibir_arma(std::list<Arma>& armas);
    std::list<Arma> recibir_armas();

    void recibir_bala(std::list<Bala>& balas);  
    std::list<Bala> recibir_balas();

    void recibir_granada(std::list<Granada>& granadas);  
    std::list<Granada> recibir_granadas();


    
    EstadoJuego recibir_estado_juego();
};

#endif
