#ifndef _DRON_H
#define _DRON_H

#include <vector>
#include <cstdlib>
#include <ctime>

#include "Registro.h"

class Dron{
    public:
        Dron(int _id);
        Registro getRegistro(int i);
        std::vector<Registro>& getRegistros(void);
        void addRegistro(void);

        //Agregados
        int getId(void);
        int getCantRegistros(void);

    private:
        std::vector<Registro>registros;
        int id;

        //Agregados
        float velocidadMaxima;
        float alturaMaxima;
        int cantRegistros;
};
#endif