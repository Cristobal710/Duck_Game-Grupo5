#ifndef COMMON_LOBBY_INFO_H
#define COMMON_LOBBY_INFO_H
#include <list>
#include "common_partida.h"
class LobbyInfo {
    private:
    std::list<Partida> partidas;
    std::list<uint16_t> id_jugadores;

    public:
    LobbyInfo();
    void agregar_partida(uint16_t id_jugador_inicial);
    void agregar_partida(Partida& partida);
    void unirse_a_partida(uint8_t& id_partida, uint16_t& id_jugador);
    uint8_t cantidad_partidas();
    std::list<Partida>& obtener_partidas();
};



#endif
