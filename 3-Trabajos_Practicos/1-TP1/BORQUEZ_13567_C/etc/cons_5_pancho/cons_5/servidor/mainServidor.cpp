#include <iostream>
#include <stdlib.h>
#include <sstream>
#include <string>
#include <typeinfo>
using namespace std;

#include "XmlRpc.h"

using namespace XmlRpc;

#include "C5NumberEngine.h"

// s es el servidor
XmlRpcServer S;
C5NumberEngine* generador = new C5NumberEngine();
bool ultimoFueInt;

class Validar : public XmlRpcServerMethod
{
  public:
    Validar(XmlRpcServer* S) : XmlRpcServerMethod("Validar", S) {}

    void execute(XmlRpcValue& params, XmlRpcValue& result)
    {

  /*
      if (params.size() != 1 || params[0].getType() != XmlRpcValue::TypeInt) {
      result = "Invalid argument"; // Handle invalid input
      return;
    }
  */  
      if(params.size() == 1){

      int userId = int(params[0]);
      
      
      bool enArchivo = generador->userValidate(userId);
      if (enArchivo == true){
        std::string resultString = "Hola, usuario ";
        resultString += std::to_string(userId);
        result = resultString;
      }
      else{
        result = "Usuario no válido";
      }
      }else{
        result = "Ingrese un solo parametro";
      }

      //delete validador;
    }

    //std::string help() { return std::string("Diga Hola");}

} validar(&S);    // Este constructor registra el método en el servidor

class Generar: public XmlRpcServerMethod{

  public:
    Generar(XmlRpcServer* S): XmlRpcServerMethod("Generar", S){}
    void execute(XmlRpcValue& params, XmlRpcValue& result){
 
        

        if (params[0].getType() == 2 && params[1].getType() == 2){ // se fija si el nro ingresado es entero o decimal. Si es 3, es double, si es 2, es int.
           int min = int(params[0]);
           int max = int(params[1]);

           if (max < min){ // por si se ingreso primero el CS y luego el CI

            int temp = max;
            max = min;
            min = temp;

          }
          
            ultimoFueInt = true;
            
            int numRandom = generador->getInt(min,max);

            result = numRandom;
            


        } else if(params[0].getType() == 3 && params[1].getType() == 3){

           double min = double(params[0]);
           double max = double(params[1]);

           if (max < min){

            double temp = max;
            max = min;
            min = temp;


        }
            ultimoFueInt = false;
            
            double numRandom = generador->getReal(min,max);
            
            result = numRandom;
           
      } else if((params[0].getType() == 4)){ // tipo 4 es string
        


          if (std::string(params[0]) == "noBoundaries"){

              if (ultimoFueInt){
                int numeroEntero = generador->getInt();
                result = numeroEntero;
              }else if (!ultimoFueInt){
                double numeroReal = generador->getReal();
                result = numeroReal;
              }


          }else if(std::string(params[0]) == "Numero ya generado"){

            try {

            InfoObjeto info = generador->getNumberOld(params[1]);
              result[0] = info.bmin;
              result[1] = info.bmax;
              result[2] = std::string(info.time);
              result[3] = info.value;
    
              } catch (const std::runtime_error& e) {
              result = "Objeto no encontrado";
              std::cerr << "Error: " << e.what() << std::endl;
            
            }
          }else if(std::string(params[0]) == "Estadisticas"){

            try {

            Estadisticas info = generador->getStat(params[1]);
              result[0] = info.cantidadDeNumeros;
              result[1] = info.suma;
              result[2] = info.promedio;
    
              } catch (const std::runtime_error& e) {
              result = "ID de usuario no encontrado";
              std::cerr << "Error: " << e.what() << std::endl;
          }
          }else if(std::string(params[0]) == "Listar"){
            try{
            int row=0;
            std::vector<InfoObjeto> listado = generador->getNumberList(params[1]);
            for(const auto& estructura : listado){ // cada fila corresponde a una instancia de generacion. Cada columna a cada uno de los valores que influyeron en la generacion
              result[row][0] = estructura.ordinal;
              result[row][1] = estructura.bmin;
              result[row][2] = estructura.bmax;
              result[row][3] = std::string(estructura.time);
              result[row][4] = estructura.value;
              result[row][5] = estructura.type;
              row +=1;
            }
            } catch (const std::runtime_error& e){
              result = "ID de usuario no encontrado";
              std::cerr << "Error: " << e.what() << std::endl;
            }
          }
        }
  
       //delete generador;
      
    }
  private:
    
    
    
} generar(&S);

int main(int argc, char** argv) {
  if (argc != 2) {
    std::cerr << "Uso: ./servidor N_Port\n";
    return -1;
  }
  int port = atoi(argv[1]);

  XmlRpc::setVerbosity(5);

  // Se crea un socket de servidor sobre el puerto indicado
  S.bindAndListen(port);

  // Enable introspection
  S.enableIntrospection(true);

  // A la escucha de requerimientos
  S.work(-1.0);
  
  return 0;
}

