#ifndef _C5NUMBERENGINE_H
#define _C5NUMBERENGINE_H
#include "C5Requeriment.h"
#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <random>
#include <algorithm>
#include "json.hpp"
#include <typeinfo>
#include <chrono>
#include <stdexcept>


struct InfoObjeto {
    int ordinal;
    string type;
    double value;
    double bmin;
    double bmax;
    string time;
};

struct Estadisticas{
    int cantidadDeNumeros;
    double suma;
    double promedio;
};

class C5NumberEngine {
  
  public:


    bool userValidate(int userId);

    int getInt(int bmin, int bmax);

    int getInt();

    double getReal(double bmin, double bmax);

    double getReal();

    InfoObjeto getNumberOld(int ordinal);

    Estadisticas getStat(int userId);

    std::vector<InfoObjeto> getNumberList(int userId);

    std::vector<C5Requeriment*> getRequeriment();


  private:

    int indice = 0;
    std::vector<C5Requeriment*> requeriments;

};
#endif
