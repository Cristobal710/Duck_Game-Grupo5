#include "server_protocolo.h"
#define EXITO 0
#define ERROR 1
#define MAPA_CAJAS 0x02
#define MAPA_TILES 0x03
#define MAPA_SPAWNS 0x04
#define MAPA_EQUIPAMIENTO 0x05
#define ARMADURA "armadura"
#define ARMA "arma"
#define CASCO "casco"  
#define BYTE_ARMADURA 0X06
#define BYTE_CASCO 0X07
#define BYTE_ARMA 0X08


ServerProtocolo::ServerProtocolo(Socket& skt): Protocolo(skt) {}

EventoServer ServerProtocolo::recibir_evento() {
    bool cerrado = false;
    EventoServer evento;
    

    evento.accion = recibir_byte(cerrado);
    if (cerrado) return evento;

    evento.jugador_id = recibir_byte(cerrado);
    if (cerrado) return evento;

    evento.pedido.crear_partida = recibir_byte(cerrado);
    evento.pedido.unirse_a_partida = recibir_byte(cerrado);
    evento.pedido.id_partida_a_unirse = recibir_byte(cerrado);
    evento.pedido.un_jugador = recibir_byte(cerrado);
    evento.pedido.dos_jugadores = recibir_byte(cerrado);
    evento.pedido.empezar = recibir_byte(cerrado);
    return evento;
}

void ServerProtocolo::enviar_estado_lobby(LobbyInfo lobby_data) {
    enviar_dos_bytes(lobby_data.cantidad_partidas());
    for (Partida& partida : lobby_data.obtener_partidas()){
        enviar_byte(partida.obtener_id());
        enviar_dos_bytes(partida.cantidad_jugadores());
        for (const auto& jugador : partida.obtener_jugadores()){
            enviar_dos_bytes(jugador);
        }
    }
}

void ServerProtocolo::enviar_coordenada(SDL_Point& coord) {
    enviar_dos_bytes(static_cast<uint16_t>(coord.x));
    enviar_dos_bytes(static_cast<uint16_t>(coord.y));
}

void ServerProtocolo::enviar_equipamiento(std::map<std::string, std::vector<SDL_Point>>& equipamiento){
//    enviar_byte(MAPA_EQUIPAMIENTO);
    enviar_dos_bytes(equipamiento.size());
    for(const auto& key : equipamiento){
//        if(key.first == ARMADURA){
//            enviar_byte(BYTE_ARMADURA);
//        }else if(key.first == ARMA){
//            enviar_byte(BYTE_ARMA);
//        }else if(key.first == CASCO){
//            enviar_byte(BYTE_CASCO);
//        }
        enviar_string(key.first);
        std::vector<SDL_Point> coordenadas = equipamiento.at(key.first);
        enviar_dos_bytes(coordenadas.size());
        for(SDL_Point coord: coordenadas){
            enviar_coordenada(coord);
        }
    }    
}


// void ServerProtocolo::enviar_spawns(Mapa& mapa){
//     // std::map<std::string, std::vector<SDL_Point>> spawns =mapa.getSpawns();

//     // if(spawns.find("default") != spawns.end()){
//     //     std::vector<SDL_Point> spawns_list = spawns.at("default");

//     //     // enviar_byte(MAPA_SPAWNS);
//     //     uint16_t size_spawns = spawns_list.size();
//     //     enviar_dos_bytes(size_spawns);
//     //     std::cout << "spawns size server " << static_cast<int>(size_spawns) << std::endl;
//     //     for(SDL_Point coord : spawns_list){

//     //         enviar_coordenada(coord);
//     //     }
//     // }
// }

void ServerProtocolo::enviar_spawns(Mapa& mapa) {
    std::map<std::string, std::vector<SDL_Point>> spawns = mapa.getSpawns();
    enviar_dos_bytes(spawns.size());
    
    for (const auto& [key, coordinates] : spawns) {
        enviar_string(key);
        enviar_dos_bytes(coordinates.size());
        for (SDL_Point coord : coordinates) {
            enviar_coordenada(coord);
        }
    }
}

void ServerProtocolo::enviar_cajas_mapa(Mapa& mapa){
    std::map<std::string, std::vector<SDL_Point>> cajas =mapa.getCajas();
    std::vector<SDL_Point> cajas_list;
    if (cajas.find("default") != cajas.end()){
        cajas_list = cajas.at("default");
    }

    uint16_t size_cajas = cajas_list.size();
    enviar_dos_bytes(size_cajas);
    for(SDL_Point coord : cajas_list){
        enviar_coordenada(coord);
    }
}


void ServerProtocolo::enviar_tiles(Mapa& mapa){
    std::map<std::string, std::vector<SDL_Point>> tiles =mapa.getTiles();
    uint16_t largo_tiles = tiles.size();
    enviar_dos_bytes(largo_tiles);
    for(const auto& key : tiles){
        enviar_string(key.first);
        std::vector<SDL_Point> tiles_list = tiles.at(key.first);
        uint16_t size_tiles = tiles_list.size();
        enviar_dos_bytes(size_tiles);
        for(SDL_Point coord : tiles_list){
            enviar_coordenada(coord);
        }
    }



}

void ServerProtocolo::enviar_mapa(Mapa& mapa){
    enviar_string(mapa.getFondo());
    //enviar_spawns(mapa);
    //enviar_cajas_mapa(mapa);
    enviar_tiles(mapa);

    std::map<std::string, std::vector<SDL_Point>> equipo = mapa.getEquipamiento();
    enviar_equipamiento(equipo);    
}



