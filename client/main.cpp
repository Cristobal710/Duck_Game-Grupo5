#include "cliente.h"
#include "../common/common_socket.h"

int main(int argc, char* argv[]) {
    

    if (argc != 3){
        return -1;
    }

    Client cliente(argv[1] , argv[2]);
    cliente.start();

    std::string in;
    while (std::cin >> in, (in != "q")) {}

    cliente.stop();

    return 0;
}
