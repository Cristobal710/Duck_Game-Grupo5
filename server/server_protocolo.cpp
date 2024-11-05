#include "server_protocolo.h"
#define EXITO 0
#define ERROR 1

ServerProtocolo::ServerProtocolo(Socket& skt): Protocolo(skt) {}

EventoServer ServerProtocolo::recibir_evento() {
    bool cerrado = false;
    EventoServer evento;
    evento.accion = recibir_byte(cerrado);
    evento.jugador_id = recibir_byte(cerrado);
    return evento;
}

void ServerProtocolo::enviar_estado_juego(EstadoJuego& estado) {
    enviar_byte(static_cast<uint8_t>(estado.patos.size()));
    enviar_patos(estado.patos);
    // enviar_byte(estado.cajas.size());
    // enviar_cajas(estado.cajas);
    // enviar_byte(estado.armas.size());
    // enviar_armas(estado.armas);
    // enviar_byte(estado.balas.size());
    // enviar_balas(estado.balas);
    // enviar_byte(estado.granadas.size());
    // enviar_granadas(estado.granadas);
}

void ServerProtocolo::enviar_pato(Pato& pato) {
    enviar_dos_bytes(pato.get_id());
    enviar_dos_bytes(pato.get_pos_x());
    enviar_dos_bytes(pato.get_pos_y());
    enviar_dos_bytes(pato.get_direccion());
    enviar_byte(pato.estado.get_estado_movimiento());
    enviar_dos_bytes(pato.esta_apuntando_arriba());
    enviar_dos_bytes(pato.esta_tirado_al_piso());
    enviar_dos_bytes(pato.esta_vivo());
    enviar_dos_bytes(pato.casco_en_inventario());
    enviar_dos_bytes(pato.armadura_en_inventario());
    enviar_dos_bytes(pato.get_casco_equipado());
    enviar_dos_bytes(pato.get_armadura_equipada());
    if (pato.get_arma() != nullptr){
        enviar_dos_bytes((pato.get_arma())->get_id());
        enviar_dos_bytes((pato.get_arma())->get_municion_disponible());
    }
}

void ServerProtocolo::enviar_caja(Caja& caja) {
    enviar_dos_bytes(caja.get_id());
    enviar_dos_bytes(caja.get_pos_x());
    enviar_dos_bytes(caja.get_pos_y());
    enviar_byte(caja.get_recompensa());
}

void ServerProtocolo::enviar_arma(Arma& arma) {
    enviar_byte(arma.get_id());
    enviar_byte(arma.get_pos_x());
    enviar_byte(arma.get_pos_y());
    enviar_byte(arma.get_alcance());
    enviar_byte(arma.get_municion_disponible());
    enviar_byte(arma.get_balas_max());
}

void ServerProtocolo::enviar_bala(Bala& bala) {
    enviar_byte(bala.get_id());
    enviar_byte(bala.get_pos_x());
    enviar_byte(bala.get_pos_y());
    enviar_byte(bala.get_pos_x_final());
    enviar_byte(bala.get_pos_y_final());
    enviar_byte(bala.get_direccion());
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
