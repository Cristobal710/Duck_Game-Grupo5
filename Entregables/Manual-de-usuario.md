# Manual de Usuario

##### Sistema Operativo Minimo Requerido

Ubuntu 20.04 Focal Fossa (o en su versión más ligera Xubuntu 20.04)

##### Instalaciones y dependencias necesarias

```
sudo apt-get install -y make git gcc g++ python3 python3-pip python3-dev valgrind gdb bsdmainutils diffutils manpages-dev build-essential strace unzip cppcheck

```

##### Clonar repositorio
Clonar el repositorio con el comando 
```
git clone https://github.com/Cristobal710/Duck_Game-Grupo5.git
```


##### Instalacion de dependencias y librerias restantes y compilacion del programa 
Luego de deberan instalar las dependencias y librerias restantes corriendo el script de la siguiente forma:

1. correr el siguiente comando: 

```
chmod +x install_dependencies.sh

```
2. y luego correr: 

```
sudo ./install_dependencies.sh

```

##### Jugar 

1. ingresar a la carpeta build con el comando: 

```
cd build/

```

2. levantar el servidor con el comando: 

```
./taller_server 8080

```

3. conectarse con un cliente con el comando: 

```
./taller_client localhost 8080

```

##### Editar niveles

1. ingresar a la carpeta build con el comando: 

```
cd build/

```

2. correr el comando: 

```
./taller_editor

```





*Una vez terminado el mapa que se desea crear, escribir en consola el nombre con el que sera guardado, e inmediatamente ingresara a la pool de mapas disponibles*
