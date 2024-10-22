#include "server_protocolo.h"

#define EXITO 0
#define ERROR 1

ServerProtocolo::ServerProtocolo(Socket& skt): Protocolo(skt) {}

Comando ServerProtocolo::recibir_comando() {
    bool cerrado;
    Comando comando;
    comando.comando = recibir_byte(cerrado);
    comando.accion = recibir_byte(cerrado);
    comando.jugador_id = recibir_byte(cerrado);
    return comando;
}
