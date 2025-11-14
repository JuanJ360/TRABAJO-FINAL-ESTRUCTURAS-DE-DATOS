#ifndef USER_H
#define USER_H

#include <string>
#include <vector>
#include "cartas/CartaSuerte.h"

struct User {
    std::string name;
    int cash;
    int posicion;
    int contPares; // contador de numeros de pares
    bool activo; // representa si el jugador puede seguir jugando o ya ha perdido
    std::vector<CartaSuerte> cartas;
};


User CrearUsuario(std::string);
User CambiarNombreUsuario(User, std::string);
User AumentarSumSados(User, int);
User GanarDinero(User, int);
User PerderDinero(User, int);
User UsuarioEliminado(User);
User ResetContPares(User);
User AumentarContPares(User);

#endif