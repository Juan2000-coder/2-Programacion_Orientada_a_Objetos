#ifndef _C5REQUERIMENT_H
#define _C5REQUERIMENT_H

#include "C5Number.h"
#include <iostream>
#include <string>
#include <vector>
using namespace std;

class C5Requeriment {
public:
  
  C5Requeriment(int, long);

  void setDatos(string, double, double, double, long);

  long getInitialTime() const;
  
  int getUserId() const;

  std::vector<C5Number*> getMiVector() const;

  ~C5Requeriment();

private:
    std::vector<C5Number*> datos;
    int userId;
    long initialTime;
};

#endif

