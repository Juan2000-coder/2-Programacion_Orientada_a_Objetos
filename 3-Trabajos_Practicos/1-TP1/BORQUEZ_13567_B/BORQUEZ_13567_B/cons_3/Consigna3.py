from C3Report import C3Report
import os
import time

if __name__ == "__main__":
    reporte = C3Report()
    reporte.readUser()

    while not reporte.validFileName:    # The flags starts with a False value
        print("\nDIRECTORIO DEL REPORTE: \n")
        for element in reporte.fileDirectory:
            print(element)

        reporte.readFileName()
        os.system('cls' if os.name == 'nt' else 'clear')    # Clear Screen

        if any(fileName == reporte.filename for fileName in reporte.fileDirectory):
            if reporte.filename[-3:] == 'csv':
                reporte.validFileName = True
                reporte.createReport()
                break

        print("INDIQUE EL NOMBRE DE UN ARCHIVO VÁLIDO: ")
        time.sleep(2)
        os.system('cls' if os.name == 'nt' else 'clear')
    input(' ')