#ifndef CAMARA_H
#define CAMARA_H
#include <algorithm>
#include <cmath>
#include <iostream>
#include <vector>
#include "pato_interfaz.h"
class Camara {
public:
    Camara(int ancho, int alto);

    // Método para actualizar la cámara, seguir al jugador y ajustar el zoom
    void actualizar( PatoInterfaz& rect_jugador_principal,  std::vector<PatoInterfaz>& jugadores);

    // Obtener el rectángulo de la cámara
    SDL2pp::Rect obtener_rect_camara() const;

    // Obtener el factor de zoom actual
    float obtener_zoom() const;

private:
    SDL2pp::Rect camara;      // Posición y tamaño de la cámara en el mundo
    float zoom;               // Factor de zoom
    int ancho_ventana, alto_ventana; // Dimensiones de la ventana

    // Función para calcular la distancia entre dos puntos
    float calcular_distancia( PatoInterfaz& rect1,  PatoInterfaz& rect2);
};

#endif // CAMERA_H