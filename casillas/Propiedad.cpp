#include "Propiedad.h"

Propiedad CrearPropiedad(std::string nombre, int valor, int alquiler, int ccc, int cch) {
    Propiedad p;
    p.type = "Propiedad";
    p.name = nombre;
    p.color = "";
    p.value = valor;
    p.alquiler = alquiler;
    p.costoConstruirCasa = ccc;
    p.flagCasa = false;
    p.costoConstruirHotel = cch;
    p.flagHotel = false;
    return p;
}
