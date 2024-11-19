#!/bin/bash

# Install essential build tools (CMake, make)
sudo apt install -y build-essential cmake pkg-config

# Install SDL2 and related libraries
sudo apt install -y libsdl2-dev libsdl2-image-dev libsdl2-ttf-dev libsdl2-mixer-dev

# Check if everything was installed successfully
echo "Installation Complete!"

# Print the installed SDL2 libraries to verify installation
echo "Installed SDL2 Libraries:"
dpkg -l | grep sdl2

make -f Makefile

