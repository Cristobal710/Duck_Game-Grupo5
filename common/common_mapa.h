#ifndef COMMON_MAPA_H
#define COMMON_MAPA_H
#include <SDL2/SDL.h>
#include <string>
#include <nlohmann/json.hpp>
#include <iostream>
using json = nlohmann::json;

class Mapa {
    private:
    bool mapa_procesado;
    std::string fondo;
    std::map<std::string,std::vector<SDL_Point>>  tiles;
    std::map<std::string,std::vector<SDL_Point>>  spawns;
    std::map<std::string,std::vector<SDL_Point>>  equipamiento;
    std::map<std::string,std::vector<SDL_Point>>  cajas;

    public:
    Mapa(){}


    static Mapa from_json(const json& j, Mapa& mapa) {
        
        mapa.mapa_procesado = false;
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
                std::string path;
                int x = item.at("x").get<int>();
                int y = item.at("y").get<int>();

                // Extract the path based on the available keys
                if (item.contains("armadura")) {
                    path = item["armadura"];
                } else if (item.contains("arma")) {
                    path = item["arma"];
                } else if (item.contains("casco")) {
                    path = item["casco"];
                } else {
                    continue; // Skip unknown equipment types
                }

                // Store the extracted path and position
                mapa.equipamiento[path].emplace_back(SDL_Point{x, y});
            }
        }

        if (j.contains("cajas")) {
            for (const auto& caja : j["cajas"]) {
                int x = caja.at("x").get<int>();
                int y = caja.at("y").get<int>();
                mapa.cajas["default"].emplace_back(SDL_Point{x, y});
            }
        }

        return mapa;
    }

    void print() const {
        // Check if any of the maps are empty and print accordingly
        if (tiles.empty()) {
            std::cout << "Tiles map is empty!" << std::endl;
        } else {
            std::cout << "Tiles map contains:" << std::endl;
            for (const auto& entry : tiles) {
                std::cout << "Texture: " << entry.first << " with " << entry.second.size() << " points." << std::endl;
            }
        }

        if (spawns.empty()) {
            std::cout << "Spawns map is empty!" << std::endl;
        } else {
            std::cout << "Spawns map contains:" << std::endl;
            for (const auto& entry : spawns) {
                std::cout << "Spawn group: " << entry.first << " with " << entry.second.size() << " points." << std::endl;
            }
        }

        if (equipamiento.empty()) {
            std::cout << "Equipamiento map is empty!" << std::endl;
        } else {
            std::cout << "Equipamiento map contains:" << std::endl;
            for (const auto& entry : equipamiento) {
                std::cout << "Path: " << entry.first << " with " << entry.second.size() << " points." << std::endl;
            }
        }

        if (cajas.empty()) {
            std::cout << "Cajas map is empty!" << std::endl;
        } else {
            std::cout << "Cajas map contains:" << std::endl;
            for (const auto& entry : cajas) {
                std::cout << "Caja group: " << entry.first << " with " << entry.second.size() << " points." << std::endl;
            }
        }

        // Print fondo if necessary
        std::cout << "Fondo: " << fondo << std::endl;
    }

    const std::string& getFondo() const { return fondo; };
    const std::map<std::string, std::vector<SDL_Point>>& getTiles() const { return tiles; };
    const std::map<std::string, std::vector<SDL_Point>>& getSpawns() const { return spawns; };
    const std::map<std::string, std::vector<SDL_Point>>& getEquipamiento() const { return equipamiento; };
    const std::map<std::string, std::vector<SDL_Point>>& getCajas() const { return cajas; };

    void set_fondo(const std::string& nuevoFondo) { fondo = nuevoFondo; };
    void set_tiles(const std::map<std::string, std::vector<SDL_Point>>& nuevosTiles) { tiles = nuevosTiles; };
    void set_spawns(const std::map<std::string, std::vector<SDL_Point>>& nuevosSpawns) { spawns = nuevosSpawns; };
    void set_equipamiento(const std::map<std::string, std::vector<SDL_Point>>& nuevoEquipamiento) { equipamiento = nuevoEquipamiento; };
    void set_cajas(const std::map<std::string, std::vector<SDL_Point>>& nuevasCajas) { cajas = nuevasCajas; };
    bool esta_procesado() {return mapa_procesado;};
};

#endif
