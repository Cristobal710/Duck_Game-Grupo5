#!/bin/bash

sudo apt install -y make  gcc g++ python3 python3-pip python3-dev valgrind gdb bsdmainutils diffutils manpages-dev build-essential strace unzip cppcheck

# Install essential build tools (CMake, make)
sudo apt install -y build-essential cmake pkg-config

sudo apt-get install libjpeg-dev libpng-dev libfreetype-dev libopusfile-dev libflac-dev libxmp-dev libfluidsynth-dev libwavpack-dev cmake libmodplug-dev libsdl2-dev

# Download SDL_image release 2.6.3
echo "Downloading SDL_image 2.6.3..."
wget https://github.com/libsdl-org/SDL_image/releases/download/release-2.6.3/SDL_image-2.6.3.tar.gz
tar -xzf SDL_image-2.6.3.tar.gz
rm SDL_image-2.6.3.tar.gz

# Download SDL_mixer release 2.6.3
echo "Downloading SDL_mixer 2.6.3..."
wget https://github.com/libsdl-org/SDL_mixer/releases/download/release-2.6.3/SDL_mixer-2.6.3.tar.gz
tar -xzf SDL_mixer-2.6.3.tar.gz
rm SDL_mixer-2.6.3.tar.gz

# Download SDL_ttf release 2.20.2
echo "Downloading SDL_ttf 2.20.2..."
wget https://github.com/libsdl-org/SDL_ttf/releases/download/release-2.20.2/SDL_ttf-2.20.2.tar.gz
tar -xzf SDL_ttf-2.20.2.tar.gz
rm SDL_ttf-2.20.2.tar.gz

# Function to build and install a library
build_and_install() {
    local folder_name=$1
    echo "Building and installing $folder_name..."

    # Navigate to the folder
    cd $folder_name

    # Create build directory and move into it
    mkdir -p build
    cd build

    # Run cmake, make and install
    cmake ..
    make -j4
    sudo make install

    # Go back to the original directory
    cd ../..
}

# Build and install SDL_image
build_and_install SDL_image-2.6.3

# Build and install SDL_mixer
build_and_install SDL_mixer-2.6.3

# Build and install SDL_ttf
build_and_install SDL_ttf-2.20.2
# Check if everything was installed successfully
echo "Installation Complete!"

# Print the installed SDL2 libraries to verify installation
echo "Installed SDL2 Libraries:"
dpkg -l | grep sdl2

make -f Makefile

