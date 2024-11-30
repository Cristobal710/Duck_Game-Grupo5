#include "cliente_protocolo.h"

#include <cstring>
#include <iostream>

#include <arpa/inet.h>

#include "../common/common_liberror.h"

ClienteProtocolo::ClienteProtocolo(Socket& socket): Protocolo(socket) {}

void ClienteProtocolo::enviar_comando(ComandoGrafica comando) {
    uint8_t accion = acciones[comando.tecla];
    enviar_byte(accion);
    enviar_byte(comando.jugador_id);
    enviar_byte(comando.pedido.crear_partida);
    enviar_byte(comando.pedido.unirse_a_partida);
    enviar_byte(comando.pedido.id_partida_a_unirse);
    enviar_byte(comando.pedido.un_jugador);
    enviar_byte(comando.pedido.dos_jugadores);
    enviar_byte(comando.pedido.empezar);
}

void ClienteProtocolo::recibir_pato(std::list<Pato>& patos) {
    bool cerrado;
    uint16_t id = recibir_dos_bytes(cerrado);
    uint16_t pos_x = recibir_dos_bytes(cerrado);
    uint16_t pos_y = recibir_dos_bytes(cerrado);
    uint8_t direccion = recibir_byte(cerrado);
    uint8_t estado_movimiento = recibir_byte(cerrado);
    uint8_t estado_salto = recibir_byte(cerrado);
    uint8_t apunta_arriba = recibir_byte(cerrado);
    uint8_t estado_agachado = recibir_byte(cerrado);
    uint8_t estado_disparo = recibir_byte(cerrado);
    uint8_t esta_vivo = recibir_byte(cerrado);
    uint8_t casco_inventario = recibir_byte(cerrado);
    uint8_t armadura_inventario = recibir_byte(cerrado);
    uint8_t casco_equipado = recibir_byte(cerrado);
    uint8_t armadura_equipada = recibir_byte(cerrado);
    uint8_t tiene_arma = recibir_byte(cerrado);

    Pato pato(id, pos_x, pos_y, direccion);
    pato.estado = EstadoPato(estado_movimiento, estado_salto, estado_agachado, estado_disparo);
    if (tiene_arma == TOMAR_ARMA) {
        uint16_t arma_id = recibir_dos_bytes(cerrado);
        uint8_t municion_disponible = recibir_byte(cerrado);
        uint8_t tipo_arma = recibir_byte(cerrado);
        Arma* arma = new Arma(arma_id, pos_x, pos_y, municion_disponible, 30, tipo_arma);
        pato.tomar_arma(arma);
    }
    if (static_cast<bool>(apunta_arriba)) {
        pato.apuntar_arriba();
    }
    if (static_cast<bool>(casco_inventario)) {
        pato.tomar_casco();
    }
    if (static_cast<bool>(armadura_inventario)) {
        pato.tomar_armadura();
    }
    if (static_cast<bool>(casco_equipado)) {
        pato.equipar_casco();
    }
    if (static_cast<bool>(armadura_equipada)) {
        pato.equipar_armadura();
    }
    if (!(static_cast<bool>(esta_vivo))) {
        pato.morir();
    }
    patos.push_back(pato);
}

std::list<Pato> ClienteProtocolo::recibir_patos() {
    std::list<Pato> patos;
    std::vector<uint8_t> cantidad_patos(1);
    bool cerrado;
    socket.recvall(cantidad_patos.data(), cantidad_patos.size(), &cerrado);
    int cantidad = static_cast<int>(cantidad_patos[0]);

    for (int i = 0; i < cantidad; i++) {
        recibir_pato(patos);
    }
    return patos;
}


void ClienteProtocolo::recibir_caja(std::list<Caja>& cajas) {
    bool cerrado;
    uint16_t id = recibir_dos_bytes(cerrado);
    uint16_t pos_x = recibir_dos_bytes(cerrado);
    uint16_t pos_y = recibir_dos_bytes(cerrado);
    uint8_t recompensa_id = recibir_byte(cerrado);
    Caja caja(id, pos_x, pos_y, recompensa_id);
    cajas.push_back(caja);
}


std::list<Caja> ClienteProtocolo::recibir_cajas() {
    std::list<Caja> cajas;
    std::vector<uint8_t> cantidad_patos(2);
    bool cerrado;
    socket.recvall(cantidad_patos.data(), cantidad_patos.size(), &cerrado);
    int cantidad = static_cast<int>(cantidad_patos[1]);

    for (int i = 0; i < cantidad; i++) {
        recibir_caja(cajas);
    }
    return cajas;
}

