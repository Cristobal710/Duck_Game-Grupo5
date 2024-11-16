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

   
    void actualizar( PatoInterfaz& rect_jugador_principal,  std::vector<PatoInterfaz>& jugadores);

    
    SDL2pp::Rect obtener_rect_camara() const;

   
    float obtener_zoom() const;

private:
    SDL2pp::Rect camara;     
    float zoom;              
    int ancho_ventana, alto_ventana; 

    float calcular_distancia( PatoInterfaz& rect1,  PatoInterfaz& rect2);
};

#endif // CAMERA_H