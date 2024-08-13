
#ifndef _C5REQUERIMENT_H
#define _C5REQUERIMENT_H

#include "C5Number.h"
#include <iostream>
#include <string>
#include <vector>

class C5Requeriment {

private:

    int userId;
    
    long initialTime;

    std::vector<C5Number> numeros;

public:

    C5Requeriment(int userId, long initialTime);

    void setNumber(int, std::string, double, double, double, long);

    C5Number getNumber(int);

    long getInitialTime();

    int getUserId();

    std::vector<C5Number> getNumbers();

};

#endif