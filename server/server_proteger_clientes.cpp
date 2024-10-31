#include "server_proteger_clientes.h"

ClientesProtegidos::ClientesProtegidos(std::map<ServerClient*, Queue<EventoServer>*>& mapa_clientes):
        clientes(mapa_clientes) {}

void ClientesProtegidos::agregar_cliente(ServerClient& cliente, Queue<EventoServer>& enviados) {
    std::lock_guard<std::mutex> lock(mutex);
    clientes[(&cliente)] = &enviados;
}


std::vector<EventoServer> ClientesProtegidos::recibir_mensajes_clientes() {
    std::vector<EventoServer> eventos;
    std::lock_guard<std::mutex> lock(mutex);
    if (!clientes.empty()) {
        for (const auto& cliente: clientes) {
            EventoServer evento;
            cliente.second->try_pop(evento);
            eventos.push_back(evento);
        }
    }
    return eventos;
}

void ClientesProtegidos::eliminar_clientes_cerrados() {
    std::lock_guard<std::mutex> lock(mutex);
    if (!clientes.empty()) {
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
    std::lock_guard<std::mutex> lock(mutex);
    if (!clientes.empty()) {
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
