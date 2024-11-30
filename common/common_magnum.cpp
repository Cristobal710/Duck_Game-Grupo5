#include "common_magnum.h"

bool Magnum::disparar() {
    if (municion_disponible > 0) {
        municion_disponible--;
        // Implementar lógica específica para Magnum
        return true;
    }
    return false;
}