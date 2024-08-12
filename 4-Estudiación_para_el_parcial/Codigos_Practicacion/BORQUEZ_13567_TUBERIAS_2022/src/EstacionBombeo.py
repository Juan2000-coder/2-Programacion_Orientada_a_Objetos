import random
from Tuberia import Tuberia
from prettytable import PrettyTable

class EstacionBombeo():
    def __init__(self):
        self.identificador = "Estacion 1"
        self.localidad = "Las Heras"
        self.tuberias = [] # Una lista con las tuberias
        self.Ntuberias = random.randint(5, 15)
        # Se crea la lista con las tuberias
        for i in range(self.Ntuberias):
            self.tuberias.append(Tuberia())


    def calcularCaudalHabilitado(self):
        """Obtiene la suma de los caudales para todas las tuberias habilitadas."""
        return sum(tuberia.caudal for tuberia in self.tuberias if tuberia.estado == "HABILITADA")
    
    def obtenerDetalle(self):
        """Obtiene el detalle de la estacion de bombeo."""
        tabla = PrettyTable(["Numero de Tuberia", "Fluido", "Caudal", "Estado"])
        for i, tuberia in enumerate(self.tuberias):
            tabla.add_row([i, tuberia.fluido, tuberia.caudal, tuberia.estado])

        tabla.title = self.identificador + "-" + self.localidad
        tabla.float_format = ".2"
        return tabla
    def configurarTuberia(self, i, estado:str):
        self.tuberias[i].estado = estado
