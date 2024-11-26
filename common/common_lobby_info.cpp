#include "common_lobby_info.h"


LobbyInfo::LobbyInfo():
partidas(), id_jugadores()
 {}

void LobbyInfo::agregar_partida(uint16_t id_jugador) {
    Partida partida_nueva(static_cast<uint8_t>(partidas.size()));
    partida_nueva.agregar_jugador(id_jugador);
    partidas.emplace_front(partida_nueva);
}

void LobbyInfo::agregar_partida(Partida& partida) {
    partidas.emplace_front(partida);
}

void LobbyInfo::unirse_a_partida(uint8_t& id_partida, uint16_t& id_jugador) {
    for (Partida& partida : partidas){
        if (partida.tiene_id(id_partida)){
            partida.agregar_jugador(id_jugador);
        }
    }
}

uint8_t LobbyInfo::cantidad_partidas() { 
    return static_cast<uint8_t>(partidas.size()) ; }

std::list<Partida>& LobbyInfo::obtener_partidas() {
    return partidas;
}
