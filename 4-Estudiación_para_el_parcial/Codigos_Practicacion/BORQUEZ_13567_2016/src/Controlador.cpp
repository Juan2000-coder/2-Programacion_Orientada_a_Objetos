#include "Controlador.h"
#include "Tanque.h"
#include "Electrovalvula.h"
#include <vector>

Controlador::Controlador(int _cantMediciones, int A, int B, int C, float hSensorAlta, float hSensorBaja){
    this->cantMediciones = _cantMediciones;
    this->tanque = new Tanque(hSensorAlta, hSensorBaja, A, B, C);
}
void Controlador::cicloControlador(int t){
    float valorMedido;
    this->mediciones.push_back(std::vector<Medicion>(4)); // Registro
    for (int id = 1; id <= 4; id++){
        const Electrovalvula& electrovalvulaTemp = this->tanque->getElectrovalvula(id); //Dependencia con electrovalvula
        valorMedido = electrovalvulaTemp.getCaudal(t);
        this->mediciones.at(t).push_back(Medicion(valorMedido, t, id));
    }
}
