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

#include "server_client.h"
#include "server_evento.h"
#include "server_arma_config.h"
#include "server_proteger_clientes.h"
#include "common/common_tile.h"
#include "../common/common_tipo_colision.h"


#define RUTA_CONFIGURACION "../resources/config.yaml"

class GameLoop: public Thread {
private:
    std::map<ServerClient*, Queue<EventoServer>*> mapa_clientes;
    ClientesProtegidos clientes;
    Queue<EstadoJuego>& cola_estados_juego;
    bool* esta_cerrado;
    EstadoJuego ultimo_estado;
    std::vector<Tile> colisiones;
    std::map<std::string, ArmaConfig> armamento_config;


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


    void leer_configuracion(const std::string& archivo_yaml);
    uint8_t mapear_armas(ArmaConfig armamento);

public:
    GameLoop(Queue<EstadoJuego>& cola_estados_juego,
             bool* conexion);
    void procesar_evento(EventoServer& evento, EstadoJuego& cola_estados_juego);
    int get_indice_por_id(uint8_t id);
    void agregar_cliente(ServerClient& cliente, Queue<EventoServer>& cola_cliente);
    void run() override;
};

#endif