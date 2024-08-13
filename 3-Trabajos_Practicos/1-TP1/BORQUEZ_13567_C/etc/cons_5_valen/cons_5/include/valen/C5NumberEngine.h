
#ifndef _C5NUMBERENGINE_H
#define _C5NUMBERENGINE_H

#include <vector>
#include <iostream>

#include "C5Requeriment.h"

class C5NumberEngine {

private:

    std::vector<C5Requeriment> users;

public:

    C5NumberEngine();

    bool userValidate(int);
    
    int getInt(int,int);
    
    int getInt();
    
    double getReal(double, double);
    
    double getReal();
    
    std::string getNumberOld(int);

    std::string getStat(int);

    std::string getNumberList(int);

    C5Requeriment newClient(int);

};

#endif