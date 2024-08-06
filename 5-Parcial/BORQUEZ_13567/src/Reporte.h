#ifndef _REPORTE_H
#define _REPORTE_H
#include <string>
#include <vector>
#include "Registro.h"

class Reporte{
    public:
        Reporte(int idDron, int cantRegistros);
        void listar(std::vector<Registro>& registros);
    private:
        std::string encabezado;
};
#endif