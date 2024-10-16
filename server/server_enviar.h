#ifndef SERVER_SENDER_H
#define SERVER_SENDER_H

#include <string>

#include "common_queue.h"
#include "common_socket.h"
#include "common_thread.h"
#include "server_protocolo.h"

class ServerEnviar: public Thread {
private:
    Socket& socket;
    Queue<std::string>& enviados;
    bool esta_cerrado;

public:
    ServerEnviar(Socket& skt, Queue<std::string>& enviados);
    void run() override;
};

#endif
