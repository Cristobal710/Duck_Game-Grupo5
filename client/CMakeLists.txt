file(GLOB CLIENTE_SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp")
file(GLOB COMMON_SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/../common/*.cpp")

# Obtiene todos los archivos .h en el directorio del servidor y el directorio común
file(GLOB CLIENTE_HEADERS "${CMAKE_CURRENT_SOURCE_DIR}/*.h")
file(GLOB COMMON_HEADERS "${CMAKE_CURRENT_SOURCE_DIR}/../common/*.h")



target_sources(taller_client
    PRIVATE
    ${CLIENTE_SOURCES}
    ${COMMON_SOURCES}
    
    PUBLIC
    ${CLIENTE_HEADERS}
    ${COMMON_HEADERS}
)


 target_include_directories(taller_client
    PRIVATE
    ../common
 )