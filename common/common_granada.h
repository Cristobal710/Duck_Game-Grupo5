#ifndef GRANADA_H
#define GRANADA_H

#include "common_entidad.h"

class Granada: public Entidad {
protected:
    uint8_t rango;
    bool exploto;
    bool activa;

public:
    Granada(uint8_t id, uint8_t pos_x, uint8_t pos_y, uint8_t rango);
    uint8_t get_rango();
    bool esta_activa();
    bool get_exploto();
    void activar();
    void explotar();
};

#endif
