#ifndef _CONTROLADOR_H
#define _CONTROLADOR_H

#include "Tanque.h"
#include "Medicion.h"
#include <string>
#include <vector>


class Controlador{
    public:
        Controlador(int _cantMediciones, int A, int B, int C, float hSensorAlta, float hSensorBaja);
        std::string reporteDeSimulacion(void) const;
        void cicloControlador(int t); // Medicion de sensores y actuación.
    private:
        Tanque* tanque;
        std::vector<std::vector<Medicion>> mediciones;
        int cantMediciones;
        int caudalMaximo;   //Interpretado como el máximo caudal registrado en cualquiera de las válvulas.
        int caudalMinimo;   //Interpretado como el caudal mínimo en cualquiera de las valvulas.
        int cantActivacionSensor;
};
#endif