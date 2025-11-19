#include "CartaArcaComunal.h"

CartaArcaComunal CrearCartaArcaComunal(std::string _tipo, std::string _nombre, std::string _mensaje) {
    CartaArcaComunal cac;
    cac.tipo = _tipo;
    cac.nombre = _nombre;
    cac.mensaje = _mensaje;
    return cac;
}


std::queue<CartaArcaComunal> GenerarColaCartasArcaComunal() {
    std::vector<CartaArcaComunal> cacVector;
    std::ifstream archivo("viernes13/CartasArcaComunal.json");
    if (archivo.is_open()) {
        json j;
        archivo >> j;
        int i;
        for (i = 0; i < j.size(); i++) {
            cacVector.push_back(CrearCartaArcaComunal(j[i]["tipo"], j[i]["nombre"], j[i]["mensaje"]));
        }
        std::random_device rd; 
        std::mt19937 gen(rd());
        std::shuffle(cacVector.begin(), cacVector.end(), gen);

        std::queue<CartaArcaComunal> ans;
        for (i = 0; i < cacVector.size(); i++) {
            ans.push(cacVector[i]);
        }

        return ans;
    }
    else {
        throw std::runtime_error("GenerarColaCartasSuerte: El archivo json no se ha abierto correctamente");
    }
}