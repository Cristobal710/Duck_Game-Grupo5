#ifndef MODO_JUEGO_H
#define MODO_JUEGO_H
#include <chrono>
#include <map>
#include <string>
#include <vector>
#include "../common/common_thread.h"
#include "server_client.h"
#include "server_evento.h"
#include "queue_protegida.h"
#include "../common/common_arma.h"
#include <random>
#include "server_arma_config.h"
#include "puntaje.h"
class ModoJuego: public Thread {
    private:
    ServerClient& cliente;
    Queue<EventoServer>& queue_cliente;
    QueueProtegida broadcast;
    EstadoJuego ultimo_estado;
    uint8_t id_partida;
    std::list<ModoJuego*>& partidas_distintas;
    bool partida_nueva;
    std::list<ServerClient*> clientes;
    std::map<std::string, ArmaConfig> armamento_config;
    std::vector<ArmaConfig> armas_posibles;
    std::vector<std::string> mapas_disponibles;


    void procesar_evento_lobby(EventoServer& evento, bool& iniciar_partida);
    void drop_and_rest(float& tiempo_ultimo_frame);
    void ejecutar_accion_lobby(PedidoJugador& pedido, uint16_t id_jugador, bool& iniciar_partida);
    void buscar_partidas();
    void inicializar_patos(EstadoJuego& estado);
    void inicializar_cajas(EstadoJuego& estado);
    void inicializar_armas(EstadoJuego& estado);
    Arma elegir_arma_aleatoria(SDL_Point posicion_caja);
    Arma mapear_armas(ArmaConfig armamento, SDL_Point posicion_arma);
    void leer_configuracion(const std::string& archivo_yaml);
    std::string sortear_mapa();

    public:
    ModoJuego(ServerClient& cliente, Queue<EventoServer>& cola_cliente, Queue<EstadoJuego>& recibidos, uint8_t id,
    std::list<ModoJuego*>& partidas_distintas);
    void run() override;
    bool tiene_partida();
    uint8_t obtener_id_partida();
    bool tiene_id(uint8_t un_id);
    void nuevo_jugador(ServerClient* client);
    bool no_hay_ganador(std::vector<Puntaje>& puntaje_jugadores);
};



#endif

