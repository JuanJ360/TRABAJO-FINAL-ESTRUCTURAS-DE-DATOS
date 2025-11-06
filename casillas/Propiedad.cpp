#include "Propiedad.h"

Propiedad CrearPropiedad(std::string nombre, std::string subType, std::string color, bool hipoteca, int valor, int alquiler[6]) {
    Propiedad p;
    p.type = "Propiedad";
    p.name = nombre;
    p.subType = subType;
    p.color = color;
    p.value = valor;
    p.hipotecada = hipoteca;
    for (int i = 0; i < 6; ++i) {
        p.alquiler[i] = alquiler[i];
    }
    return p;
}