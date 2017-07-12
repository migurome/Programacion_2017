#include <iostream>
#include <string>
#include <fstream>
using namespace std;

int solicitaAnyo();
int solicitaMes();
int solicitaDia(int mes, int anyo);
bool esBisiesto(int anyo);
int diasMes(int mes, int anyo);
bool diasMesCorrecto(int mes , int dia, int anyo);
long int diasTranscurridos (int dia, int mes, int anyo);
long int diasAnyosCompletos (int anyo);
int diasEsteAnyo (int dia, int mes, int anyo);
int contarBisiestos (int anyoInicio, int anyoFinal);
int diasMes (int mes, int anyo);
int diaSemana (long int numDias);
string nombreDia (int representacionDia);
string diaDeLaSemana(int dia, int mes, int anyo);
string nombreMes(int mes);
int diaDeLaSemanaEntero(int dia, int mes, int anyo);
int primerDomingoMes(int mes, int anyo);
int contadorDomingosMes(int mes, int anyo);
int domingosAnyo(int anyo);
bool puentes(int anyo);

int main(){

 	return 0;
}

// solicita, valida y devuelve un año introducido por el usuario a través de teclado. Debe ser 1900 o posterior.
int solicitaAnyo(){

	int var;
	bool ok = true;

	while(ok){
		cout << "Introduce un año" << endl;
		cin >> var;
	
		if(var >= 1900)
			ok = false;
		else
			cout << "El año debe ser superior a 1900" << endl;
	}

	return var;

}

//Pide un mes al usuario
int solicitaMes(){

	int var;
	bool ok = true;

	while(ok){
		cout << "Introduce un mes" << endl;
		cin >> var;
	
		if(var <= 12 && var >= 1)
			ok = false;
		else
			cout << "El mes debe estar contenido entre 1 y 12" << endl;
	}

	return var;

} 

// Pide un dia de entrada al usuario
int solicitaDia(int mes, int anyo){

	int dia;
	bool bisiesto = false;
	bool ok = true;

	while(ok){

		cout << "Introduce dia" << endl;
		cin >> dia;

		if(dia >= 1 && dia <= 31 ){
			ok = false;
			ok = diasMesCorrecto(mes , dia, anyo);
		}
		else
			cout << "Dia incorrecto" << endl << endl;
	}

	return dia;
}


// Calcula el numero de dias transcurridos desde el 1/1/1900 hasta el 1/1 del año introducido
long int diasAnyosCompletos (int anyo){
	
	long cuenta_total = 0;

		for(int i = 1900; i < anyo; i++)
			if(esBisiesto(i))
				cuenta_total += 366;
			else
				cuenta_total += 365;

	return cuenta_total;
}

// Calcula el numero de dias transcurridos desde el 1/1/1900 hasta la fecha de entrada
long int diasTranscurridos (int dia, int mes, int anyo){

	long cuenta_total = 0;

	for(int i = 1900; i < anyo; i++)
		if(esBisiesto(i))
			cuenta_total += 366;
		else
			cuenta_total += 365;

	for(int i = 1; i < mes; i++)
		cuenta_total += diasMes(i, anyo);

	for(int i = 1; i < dia; i++)
		cuenta_total++;

	return cuenta_total;
}

// Calcúla el número de días que tiene el mes 
int diasMes(int mes, int anyo){

	int dia;

	if(mes == 1 || mes == 3 || mes == 5 || mes == 7 || mes == 8 || mes == 10 || mes == 12)
		dia = 31;
	else if(mes == 4 || mes == 6 || mes == 5 || mes == 9 || mes == 11)
		dia = 30;
	else{
		if(esBisiesto(anyo))
			dia = 29;
		else
			dia = 28;
	}

	return dia;
}

// Nos indica si el día del mes es correcto
bool diasMesCorrecto(int mes , int dia, int anyo){

	bool var = false;

	if(dia > diasMes(mes, anyo))
		var = true;

	return var;
}

// Nos indica si un año es o no bisiesto
bool esBisiesto(int anyo){
	return ((anyo % 4 == 0 && anyo % 100 != 0) || anyo % 400 == 0);
}

