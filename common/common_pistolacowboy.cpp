#include "common_pistolacowboy.h"

bool PistolaCowboy::disparar() {
    if (municion_disponible > 0) {
        municion_disponible--;
        // Implementar lógica específica para PistolaCowboy
        return true;
    }
    return false;
}