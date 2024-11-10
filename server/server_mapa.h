#ifndef MAPA_H
#define MAPA_H
#include <SDL2pp/SDL2pp.hh>
#include <SDL2/SDL.h>
#include <string>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

class Mapa {
    private:
    std::string fondo;
    std::map<std::string,std::vector<SDL_Point>>  tiles;
    std::map<std::string,std::vector<SDL_Point>>  spawns;
    std::map<std::string,std::vector<SDL_Point>>  equipamiento;
    std::map<std::string,std::vector<SDL_Point>>  cajas;

    public:
    static Mapa from_json(const json& j, Mapa& mapa) {
        
        mapa.fondo = j.at("background").get<std::string>();

        
        if (j.contains("tiles")) {
            for (const auto& tile : j["tiles"]) {
                std::string texture = tile.at("texture").get<std::string>();
                int x = tile.at("x").get<int>();
                int y = tile.at("y").get<int>();
                mapa.tiles[texture].emplace_back(SDL_Point{x, y});
            }
        }

        
        if (j.contains("spawns")) {
            for (const auto& spawn : j["spawns"]) {
                int x = spawn.at("x").get<int>();
                int y = spawn.at("y").get<int>();
                mapa.spawns["default"].emplace_back(SDL_Point{x, y});
            }
        }

        
        if (j.contains("equipamiento")) {
            for (const auto& item : j["equipamiento"]) {
                for (auto& el : item.items()) {
                    std::string key = el.key();
                    int x = item.at("x").get<int>();
                    int y = item.at("y").get<int>();
                    mapa.equipamiento[key].emplace_back(SDL_Point{x, y});
                }
            }
        }

        // Cajas - Assuming you want to process this the same way (if exists in the JSON)
        if (j.contains("cajas")) {
            for (const auto& caja : j["cajas"]) {
                int x = caja.at("x").get<int>();
                int y = caja.at("y").get<int>();
                mapa.cajas["default"].emplace_back(SDL_Point{x, y});
            }
        }

        return mapa;
    }

    const std::string& getFondo() const { return fondo; };
    const std::map<std::string, std::vector<SDL_Point>>& getTiles() const { return tiles; };
    const std::map<std::string, std::vector<SDL_Point>>& getSpawns() const { return spawns; };
    const std::map<std::string, std::vector<SDL_Point>>& getEquipamiento() const { return equipamiento; };
    const std::map<std::string, std::vector<SDL_Point>>& getCajas() const { return cajas; };
};

#endif
