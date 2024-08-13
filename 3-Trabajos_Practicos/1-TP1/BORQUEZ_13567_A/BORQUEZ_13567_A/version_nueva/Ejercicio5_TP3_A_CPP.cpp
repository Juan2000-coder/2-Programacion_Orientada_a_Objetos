/**
 * Programa que determina la fecha anterior, la fecha siguiente
 * y la cantidad de días para concluir el mes de una fecha valida
 * ingresada por el usuario
 * 
 * @version 
 * @date 	2023.08.23
 * @author 	Juan Manuel BORQUEZ PEREZ
 * @contact borquez.juan00@gmail.com
 * 
*/
#include <iostream>		//Cambio de los nombres de las librerías
#include <cstdlib>		//Cambio de los nombres de las librerías
#include <ios>			//Para <streamsize>
#include <iomanip>
#include <limits>		//Para numeric_limits
#include <string>		//Por stoi

using namespace std;	//Uso del espacio de nombres estándar

struct Date{			//Eliminación del modificador "typedef" en la declaración de la estructura
	short int DD;
	short int MM;
	short int AAAA;
};

Date previous(Date actual);	//Devuelve la fecha anterior
Date next(Date actual);		//Devuelve la fecha posterior

bool is_leap(Date actual);		//Cambio del tipo de dato de retorno (lógico) a "bool"
short int days_month(Date actual);
bool valid_DD(char* DD);
bool valid_MM(char* MM);
bool valid_AAAA(char* AAAA);
bool valid_date(Date actual);	//Cambio del tipo de dato de retorno (lógico) a "bool"
void print_out(Date current, Date previous, Date next, short int days_MM);

