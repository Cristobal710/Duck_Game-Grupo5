#include "equipamiento_interfaz.h"

#define PIXEL_EQUIPAMIENTO 32

EquipamientoInterfaz::EquipamientoInterfaz(SDL2pp::Surface& superficie, 
                const std::string& equipamiento_path, int pos_x, int pos_y)
    : superficie(superficie),
    equipamiento_surface(IMG_Load(equipamiento_path.c_str())),
    equipamiento(),
    rect_inicio_equipamiento(0, 0, PIXEL_EQUIPAMIENTO, PIXEL_EQUIPAMIENTO),
    rect_dibujado_equipamiento(pos_x, pos_y, PIXEL_EQUIPAMIENTO, PIXEL_EQUIPAMIENTO),
    recogido(false)
{
    cargar_frames(equipamiento_surface, 1, equipamiento, 0, 0, PIXEL_EQUIPAMIENTO, PIXEL_EQUIPAMIENTO);
}

void EquipamientoInterfaz::dibujar(){
    if (!recogido){
        SDL_BlitScaled(equipamiento[0].Get(), &rect_inicio_equipamiento, superficie.Get(), &rect_dibujado_equipamiento);    
    }    
}

void EquipamientoInterfaz::no_dibujar(){
    recogido = true;
}

bool EquipamientoInterfaz::mismo_equip(int x, int y) {
    if (x == rect_dibujado_equipamiento.x && y == rect_dibujado_equipamiento.y){
        return true;
    }
    return false;
}
