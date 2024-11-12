#include "pato_interfaz.h"

#include "../common/common_constantes.h"
#include <SDL2/SDL_image.h>
#define PIXEL_PATO 32

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
    movimiento_pato_agachado(renderer, pato_path, 150, 150)
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
        Disparo pato_disparo = tomar_arma(renderer, "../resources/weapons/Darts.png", "../resources/weapons/Darts.png");
        pato_disparo.mostrar_disparo(estado_balas, direccion_pato, pos_x, pos_y, it, zoom_factor);
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
    }
    tipo_estado.clear();
}

Disparo PatoInterfaz::tomar_arma(SDL2pp::Renderer& renderer, const std::string& arma_path, const std::string& bala_path) {
    return Disparo(renderer, arma_path, bala_path, rect_dibujado.GetX(), rect_dibujado.GetY());
}
