#include "cliente.h"
#include "../common/common_socket.h"

int main(int argc, char* argv[]) {
    

    if (argc != 3){
        return -1;
    }

    std::atomic_bool cerrar_programa = false;;

    Client cliente(argv[1] , argv[2], cerrar_programa);
    cliente.start();

    std::string in;
    while (!cerrar_programa) {
        std::this_thread::sleep_for(std::chrono::seconds(2));
    }

    cliente.join();
    cliente.stop();

    return 0;
}
