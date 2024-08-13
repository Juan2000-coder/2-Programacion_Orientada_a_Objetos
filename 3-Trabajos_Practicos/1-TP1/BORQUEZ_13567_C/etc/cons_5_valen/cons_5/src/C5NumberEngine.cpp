#include "C5NumberEngine.h"
#include "C5Requeriment.h"


#include <cstdlib>
#include <ctime>
#include <cmath>
#include <vector>
#include <chrono>
#include <string>
#include <iostream>
#include <fstream>


C5NumberEngine::C5NumberEngine() {
    this -> users = users;
}

bool C5NumberEngine::userValidate(int _userId) {
    bool validate = false;
    std::ifstream archivo("usuarios_validos.txt");
        
    if (!archivo.is_open()) {
        std::cerr << "Error: No se pudo abrir el archivo." << std::endl;
        return false;
    }

    int idLeido;
    while (archivo >> idLeido) {
        if (idLeido == _userId) {
            archivo.close();

            // Se verifica si ya existe un usuario con el mismo ID y se obtiene su índice.
            int existingUserIndex = -1;
            for (int i = 0; i < users.size(); i++) {
                if (users[i].getUserId() == _userId) {
                    existingUserIndex = i;
                    break;
                }
            }

            // Si el usuario existe en el vector, se lo mueve al principio.
            if (existingUserIndex != -1) {
                C5Requeriment existingUser = users[existingUserIndex];
                users.erase(users.begin() + existingUserIndex);  // Elimina el usuario existente.
                users.insert(users.begin(), existingUser);  // Agrega el usuario existente al principio.
            } else {
                // Si el usuario no existe en el vector, se crea uno nuevo y se lo agrega al principio.
                C5Requeriment newUser = C5NumberEngine::newClient(_userId);
                users.insert(users.begin(), newUser);
            }

            return true; // Se encontró el ID en el archivo y se movió o creó un usuario.
        }
    }

    archivo.close();
    return false; // No se encontró el ID en el archivo.
}


int C5NumberEngine::getInt(int _bmin, int _bmax) {
    // Generar un número entero en el rango [-CI, CS]
    int value = std::rand() % (_bmax - _bmin + 1) + _bmin;


    auto tiempo_actual = std::chrono::high_resolution_clock::now();
    auto duracion_seg = std::chrono::duration_cast<std::chrono::seconds>(tiempo_actual.time_since_epoch());
    long tiempo_actual_long = duracion_seg.count();
    long tiempo = tiempo_actual_long - users[0].getInitialTime();
    
    users[0].setNumber(users.size() , "int" , value , _bmin , _bmax , tiempo);
    return value;
}

int C5NumberEngine::getInt() {
    int bmin;
    int bmax;
    std::vector<C5Number> numerosGen = users[0].getNumbers();

    if (!numerosGen.empty()) {
        bmin = int(numerosGen[numerosGen.size()-1].getBmin());
        bmax = int(numerosGen[numerosGen.size()-1].getBmax());
    } else {
        bmin = 10;
        bmax = 20;
    }
    int value = std::rand() % (bmax - bmin + 1) + bmin;

    auto tiempo_actual = std::chrono::high_resolution_clock::now();
    auto duracion_seg = std::chrono::duration_cast<std::chrono::seconds>(tiempo_actual.time_since_epoch());
    long tiempo_actual_long = duracion_seg.count();
    long tiempo = tiempo_actual_long - users[0].getInitialTime();
    
    users[0].setNumber(users.size() , "int" , value , bmin , bmax , tiempo);
    return value;
}

double C5NumberEngine::getReal(double _bmin, double _bmax) {
    // Generar un número real en el rango [-CI, CS] con 2 dígitos de precisión
    double numero = (double)std::rand() / RAND_MAX; // Genera un número entre 0 y 1
    numero = _bmin + numero * (_bmax - _bmin); // Escalar al rango deseado
    double value = std::round(numero * 100) / 100.0; // Redondear a 2 decimales 
    
    auto tiempo_actual = std::chrono::high_resolution_clock::now();
    auto duracion_seg = std::chrono::duration_cast<std::chrono::seconds>(tiempo_actual.time_since_epoch());
    long tiempo_actual_long = duracion_seg.count();
    long tiempo = tiempo_actual_long - users[0].getInitialTime();
    
    users[0].setNumber(users.size() , "real" , value , _bmin , _bmax , tiempo);
    return value;
}