void ClienteProtocolo::recibir_arma(std::list<Arma>& armas) {
    bool cerrado;
    uint8_t id = recibir_byte(cerrado);
    uint8_t pos_x = recibir_byte(cerrado);
    uint8_t pos_y = recibir_byte(cerrado);
    uint8_t alcance = recibir_byte(cerrado);
    uint8_t municion_disponible = recibir_byte(cerrado);
    uint8_t tipo_arma = recibir_byte(cerrado);
    Arma arma(id, pos_x, pos_y, alcance, municion_disponible, tipo_arma);
    armas.push_back(arma);
}

std::list<Arma> ClienteProtocolo::recibir_armas() {
    std::list<Arma> armas;
    std::vector<uint8_t> cantidad_armas(2);
    bool cerrado;
    socket.recvall(cantidad_armas.data(), cantidad_armas.size(), &cerrado);
    int cantidad = static_cast<int>(cantidad_armas[1]);

    for (int i = 0; i < cantidad; i++) {
        recibir_arma(armas);
    }
    return armas;
}


void ClienteProtocolo::recibir_bala(std::list<Bala>& balas) {
    bool cerrado;
    uint16_t id = recibir_dos_bytes(cerrado);
    uint16_t pos_x = recibir_dos_bytes(cerrado);
    uint16_t pos_y = recibir_dos_bytes(cerrado);
    uint8_t direccion = recibir_byte(cerrado);
    uint8_t tipo_arma = recibir_byte(cerrado);
    Bala bala(id, pos_x, pos_y, 0, 0, direccion, tipo_arma);
    balas.push_back(bala);
}

std::list<Bala> ClienteProtocolo::recibir_balas() {
    std::list<Bala> balas;
    std::vector<uint8_t> cantidad_balas(1);
    bool cerrado;
    socket.recvall(cantidad_balas.data(), cantidad_balas.size(), &cerrado);
    int cantidad = static_cast<int>(cantidad_balas[0]);

    for (int i = 0; i < cantidad; i++) {
        recibir_bala(balas);
    }
    return balas;
}

void ClienteProtocolo::recibir_granada(std::list<Granada>& granadas) {
    bool cerrado;
    uint8_t id = recibir_byte(cerrado);
    uint8_t pos_x = recibir_byte(cerrado);
    uint8_t pos_y = recibir_byte(cerrado);
    uint8_t rango = recibir_byte(cerrado);
    uint8_t activa = recibir_byte(cerrado);
    uint8_t exploto = recibir_byte(cerrado);

    Granada granada(id, pos_x, pos_y, rango);
    if (static_cast<bool>(activa)) {
        granada.activar();
    }
    if (static_cast<bool>(exploto)) {
        granada.explotar();
    }
    granadas.push_back(granada);
}

std::list<Granada> ClienteProtocolo::recibir_granadas() {
    std::list<Granada> granadas;
    std::vector<uint8_t> cantidad_granadas(2);
    bool cerrado;
    socket.recvall(cantidad_granadas.data(), cantidad_granadas.size(), &cerrado);
    int cantidad = static_cast<int>(cantidad_granadas[1]);

    for (int i = 0; i < cantidad; i++) {
        recibir_granada(granadas);
    }
    return granadas;
}

EstadoJuego ClienteProtocolo::recibir_estado_juego() {
    EstadoJuego estado_juego;
    bool cerrado = false;

    uint8_t cant_ids_tomados = recibir_byte(cerrado);
    std::list<uint16_t> lista_id;
    for (uint8_t i = 0; i < cant_ids_tomados ; i++){
        lista_id.emplace_front(recibir_dos_bytes(cerrado));
    }

    estado_juego.ids_tomados = lista_id;
    estado_juego.id_partida = recibir_byte(cerrado);
    estado_juego.mapa = recibir_mapa();

    //estado_juego.lobby_data = recibir_lobby_data();
    
    estado_juego.patos = recibir_patos();

    estado_juego.balas = recibir_balas();
    
    //estado_juego.cajas = recibir_cajas();
    
    estado_juego.armas = recibir_armas();
    return estado_juego;
}

/*std::string ClienteProtocolo::recibir_string() {
    std::vector<uint8_t> mensajeSize(2);
    bool cerrado;

    socket.recvall(mensajeSize.data(), mensajeSize.size(), &cerrado);
    int tam = static_cast<int>(mensajeSize[1]);
    std::vector<uint8_t> datos_recibidos(tam);
    socket.recvall(datos_recibidos.data(), datos_recibidos.size(), &cerrado);


    uint8_t largo = datos_recibidos.size();

    std::string mensajeDeserializado = std::string(datos_recibidos.begin(), datos_recibidos.begin() + largo);
    return mensajeDeserializado;
}*/

