#include "pato_interfaz.h"

#include "../common/common_constantes.h"
#include <SDL2/SDL_image.h>

PatoInterfaz::PatoInterfaz(SDL2pp::Renderer& renderer, const std::string& pato_path, int pos_inicial_x, int pos_inicial_y,
uint16_t pato_id, SDL_Color color):
    vivo(true),
    estado_pato_movimiento(BYTE_NULO),
    estado_pato_salto(BYTE_NULO),
    direccion_pato(DIRECCION_DERECHA),
    se_tira_al_piso(BYTE_NULO),
    estado_arma(BYTE_NULO),
    estado_balas(BYTE_NULO),
    renderer(renderer),
    rect_dibujado(pos_inicial_x, pos_inicial_y, PIXEL_PATO, PIXEL_PATO),
    movimiento_pato_lateral(renderer, pato_path, 150, 150, color),
    movimiento_pato_salto(renderer, pato_path, 150, 150, color),
    movimiento_pato_agachado(renderer, pato_path, 150, 150, color),
    municion_disponible(0),
    tipo_arma(TipoArma::Granada),
    id_jugador(pato_id),
    color(color),
    ya_dibujado_muerto(false)
{}


PatoInterfaz::PatoInterfaz(PatoInterfaz&& other) noexcept 
    :vivo(other.vivo),
    estado_pato_movimiento(other.estado_pato_movimiento),
    estado_pato_salto(other.estado_pato_salto),
    direccion_pato(other.direccion_pato),
    se_tira_al_piso(other.se_tira_al_piso),
    estado_arma(other.estado_arma),
    estado_balas(other.estado_balas),
    renderer(other.renderer),
    rect_dibujado(std::move(other.rect_dibujado)),
    movimiento_pato_lateral(std::move(other.movimiento_pato_lateral)),
    movimiento_pato_salto(std::move(other.movimiento_pato_salto)),
    movimiento_pato_agachado(std::move(other.movimiento_pato_agachado)),
    municion_disponible(other.municion_disponible),
    tipo_arma(other.tipo_arma),
    id_jugador(other.id_jugador),
    color(other.color)
{}


void PatoInterfaz::dibujar(int it, float zoom_factor) {
    int pos_x = rect_dibujado.GetX();
    int pos_y = rect_dibujado.GetY();
    
    if(se_tira_al_piso == TIRAR_PISO || se_tira_al_piso == DEJAR_TIRAR_PISO){
        movimiento_pato_agachado.pato_agachado(se_tira_al_piso, pos_x, pos_y, zoom_factor, direccion_pato);
        return;
    }
    if (estado_pato_salto == SALTAR_ALETEAR || estado_pato_salto == CAER) {
        movimiento_pato_salto.pato_salta(estado_pato_salto, pos_x, pos_y, it, zoom_factor, direccion_pato);
        return;
    }
    movimiento_pato_lateral.pato_movimiento(estado_pato_movimiento, direccion_pato, pos_x, pos_y, it, zoom_factor);
    if(estado_arma == TOMAR_ARMA){
        ArmaInterfaz arma = tomar_arma();
        arma.dibujar(direccion_pato);
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

ArmaInterfaz PatoInterfaz::tomar_arma() {
    std::string arma_path; 
    if(tipo_arma == TipoArma::Granada){
        arma_path = "../resources/weapons/grenadeLauncher.png";
        //bala_path = "../resources/weapons/grenade.png";
    } else if (tipo_arma == TipoArma::Banana){
        arma_path = "../resources/weapons/bananaMano.png";
        //bala_path = "../resources/weapons/bananaPiso.png";
    } else if (tipo_arma == TipoArma::Pew_Pew_Laser){
        arma_path = "../resources/weapons/pewpewLaser.png";
        //bala_path = "../resources/weapons/rafaga.png";
    } else if (tipo_arma == TipoArma::Laser_Rifle){
        arma_path = "../resources/weapons/laserRifle.png";
        //bala_path = "../resources/weapons/rayos.png";
    } else if (tipo_arma == TipoArma::AK47){
        arma_path = "../resources/weapons/ak47.png";
        //bala_path = "../resources/weapons/dart.png";
    } else if(tipo_arma == TipoArma::Pistola_Duelos){
        arma_path = "../resources/weapons/combatShotgun.png";
        //bala_path = "../resources/weapons/dart.png";
    } else if (tipo_arma == TipoArma::Pistola_Cowboy){
        arma_path = "../resources/weapons/cowboyPistol.png";
        //bala_path = "../resources/weapons/dart.png";
    } else if (tipo_arma == TipoArma::Magnum){
        arma_path = "../resources/weapons/magnum.png";
        //bala_path = "../resources/weapons/dart.png";
    } else if (tipo_arma == TipoArma::Escopeta){
        arma_path = "../resources/weapons/shotgun.png";
        //bala_path = "../resources/weapons/dart.png";
    } else if (tipo_arma == TipoArma::Sniper){
        arma_path = "../resources/weapons/sniper.png";
        //bala_path = "../resources/weapons/dart.png";
    }
    return ArmaInterfaz(renderer, arma_path, rect_dibujado.GetX(), rect_dibujado.GetY());
}

void PatoInterfaz::set_tipo_arma(TipoArma tipo_arma) {
    tipo_arma = tipo_arma;
}

bool PatoInterfaz::mismo_id(uint16_t id) { 
    if (id == id_jugador){
        return true;
    }
    return false; 
}

void PatoInterfaz::set_esta_vivo(bool estado) { vivo = estado; }

bool PatoInterfaz::esta_vivo() { return vivo; }

void PatoInterfaz::dibujar_muerto(float zoom_factor) {
    if(ya_dibujado_muerto){
        return;
    }
    int pos_x = rect_dibujado.GetX();
    int pos_y = rect_dibujado.GetY();
    movimiento_pato_agachado.mostrar_muerte(pos_x, pos_y, zoom_factor, direccion_pato);
    ya_dibujado_muerto = true;
}

int PatoInterfaz::pos_x() { return rect_dibujado.GetX(); }

int PatoInterfaz::pos_y() { return rect_dibujado.GetY();  }

int PatoInterfaz::get_w() { return rect_dibujado.GetW(); }

int PatoInterfaz::get_h() { return rect_dibujado.GetH(); }
