#include <stdio.h>
#include <stdlib.h>

typedef struct{
	short int DD;
	short int MM;
	short int AAAA;
} date;
//devuelve la fecha anterior
date previous(date actual);

//devuelve la fecha posterior
date next(date actual);

short int is_leap(date actual);
short int days_month(date actual);
short int is_valid(date actual);

int main(void){
	date actual, prev, nex;
	char c;
	short int daysMM;
	printf("TP3-PARTE1-EJERCICIO 5");
	printf("\n\nA continuacion indicar una fecha con el formato DD/MM/AAAA\n");
	printf("\nSi indica una fecha incorrecta se volvera a pedir la fecha\n");
	printf("Presione una tecla: "); c = getchar();
	do{
		system("clear");
		do{
			system("clear");
			printf("\nDD:\t");scanf("%2hd", &actual.DD);
		}while((actual.DD < 1)||(actual.DD > 31));
		do{
			system("clear");
			printf("\nMM:\t");scanf("%2hd", &actual.MM);
		}while((actual.MM < 1)||(actual.MM > 12));
		system("clear");
		printf("\nAAAA:\t");scanf("%4hd", &actual.AAAA);
	}while(!is_valid(actual));
	system("clear");
	prev = previous(actual);
	nex = next(actual);
	daysMM = days_month(actual);

	printf("\nFecha actual: \t%hd/%hd/%hd", actual.DD, actual.MM, actual.AAAA);
	printf("\nFecha anterior: \t%hd/%hd/%hd", prev.DD, prev.MM, prev.AAAA);
	printf("\nFecha siguiente: \t%hd/%hd/%hd", nex.DD, nex.MM, nex.AAAA);
	printf("\nUltimo dia del mes: \t%hd/%hd/%hd", daysMM, actual.MM, actual.AAAA);
	printf("\nDias para que termine el mes: \t%d\n\n", daysMM-actual.DD);
	
}
date previous(date actual){
	date previous;
	if((actual.DD - 1) != 0){
		previous.DD = actual.DD-1;
		previous.MM = actual.MM;
		previous.AAAA = actual.AAAA;
	}
	else{
		previous.MM = actual.MM - 1; previous.AAAA = actual.AAAA;
		previous.DD = days_month(previous);
		previous.MM = ((actual.MM-1) != 0)? actual.MM - 1:12;
		previous.AAAA = ((actual.MM-1) != 0)? actual.AAAA:actual.AAAA-1;
	}
	return (previous);
}
date next(date actual){
	date next;
	if(actual.DD < days_month(actual)){
		next.DD = actual.DD + 1;
		next.MM = actual.MM;
		next.AAAA = actual.AAAA;
	}
	else{
		next.DD = 1;
		next.MM = (actual.MM != 12)? actual.MM + 1:1;
		next.AAAA = (actual.MM != 12)? actual.AAAA:actual.AAAA+1;
	}
	return (next);
}
short int days_month(date actual){
	if (actual.MM != 2){
		return((((actual.MM%2)&&(actual.MM <= 7))||(!(actual.MM%2)&&(actual.MM > 7))||(actual.MM == 0))? 31:30);
	}
	else{
		return((is_leap(actual))?29:28);
	}
}
short int is_leap(date actual){
	// es bisiesto si es divisible por 4 y no por 100 o si es divisile por 400
	return(((!(actual.AAAA%4)&&(actual.AAAA%100))||!(actual.AAAA%400))? 1:0);
}
short int is_valid(date actual){
	return((actual.DD <= days_month(actual))? 1:0);
}