void ServerProtocolo::enviar_string(const std::string& mensaje) {
    bool cerrado;
    uint16_t largo = mensaje.size(); 
    enviar_dos_bytes(largo); 

    socket.sendall(mensaje.data(), largo, &cerrado);  
}

void ServerProtocolo::enviar_estado_juego(EstadoJuego& estado) {
    enviar_byte(estado.informacion_enviada);

    if (estado.informacion_enviada == ENVIAR_MAPA){
        enviar_byte(estado.partida_iniciada);
        enviar_byte(estado.id_partida);
        enviar_mapa(estado.mapa);
        enviar_patos(estado.patos);
        enviar_cajas(estado.cajas);
        enviar_armas(estado.armas);
        return;
    }

    if (estado.informacion_enviada == ENVIAR_ESTADO_JUEGO){
        enviar_byte(estado.id_partida);
        enviar_patos(estado.patos);
        enviar_cajas(estado.cajas);
        enviar_armas(estado.armas);
        enviar_balas(estado.balas);
        enviar_protecciones(estado.armaduras);
        return;
    }

    if (estado.informacion_enviada == ESTADO_LOBBY){
        enviar_dos_bytes(estado.id_jugador);
        enviar_byte(estado.partida_iniciada);
        enviar_byte(estado.id_partida);
        
        enviar_byte(estado.partidas.size());
        for (uint8_t id_partida_creada : estado.partidas){
            enviar_byte(id_partida_creada);
        }
        return;
    }
    
}

void ServerProtocolo::enviar_pato(Pato& pato) {
    enviar_dos_bytes(pato.get_id());
    enviar_dos_bytes(pato.get_pos_x());
    enviar_dos_bytes(pato.get_pos_y());
    enviar_byte(pato.get_direccion());
    enviar_byte(pato.estado.get_estado_movimiento());
    enviar_byte(pato.estado.get_estado_salto());
    enviar_byte(pato.esta_apuntando_arriba());
    enviar_byte(pato.estado.get_estado_agachado());
    enviar_byte(pato.estado.get_estado_disparo());
    enviar_byte(pato.esta_vivo());
    enviar_byte(pato.get_casco_equipado());
    enviar_byte(pato.get_armadura_equipada());
    enviar_byte(pato.tiene_arma());
    if (pato.tiene_arma() == TOMAR_ARMA){
        enviar_dos_bytes((pato.get_arma()).get_id());
        enviar_byte((pato.get_arma()).get_municion_disponible());
        enviar_byte((pato.get_arma()).get_tipo_arma());
    }
}

void ServerProtocolo::enviar_caja(Caja& caja) {
    enviar_dos_bytes(caja.get_id());
    enviar_dos_bytes(caja.get_pos_x());
    enviar_dos_bytes(caja.get_pos_y());
    enviar_byte(caja.get_esta_vacia());
}

void ServerProtocolo::enviar_arma(Arma& arma) {
    enviar_dos_bytes(arma.get_id());
    enviar_dos_bytes(arma.get_pos_x());
    enviar_dos_bytes(arma.get_pos_y());
    enviar_dos_bytes(arma.get_alcance());
    enviar_byte(arma.get_municion_disponible());
    enviar_byte(arma.get_tipo_arma());
    enviar_byte(arma.get_se_agarro());
}

void ServerProtocolo::enviar_bala(Bala& bala) {
    enviar_dos_bytes(bala.get_id());
    enviar_dos_bytes(bala.get_pos_x());
    enviar_dos_bytes(bala.get_pos_y());
    enviar_byte(bala.get_direccion());
    enviar_byte(bala.get_tipo_arma());
}

void ServerProtocolo::enviar_granada(Granada& granada) {
    enviar_byte(granada.get_id());
    enviar_byte(granada.get_pos_x());
    enviar_byte(granada.get_pos_y());
    enviar_byte(granada.get_rango());
    enviar_byte(granada.esta_activa());
    enviar_byte(granada.get_exploto());
}

void ServerProtocolo::enviar_patos(std::list<Pato>& patos) {
    enviar_byte(patos.size());
    for (auto& pato: patos) {
        enviar_pato(pato);
    }
}

void ServerProtocolo::enviar_cajas(std::list<Caja>& cajas) {
    enviar_byte(cajas.size());
    for (auto& caja: cajas) {
        enviar_caja(caja);
    }
}

void ServerProtocolo::enviar_armas(std::list<Arma>& armas) {
    enviar_byte(armas.size());
    for (auto& arma: armas) {
        enviar_arma(arma);
    }
}

void ServerProtocolo::enviar_balas(std::list<Bala>& balas) {
    enviar_byte(balas.size());
    for (auto& bala: balas) {
        enviar_bala(bala);
    }
}

void ServerProtocolo::enviar_granadas(std::list<Granada>& granadas) {
    enviar_byte(granadas.size());
    for (auto& granada: granadas) {
        enviar_granada(granada);
    }
}

void ServerProtocolo::enviar_protecciones(std::list<Proteccion>& protecciones){
    enviar_byte(protecciones.size());
    for(auto& proteccion : protecciones){
        enviar_proteccion(proteccion);
    }
    
}

void ServerProtocolo::enviar_proteccion(Proteccion& proteccion){
    enviar_dos_bytes(proteccion.get_id());
    enviar_dos_bytes(proteccion.get_pos_x());
    enviar_dos_bytes(proteccion.get_pos_y());
    enviar_byte(proteccion.get_se_agarro());
    if (proteccion.get_tipo() == ARMADURA_ENUM){
        enviar_byte(BYTE_ARMADURA);
    }else if(proteccion.get_tipo() == CASCO_ENUM){
        enviar_byte(BYTE_CASCO);
    }
}
