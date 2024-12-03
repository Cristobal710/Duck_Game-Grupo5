#ifndef COMMON_PATO_H
#define COMMON_PATO_H

#include <string>

#include "common_arma.h"
#include "common_constantes.h"
#include "common_estado_pato.h"
#include "common_tipo_colision.h"
#include "common_bala.h"

class Pato: public Entidad {
private:
    Arma arma;
    bool armadura_equipada;
    bool casco_equipado;
    bool vivo;
    bool apunta_arriba;
    uint8_t direccion;
    // uint8_t color;  // hacer map con colores

public:
    void calcular_hitbox() override;
    EstadoPato estado;
    uint8_t contador_salto;
    uint8_t contador_caer;
    uint8_t velocidad_caida;
    Pato();
    Pato(uint16_t id, uint16_t pos_x, uint16_t pos_y, uint8_t direccion);
    //~Pato();
    // uint8_t get_color();
    uint8_t tiene_arma();
    void moverse_izquierda();
    void moverse_derecha();
    void saltar();
    void aletear();
    void caer();
    void tomar_arma(Arma nueva_arma);
    void soltar_arma();
    bool disparar();
    void apuntar_arriba();
    void dejar_de_apuntar_arriba();
    void tirarse_al_piso();
    void levantarse_del_piso();
    void equipar_armadura();
    void equipar_casco();
    bool get_casco_equipado();
    bool get_armadura_equipada();
    void recibir_danio();
    bool esta_vivo() const;
    uint8_t get_direccion();
    Arma get_arma();
    bool esta_apuntando_arriba();
    bool esta_tirado_al_piso();
    void morir();
    TipoColision colisiona_con_tile(SDL2pp::Rect hitbox_tile);
    TipoColision colisiona_con_bala(Bala& bala);
    TipoColision colisiona_con_recompensa(HitBox hitbox_caja);
    void ajustar_sobre_tile(const SDL2pp::Rect& tile_hitbox);
    void ajustar_derecha_tile(const SDL2pp::Rect& tile_hitbox);
    void ajustar_izquierda_tile(const SDL2pp::Rect& tile_hitbox);
    void posicion_pato_muerto();
};

#endif
