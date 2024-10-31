#include "cliente.h"

#include <cstring>
#include <iostream>
#include <map>
#include <string>

#include <arpa/inet.h>

#define QUIT "Exit"
#define PICKUP "Pickup"
#define READ "Read"

Client::Client(const char* hostname, const char* servname): socket(hostname, servname) {}

void Client::run() {

    Queue<ComandoGrafica> cola_eventos;
    Queue<EstadoJuego> cola_estado_juego;

    ClientEnviar enviarComandos(socket, cola_eventos);
    ClienteRecibir recibirComandos(socket, cola_estado_juego);

    
    enviarComandos.start();
    recibirComandos.start();

    InterfazGrafica interfaz = InterfazGrafica(cola_eventos, cola_estado_juego);
    interfaz.iniciar();
    
    
    std::string in;
    while (std::cin >> in, (in != "q")) {}

    enviarComandos.join();
    enviarComandos.stop();
    recibirComandos.join();
    recibirComandos.stop();
}
