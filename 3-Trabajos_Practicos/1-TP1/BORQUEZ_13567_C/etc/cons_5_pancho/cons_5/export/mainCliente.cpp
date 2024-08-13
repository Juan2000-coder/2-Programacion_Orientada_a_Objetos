#include <iostream>
#include <stdlib.h>
#include <fstream>
#include <algorithm>
#include <cctype> // Include for std::isdigit
#include <iomanip> 
using namespace std;

#include "json.hpp"
#include "XmlRpc.h"

using namespace XmlRpc;

void mostrarMenuAyuda() {
    std::cout << "Comandos Disponibles:" << std::endl;
    std::cout << "  c[id]: Seleccionar un usuario" << std::endl;
    std::cout << "  r[arg1][arg2]: Generar un número aleatorio" << std::endl;
    std::cout << "  n: Generar un número aleatorio sin límites" << std::endl;
    std::cout << "  e: Obtener información de un número ya generado" << std::endl;
    std::cout << "  f: Guardar números generados y estadísticas en un archivo CSV" << std::endl;
    std::cout << "  b[posicion]: Obtener informacion de un número ya generado" << std::endl;
    std::cout << "  h: Mostrar este menú de ayuda" << std::endl;
    std::cout << "  q: Salir de la aplicación" << std::endl;
}


bool isValidInt(const std::string& str) {
    // Check if all characters in the string are digits
    return !str.empty() && std::all_of(str.begin(), str.end(), ::isdigit);
}

// Función para validar si una cadena es un número de punto flotante
bool isValidDouble(const std::string& str) {
    size_t dotCount = std::count(str.begin(), str.end(), '.');
    return !str.empty() && dotCount == 1;
}

