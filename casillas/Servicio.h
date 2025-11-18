#ifndef SERVICIO_H
#define SERVICIO_H

#include <string>
#include <stdexcept>

struct Servicio {
    std::string tipo;
    std::string nombre;
    int valor;
    int hipoteca;
};

// OPERACIONES
Servicio CrearServicio(std::string, int, int);
int ValorRentaServicio(int, int); // recibe tirada de dados que llevó al jugador a esa casilla y cantidad de Servicios Públicos que posea el dueño.
int MultDadoServicio(int ns); // recibe numero de servicios y devuelve el multiplicador de la tirada del dado correspondiente

#endif