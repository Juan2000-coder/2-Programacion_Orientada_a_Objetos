#include "Reporte.h"
#include "Dron.h"

#include <cstdlib>
#include <ctime>
#include <vector>
#include <chrono>
#include <thread>

int main(void){
    std::srand(static_cast<unsigned int>(std::time(nullptr)));
    // Aca defino la cantida de registros que se van a realizar o que se van a tomar del Dron.
    // Asumo que el poder de generación de los registros es del dron.
    int cantRegistros = 1 + std::rand()%20;

    Dron dron(1 + std::rand()%10);
    Reporte reporte(dron.getId(), cantRegistros);

    

    std::chrono::milliseconds duracion(800); //delay
    
    for(int i = 1; i <= cantRegistros; i++){//Generación de los registros
        dron.addRegistro();
        std::this_thread::sleep_for(duracion);
    }
    
    reporte.listar(dron.getRegistros());
    return EXIT_SUCCESS;
}