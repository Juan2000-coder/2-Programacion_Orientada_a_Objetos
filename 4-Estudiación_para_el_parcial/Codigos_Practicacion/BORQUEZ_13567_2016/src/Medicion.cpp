#include "Medicion.h"

Medicion::Medicion(float medicion, int instante, int idElectrovalvula){
    this->medicion = medicion;
    this->instante = instante;
    this->idElectrovalvula = idElectrovalvula;
}
int Medicion::getIdElectrovalvula(void){
    return this->idElectrovalvula;
}
int Medicion::getInstanteCaudal(void){
    return this->instante;
}