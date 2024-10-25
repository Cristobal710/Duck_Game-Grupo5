#ifndef COMMON_PATO_H
#define COMMON_PATO_H

#include <string>

#include "common_arma.h"

class Pato: public Entidad {
private:
    Arma* arma;
    bool tomo_armadura;
    bool tomo_casco;
    bool armadura_equipada;
    bool casco_equipado;
    bool vivo;
    bool apunta_arriba;
    int color;  // hacer map con colores

public:
    Pato(uint8_t id, uint8_t pos_x, uint8_t pos_y, const std::string& color);
    ~Pato();

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
    void recibir_danio();
    bool esta_vivo() const;
    void morir();
};

#endif
