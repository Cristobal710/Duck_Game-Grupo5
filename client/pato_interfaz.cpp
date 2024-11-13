#include "pato_interfaz.h"

#include "../common/common_constantes.h"
#include <SDL2/SDL_image.h>

PatoInterfaz::PatoInterfaz(SDL2pp::Renderer& renderer, const std::string& pato_path, int pos_inicial_x, int pos_inicial_y):
    estado_pato_movimiento(BYTE_NULO),
    estado_pato_salto(BYTE_NULO),
    direccion_pato(DIRECCION_DERECHA),
    se_tira_al_piso(BYTE_NULO),
    estado_arma(BYTE_NULO),
    estado_balas(BYTE_NULO),
    renderer(renderer),
    rect_dibujado(pos_inicial_x, pos_inicial_y, PIXEL_PATO, PIXEL_PATO),
    movimiento_pato_lateral(renderer, pato_path, 150, 150),
    movimiento_pato_salto(renderer, pato_path, 150, 150),
    movimiento_pato_agachado(renderer, pato_path, 150, 150),
    municion_disponible(0),
    pos_x_final_bala(0), pos_y_final_bala(0),
    tipo_arma(TipoArma::Granada)
{}

void PatoInterfaz::dibujar(int it, float zoom_factor) {
    int pos_x = rect_dibujado.GetX();
    int pos_y = rect_dibujado.GetY();
    
    if(se_tira_al_piso == TIRAR_PISO){
        movimiento_pato_agachado.pato_agachado(se_tira_al_piso, pos_x, pos_y, it, zoom_factor);
        return;
    } else if (estado_pato_salto == SALTAR_ALETEAR || estado_pato_salto == CAER) {
        movimiento_pato_salto.pato_salta(estado_pato_salto, pos_x, pos_y, it, zoom_factor);
        return;
    }
    movimiento_pato_lateral.pato_movimiento(estado_pato_movimiento, direccion_pato, pos_x, pos_y, it, zoom_factor);
    if(estado_arma == TOMAR_ARMA){
        Disparo pato_disparo = tomar_arma();
        if(estado_balas == DISPARAR){
            pato_disparo.get_arma().set_municion(municion_disponible);
            pato_disparo.get_bala().set_posicion_bala(pos_x_final_bala, pos_y_final_bala);
        }
        pato_disparo.mostrar_disparo(estado_balas, direccion_pato, pos_x, pos_y, zoom_factor, it);
    }
}

void PatoInterfaz::actualizar_estado(uint8_t estado_nuevo, std::string tipo_estado) {
    if (tipo_estado == ESTADO_MOVIMIENTO){
        estado_pato_movimiento = estado_nuevo;
    }
    if (tipo_estado == ESTADO_SALTO){
        estado_pato_salto = estado_nuevo;
    }
    if (tipo_estado == ESTADO_DIRECCION){
        direccion_pato = estado_nuevo;
    }
    if (tipo_estado == ESTADO_PISO){
        se_tira_al_piso = estado_nuevo;
    }
}

void PatoInterfaz::actualizar_posicion(int pos_x, int pos_y) {
    rect_dibujado.SetX(pos_x);
    rect_dibujado.SetY(pos_y);
}

void PatoInterfaz::actualizar_equipamiento(uint8_t estado_nuevo, std::string tipo_estado) {
    if(tipo_estado == ESTADO_ARMA){
        estado_arma = estado_nuevo;
    } else if(tipo_estado == ESTADO_BALAS){
        estado_balas = estado_nuevo;
    } else if(tipo_estado == ESTADO_MUNICION){
        municion_disponible = estado_nuevo;
    }
    tipo_estado.clear();
}

void PatoInterfaz::actualizar_posicion_bala(uint16_t pos_x_final, uint16_t pos_y_final) {
    pos_x_final_bala = pos_x_final;
    pos_y_final_bala = pos_y_final;
}

Disparo PatoInterfaz::tomar_arma() {
    std::string arma_path; 
    std::string bala_path;
    if(tipo_arma == TipoArma::Granada){
        arma_path = "../resources/weapons/grenadeLauncher.png";
        bala_path = "../resources/weapons/grenade.png";
    } else if (tipo_arma == TipoArma::Banana){
        arma_path = "../resources/weapons/bananaMano.png";
        bala_path = "../resources/weapons/bananaPiso.png";
    } else if (tipo_arma == TipoArma::Pew_Pew_Laser){
        arma_path = "../resources/weapons/pewpewLaser.png";
        bala_path = "../resources/weapons/rafaga.png";
    } else if (tipo_arma == TipoArma::Laser_Rifle){
        arma_path = "../resources/weapons/laserRifle.png";
        bala_path = "../resources/weapons/rayos.png";
    } else if (tipo_arma == TipoArma::AK47){
        arma_path = "../resources/weapons/ak47.png";
        bala_path = "../resources/weapons/dart.png";
    } else if(tipo_arma == TipoArma::Pistola_Duelos){
        arma_path = "../resources/weapons/combatShotgun.png";
        bala_path = "../resources/weapons/dart.png";
    } else if (tipo_arma == TipoArma::Pistola_Cowboy){
        arma_path = "../resources/weapons/cowboyPistol.png";
        bala_path = "../resources/weapons/dart.png";
    } else if (tipo_arma == TipoArma::Magnum){
        arma_path = "../resources/weapons/magnum.png";
        bala_path = "../resources/weapons/dart.png";
    } else if (tipo_arma == TipoArma::Escopeta){
        arma_path = "../resources/weapons/shotgun.png";
        bala_path = "../resources/weapons/dart.png";
    } else if (tipo_arma == TipoArma::Sniper){
        arma_path = "../resources/weapons/sniper.png";
        bala_path = "../resources/weapons/dart.png";
    }
    return Disparo(renderer, arma_path, bala_path, rect_dibujado.GetX(), rect_dibujado.GetY());
}

void PatoInterfaz::set_tipo_arma(TipoArma tipo_arma) {
    tipo_arma = tipo_arma;
}