int main(void){
	Date current_date;		//Fecha actual
	Date previous_date;		//Fecha anterior
	Date next_date;			//Fecha siguiente
	char auxiliar[5];		//Variable auxiliar para entrada del usuario
	short int month_days;	//Número de días en el mes de la fecha

	cout << "\nTP3-PARTE1-EJERCICIO 5" << "\n\n\n";	//Cambio de la función de salida estándar.
	cout << "A continuacion indicar una fecha con el formato DD/MM/AAAA\n\n";			//Cambio de la función de salida estándar.
	cout << "Si la fecha es incorrecta se solicitara que indique otra nuevamente\n";	//Cambio de la función de salida estándar.
	cout << "Se consideran solamente aquellas fechas desde el 1 de noviembre de 1582 inclusive\n\n";
	cout << "Presione ENTER: ";								//Cambio de la función de salida estándar.
	cin.ignore(numeric_limits<streamsize>::max(), '\n'); 	//Flush del buffer de entrada hasta la presión de ENTER

	do{
		do{
			system("cls");
			cout << "\nDD:" << setw(3);			//Cambio de la función de salida estándar.
			cin.get(auxiliar, 3);				//Cambio de la función de entrada estándar.
			cin.ignore(numeric_limits<streamsize>::max(), '\n'); 	//Flush del buffer de entrada hasta la presión de ENTER
		}while(!valid_DD(auxiliar));

		current_date.DD = stoi(auxiliar);			//Se extrae el número del string
		do{
			system("cls");
			cout << "\nMM:" << setw (3);		//Cambio de la función de salida estándar.
			cin.get(auxiliar, 3);				//Cambio de la función de entrada estándar.
			cin.ignore(numeric_limits<streamsize>::max(), '\n'); 	//Flush del buffer de entrada hasta la presión de ENTER
		}while(!valid_MM(auxiliar));

		current_date.MM = stoi(auxiliar);			//Se extrae el número del string
		do{
			system("cls");
			cout << "\nAAAA:" << setw(3);		//Cambio de la función de salida estándar.
			cin.get(auxiliar, 5);				//Cambio de la función de entrada estándar.
			cin.ignore(numeric_limits<streamsize>::max(), '\n'); 	//Flush del buffer de entrada hasta la presión de ENTER
		}while(!valid_AAAA(auxiliar));

		current_date.AAAA =  stoi(auxiliar);	//Se extrae el número del string
	}while(!valid_date(current_date));

	system("cls");
	previous_date = previous(current_date);			//Obtención de la fecha previa
	next_date = next(current_date);					//Obtención de la fecha siguiente
	month_days = days_month(current_date);			//Obtención de la cantidad de días en el mes
	print_out(current_date, previous_date, next_date, month_days);	//Muestra por pantalla en columnas
	return EXIT_SUCCESS;
}
/**
 * @brief Determina la fecha previa a una fecha dada
 * @param actual - la fecha actual
 * @return previous - la fecha anterior a la actual
*/
Date previous(Date actual){
	Date previous = actual;
	if((actual.DD - 1) != 0){
		//Actual no es el primer día del mes
		previous.DD = actual.DD - 1;
	}
	else{
		//Actual es el primer día del mes
		if((actual.MM - 1) != 0){
			//Actual no está en el primer mes del año
			previous.MM = actual.MM - 1;
		}
		else{
			//Actual está en el primer mes del año
			previous.MM = 12;
			previous.AAAA = actual.AAAA - 1;
		}
		//Entonces se obtienen la cantidad de días del mes anterior
		previous.DD = days_month(previous);
	}
	return(previous);
}
/**
 * @brief Determina la fecha siguiente a una fecha dada
 * @param actual - la fecha actual
 * @return next - la fecha siguiente a la actual
*/
Date next(Date actual){
	Date next = actual;
	if(actual.DD < days_month(actual)){
		//No es el último día del mes
		next.DD = actual.DD + 1;
	}
	else{
		//Es el último día del mes
		next.DD = 1;
		if(actual.MM != 12){
			//No esta en el último mes del año
			next.MM = actual.MM + 1;
		}
		else{
			//Está en el último mes del año
			next.MM = 1;
			next.AAAA = actual.AAAA + 1;
		}
	}
	return (next);
}
/**
 * @brief Determina la cantidad del mes de la fecha
 * @param actual - la fecha actual
 * @return la cantidad de días del mes
*/
short int days_month(Date actual){
	if (actual.MM != 2){
		//No es febrero
		//La siguiente determina y devuelve la cantidad de dias en el mes actual

		//return(((es mes impar entes de agosto) o (es mes par despues de julio))?    31:30);
		return((((actual.MM%2)&&(actual.MM <= 7))||(!(actual.MM%2)&&(actual.MM > 7)))? 31:30);

	}
	else{
		//Es febrero
		return(is_leap(actual)?29:28);
	}
}
/**
 * @brief Determina si el año de la fecha es bisiesto o no
 * @param actual - la fecha actual
 * @return true si es bisiesto o false si no lo es
*/
bool is_leap(Date actual){		//Cambio del tipo de dato lógico a bool
	//return(((divisible por 4 y no por 100)     o  (es divisible por 400))? true:false);
	return(((!(actual.AAAA%4)&&(actual.AAAA%100))||!(actual.AAAA%400))? true:false);
}
/**
 * @brief Determina si una cadena es válida como día de una fecha
 * @param DD - una cadena de a lo sumo 2 carácteres
 * @return true si la cadena es valida o false si no lo es
*/
bool valid_DD(char* DD){
	int dia;
	try {
        dia = stoi(DD, nullptr);
    } catch (const invalid_argument&) {
		return false;
    } catch (const out_of_range& ){
		return false;
    }
	return((dia >= 1 )&&(dia <= 31))? true:false;
}
/**
 * @brief Determina si una cadena es válida como mes de una fecha
 * @param MM - una cadena de a lo sumo 2 carácteres
 * @return true si la cadena es valida o false si no lo es
*/
bool valid_MM(char* MM){
	int mes;
	try {
        mes = stoi(MM, nullptr);
    } catch (const invalid_argument&) {
		return false;
    } catch (const out_of_range&) {
		return false;
    }
	return((mes >= 1 )&&(mes <= 12))? true:false;
}
/**
 * @brief Determina si una cadena es válida como año de una fecha
 * @param AAAA - una cadena de a lo sumo 4 carácteres
 * @return true si la cadena es valida o false si no lo es
*/
bool valid_AAAA(char* AAAA){
	int anio;
	try {
        anio = stoi(AAAA, nullptr);
    } catch (const invalid_argument&) {
		return false;
    } catch (const out_of_range&) {
		return false;
    }
	return true;
}
/**
 * @brief Determina si una fecha es valida
 * @param actual - la fecha actual
 * @return true si es una fecha válida o false si no lo es
*/
bool valid_date(Date actual){
	//Se consideran validas solamente a las fechas desde el mes siguiente al mes en que se instauró
	//el calendario gregoriano. Es decir, desde noviembre de 1582. Siempre que la fecha dada sea válida

	if((actual.AAAA > 1582)||((actual.AAAA == 1582)&&(actual.MM > 8))){
		return (actual.DD <= days_month(actual))? true:false;
	}
	return false;
}
/**
 * @brief Presenta por pantalla los resultados
 * @param current - la fecha actual
 * @param previous - la fecha anterior a la actual
 * @param next - la fecha siguiente a la actual
 * @param days_MM - la cantidad de dias en el mes
 * @return true si es una fecha válida o false si no lo es
*/
void print_out(Date current, Date previous, Date next, short int days_MM){
	cout<<setw(32)<<right<<setfill(' ')<<"Fecha actual|"
	<<setw(3)<<right<<setfill(' ')<<current.DD<<'/'
	<<setw(2)<<right<<setfill(' ')<<current.MM<<'/'
	<<setw(4)<<right<<setfill(' ')<<current.AAAA<<'\n'
	<<setw(32)<<right<<setfill(' ')<<"Fecha anterior|"
	<<setw(3)<<right<<setfill(' ')<<previous.DD<<'/'
	<<setw(2)<<right<<setfill(' ')<<previous.MM<<'/'
	<<setw(4)<<right<<setfill(' ')<<previous.AAAA<<'\n'
	<<setw(32)<<right<<setfill(' ')<<"Fecha siguiente|"
	<<setw(3)<<right<<setfill(' ')<<next.DD<<'/'
	<<setw(2)<<right<<setfill(' ')<<next.MM<<'/'
	<<setw(4)<<right<<setfill(' ')<<next.AAAA<<'\n'
	<<setw(32)<<right<<setfill(' ')<<"Dias para que termine el mes|"
	<<setw(3)<<right<<setfill(' ')<<days_MM-current.DD<<endl;
}