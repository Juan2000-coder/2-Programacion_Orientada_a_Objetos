import random

class Tuberia():
    def __init__(self):
        self.fluido = random.choice(["Agua","Petroleo","Gas","Aceite"])
        self.caudal = random.uniform(1000.0, 5000.0) # CAUDAL DEN LITROS POR HORA
        self.estado = "NO CONFIGURADO" # LUEGO PUEDE SER HABILITADO O NO HABILITADO