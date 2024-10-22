#ifndef COMMON_PATO_H
#define COMMON_PATO_H

#include <string>
#include "common_arma.h"

class Pato {
private:
    int id;
    int pos_x, pos_y; // Posición del pato en el escenario
    Arma* arma;
    bool tomo_armadura;
    bool tomo_casco;
    bool armadura_equipada;
    bool casco_equipado;
    bool vivo;
    bool apunta_arriba;

public:
    Pato(const std::string& color, int x, int y);
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