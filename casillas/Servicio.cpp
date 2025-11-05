#include "Servicio.h"

Servicio CrearServicio (std::string nombre, int valor){

    Servicio s;
    s.name = nombre;
    s.value =valor;
    s.type = "Servicio";

}