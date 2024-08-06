#include "Reporte.h"
#include <sstream>
#include <iostream>
#include <iomanip>
using namespace std;

Reporte::Reporte(int idDron, int cantRegistros){
    stringstream ssaux;
    ssaux << "id Dron: " << idDron <<"- Cantidad Registros" << cantRegistros << endl;
    ssaux << setw(12) << right << setfill(' ') << "Altura"
    << setw(12) << right << setfill(' ') << "Velocidad"
    << setw(12) << right << setfill(' ') <<"Tiempo"
    << setw(12) << right << setfill(' ') <<"Direccion" << endl;

    this->encabezado = ssaux.str();
}
void Reporte::listar(vector<Registro>& registros){
    char buffer[80];
    std::time_t tiempo;
    cout << this->encabezado << endl;
    for(vector<Registro>::iterator it = registros.begin(); it != registros.end(); it++){
        tiempo = it->getTime();
        tm* tiempoLocal = std::localtime(&tiempo);
        std::strftime(buffer, sizeof(buffer), "%H:%M:%S", tiempoLocal);
        cout << setw(12) << right << setfill(' ') << fixed << setprecision(4) << it->getAltura()
        << setw(12) << right << setfill(' ') << fixed << setprecision(4) << it->getVelocidad()
        << setw(12) << right << setfill(' ') << fixed << setprecision(4) << buffer
        <<setw(12) << right << setfill(' ') << it->getDireccion() << endl;
    }
}
