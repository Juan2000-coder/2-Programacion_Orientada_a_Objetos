#include "Registro.h"
Registro::Registro(float _altura, float _velocidad, time_t _tiempo, char _direccion){
    this->altura = _altura;
    this->velocidad = _velocidad;
    this->tiempo = _tiempo;
    this->direccion = _direccion;
}
float Registro::getAltura(void){
    return this->altura;
}
float Registro::getVelocidad(void){
    return this->velocidad;
}
std::time_t Registro::getTime(void){
    return this->tiempo;
}
char Registro::getDireccion(void){
    return this->direccion;
}