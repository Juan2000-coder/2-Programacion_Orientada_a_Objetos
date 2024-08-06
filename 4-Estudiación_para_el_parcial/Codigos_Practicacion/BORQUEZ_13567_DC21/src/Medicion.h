class Medicion{
    public:
        Medicion();
        float getFechaHora(void);
        float getMedida(void);
    private:
        float fechaHora; // El timestamp de la medición
        float valor;     // El valor medido
};