#include "Ferrocarril.h"

Ferrocarril CrearFerrocarril(std::string nombre) {
    Ferrocarril p;
    p.name = nombre;
    p.type = "Ferrocarril";
    
    return p;
}
