#ifndef _ELECTROVALVULA_H
#define _ELECTROVALVULA_H
#include <iostream>
class Electrovalvula{
    public:
        Electrovalvula(int _Id, int _A, int _B, int _C): Id(_Id), A(_A), B(_B), C(_C), cantQcero(0){};
        int getId(void) const;
        float getCaudal(int t); // Modifica cantQcero.
        int getQcero(void) const;
        void setEstado(bool estado);
        bool getEstado(void) const;
    private:
        int A;
        int B;
        int C;
        bool estado; //abierta(true) o cerrada(false)
        int Id;
        int cantQcero;
};

class ElectrovalvulaEx:public std::exception{
    public:
        ElectrovalvulaEx(int _source): exception(), source(_source){};
        const char* what() const throw();

    private:
        int source;
};
#endif