#include "CartaSuerte.h"

CartaSuerte CrearCartaSuerte(std::string _nombre, std::string _tipo, std::string _mensaje) {
    CartaSuerte cs;
    cs.nombre = _nombre;
    cs.tipo = _tipo;
    cs.mensaje = _mensaje;
    return cs;
}

std::queue<CartaSuerte> GenerarColaCartasSuerte() {
    std::vector<CartaSuerte> csVector;
    std::ifstream archivo("viernes13/CartasSuerte.json");
    if (archivo.is_open()) {
        json j;
        archivo >> j;
        int i;
        for (i = 0; i < j.size(); i++) {
            csVector.push_back(CrearCartaSuerte(j[i]["tipo"], j[i]["nombre"], j[i]["mensaje"]));
        }
        std::random_device rd; 
        std::mt19937 generador(rd());
        std::shuffle(csVector.begin(), csVector.end(), generador());

        std::queue<CartaSuerte> ans;
        for (i = 0; i < csVector.size(); i++) {
            ans.push(csVector[i]);
        }

        return ans;
    }
    else {
        throw std::runtime_error("GenerarColaCartasSuerte: El archivo json no se ha abierto correctamente");
    }
}