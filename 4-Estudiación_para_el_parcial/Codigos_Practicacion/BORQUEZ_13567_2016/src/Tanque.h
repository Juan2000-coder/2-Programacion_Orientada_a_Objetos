#ifndef _TANQUE_h
#define _TANQUE_H

#include "Electrovalvula.h"
#include <iostream>
#include <vector>

class Tanque{
    public:
        Tanque(float hSensorAlto, float hSensorBajo, int A, int B, int C);
        float getHSensor(int i) const;
        bool getEstadoSensor(int i) const;
        float getAltura() const;
        float getDiametro() const;
        const Electrovalvula& getElectrovalvula(int id) const;

        // Cosas agregadas.
        void actualizarCota(int t);     // El tanque sabe su cota de agua.
        void actualizarEstadosSensores(int t); // El tanque actualiza el estado de los sensores.
    private:
        std::vector<float> hSensor;
        std::vector<bool> estadoSensor;
        std::vector<Electrovalvula> electrovalvulas;
        float altura;
        float diametro;

        float seccionTransversal;
        float cota;
};
class TanqueEx:public std::exception{
    public:
        TanqueEx(int _source): exception(), source(_source){};
        const char* what() const throw();
    private:
        int source;
};
#endif