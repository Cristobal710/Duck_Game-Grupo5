#include "common_laserrifle.h"

bool LaserRifle::disparar() {
    if (municion_disponible > 0) {
        municion_disponible--;
        // Implementar lógica específica para LaserRifle
        return true;
    }
    return false;
}