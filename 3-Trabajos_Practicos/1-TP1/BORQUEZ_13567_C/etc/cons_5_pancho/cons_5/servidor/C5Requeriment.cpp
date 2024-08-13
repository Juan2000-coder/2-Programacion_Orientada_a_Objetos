
#include "C5Requeriment.h"
#include "C5NumberEngine.h"
#include "C5Number.h"


C5Requeriment::C5Requeriment(int userId, long initialTime){
    this->userId = userId;
    this->initialTime = initialTime;
    // C5Number(ordinal, type, value, bmin, bmax, time);
}

void C5Requeriment::setDatos(string type, double value, double bmin, double bmax, long time){
    int ordinal = datos.size()+1;
    C5Number* dato = new C5Number(ordinal, type, value, bmin, bmax, time);
    this->datos.push_back(dato);
}

long C5Requeriment::getInitialTime() const { 
    return this->initialTime;
}
   
std::vector<C5Number*> C5Requeriment::getMiVector() const {
    return this->datos;
}

int C5Requeriment::getUserId() const{
    return this->userId;
}

C5Requeriment::~C5Requeriment() {
    // Release dynamically allocated C5Number objects
    for (auto it = datos.begin(); it != datos.end(); ++it) {
        delete *it;  // Deallocate memory for C5Number objects
    }
}