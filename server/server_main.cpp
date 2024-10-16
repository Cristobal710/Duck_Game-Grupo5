#include "server_.h"

#define EXITO 0
#define ERROR 1

int main(int argc, char* argv[]) {
    int ret = EXITO;
    if (argc != 2) {
        return ERROR;
    }

    Server server(argv[1]);
    ret = server.run();

    return ret;
}
