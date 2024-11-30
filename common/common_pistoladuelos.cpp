#include "common_pistoladuelos.h"

bool PistolaDuelos::disparar() {
    if (municion_disponible > 0) {
        municion_disponible--;
        // Implementar lógica específica para PistolaDuelos
        return true;
    }
    return false;
}