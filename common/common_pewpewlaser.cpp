#include "common_pewpewlaser.h"

bool PewPewLaser::disparar() {
    if (municion_disponible > 0) {
        municion_disponible--;
        // Implementar lógica específica para PewPewLaser
        return true;
    }
    return false;
}