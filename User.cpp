#include "User.h"

User CrearUsuario(std::string _name) {
    User user;
    user.nombre = _name;
    user.cash = 0;
    user.posicion = 0;
    user.contPares = 0;
    user.activo = true;
    user.cartaSalirDeLaCarcel = false;

    user.servicios = {};
    user.propiedades = {};
    user.ferrocarriles = {};

    return user;
}

User CambiarNombreUsuario(User user, std::string newName) {
    user.nombre = newName;
    return user;
}

User AumentarPosicion(User user, int aumento) {
    user.posicion += aumento;
    return user;
}

User GanarDinero(User user, int dinero) {
    user.cash += dinero;
    return user;
}

User PerderDinero(User user, int dinero) {
    user.cash -= dinero;
    return user;
}

User UsuarioEliminado(User user) {
    user.activo = false;
    return user;
}

User ResetContPares(User user) {
    user.contPares = 0;
    return user;
}

User AumentarContPares(User user) {
    user.contPares++;
    return user;
}

User GanarCartaSalirDeLaCarcel(User user) {
    user.cartaSalirDeLaCarcel = true;
    return user;
}

User GastarCartaSalirDeLaCarcel(User user) {
    user.cartaSalirDeLaCarcel = false;
    return user;
}
