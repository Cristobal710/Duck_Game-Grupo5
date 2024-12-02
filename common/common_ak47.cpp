#include "common_ak47.h"

bool AK47::disparar() {
    if (municion_disponible > 0) {
        municion_disponible--;
        // Implementar lógica específica para AK47
        return true;
    }
    return false;
}