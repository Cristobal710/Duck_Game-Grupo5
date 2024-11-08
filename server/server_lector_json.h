#ifndef SERVER_LECTOR_H
#define SERVER_LECTOR_H

#include <iostream>
#include <fstream>
#include <nlohmann/json.hpp>

class LectorJson {
public:
    explicit LectorJson() = default;  // Constructor predeterminado
    nlohmann::json leer_json(const std::string& ruta);

private:
    // Puedes agregar atributos privados aquí si necesitas mantener algún estado
};

#endif // SERVER_LECTOR_H
