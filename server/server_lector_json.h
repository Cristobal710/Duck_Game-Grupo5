#ifndef SERVER_LECTOR_H
#define SERVER_LECTOR_H
#include "../common/common_mapa.h"
#include <iostream>
#include <fstream>

class LectorJson {
public:
    explicit LectorJson() = default;
    Mapa procesar_mapa(const std::string& ruta);
};

#endif
