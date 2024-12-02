#ifndef SERVER_GAMELOOP_H
#define SERVER_GAMELOOP_H

#include <chrono>
#include <map>
#include <string>
#include <vector>
#include <yaml-cpp/yaml.h>


#include "../common/common_mapa.h"
#include "server_lector_json.h"
#include "../common/common_estado_juego.h"
#include "../common/common_queue.h"
#include "../common/common_thread.h" 
#include "../common/common_tipo_proteccion.h"

#include "../common/common_ak47.h"
#include "../common/common_escopeta.h"
#include "../common/common_laserrifle.h"
#include "../common/common_magnum.h"
#include "../common/common_pistolacowboy.h"
#include "../common/common_pistoladuelos.h"
#include "../common/common_pewpewlaser.h"
#include "../common/common_sniper.h"
#include "common/common_tile.h"
#include "server_client.h"
#include "server_evento.h"
#include "server_arma_config.h"
#include "server_proteger_clientes.h"
#include "../common/common_tipo_colision.h"
#include "queue_protegida.h"


#define RUTA_CONFIGURACION "../resources/config.yaml"

class GameLoop: public Thread {
private:
    ClientesProtegidos clientes;
    bool* esta_cerrado;
    EstadoJuego ultimo_estado;
    std::vector<Tile> colisiones;
    uint16_t id_ultimo_jugador;
    uint8_t id_partida;
    std::map<uint16_t, Queue<EstadoJuego>*>* mapa_jugadores;
    std::map<std::string, ArmaConfig> armamento_config;
    std::vector<ArmaConfig> armas_posibles;
    // void eliminar_clientes_cerrados();
    // void cerrar_gameloop();
    void inicializar_juego();
    void inicializar_cajas();
    void inicializar_patos();
    void inicializar_armas();
    void ejecutar_accion(uint8_t accion, Pato& pato);
    void enviar_estado_juego_si_cambio( EstadoJuego& estado_juego);
    void avanzar_balas();
    void continuar_saltando_patos();
    void frenar_saltos_patos_si_colisionan();
    void drop_and_rest(float& tiempo_ultimo_frame);
    void aplicar_logica();
    void avanzar_balas_direccion_izquierda(std::__cxx11::list<Bala>::iterator& it);
    void avanzar_balas_direccion_derecha(std::__cxx11::list<Bala>::iterator& it);
    void avanzar_balas_direccion_arriba(std::__cxx11::list<Bala>::iterator& it);
    void eliminar_balas_fuera_de_alcance(std::__cxx11::list<Bala>::iterator& it);
    void calcular_colisiones_tiles(Mapa mapa);
    void crear_bala(Pato& pato);
    void actualizar_hitbox_entidades();
    void aplicar_gravedad();
    void aplicar_estados();
    void calcular_colisiones_balas();
    void eliminar_patos_muertos();
    bool validar_movimiento(Pato& pato, TipoColision tipo_colision);
    void eliminar_balas_si_colisionan(std::__cxx11::list<Bala>::iterator& it);
    void agarrar_recompensa(Pato& pato);
    Arma elegir_arma_aleatoria(SDL_Point posicion_caja);
    void leer_configuracion(const std::string& archivo_yaml);
    Arma mapear_armas(ArmaConfig armamento, SDL_Point posicion_arma);

public:
    GameLoop(std::map<uint16_t, Queue<EstadoJuego>*>* mapa_jugadores,
             bool* conexion, uint8_t id);
    void procesar_evento(EventoServer& evento, EstadoJuego& cola_estados_juego);
    int get_indice_por_id(uint8_t id);
    void agregar_cliente(ServerClient& cliente, Queue<EventoServer>& cola_cliente);
    void run() override;
    void mandar_id_cliente(uint16_t& id);
};

#endif