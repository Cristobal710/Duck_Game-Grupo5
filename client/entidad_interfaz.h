#ifndef ENTIDAD_INTERFAZ_H
#define ENTIDAD_INTERFAZ_H

class EntidadInterfaz {


    public:
    virtual ~EntidadInterfaz() = default;

    virtual void dibujar(int it, float zoom_factor) = 0;
}
;


#endif
