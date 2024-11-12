#ifndef SERVER_LECTOR_H
#define SERVER_LECTOR_H
#include "../common/common_mapa.h"
#include <iostream>
#include <fstream>

class LectorJson {
public:
    explicit LectorJson() = default;  // Constructor predeterminado
    Mapa procesar_mapa(const std::string& ruta);

private:
    // Puedes agregar atributos privados aquí si necesitas mantener algún estado
};

#endif // SERVER_LECTOR_H
