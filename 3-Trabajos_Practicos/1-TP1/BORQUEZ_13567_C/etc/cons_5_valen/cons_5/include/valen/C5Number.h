#ifndef _C5NUMBER_H
#define _C5NUMBER_H

#include <string>

class C5Number {

public:
    C5Number();

    C5Number(int ordinal, std::string type, double value, double bmin, double bmax, long time);

    int getOrdinal();

    std::string getType();

    double getValue();

    double getBmin();

    double getBmax();

    long getTime();

private:

    int ordinal;

    std::string type;

    double value;

    double bmin;

    double bmax;

    long time;

};

#endif