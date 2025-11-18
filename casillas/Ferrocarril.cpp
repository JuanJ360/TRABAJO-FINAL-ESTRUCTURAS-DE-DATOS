#include "Ferrocarril.h"

Ferrocarril CrearFerrocarril(std::string _nombre, int _valor, bool _hipotecada, int _alquiler[4]) {
    Ferrocarril p;
    p.tipo = "Ferrocarril";
    p.nombre = _nombre;
    p.valor = _valor;
    p.hipotecada = _hipotecada;
    for (int i = 0; i < 4; i++) {
        p.alquiler[i] = _alquiler[i];
    }
    return p;
}

int ValorFerrocarril(int nFerro) {
    if (nFerro < 1 || nFerro > 4) {
        throw std::invalid_argument("Ferrocarril: ValorFerrocarril: se espera que el numemro de ferrocarriles sea un numero entre 1 y 4");
    }

    return 25 * std::pow(2, nFerro - 1);
}