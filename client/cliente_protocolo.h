#ifndef CLIENT_PROTOCOL_H
#define CLIENT_PROTOCOL_H

#include <list>
#include <map>
#include <string>
#include <SDL2pp/SDL2pp.hh>

#include "../common/common_arma.h"
#include "../common/common_bala.h"
#include "../common/common_caja.h"
#include "../common/common_granada.h"
#include "../common/common_pato.h"
#include "../common/common_protocolo.h"
#include "../common/common_socket.h"
#include "../common/common_constantes.h"
#include "../common/common_estado_pato.h"
#include "../common/common_mapa.h"
#include "cliente_comando.h"

/*
 * Clase para encapsular el protocolo de comunicacion con el servidor
 * */
class ClienteProtocolo: public Protocolo {

public:
    explicit ClienteProtocolo(Socket& socket);

    void enviar_comando(ComandoGrafica comando);
    
    std::string recibir_string();

    void recibir_pato(std::list<Pato>& patos);
    std::list<Pato> recibir_patos();
    // std::vector<Pato> deserializar_patos(std::vector<uint8_t>& patos);

    void recibir_caja(std::list<Caja>& cajas);
    std::list<Caja> recibir_cajas();

    void recibir_arma(std::list<Arma>& armas);
    std::list<Arma> recibir_armas();

    void recibir_bala(std::list<Bala>& balas);
    std::list<Bala> recibir_balas();

    void recibir_granada(std::list<Granada>& granadas);
    std::list<Granada> recibir_granadas();

    void recibir_proteccion(std::list<Proteccion>& protecciones);
    std::list<Proteccion> recibir_protecciones();

    Mapa recibir_mapa();

    EstadoJuego recibir_estado_juego();
    SDL_Point recibir_coordenada();

    void recibir_tiles(Mapa& mapa);
    void recibir_equipamiento(Mapa& mapa);
    void recibir_spawns(Mapa& mapa);
    void recibir_cajas(Mapa& mapa);
};

#endif
