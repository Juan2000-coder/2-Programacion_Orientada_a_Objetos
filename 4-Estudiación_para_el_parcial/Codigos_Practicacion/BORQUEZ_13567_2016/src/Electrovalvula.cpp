#include "Electrovalvula.h"
#include <cmath>
#include <cstdlib>
#include <ctime>

int Electrovalvula::getId() const{
    return this->Id;

}
int Electrovalvula::getQcero() const{
    return this->cantQcero;
}
float Electrovalvula::getCaudal(int t){
    float caudalAuxiliar;
    srand(t); //De esta manera el número aleatorio que se genera es único para cada t.
    switch (this->Id){
        case 1:
            if (this->estado){
                caudalAuxiliar = 100 + 35*std::abs(this->A*std::sin(15*t));
                if (caudalAuxiliar == 0.0){
                    this->cantQcero += 1;
                }
                return caudalAuxiliar;
            }
            else{
                this->cantQcero += 1;
                return 0.0;
            }
        case 2:
            if (this->estado){
                caudalAuxiliar = 100 + 45*std::abs(this->B*std::cos(10*t));
                if (caudalAuxiliar == 0.0){
                    this->cantQcero += 1;
                }
                return caudalAuxiliar;
            }
            else{
                this->cantQcero += 1;
                return 0.0;
            }
        case 3:
            if (this->estado){
                caudalAuxiliar = 10 + C*(std::rand()%static_cast<int>(this->C*1.1));
                if (caudalAuxiliar == 0.0){
                    this->cantQcero += 1;
                }
                return caudalAuxiliar;
            }
            else{
                this->cantQcero += 1;
                return 0.0;
            }
        case 4:
            if (this->estado){
                caudalAuxiliar = 10 + C*(std::rand()%static_cast<int>(this->C*1.1));
                if (caudalAuxiliar == 0.0){
                    this->cantQcero += 1;
                }
                return caudalAuxiliar;
            }
            else{
                this->cantQcero += 1;
                return 0.0;
            }
        default:
            throw ElectrovalvulaEx(1);
    }
}
bool Electrovalvula::getEstado(void) const{
    return this->estado;
}
void Electrovalvula::setEstado(bool estado){
    this->estado = estado;
}
const char* ElectrovalvulaEx::what() const throw(){
    switch(this->source){
        case 1:
            return "Indice de vector fuera de rango en Módulo de Electroválvulas. Modulo Electrovalvulas.";
        default:
            return "Error en Modulo Electrovalvulas.";
    }
}