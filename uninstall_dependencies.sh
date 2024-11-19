#!/bin/bash

# Uninstall SDL2 and related libraries
sudo apt remove --purge -y libsdl2-dev libsdl2-image-dev libsdl2-ttf-dev libsdl2-mixer-dev

# Uninstall the nlohmann JSON library
sudo apt remove --purge -y nlohmann-json3-dev

# Try to uninstall SDL2pp if installed
sudo apt remove --purge -y libsdl2pp-dev

# Optionally, remove unused dependencies (after uninstalling)
sudo apt autoremove -y

# Clean up any remaining package configuration files
sudo apt clean

# Check if the libraries were removed
echo "Checking removed libraries..."
dpkg -l | grep -E 'libsdl2|nlohmann-json|libsdl2pp'
