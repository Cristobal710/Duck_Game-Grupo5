#!/bin/bash

# Salir inmediatamente si ocurre un error
set -e

# Actualizar los repositorios e instalar herramientas básicas
echo "Actualizando repositorios e instalando herramientas básicas..."
sudo apt-get update || { echo "Fallo al actualizar repositorios"; exit 1; }
sudo apt-get install -y make git gcc g++ python3 python3-pip python3-dev valgrind gdb bsdmainutils diffutils manpages-dev build-essential strace unzip cppcheck curl || { echo "Fallo al instalar herramientas básicas"; exit 1; }

# Instalar dependencias específicas para SDL
echo "Instalando dependencias específicas para SDL..."
sudo apt-get install -y libjpeg-dev libpng-dev libfreetype-dev libopusfile-dev libflac-dev libxmp-dev libfluidsynth-dev libwavpack-dev cmake libmodplug-dev libsdl2-dev || { echo "Fallo al instalar dependencias de SDL"; exit 1; }

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

    echo "Descargando $url..."
    curl -L -o "$temp_dir/library.zip" "$url" || { echo "Fallo al descargar $url"; exit 1; }

    echo "Descomprimiendo..."
    unzip -q "$temp_dir/library.zip" -d "$temp_dir" || { echo "Fallo al descomprimir $url"; exit 1; }

    TARGET_DIR=$(find "$temp_dir" -mindepth 1 -maxdepth 1 -type d | head -n 1)
    if [[ -z "$TARGET_DIR" ]]; then
        echo "Error: No se encontró el directorio descomprimido para $url."
        exit 1
    fi

    echo "Cambiando al directorio $TARGET_DIR..."
    cd "$TARGET_DIR" || exit 1

    echo "Compilando e instalando..."
    mkdir -p build
    cd build
    cmake .. || { echo "Fallo en cmake para $url"; exit 1; }
    make -j$(nproc) || { echo "Fallo en make para $url"; exit 1; }
    sudo make install || { echo "Fallo en make install para $url"; exit 1; }
}

# Función para clonar, compilar e instalar desde un repositorio git
install_git_library() {
    local repo_url=$1
    local temp_dir=$2

    echo "Clonando $repo_url..."
    git clone "$repo_url" "$temp_dir/repo" || { echo "Fallo al clonar $repo_url"; exit 1; }

    cd "$temp_dir/repo" || exit 1

    echo "Compilando e instalando..."
    mkdir -p build
    cd build
    cmake .. || { echo "Fallo en cmake para $repo_url"; exit 1; }
    make -j$(nproc) || { echo "Fallo en make para $repo_url"; exit 1; }
    sudo make install || { echo "Fallo en make install para $repo_url"; exit 1; }
}

# Instalar las librerías SDL2
install_sdl_library "$SDL2_IMAGE_URL" "$TEMP_DIR"
install_sdl_library "$SDL2_MIXER_URL" "$TEMP_DIR"
install_sdl_library "$SDL2_TTF_URL" "$TEMP_DIR"

# Instalar libSDL2pp
install_git_library "$SDL2PP_REPO_URL" "$TEMP_DIR"

# Limpiar directorio temporal
echo "Limpiando directorio temporal..."
if [[ -d "$TEMP_DIR" ]]; then
    rm -rf "$TEMP_DIR"
else
    echo "Directorio temporal ya eliminado o inexistente."
fi

echo "Instalación completada."

# Verificación final
echo "Verificando las bibliotecas instaladas..."
ls /usr/local/lib | grep SDL2 || echo "Algunas bibliotecas SDL2 podrían no estar instaladas correctamente."

