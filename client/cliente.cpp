#include "cliente.h"

#include <cstring>
#include <iostream>
#include <map>
#include <string>

#include <arpa/inet.h>

#define QUIT "Exit"
#define PICKUP "Pickup"
#define READ "Read"

Client::Client(const char* hostname, const char* servname, std::atomic_bool& cerrar_programa): 
socket(hostname, servname), cerrar_programa(cerrar_programa)  {}

void Client::run() {

    Queue<ComandoGrafica> cola_eventos;
    Queue<EstadoJuego> cola_estado_juego;

    ClientEnviar enviarComandos(socket, cola_eventos);
    ClienteRecibir recibirComandos(socket, cola_estado_juego);

    
    enviarComandos.start();
    recibirComandos.start();

    InterfazGrafica interfaz = InterfazGrafica(cola_eventos, cola_estado_juego);
    interfaz.iniciar();
    //si sali de la interfaz es porque se termino el juego, hay que cerrar todo
    cola_eventos.close();
    cola_estado_juego.close();
    enviarComandos.join();
    enviarComandos.stop();
    recibirComandos.join();
    recibirComandos.stop();

    cerrar_programa = true;
}
