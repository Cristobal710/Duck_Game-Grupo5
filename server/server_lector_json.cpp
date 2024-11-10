#include "server_lector_json.h"

Mapa LectorJson::procesar_mapa(const std::string& ruta) {
    std::ifstream archivo(ruta);
    nlohmann::json j;
    archivo >> j;

    Mapa mapa;
    mapa.from_json(j, mapa);

    return mapa;
}
