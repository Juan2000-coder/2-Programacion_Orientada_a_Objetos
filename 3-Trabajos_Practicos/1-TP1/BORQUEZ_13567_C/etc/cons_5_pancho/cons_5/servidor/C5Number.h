#ifndef _C5NUMBER_H
#define _C5NUMBER_H


#include <string>
using namespace std;


class C5Number {
  public:

    C5Number(int ordinal, string type, double value, double bmin, double bmax, long time){
      this->ordinal = ordinal;

      this->type = type;

      this->value = value;

      this->bmin = bmin;

      this->bmax = bmax;

      this->time = time;

    }

    string getType(){
      return this->type;
    }
    double getBmin(){
      return this->bmin;
    }
    double getBmax(){
      return this->bmax;
    }
    long getTime(){
      return this->time;
    }
    double getValue(){
      return this->value;
    }
    int getOrdinal(){
      return this->ordinal;
    }

  private:
    int ordinal;

    string type;

    double value;

    double bmin;

    double bmax;

    long time;


};
#endif
