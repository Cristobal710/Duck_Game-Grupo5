#include "server_lector_json.h"

nlohmann::json LectorJson::leer_json(const std::string& ruta) {
    std::ifstream archivo(ruta);
    nlohmann::json data;

    if (archivo.is_open()) {
        try {
            archivo >> data;  // Leer el contenido del archivo en el objeto JSON
        } catch (const nlohmann::json::parse_error& e) {
            std::cerr << "Error de parsing en el archivo JSON: " << e.what() << std::endl;
        }
    } else {
        std::cerr << "No se pudo abrir el archivo: " << ruta << std::endl;
    }

    return data;
}
