#include "camara.h"



Camara::Camara(int ancho, int alto)
    : camara(0, 0, ancho, alto), zoom(1.0f), ancho_ventana(ancho), alto_ventana(alto) {}

void Camara::actualizar(PatoInterfaz& jugador_principal, std::vector<PatoInterfaz>& jugadores) {
    // Calcular la distancia entre los jugadores más cercanos y más lejanos
    float distancia_maxima = 1.0f;

    if (jugadores.size() > 1){
        for (auto& jugador : jugadores) {
        // Compara la distancia entre el jugador principal y el resto
        float distancia = calcular_distancia(jugador_principal, jugador);
        distancia_maxima = std::max(distancia_maxima, distancia);
        }
    }
    
    zoom = 1.0f / (distancia_maxima / 500.0f);  
    zoom = std::max(1.0f, std::min(zoom, 2.4f));  

    camara.x = jugador_principal.pos_x() - ancho_ventana / 2 / zoom;
    camara.w = jugador_principal.get_w();
    camara.y = jugador_principal.pos_y() - alto_ventana / 2 / zoom;
    camara.h = jugador_principal.get_h();

    // camara.x = std::min(camara.x, ancho_ventana);
    // camara.y = std::min(camara.y, alto_ventana);
}

SDL2pp::Rect Camara::obtener_rect_camara() const {
    return camara;
}

float Camara::obtener_zoom() const {
    return zoom;
}

float Camara::calcular_distancia( PatoInterfaz& pato_princiapl,  PatoInterfaz& otro_pato)  {
    // Usamos el centro de los rectángulos para calcular la distancia

    float x1 = pato_princiapl.pos_x() + pato_princiapl.get_w() / 2;
    float y1 = pato_princiapl.pos_y() + pato_princiapl.get_h() / 2;
    float x2 = otro_pato.pos_x() + otro_pato.get_w() / 2;
    float y2 = otro_pato.pos_y() + otro_pato.get_h() / 2;

    return std::sqrt(std::pow(x2 - x1, 2) + std::pow(y2 - y1, 2));
}