# Manual de Usuario

##### Sistema Operativo Minimo Requerido

Ubuntu 20.04 Focal Fossa (o en su versión más ligera Xubuntu 20.04)

##### Instalaciones y dependencias necesarias

```
$ sudo apt-get update
$ sudo apt-get install              \
            make                    \
            git                     \
            gcc                     \
            g++                     \
            python3                 \
            python3-pip             \
            python3-dev             \
            valgrind                \
            gdb                     \
            bsdmainutils            \
            diffutils               \
            manpages-dev            \
            build-essential         \
            strace                  \
            unzip                   \
            cppcheck
```
Luego de debera instalar SDL2 y todas sus dependencias necesarias de la siguiente manera:

1. Instalar dependencias que van a necesitar desde apt-get

```
sudo apt-get install libjpeg-dev libpng-dev libfreetype-dev libopusfile-dev libflac-dev libxmp-dev libfluidsynth-dev libwavpack-dev cmake libmodplug-dev libsdl2-dev
```
2. Bajarse los archivos .zip de estos repositorios:
libsdl2-image ( 2.6.3, https://github.com/libsdl-org/SDL_image/releases/tag/release-2.6.3)
libsdl2-mixer (2.6.3, https://github.com/libsdl-org/SDL_mixer/releases/tag/release-2.6.3)  
libsdl2-ttf (2.20.2, https://github.com/libsdl-org/SDL_ttf/releases/tag/release-2.20.2) 

y unzipearlos con 

```
unzip <nombre_de_la_carpeta>
```

3. Luego, para cada una de las tres carpetas compilarlas e instalarlas:

```
cd carpeta_sdl_x
mkdir build
cd build
cmake ..
make -j4
sudo make install #importante que hagan esto como sudo!
```

4. Luego compilar e instalar libsdl2pp (https://github.com/libSDL2pp/libSDL2pp)

```
cd libSDL2pp-0.18.1
mkdir build
cd build
cmake ..
make -j4
sudo make install #importante que hagan esto como sudo!
```

##### Compilacion del programa

El programa se compila corriendo:

```
make -f Makefile
```

