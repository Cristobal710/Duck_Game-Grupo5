
file(GLOB COMMON_SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp")

# Obtiene todos los archivos .h en el directorio del servidor y el directorio común
file(GLOB COMMON_HEADERS "${CMAKE_CURRENT_SOURCE_DIR}/*.h")

target_link_libraries(taller_common
    PRIVATE
    nlohmann_json::nlohmann_json
    SDL2pp::SDL2pp
)

target_sources(taller_common
    PRIVATE
    ${COMMON_SOURCES}
    
    PUBLIC
    ${COMMON_HEADERS}
)


target_include_directories(taller_common
    PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}  # This will include the current directory (common/)
)
    
