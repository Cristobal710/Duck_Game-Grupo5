#include "common_escopeta.h"

bool Escopeta::disparar() {
    if (municion_disponible > 0) {
        municion_disponible--;
        // Implementar lógica específica para Escopeta
        return true;
    }
    return false;
}