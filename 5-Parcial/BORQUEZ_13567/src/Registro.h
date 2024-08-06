#ifndef _REGISTRO_H
#define _REGISTRO_H
#include <ctime>

class Registro{
    public:
        Registro(float _altura, float _velocidad, std::time_t _tiempo, char _direccion);
        float getAltura(void);
        float getVelocidad(void);
        std::time_t getTime(void);
        char getDireccion(void);
    private:
        float altura;
        float velocidad;
        std::time_t tiempo;
        char direccion;
};
#endif