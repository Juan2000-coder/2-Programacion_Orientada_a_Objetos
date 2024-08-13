

#include "C5NumberEngine.h"



using namespace std;


bool C5NumberEngine::userValidate(int userId) {
      this->indice = 0;
      for (const auto& user : requeriments) {
        
        if (user->getUserId() == userId) {
            
            return true;
        }
        this->indice = this->indice + 1;
    }
    
  ifstream file("valid_users.json");
  nlohmann::json root;
  file >> root;

  // Recorre los usuarios hasta encontrar el ingresado
  for (const auto& user : root["users"]) {
    if (user["id"] == userId){
        long initialTime = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock::now().time_since_epoch()).count(); // empieza a contar el tiempo desde que el usuario "inició sesión"
        C5Requeriment* usuarioActual = new C5Requeriment(userId, initialTime);
        this->requeriments.push_back(usuarioActual);
        
        return true;
    }
  }
  return false;
}

int C5NumberEngine::getInt(int bmin, int bmax) { //int
    std::random_device rd;
    std::mt19937 generador(rd());
    std::uniform_int_distribution<int> distribucion(bmin, bmax);
    int numeroEntero = distribucion(generador);
    long tiempoDesdeEjecucion = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock::now().time_since_epoch()).count(); //termina de contar el tiempo
    long elapsedTime = tiempoDesdeEjecucion - this->requeriments[this->indice]->getInitialTime();
    cout << elapsedTime << endl;
    this->requeriments[this->indice]->setDatos("int", numeroEntero, bmin, bmax, elapsedTime);
    return numeroEntero;

}

int C5NumberEngine::getInt() { //int

  int bmax;
  int bmin;

    for (const auto& element : requeriments[this->indice]->getMiVector()) {

      if (element->getType() == "int"){
        bmax = element->getBmax();
        bmin = element->getBmin();
      }
    }

    int numeroEntero = getInt(bmin, bmax);
    return numeroEntero;


}

double C5NumberEngine::getReal(double bmin, double bmax) {
    std::random_device rd;
    std::mt19937 generador(rd());
    std::uniform_real_distribution<double> distribucion(bmin, bmax);
    double numeroReal = distribucion(generador);
    long tiempoDesdeEjecucion = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock::now().time_since_epoch()).count();
    long elapsedTime = tiempoDesdeEjecucion - requeriments[this->indice]->getInitialTime();
    requeriments[this->indice]->setDatos("double", numeroReal, bmin, bmax, elapsedTime);
    return numeroReal;
}

double C5NumberEngine::getReal() { //double


  double bmax;
  double bmin;

    for (const auto& element : requeriments[this->indice]->getMiVector()) {

      if (element->getType() == "double"){
        bmax = element->getBmax();
        bmin = element->getBmin();
      }
    }
    double numeroReal = getReal(bmin, bmax);
    return numeroReal;
}

InfoObjeto C5NumberEngine::getNumberOld(int ordinal) {

    for (const auto& element : requeriments[this->indice]->getMiVector()) {

      if(element->getOrdinal() == ordinal){

            InfoObjeto info;
            info.value = element->getValue();
            info.bmin = element->getBmin();
            info.bmax = element->getBmax();
            string xd = to_string(element->getTime());
            info.time = xd;
            return info; // Devuelve la información del objeto encontrado
      }

    }

    throw std::runtime_error("Objeto no encontrado"); // Error por si no hay ningun objeto con ese ordinal
    
}

Estadisticas C5NumberEngine::getStat(int userId) {

  for (const auto& element : requeriments){

      if(element->getUserId() == userId){
        Estadisticas stats;
        stats.cantidadDeNumeros = element->getMiVector().size();
        stats.suma = 0;
        for (const auto& element2 : element->getMiVector()){
          stats.suma = stats.suma + element2->getValue();
        }
        stats.promedio = stats.suma / stats.cantidadDeNumeros;
        return stats;
      }
  }
  throw std::runtime_error("userId no encontrado"); // Error por si no hay ningun objeto con ese userID
}

std::vector<InfoObjeto> C5NumberEngine::getNumberList(int userId) { 

std::vector<InfoObjeto> listado;

   for (const auto& element : requeriments){

      if(element->getUserId() == userId){
        InfoObjeto info;           
        for(const auto& element2 : element->getMiVector()){
          info.bmin = element2->getBmin();
          info.bmax = element2->getBmax();
          info.time = to_string(element2->getTime());
          info.type = element2->getType();
          info.value = element2->getValue();
          info.ordinal = element2->getOrdinal();
          listado.push_back(info);
        }
      return listado;
      }
  }
  throw std::runtime_error("userId no encontrado"); // Error por si no hay ningun objeto con ese userID

}

std::vector<C5Requeriment*> C5NumberEngine::getRequeriment(){
  return this->requeriments;
}
