#ifndef _MEDICION_H
#define _MEDICION_H
class Medicion{
    public:
        Medicion(float medicion, int instante, int idElectrovalvula);
        int getInstanteCaudal();
        int getIdElectrovalvula();
    private:
        int instante;
        float medicion;
        int idElectrovalvula;
};
#endif