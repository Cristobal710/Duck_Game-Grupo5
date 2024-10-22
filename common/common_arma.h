#ifndef ARMA_H
#define ARMA_H

#include <string>

class Arma {
    protected:
        std::string nombre;
        int municion_disponible;
        int balas_max;
        int alcance;
    public:
        void disparar() {
            municion_disponible--;
        }
        void recargar() {
            municion_disponible = balas_max;
        }
};


#endif