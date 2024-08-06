from EstacionBombeo import EstacionBombeo
import os

if __name__ == "__main__":
    estacion = EstacionBombeo()
    for i in range(estacion.Ntuberias):
        os.system("cls")
        print("PROMPT DE CONFIGURACIÓN DE LA PLANTA")
        print(estacion.obtenerDetalle())
        print("A continuación indique el estado de las tuberias de la planta.")
        print("Para cada una indicar \'y(Y)\' para HABILITAR o \'n(N)\' para INHABILITAR.")

        flag = True
        while flag:
            try:
                eleccion = input(f"Habilitar tuberia {i} ?  ")
                if eleccion in ['y','Y']:
                    estacion.configurarTuberia(i, "HABILITADA")
                elif eleccion in ['n', 'N']:
                    estacion.configurarTuberia(i, "DESHABILITADA")
                else:
                    raise Exception("Elija una opcion valida.")
                flag = False
            except Exception as e:
                print(e)
    os.system("cls")
    print(estacion.obtenerDetalle())
    print("CAUDAL TOTAL DE LAS CAÑERIAS HABILITADAS = " + "{:.2f}".format(estacion.calcularCaudalHabilitado()))
    for i in range(5):
        print()