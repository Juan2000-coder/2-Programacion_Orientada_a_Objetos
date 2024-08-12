#include "Tanque.h"
#include <cmath>
#include <vector>

Tanque::Tanque(float hSensorBajo, float hSensorAlto, int A, int B, int C){
    this->altura = 20.8;
    this->diametro = 35.7;
    this->hSensor = {hSensorBajo, hSensorAlto};
    this->cota = 0.5; // Nivel inicial
    this->estadoSensor = {getEstadoSensor(0), getEstadoSensor(1)}; //El de nivel bajo se activa
    
    for (int id = 1; id <= 4; id++){
        this->electrovalvulas.push_back(Electrovalvula(id, A, B, C));
    }
    this->seccionTransversal = double(M_PI)*pow(this->diametro, 2)/4;
}
bool Tanque::getEstadoSensor(int i) const{
    switch(i){
        case 0:
            return (this->cota <= this->hSensor[i]);
        case 1:
            return (this->cota >= this->hSensor[i]);
        default:
            throw TanqueEx(1);
    }
}
const char* TanqueEx::what() const throw(){
    switch (this->source){
        case 1:
            return "Indice de vector de alturas de sensores fuera de rango. Modulo Tanque.";
        default:
            return "Error en Modulo Tanque.";
    }
}
float Tanque::getAltura() const{
    return this->altura;
}
float Tanque::getDiametro() const{
    return this->diametro;
}
float Tanque::getHSensor(int i) const{ 
    return this->hSensor[i];
}
const Electrovalvula& Tanque::getElectrovalvula(int id) const{
    return this->electrovalvulas.at(id);
}
void Tanque::actualizarCota(int t){
    float caudalEntradaNeto = 0.0;
    float cambioCota = 0.0;

    for (int id = 1; id <= 4; id++){ //Determinación del caudal neto entrante.
        if ((id == 1) || (id == 2)){
            caudalEntradaNeto += this->electrovalvulas.at(id).getCaudal(t);
        }
        else {
            caudalEntradaNeto -= this->electrovalvulas.at(id).getCaudal(t);
        }
    }
    cambioCota = caudalEntradaNeto/this->seccionTransversal;
    if ((this->cota + cambioCota) <= 0){
        this->cota = 0.0;           // En caso de salida de rango por debajo se asume 0.0.
    }
    else if (this->cota + cambioCota >= this->altura){
        this->cota = altura;        // En caso de salida de rango por encima se suma el tope.
    }
    else{
        this->cota += cambioCota;   // En otro caso se asuma el cambio de cota calculado.
    }
}
void Tanque::actualizarEstadosSensores(int t){
    if (this->cota <= this->hSensor.at(1)){
        this->estadoSensor.at(1) = true;
    }
    else{
        this->estadoSensor.at(1) = false;
        if (this->cota >= this->hSensor.at(2)){
            this->estadoSensor.at(2) = true;
        }
        else{
            this->estadoSensor.at(2) = false;
        }
    }
}