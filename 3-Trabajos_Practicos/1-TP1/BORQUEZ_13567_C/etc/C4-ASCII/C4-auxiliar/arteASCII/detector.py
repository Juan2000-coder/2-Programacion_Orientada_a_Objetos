import chardet
import os

def detectar_codificacion(archivo):
    detector = chardet.universaldetector.UniversalDetector()
    with open(archivo, 'rb') as file:
        for linea in file:
            detector.feed(linea)
            if detector.done:
                break
    detector.close()
    return detector.result['encoding']

print(detectar_codificacion("salida.txt"))
print("algo")
"""print(detectar_codificacion("ejemplo0.txt"))
print(detectar_codificacion("ejemplo2.txt"))
print(detectar_codificacion("ejemplo4.txt"))
print(detectar_codificacion("ejemplo6.txt"))"""