double C5NumberEngine::getReal() {
    double bmin;
    double bmax;
    std::vector<C5Number> numerosGen = users[0].getNumbers();


    if (!numerosGen.empty()) {
        bmin = double(numerosGen[numerosGen.size()-1].getBmin());
        bmax = double(numerosGen[numerosGen.size()-1].getBmax());
    } else {
        bmin = 10.0;
        bmax = 20.0;
    }


    // Generar un número real en el rango [-CI, CS] con 2 dígitos de precisión
    double numero = (double)std::rand() / RAND_MAX; // Genera un número entre 0 y 1
    numero = bmin + numero * (bmax - bmin); // Escalar al rango deseado
    double value = std::round(numero * 100) / 100.0; // Redondear a 2 decimales 
    
    auto tiempo_actual = std::chrono::high_resolution_clock::now();
    auto duracion_seg = std::chrono::duration_cast<std::chrono::seconds>(tiempo_actual.time_since_epoch());
    long tiempo_actual_long = duracion_seg.count();
    long tiempo = tiempo_actual_long - users[0].getInitialTime();
    
    users[0].setNumber(users.size() , "real" , value , bmin , bmax , tiempo);
    return value;
}

std::string C5NumberEngine::getNumberOld(int _ordinal) {
    C5Number num = users[0].getNumber(_ordinal);
    std::string value = "Valor: " + std::to_string(num.getValue()) + "  Cotas:  [" + std::to_string(num.getBmin()) + " , " + std::to_string(num.getBmax()) + "]  Tiempo: " + std::to_string(num.getTime());
    return value;
}

std::string C5NumberEngine::getStat(int _userId){
    //Informar la cantidad de números generados por el usuario, su suma total y su promedio.
    std::string stats;

    for (int i = 0 ; i < users.size() ; i++) {
        if (_userId == users[i].getUserId()){
            std::vector<C5Number> numeros = users[i].getNumbers();
            double suma;
            int cantNumGenerados = numeros.size();
            for (int j = 0 ; j < numeros.size() ; j++){
                suma = suma + numeros[j].getValue();
            }
            if (cantNumGenerados != 0){
                double promedio = suma / cantNumGenerados;
                stats = ("ESTADÍSTICAS DE LOS NÚMEROS GENERADOS POR EL USUARIO DE ID: " + std::to_string(_userId) + "\n");
                stats = stats + ("   Cantidad de números generados:       " + std::to_string(cantNumGenerados) + "\n");
                stats = stats + ("   Sumatoria de los números generados:  " , std::to_string(promedio) , "\n");
            } else {
                stats = ("Error, la cantidad de numeros generados por el usuario: '" + std::to_string(_userId) + "' es de 0 numeros. \n");
            }
        }
    }
    return stats;
}

std::string C5NumberEngine::getNumberList(int _userId){
    /*
    Listar los números generados por el usuario remoto, desde que inició el proceso de generación, incluyendo 
    el tipo, el instante de tiempo en que se generó, el rango de cada uno y al final, el tiempo que ocupó
    realizar todo el proceso desde que se hizo la primera petición.
    */
    std::string stats = ("LISTA COMPLETA DE LOS NUMEROS GENERADOS POR EL USUARIO DE ID: " + std::to_string(_userId) + "\n");
    
    for (int i = 0 ; i < users.size() ; i++) {
        if (_userId == users[i].getUserId()){
            std::vector<C5Number> numeros = users[i].getNumbers();

            for (int j = 0 ; j < numeros.size() ; j++){
                stats = stats + ("  Valor: " + std::to_string(numeros[j].getValue()) + "  Tipo: " + numeros[j].getType() + "  Tiempo: " + std::to_string(numeros[j].getTime()) + "  Cota: [" + std::to_string(numeros[j].getBmax()) + "," + std::to_string(numeros[j].getBmin()) + "] \n");
            }
            stats = stats + ("Tiempo total: " + std::to_string((numeros[numeros.size()-1].getTime() - users[i].getInitialTime())) + "\n");
        }
    }
    return stats;
}


C5Requeriment C5NumberEngine::newClient(int _userId) {
    // Obtiene la marca de tiempo actual
    auto tiempo_actual = std::chrono::high_resolution_clock::now();
    auto duracion_en_segundos = std::chrono::duration_cast<std::chrono::seconds>(tiempo_actual.time_since_epoch());
    long tiempo_actual_long = duracion_en_segundos.count();

    long initialTime = tiempo_actual_long;
    
    C5Requeriment user = C5Requeriment(_userId, initialTime);
    users.push_back(user);

    return user;
}