#include <cstdlib>
#include <ctime>
#include <string>
#include <iostream>
using namespace std;

#include "C5Number.h"
C5Number::C5Number(){
    
}

C5Number::C5Number(int _ordinal, std::string _type, double _value, double _bmin, double _bmax, long _time) {
    this-> ordinal = _ordinal;
    this-> type = _type;
    this-> value = _value;
    this-> bmin = _bmin;
    this-> bmax = _bmax;
    this-> time = _time;

}

int C5Number::getOrdinal() {
    return ordinal;
}

std::string C5Number::getType() {
    return type;
}

double C5Number::getValue() {
    return value;
}

double C5Number::getBmin() {
    return bmin;
}

double C5Number::getBmax() {
    return bmax;
}

long C5Number::getTime() {
    return time;
}