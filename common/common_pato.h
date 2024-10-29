#ifndef COMMON_PATO_H
#define COMMON_PATO_H

#include <string>

#include "common_arma.h"
#include "common_constantes.h"

class Pato: public Entidad {
private:
    Arma* arma;
    bool tomo_armadura;
    bool tomo_casco;
    bool armadura_equipada;
    bool casco_equipado;
    bool vivo;
    bool apunta_arriba;
    bool tirado_al_piso;
    uint8_t direccion;
    // uint8_t color;  // hacer map con colores

public:
    Pato(uint8_t id, uint8_t pos_x, uint8_t pos_y, uint8_t direccion);
    //~Pato();
    // uint8_t get_color();
    void moverse_izquierda();
    void moverse_derecha();
    void saltar();
    void planear();
    void tomar_arma(Arma* nuevaArma);
    void soltar_arma();
    void disparar();
    void apuntar_arriba();
    void dejar_de_apuntar_arriba();
    void tirarse_al_piso();
    void tomar_armadura();
    void tomar_casco();
    void equipar_armadura();
    void equipar_casco();
    bool casco_en_inventario();
    bool armadura_en_inventario();
    bool get_casco_equipado();
    bool get_armadura_equipada();
    void recibir_danio();
    bool esta_vivo() const;
    uint8_t get_direccion();
    Arma* get_arma();
    bool esta_apuntando_arriba();
    bool esta_tirado_al_piso();
    void morir();
};

#endif