//devuelve el número de días transcurridos desde la fecha 1/enero/anyo hasta la fecha dia/mes/anyo.
int diasEsteAnyo (int dia, int mes, int anyo){

	int cuenta_total = 0;

	for(int i = 1; i < mes; i++)
		cuenta_total += diasMes(i, anyo);

	for(int i = 1; i < dia; i++)
		cuenta_total += i;

	return cuenta_total;
}

//Cuenta el numero de anios bisiestos entre dos fechas
int contarBisiestos (int anyoInicio, int anyoFinal){

	int cuenta_total = 0;

	for(int i = anyoInicio; i <= anyoFinal; i++)
		if(esBisiesto(i))
			cuenta_total++;

	return cuenta_total;
}


//	devuelve una representación entera del día de la semana que es después de haber transcurrido
//	numDias días desde el 1/enero/1900 (0 si es lunes, 1 si es martes,..., 6 si es domingo).
int diaSemana (long int numDias){
	return (numDias%7);
}

//	recibe un entero que representa un día de la semana (0 si es lunes, 1 si es martes,..., 6 si es domingo) 
//	y devuelve una cadena con el nombre del día.
string nombreDia (int representacionDia){

	string semana[] = {	"Lunes", 
						"Martes", 
						"Miercoles"
						"Jueves"
						"Viernes"
						"Sábado"
						"Domingo"};

	return semana[representacionDia];
}

// Dado un numero enero devuelve una cadena con el texto de dicho mes
string nombreMes(int mes){

	string semana[] = {	"enero", 	
						"febrero", 
						"marzo"
						"abril"
						"mayo"
						"junio"
						"julio"
						"agosto"
						"septiembre"
						"octubre"
						"noviembre"
						"diciembre"};

	return semana[mes];

}

//	devuelve una cadena con el nombre del día de la semana en que cae la fecha dia/mes/anyo.
string diaDeLaSemana(int dia, int mes, int anyo){
	return nombreDia (diaSemana (diasTranscurridos (dia, mes, anyo)));
}

// recibe un dia - mes - año y devuelve el valor entero de ese día de la semana (0 lunes, 1 martes,...)
int diaDeLaSemanaEntero(int dia, int mes, int anyo){
	return diaSemana (diasTranscurridos (dia, mes, anyo));
}

//	devuelve el día del mes que corresponde al primer domingo del mes/anyo dados.
int primerDomingoMes(int mes, int anyo){

	int i = 1; 

	while(diaDeLaSemanaEntero(i, mes, anyo) != 6)
		i++;

	return i;
}

//Cuenta el numero total de domingos de un mes - anio que recibe como parámetro de entrada
int contadorDomingosMes(int mes, int anyo){

	int total = 0;
	int final = diasMes(mes, anyo);

	for(int i = 1; i <= final; i++){
		if(diaDeLaSemanaEntero(i, mes, anyo) == 6){
			total++;
		}
	}

	return total;
}

//	muestra por pantalla los domingos del año anyo y devuelve el número de domingos mostrados.
int domingosAnyo(int anyo){

	int domingos = 0;
	
	for(int i = 1; i <= 12; i++)
		domingos += contadorDomingosMes(i, anyo);

	return domingos;
}


// Dado un año calcula, extrayendo los datos del fichero FIESTAS cuales son los posibles puentes de ese anio y los 
// escribe en el fichero de salida puentes
bool puentes(int anyo){

	ifstream entrada;
	ofstream salida;
	int texto, dia, mes;
	bool next_it = true;

	entrada.open("fiestas.txt");
	salida.open("puentes.txt");

	// Nos posicionamos en el anio correcto
	while(next_it){
		entrada >> texto;
		if(texto == anyo)
			next_it = false;
	}

	next_it = true;

	// Escribo el año del puente porque si
	salida << anyo << endl;

	do{
		entrada >> dia >> mes;
		// No estamos ante una linea que no sea dia - mes
		if((dia <= 31 && mes <= 12) && (dia != 0 && mes != 0)){
			if(diaDeLaSemanaEntero(dia, mes, anyo) == 1 || diaDeLaSemanaEntero(dia, mes, anyo) == 3)
				salida << dia << " " << mes << endl;		}
		else{
			next_it = false;
			salida << "0 0";
		}
	}while(next_it);

	entrada.close();
	salida.close();
	
	return true;
}