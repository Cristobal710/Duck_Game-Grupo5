#include "server_.h"

#define EXITO 0

Server::Server(const char* servname): socket_aceptador(servname), esta_cerrado(false) {}

void Server::cerrar(Accepter& aceptador) {
    socket_aceptador.shutdown(2);
    esta_cerrado = true;
    aceptador.join();
}

int Server::run() {

    Accepter aceptador(socket_aceptador, &esta_cerrado);
    aceptador.start();

    std::string in;
    while (std::cin >> in, (in != "q")) {}

    cerrar(aceptador);
    return EXITO;
}
