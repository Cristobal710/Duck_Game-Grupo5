#include "server_proteger_clientes.h"

ClientesProtegidos::ClientesProtegidos(std::map<ServerClient*, Queue<std::string>*>& mapa_clientes):
        clientes(mapa_clientes) {}

void ClientesProtegidos::agregar_cliente(ServerClient& cliente, Queue<std::string>& enviados) {
    std::lock_guard<std::mutex> lock(mutex);
    clientes[(&cliente)] = &enviados;
}

void ClientesProtegidos::enviar_mensajes_clientes(std::string mensaje) {
    if (!clientes.empty()) {
        std::lock_guard<std::mutex> lock(mutex);
        for (const auto& cliente: clientes) {
            cliente.second->try_push(mensaje);
        }
    }
}

void ClientesProtegidos::eliminar_clientes_cerrados() {
    if (!clientes.empty()) {
        std::unique_lock<std::mutex> lck(mutex);
        for (auto it = clientes.begin(); it != clientes.end();) {
            auto* cliente_actual = it->first;
            auto* queue_actual = it->second;

            if (!(cliente_actual->is_alive())) {
                try {
                    queue_actual->close();
                } catch (...) {}

                cliente_actual->join();
                delete queue_actual;
                delete cliente_actual;

                it = clientes.erase(it);
            } else {
                ++it;
            }

            if (clientes.empty()) {
                break;
            }
        }
    }
}

void ClientesProtegidos::cerrar_gameloop() {
    if (!clientes.empty()) {
        std::unique_lock<std::mutex> lck(mutex);
        for (const auto& cliente: clientes) {
            try {
                cliente.second->close();
            } catch (...) {}

            cliente.first->join();
            delete cliente.second;
            delete cliente.first;

            if (clientes.empty()) {
                break;
            }
        }
    }
}