int main(int argc, char* argv[]) {
    if (argc != 3) {
        std::cerr << "Uso: ./cliente IP_HOST N_PORT\n";
        return -1;
    }

    int port = atoi(argv[2]);

    XmlRpcClient c(argv[1], port);
    XmlRpcValue noArgs, result;
    XmlRpcValue oneArg;
    bool flag = true;
    std::string input;
    int userId = -1; // Initialize with an invalid user ID
    std::string input1, input2; // Declare these variables outside the switch
    XmlRpcValue args;
    while (flag) {
        if (userId == -1) {
            cout << "Ingrese un número de usuario válido: ";
            cin >> input;
            if (isValidInt(input)) {
              
                userId = std::stoi(input);
                oneArg = userId;
                if (c.execute("Validar", oneArg, result)) {
                    cout << result << "\n\n";
                    if (result == "Usuario no válido") {
                        userId = -1; // Reset user ID to invalid
                        continue;    // Vuelve al inicio del bucle para pedir nueva información.
                    } else {
                        cout << "Usuario válido: " << userId << "\n";
                    }
                } else {
                    cout << "Error en la llamada a 'Validar'\n\n";
                }
            } else {

                cout << "Error: Ingrese un número válido" << endl;
                continue;
            }
        }

        char comando;
        cout << "Seleccione un comando (r/n/b/c/e/f/h (tipear h para ayuda)): ";
        cin >> comando;

        switch (comando) {
            case 'h':
                mostrarMenuAyuda();
            break;

            case 'r':
                std::cin >> input1 >> input2;

                if (isValidInt(input1) && isValidInt(input2)) {
                    // Ambos inputs son enteros
                    int value1 = std::stoi(input1);
                    int value2 = std::stoi(input2);
                    XmlRpcValue args;
                    args[0] = value1;
                    args[1] = value2;

                    if (c.execute("Generar", args, result)) {
                    } else {
                        cout << "Error en la llamada a 'Generar'\n\n";
                    }
                } else if (isValidDouble(input1) && isValidDouble(input2)) {
                    // Ambos inputs son doubles
                    double value1 = std::stod(input1);
                    double value2 = std::stod(input2);
                    XmlRpcValue args;
                    args[0] = value1;
                    args[1] = value2;

                    if (c.execute("Generar", args, result)) {
                        cout << result << "\n\n";
                    } else {
                        cout << "Error en la llamada a 'Generar'\n\n";
                    }
                } else {
                    std::cout << "Parametros no validos. Deben ser ambos int o double.\n";
                }
                break;

            case 'n':
                
                args[0] = "noBoundaries";

                if (c.execute("Generar", args, result)) {
                    cout << result << "\n\n";
                } else {
                    cout << "Error en la llamada a 'Generar'\n\n";
                }
                break;

            case 'b':
                if (userId != -1) {
                    
                    args[0] = "Numero ya generado";

                    std::cin >> input;
                    if (isValidInt(input)) {
                        int value1 = std::stoi(input);
                        args[1] = value1;

                        if (c.execute("Generar", args, result)) {
                            if (result.getType() == 4) {
                                // Server returned an error message
                                std::cout << "Error: " << result << "\n\n";
                            } else if (result.getType() == 7 && result.size() >= 4) {
                                // Server returned a valid result
                                cout << "Minimo: " << result[0] << "\n\n";
                                cout << "Maximo: " << result[1] << "\n\n";
                                cout << "Valor: " << result[3] << "\n\n";
                                cout << "Tiempo: " << result[2] << " ms" << "\n\n";
                            } else {
                                // Invalid response format
                                cout << "Error: Respuesta invalida desde el servidor\n\n";
                            }
                        } else {
                            cout << "Error en la llamada a 'Generar'\n\n";
                        }
                    } else {
                        cout << "Ingrese un número válido";
                    }
                } else {
                    cout << "Debe seleccionar un usuario válido (c) antes de usar el comando 'b'\n";
                }
                break;

            case 'c':
                userId = -1; // Resetea el user ID para volver a empezar
                break;
            case 'e':
                  if (userId != -1) {
                    
                    args[0] = "Estadisticas";
                    args[1] = userId;

                        if (c.execute("Generar", args, result)) {
                            if (result.getType() == 4) {
                                // Server returned an error message
                                std::cout << "Error: " << result << "\n\n";
                            } else if (result.getType() == 7 && result.size() >= 3) { //7 es para arrays
                                // Server returned a valid result
                                cout << "Cantidad de numeros generados: " << result[0] << "\n\n";
                                cout << "Suma de valores generados: " << result[1] << "\n\n";
                                cout << "Promedio de valores generados:  " << result[2] << "\n\n";
                               
                            } else {
                                // Invalid response format
                                cout << "Error: Respuesta invalida desde el servidor\n\n";
                            }
                        } else {
                            cout << "Error en la llamada a 'Generar'\n\n";
                        }
 
                } else {
                    cout << "Debe seleccionar un usuario válido (c) antes de usar el comando 'b'\n";
                }
                break;

            default:
                cout << "Seleccione un comando válido. Escriba h para help\n";
                break;
            case 'l':
                if(userId != -1){
                    args[0] = "Listar";
                    args[1] = userId;
                    if (c.execute("Generar", args, result)) {
                            if (result.getType() == 4) {
                                // Server returned an error message
                                std::cout << "Error: " << result << "\n\n";
                            } else if (result.getType() == 7) { //7 es para arrays
                                // Server returned a valid result
                                int numFilas = result.size();  // Calcula la cantidad de filas
                                

                                for (int i = 0; i < numFilas; i++) {
                                    // Imprime los elementos de la fila actual
                                    
                                        std::cout << "Posicion: " << result[i][0] << endl;
                                        std::cout << "Minimo: " << result[i][1] << endl;
                                        std::cout << "Maximo: " << result[i][2] << endl;
                                        std::cout << "Tiempo transcurrido: " << result[i][3] << " ms" << endl;
                                        std::cout << "Valor generado: " << result[i][4] << endl;
                                        std::cout << "Tipo: " << result[i][5] << endl;
                                    
                                    // Salto de línea al final de cada fila
                                        std::cout <<"----------------------"<<std::endl;
                                }
                               
                            } else {
                                // Invalid response format
                                cout << "Error: Respuesta invalida desde el servidor\n\n";
                            }
                        } else {
                            cout << "Error en la llamada a 'Generar'\n\n";
                        }
 
                } else {
                    cout << "Debe seleccionar un usuario válido (c) antes de usar el comando 'b'\n";
                }
                break;
         case 'f':
            if (userId != -1) {
                std::string filename;
                std::cout << "Enter the filename for the CSV file: ";
                std::cin >> filename;

                // Check if the filename has a ".csv" extension, if not, add it.
                if (filename.find(".csv") == std::string::npos) {
                    filename += ".csv";
                }

                std::ofstream outputFile(filename);
                if (!outputFile.is_open()) {
                    std::cerr << "Failed to open the file for writing." << std::endl;
                    return 1;
                }

                args[0] = "Listar";
                args[1] = userId;

                if (c.execute("Generar", args, result)) {
                    if (result.getType() == 4) {
                        // Server returned an error message
                        std::cout << "Error: " << result << "\n\n";
                    } else if (result.getType() == 7) { // 7 is for arrays
                        // Server returned a valid result

                        // Add headers to the CSV file
                        outputFile << "userID\n";
                        outputFile << userId << "\n";
                        outputFile << "\n";
                        outputFile << "Position,Minimo,Maximo,Tiempo transcurrido,Valor generado,Tipo\n";

                        int numFilas = result.size();  // Calculate the number of rows

                        for (int i = 0; i < numFilas; i++) {
                            // Format double values with fixed decimal places and write to the file
                            outputFile << result[i][0] << ",";
                            outputFile << result[i][1] << ",";
                            outputFile << result[i][2] << ",";
                            outputFile << std::fixed << std::setprecision(3) << result[i][3] << " ms,"; // Format with 3 decimal places
                            outputFile << std::fixed << std::setprecision(3) << result[i][4] << ","; // Format with 3 decimal places
                            outputFile << result[i][5] << "\n";
                        }
                        outputFile << "\n";
                    } else {
                        // Invalid response format
                        cout << "Error: Respuesta inválida desde el servidor\n\n";
                    }
                } else {
                    cout << "Error en la llamada a 'Generar'\n\n";
                }

                args[0] = "Estadisticas";
                args[1] = userId;

                if (c.execute("Generar", args, result)) {
                    if (result.getType() == 4) {
                        // Server returned an error message
                        std::cout << "Error: " << result << "\n\n";
                    } else if (result.getType() == 7 && result.size() >= 3) { // 7 is for arrays
                        // Server returned a valid result

                        // Add headers for the statistics
                        outputFile << "Cantidad de lecturas,Suma de los valores generados,Promedio de los valores generados\n";

                        // Format double values with fixed decimal places and write to the file
                        outputFile << result[0] << ",";
                        outputFile << result[1] << ",";
                        outputFile << std::fixed << std::setprecision(3) << result[2] << "\n"; // Format with 3 decimal places
                    } else {
                        // Invalid response format
                        cout << "Error: Respuesta inválida desde el servidor\n\n";
                    }
                } else {
                    cout << "Error en la llamada a 'Generar'\n\n";
                }
            } else {
                cout << "Debe seleccionar un usuario válido (c) antes de usar el comando 'f'\n";
            }
            break;
            case 'q':
                flag = false;
                break;

            }
        } 
    
        return 0;
    }

