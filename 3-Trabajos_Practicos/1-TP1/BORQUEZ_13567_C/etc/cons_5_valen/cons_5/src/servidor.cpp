
#include <iostream>
#include <typeinfo>
#include <stdlib.h>
using namespace std;
#include "XmlRpc.h"
using namespace XmlRpc;

#include "C5NumberEngine.h"

// S es el servidor
XmlRpcServer S;

int main(int argc, char* argv[]) {
  if (argc != 1) {
    std::cerr << "Uso: servidor \n";
    return -1;
  }

  std::cout << "IP: 10.68.80.75 (CHEQUEAR SEGUN RED CONECTADA)\n";
  std::cout << "PORT: 8091 \n";

  int port = 8091;
  XmlRpc::setVerbosity(5);

  // Se crea un socket de servidor sobre el puerto indicado
  S.bindAndListen(port);


  // Enable introspection
  S.enableIntrospection(true);

  // Se crea una instancia de C5NumberEngine
  C5NumberEngine user;

  // Metodo para 'generar' numeros
  class Generar : public XmlRpcServerMethod{
    public:
      Generar(XmlRpcServer* S, C5NumberEngine* user) : XmlRpcServerMethod("Generar", S), _user(user) {}

      void execute(XmlRpcValue& params, XmlRpcValue& result){

        // Verifica cual metodo ha llamado desde el cliente según los parámetros de entrada
        if (params.size() >= 1 && params[0].getType() == XmlRpcValue::TypeString) {
          std::string nombMetodo = params[0];

          if (nombMetodo == "int" && params.size() == 1) {
            int resp = _user->getInt();
            result = resp;
          }
          else if (nombMetodo == "int" && params.size() == 3 && params[1].getType() == XmlRpcValue::TypeInt && params[2].getType() == XmlRpcValue::TypeInt) {
            // Obtener los argumentos enteros de params
            int arg1 = params[1];
            int arg2 = params[2];

            int resp = _user->getInt(arg1, arg2);
            result = resp;
          }

          else if (nombMetodo == "real" && params.size() == 1) {
            double resp = _user->getReal();
            result = resp;
          }
          else if (nombMetodo == "real" && params.size() == 3 && params[1].getType() == XmlRpcValue::TypeDouble && params[2].getType() == XmlRpcValue::TypeDouble) {
            // Obtener los argumentos reales de params
            double arg1 = params[1];
            double arg2 = params[2];

            double resp = _user->getReal(arg1, arg2);
            result = resp;
          }

          else if (nombMetodo == "numberOld" && params.size() == 2 && params[1].getType() == XmlRpcValue::TypeInt) {
            // Obtener el argumento ordinal de params
            int arg1 = params[1];

            std::string resp = _user->getNumberOld(arg1);
            result = resp;
          }
        
          else if (nombMetodo == "stats" && params.size() == 2 && params[1].getType() == XmlRpcValue::TypeInt) {
            // Obtener el argumento userId de params
            int arg1 = params[1];

            std::string resp = _user->getStat(arg1);
            result = resp;
          }

          else if (nombMetodo == "numberList" && params.size() == 2 && params[1].getType() == XmlRpcValue::TypeInt) {
            // Obtener el argumento userId de params
            int arg1 = params[1];

            std::string resp = _user->getNumberList(arg1);
            result = resp;
          }

        } else {
          // Manejar un error si los argumentos no son los esperados
          result = false;
          std::cout << "Error: Argumentos ingresados no correspondidos." << std::endl; 
        }
      }
      std::string help() { return std::string("Genera un numero con características propias de los parámetros ingresados."); }

    private:
      C5NumberEngine* _user;
  } generar(&S, &user);


  // Metodo para 'Validar' usuarios
  class Validar : public XmlRpcServerMethod{
    public:
      Validar(XmlRpcServer* S, C5NumberEngine* user) : XmlRpcServerMethod("Validar", S), _user(user) {}

      void execute(XmlRpcValue& params, XmlRpcValue& result){

        if (params.size() >= 1 && params[0].getType() == XmlRpcValue::TypeInt) {
          int userId = int(params[0]);
 
          bool validate = _user->userValidate(userId);
      
          if (validate) {
            result = validate;
          } else {
            result = validate;
          }
        } else {
          // Manejar un error si los argumentos no son los esperados
          result = false;
          std::cout << "Error: Argumento ingresado no correspondido." << std::endl; 
        }
      }
      //std::string help() { return std::string("Valida el usuario que ejecuta la orden."); }

    private:
      C5NumberEngine* _user;
  } validar(&S, &user);

  // A la escucha de requerimientos
  S.work(-1.0);

  return 0;
}