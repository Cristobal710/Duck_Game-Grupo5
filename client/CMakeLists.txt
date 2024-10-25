target_sources(taller_client
    PRIVATE
    cliente_protocolo.cpp
    cliente_enviar.cpp
    fondo_interfaz.cpp
    interfaz_grafica.cpp
    pato_interfaz.cpp
    cliente_recibir.cpp
    cliente.cpp

    ../common/common_liberror.cpp 
    ../common/common_resolver.cpp
    ../common/common_resolvererror.cpp
    ../common/common_socket.cpp
    ../common/common_protocolo.cpp
    
    main.cpp

    PUBLIC

    cliente_protocolo.h
    cliente_comando.h
    cliente_enviar.h
    cliente_recibir.h
    cliente.h
    fondo_interfaz.h
    interfaz_grafica.h
    pato_interfaz.h
    
    ../common/common_liberror.h
    ../common/common_queue.h
    ../common/common_resolver.h
    ../common/common_resolvererror.h
    ../common/common_socket.h
    ../common/common_thread.h
    ../common/common_protocolo.h
    )