std::string ClienteProtocolo::recibir_string() {
    bool cerrado = false;
    uint16_t largo = recibir_dos_bytes(cerrado);
    std::vector<char> buffer(largo);
    socket.recvall(buffer.data(), largo, &cerrado);
    return std::string(buffer.begin(), buffer.end());
}

LobbyInfo ClienteProtocolo::recibir_lobby_data() {
    LobbyInfo lobby_data;
    bool cerrado = false;
    uint16_t cantidad_partidas = recibir_dos_bytes(cerrado);
    for (int i = 0; i < cantidad_partidas; i++){
        Partida partida(recibir_byte(cerrado));
        uint16_t cantidad_jugadores = recibir_dos_bytes(cerrado);
        for (int i = 0; i < cantidad_jugadores; i++) {
            partida.agregar_jugador(recibir_dos_bytes(cerrado));
        }
        lobby_data.agregar_partida(partida);
    }
    //std::cout << "hay estas partidas " << lobby_data.cantidad_partidas() << std::endl; 
    return lobby_data;
}


SDL_Point ClienteProtocolo::recibir_coordenada(){
    bool cerrado;
    SDL_Point coord;
    coord.x = recibir_dos_bytes(cerrado);
    coord.y = recibir_dos_bytes(cerrado);
    return coord;
}


void ClienteProtocolo::recibir_equipamiento(Mapa& mapa){
    bool cerrado;
    std::map<std::string, std::vector<SDL_Point>> equipo;

    uint16_t cantidad_items = recibir_dos_bytes(cerrado);
    for(int i = 0; i<cantidad_items; i++){
        std::string item = recibir_string();
        uint16_t largo_items = recibir_dos_bytes(cerrado);
        for (int i = 0; i<largo_items; i++){
            equipo[item].push_back(recibir_coordenada());
        }
    }
    mapa.set_equipamiento(equipo);

}


void ClienteProtocolo::recibir_tiles(Mapa& mapa){
    bool cerrado;
    std::map<std::string, std::vector<SDL_Point>> tiles;

    uint16_t cantidad_textura = recibir_dos_bytes(cerrado);
    for(int i = 0; i<cantidad_textura; i++){
        std::string textura = recibir_string();
        uint16_t largo_tiles = recibir_dos_bytes(cerrado);
        for (int i = 0; i<largo_tiles; i++){       
            tiles[textura].push_back(recibir_coordenada());

        }
    }
    mapa.set_tiles(tiles);
}


/*void ClienteProtocolo::recibir_spawns(Mapa& mapa){
    std::map<std::string, std::vector<SDL_Point>> mapa_spawns; 
    bool cerrado; 
    uint16_t largo_spawns = recibir_dos_bytes(cerrado);

    std::cout << "spawns size cliente " << static_cast<int>(largo_spawns) << std::endl;
    for(int i = 0; i<largo_spawns; i++){
        SDL_Point coordenada = recibir_coordenada();
        mapa_spawns["default"].push_back(coordenada);
    }
    mapa.set_spawns(mapa_spawns);
    
}*/

void ClienteProtocolo::recibir_spawns(Mapa& mapa) {
    std::map<std::string, std::vector<SDL_Point>> spawns;
    bool cerrado = false;
    uint16_t num_spawn_types = recibir_dos_bytes(cerrado);
    
    for (int i = 0; i < num_spawn_types; ++i) {
        std::string spawn_type = recibir_string();
        uint16_t num_coordinates = recibir_dos_bytes(cerrado);
        
        std::vector<SDL_Point> coordinates;
        for (int j = 0; j < num_coordinates; ++j) {
            SDL_Point point = recibir_coordenada();
            coordinates.push_back(point);
        }
        spawns[spawn_type] = coordinates;
    }
    mapa.set_spawns(spawns);
}


void ClienteProtocolo::recibir_cajas(Mapa& mapa){
    bool cerrado;
    std::map<std::string, std::vector<SDL_Point>> mapa_cajas; 
    uint16_t largo_cajas = recibir_dos_bytes(cerrado);
    for(int i = 0; i<largo_cajas; i++){
        SDL_Point coordenada = recibir_coordenada();
        mapa_cajas["default"].push_back(coordenada);
    }
    mapa.set_cajas(mapa_cajas);

}


Mapa ClienteProtocolo::recibir_mapa(){
    Mapa mapa;

    std::string fondo = recibir_string();
    mapa.set_fondo(fondo);
    //recibir_spawns(mapa);
    recibir_cajas(mapa);
    recibir_tiles(mapa);
    recibir_equipamiento(mapa);
    return mapa;

}
