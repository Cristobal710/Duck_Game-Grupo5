target_sources(taller_server
    PRIVATE
    server_.cpp
    server_accepter.cpp
    server_client.cpp
    server_enviar.cpp
    server_gameloop.cpp
    server_proteger_clientes.cpp
    server_protocolo.cpp
    server_lector_json.cpp
    modo_juego.cpp
    
    ../common/common_liberror.cpp 
    ../common/common_resolver.cpp
    ../common/common_resolvererror.cpp
    ../common/common_socket.cpp
    ../common/common_protocolo.cpp
    ../common/common_hitbox.cpp

    main.cpp

    PUBLIC
    server_.h
    server_accepter.h
    server_client.h
    server_enviar.h
    server_gameloop.h
    server_proteger_clientes.h
    server_protocolo.h
    server_lector_json.h
    modo_juego.h

    ../common/common_liberror.h
    ../common/common_queue.h
    ../common/common_resolver.h
    ../common/common_resolvererror.h
    ../common/common_socket.h
    ../common/common_thread.h
    ../common/common_protocolo.h

    )

    target_include_directories(taller_server
    PRIVATE
    ../common
)
    