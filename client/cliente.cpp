#include "cliente.h"

#include <cstring>
#include <iostream>
#include <map>
#include <string>

#include <arpa/inet.h>

#define QUIT "Exit"
#define PICKUP "Pickup"
#define READ "Read"

Client::Client(Socket& client_socket): socket(client_socket) {}

void Client::run() {
    ClienteProtocolo protocolo(socket);
    Queue<std::string> cola_eventos;
    std::string commando;
    // interfaz.start();
    while (true) {
        std::getline(std::cin, commando);
        if (commando == "w") {
            cola_eventos.push(commando);
        } else if (commando == "s") {
            cola_eventos.push(commando);
        } else if (commando == "a") {
            cola_eventos.push(commando);
        } else if (commando == "d") {
            cola_eventos.push(commando);
        }
        // bool hay_comando = true;
        // while(hay_comando){
        //     hay_comando = cola_eventos.try_pop();
        //     //protocolo.
        // }
    }
}
