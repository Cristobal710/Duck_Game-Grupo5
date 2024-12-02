#include "common_sniper.h"

bool Sniper::disparar() {
    if (municion_disponible > 0) {
        municion_disponible--;
        // Implementar lógica específica para Sniper
        return true;
    }
    return false;
}