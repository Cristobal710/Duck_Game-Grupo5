#!/bin/bash

# Actualizar los repositorios e instalar herramientas básicas
echo "Actualizando repositorios e instalando herramientas básicas..."
sudo apt-get update
sudo apt-get install -y make git gcc g++ python3 python3-pip python3-dev valgrind gdb bsdmainutils diffutils manpages-dev build-essential strace unzip cppcheck

# Instalar dependencias específicas para SDL
echo "Instalando dependencias específicas para SDL..."
sudo apt-get install -y libjpeg-dev libpng-dev libfreetype-dev libopusfile-dev libflac-dev libxmp-dev libfluidsynth-dev libwavpack-dev cmake libmodplug-dev libsdl2-dev

# Definir URLs de los archivos "Source code (zip)"
SDL2_IMAGE_URL="https://github.com/libsdl-org/SDL_image/archive/refs/tags/release-2.6.3.zip"
SDL2_MIXER_URL="https://github.com/libsdl-org/SDL_mixer/archive/refs/tags/release-2.6.3.zip"
SDL2_TTF_URL="https://github.com/libsdl-org/SDL_ttf/archive/refs/tags/release-2.20.2.zip"
SDL2PP_REPO_URL="https://github.com/libSDL2pp/libSDL2pp"

# Crear directorio temporal para descargar y compilar
TEMP_DIR=$(mktemp -d)
echo "Usando directorio temporal: $TEMP_DIR"

# Función para descargar, descomprimir, compilar e instalar desde un zip
install_sdl_library() {
    local url=$1
    local temp_dir=$2

    # Descargar archivo zip
    echo "Descargando $url..."
    curl -L -o "$temp_dir/library.zip" "$url"

    # Descomprimir
    echo "Descomprimiendo..."
    unzip -q "$temp_dir/library.zip" -d "$temp_dir"

    # Cambiar al directorio descomprimido
    cd "$temp_dir"/* || exit 1

    # Compilar e instalar
    echo "Compilando e instalando..."
    mkdir build
    cd build
    cmake ..
    make -j$(nproc)
    sudo make install
}

# Función para clonar, compilar e instalar desde un repositorio git
install_git_library() {
    local repo_url=$1
    local temp_dir=$2

    # Clonar repositorio
    echo "Clonando $repo_url..."
    git clone "$repo_url" "$temp_dir/repo"

    # Cambiar al directorio clonado
    cd "$temp_dir/repo" || exit 1

    # Compilar e instalar
    echo "Compilando e instalando..."
    mkdir build
    cd build
    cmake ..
    make -j$(nproc)
    sudo make install
}

# Instalar las librerías SDL2
install_sdl_library "$SDL2_IMAGE_URL" "$TEMP_DIR"
install_sdl_library "$SDL2_MIXER_URL" "$TEMP_DIR"
install_sdl_library "$SDL2_TTF_URL" "$TEMP_DIR"

# Instalar libSDL2pp
install_git_library "$SDL2PP_REPO_URL" "$TEMP_DIR"

# Limpiar directorio temporal
echo "Limpiando directorio temporal..."
rm -rf "$TEMP_DIR"

echo "Instalación completada."

