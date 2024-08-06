#include "Dron.h"

Dron::Dron(int _id){
    this->id = _id;
    this->alturaMaxima = 50.0; //metros
    this->velocidadMaxima = 40.0; //km/h
    this->cantRegistros = 0;
}
void Dron::addRegistro(void){
    srand(static_cast<unsigned int>(std::time(nullptr)));

    float _altura = static_cast<float>(std::rand())*this->alturaMaxima/RAND_MAX;
    float _velocidad = static_cast<float>(std::rand())*this->velocidadMaxima/RAND_MAX;
    std::time_t _tiempo;
    std::time(&_tiempo);

    char _direccion;
    switch(1 + std::rand()%4){
        case 1:
            _direccion = 'E';break;
        case 2:
            _direccion = 'N';break;
        case 3:
            _direccion = 'O';break;
        case 4:
            _direccion = 'S';break;
    }

    this->registros.push_back(Registro(_altura, _velocidad, _tiempo, _direccion));
    this->cantRegistros++;
}
Registro Dron::getRegistro(int i){

    return this->registros.at(i-1);
}
int Dron::getId(void){
    return this->id;
}
int Dron::getCantRegistros(void){
    return this->cantRegistros;
}
std::vector<Registro>& Dron::getRegistros(void){
    return this->registros;
}