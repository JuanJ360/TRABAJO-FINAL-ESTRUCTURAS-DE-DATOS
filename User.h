#ifndef USER_H
#define USER_H

#include <string>
#include <vector>
#include "cartas/CartaSuerte.h"
#include "./casillas/Propiedad.h" 
#include "./casillas/Servicio.h"
#include "./casillas/Ferrocarril.h"

struct User {
    std::string nombre;
    int cash;
    int posicion;
    int contPares;
    bool activo;
    bool cartaSalirDeLaCarcel;

    //inventarios
    std::vector<Servicio> servicios;
    std::vector<Propiedad> propiedades;
    std::vector<Ferrocarril> ferrocarriles;
};

User CrearUsuario(std::string);
User CambiarNombreUsuario(User, std::string);
User AumentarPosicion(User, int);
User GanarDinero(User, int);
User PerderDinero(User, int);
User UsuarioEliminado(User);
User ResetContPares(User);
User AumentarContPares(User);
User GanarCartaSalirDeLaCarcel(User);
User GastarCartaSalirDeLaCarcel(User);

#endif
