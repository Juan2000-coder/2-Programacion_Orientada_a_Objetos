#include <iostream>
using namespace std;

#include "C5Requeriment.h"
#include "C5Number.h"

C5Requeriment::C5Requeriment(int userId, long initialTime) {
    this-> userId = userId;
    this-> initialTime = initialTime;
    this-> numeros = numeros;

};

void C5Requeriment::setNumber(int _ordinal, std::string _type, double _value, double _bmin, double _bmax, long _time){
    C5Number numero = C5Number(_ordinal, _type, _value, _bmin, _bmax, _time);
    numeros.push_back(numero);
};

C5Number C5Requeriment::getNumber(int _ordinal){
    C5Number numero;
    for (int i = 0 ; i<numeros.size(); i++){
        if (_ordinal == numeros[i].getOrdinal()){
            numero = numeros[i];
        }
    }
    return numero;
};

long C5Requeriment::getInitialTime(){
    return initialTime;
};

int C5Requeriment::getUserId(){
    return userId;
};

std::vector<C5Number> C5Requeriment::getNumbers(){
    std::cout << numeros[0].getValue();
    return numeros;
}
