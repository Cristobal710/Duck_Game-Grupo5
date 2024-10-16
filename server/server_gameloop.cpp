#include "server_gameloop.h"

#define CAJA_NUEVA "A new box has appeared"

#define BAZOOKA_NUEVA 15
#define CHAINSAW_NUEVA 5
#define DEATH_RAY_NUEVA 20
#define SHOTGUN_NUEVA 10

#define BAZOOKA "Bazooka"
#define CHAINSAW "Chainsaw"
#define DEATH_RAY "Death ray"
#define SHOTGUN "Shotgun"

GameLoop::GameLoop(Queue<std::string>& cola_pedidos, bool* conexion):
        mapa(), clientes(mapa), cola_pedidos(cola_pedidos), esta_cerrado(conexion) {}

void GameLoop::sleep_a_little() {
    auto milliseconds_to_sleep = std::chrono::milliseconds(200);
    std::this_thread::sleep_for(milliseconds_to_sleep);
}
void GameLoop::cerrar_gameloop() {
    cola_pedidos.close();
    clientes.cerrar_gameloop();
    _is_alive = false;
}

void GameLoop::eliminar_clientes_cerrados() { clientes.eliminar_clientes_cerrados(); }

void GameLoop::agregar_cliente(ServerClient& cliente, Queue<std::string>& cola_cliente) {
    clientes.agregar_cliente(cliente, cola_cliente);
}

void GameLoop::sumar_iteracion(bool caja_disponible, int& contador_caja) {
    if (!caja_disponible) {
        contador_caja++;
    }
}

void GameLoop::agregar_caja_nueva(int& contador, int caja_nueva, bool& caja_disponible) {
    if (contador >= caja_nueva) {
        clientes.enviar_mensajes_clientes(CAJA_NUEVA);
        std::cout << CAJA_NUEVA << std::endl;
        contador = 0;
        caja_disponible = true;
    }
}

void GameLoop::manejo_mensaje(std::string mensaje, bool& bazooka_disponible) {
    bazooka_disponible = false;
    clientes.enviar_mensajes_clientes(mensaje);
    std::cout << mensaje << std::endl;
}

void GameLoop::elegir_caja(std::string mensaje, bool& bazooka_disponible, bool& chainsaw_disponible,
                           bool& death_ray_disponible, bool& shotgun_disponible) {
    if (!mensaje.empty()) {
        if ((mensaje.find(BAZOOKA) != std::string::npos) && bazooka_disponible) {
            manejo_mensaje(mensaje, bazooka_disponible);
        } else if ((mensaje.find(CHAINSAW) != std::string::npos) && chainsaw_disponible) {
            manejo_mensaje(mensaje, chainsaw_disponible);
        } else if ((mensaje.find(DEATH_RAY) != std::string::npos) && death_ray_disponible) {
            manejo_mensaje(mensaje, death_ray_disponible);
        } else if ((mensaje.find(SHOTGUN) != std::string::npos) && shotgun_disponible) {
            manejo_mensaje(mensaje, shotgun_disponible);
        }
    }
}

void GameLoop::run() {

    int contador_bazooka = 0;
    int contador_chainsaw = 0;
    int contador_death_ray = 0;
    int contador_shotgun = 0;

    bool bazooka_disponible = true;
    bool chainsaw_disponible = true;
    bool death_ray_disponible = true;
    bool shotgun_disponible = true;

    while (!(*esta_cerrado)) {
        eliminar_clientes_cerrados();

        sumar_iteracion(bazooka_disponible, contador_bazooka);
        sumar_iteracion(chainsaw_disponible, contador_chainsaw);
        sumar_iteracion(death_ray_disponible, contador_death_ray);
        sumar_iteracion(shotgun_disponible, contador_shotgun);

        std::string mensaje;
        while (cola_pedidos.try_pop(mensaje)) {
            elegir_caja(mensaje, bazooka_disponible, chainsaw_disponible, death_ray_disponible,
                        shotgun_disponible);
            mensaje.clear();
        }

        agregar_caja_nueva(contador_bazooka, BAZOOKA_NUEVA, bazooka_disponible);
        agregar_caja_nueva(contador_chainsaw, CHAINSAW_NUEVA, chainsaw_disponible);
        agregar_caja_nueva(contador_death_ray, DEATH_RAY_NUEVA, death_ray_disponible);
        agregar_caja_nueva(contador_shotgun, SHOTGUN_NUEVA, shotgun_disponible);

        sleep_a_little();
    }

    cerrar_gameloop();
}
