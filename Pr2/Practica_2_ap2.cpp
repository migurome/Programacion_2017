
/*
Fallos: 

Queda por revisar el caso en el que queremos desplazar, con la excavadora, elementos a la posicion 0 de array, en principio
no se puede desplazar completamente elementos a la izquierda, pero si a la derecha.
*/

#include <locale.h>
#include <iostream>
#include <string>
#include <fstream>
using namespace std;

const int MAX_PROD = 25;
const int PROD_NULO = 0;
const int CENTINELA = -1;
typedef double tArray[MAX_PROD];

//Métodos de manejo de filas:
void mostrarFila(const tArray fila, int tam);
bool esPosValida(int tam, int pos);
bool estaVacia(const tArray fila, int pos);
//Métodos de manejo de ficheros:
void leerFilaFich(ifstream &fich, tArray fila, int &tam);
void escribirFilaFich(ofstream &fich, const tArray fila, int tam);
//Métodos de grúa:
bool esPosibleGrua1Entre(const tArray fila, int tam, int posIni,int posSoltar);
bool grua1Elemento(tArray fila, int tam, int posIni, int posSoltar);
bool sonPosicionesPosiblesGrua(int tam, int posIni, int posFin, int posSoltar);
bool esPosibleGrua(const tArray fila, int tam, int posIni, int posFin, int posSoltar);
bool grua(tArray fila, int tam, int posIni, int posFin, int posSoltar);
void ejecutarGrua(tArray fila, int tam);
//Métodos de excavadora:
int posHuecoLibreDerecha(const tArray fila, int tam, int posIni);
bool excavadora1Derecha(tArray fila, int tam, int posIni);
int posHuecoLibreIzquierda(const tArray fila, int tam, int posIni);
bool excavadora1Izquierda(tArray fila, int tam, int posIni);
void ejecutarExcavadora(tArray fila, int tam);
bool excavadora(tArray fila, int tam, int posIni, int numDespla, int direccion);
//Métodos del menú:
int menu();
void ejecutarLeerFichero(tArray fila, int &tam);
void ejecutarGuardarFichero(const tArray fila, int tam);
void ejecutarOpc(int opc, tArray fila, int &tam);


int main(){

	menu();	
 	return 0;
}

// METODOS DE MANEJO DE FILAS //

//Dada una fila, la muestra en pantalla siguiendo el formato del final de la segunda página.
void mostrarFila(const tArray fila, int tam){

	// MOSTRAR EL CONTENIDO DEL ARRAY
	for(int i = 0; i < tam; i++){
		if(fila[i] < 10)
			cout << " ";

		if(fila[i] != PROD_NULO)
			cout << fila[i] << "|";
		else
			cout << "0" << "|";
	}
	
	cout << endl;

	// MOSTRAR UNA LINEA DE SEPARACIÓN
	for(int i = 0; i < tam*3; i++)
		cout << "-";

	cout << endl;
	
	// MOSTRAR EL TOTAL DE CASILLAS NUMERADAS
	for(int i = 0; i < tam; i++){
		if(i < 10)
			cout << " ";
		cout << i << "|";
	}

	cout << endl;

}

//Devuelve si la posición pos es válida en la fila de tamaño tam.
bool esPosValida(int tam, int pos){

	bool var = false;

	if(pos < tam && pos >= 0)
		var = true;

	return var;
}

//Devuelve si la posición pos está vacía.
bool estaVacia(const tArray fila, int pos){

	bool var = false;

	if(fila[pos] == PROD_NULO)
		var = true;

	return var;

}

// METODOS DE MANEJO DE FICHEROS //

//Dado el fichero de lectura abierto fich, carga su contenido en la fila.
void leerFilaFich(ifstream &fich, tArray fila, int &tam){

	int i = 0, elem = 0;

	//Leo los elementos del fichero hasta que llegue a su tamaño máximo o hasta que encuentre un -1
	if(fich.is_open()){
		for(i = 0; (i < MAX_PROD) && (elem != -1); i++){
			fich >> elem;
			fila[i] = elem;
		}
	}

	//Paso valores a tam
	tam = i-1;

}

//Dado el fichero de escritura abierto fich, guarda en dicho fichero el contenido de la fila.
void escribirFilaFich(ofstream &fich, const tArray fila, int tam){

	if(fich.is_open()){
		for(int i = 0; i < tam; i++)
			fich  << fila[i] << " ";
	}

	fich  << -1;
}

//Métodos de grúa://////////////////////////////////////////////////
//Devuelve cierto si posIni y posSoltar son posiciones válidas de la fila y además es posible dejar caer el contenido de la fila
//situado en posIni en su posición posSoltar.
bool esPosibleGrua1Entre(const tArray fila, int tam, int posIni,int posSoltar){
	return ( esPosValida(tam, posIni) && esPosValida(tam, posSoltar) && estaVacia(fila, posSoltar) );
}

///Si es posible, realiza el movimiento de la grúa entre las posiciones posIni y posSoltar. Devuelve si el movimiento se ha realizado.
bool grua1Elemento(tArray fila, int tam, int posIni, int posSoltar){

	bool realizado = false;

	if(esPosibleGrua1Entre(fila,tam,posIni,posSoltar)){
		fila[posSoltar] = fila[posIni];
		fila[posIni] = PROD_NULO;
		realizado = true;
	}

	return realizado;
}

//Métodos de excavadora://////////////////////////////////////////////////
//Devuelve la posición del primer hueco libre de la fila si, comenzando por posIni, vamos avanzando paso a paso hacia la derecha. 
//Si no hay ninguno, devolverá el valor tam.
int posHuecoLibreDerecha(const tArray fila, int tam, int posIni){

	int i = posIni;

	while(!estaVacia(fila,i) && esPosValida(tam,i)){
		i++;
	}

	if(i == tam)
		i = tam;

	return i;
 
}

//Devuelve la posición del primer hueco libre de la fila si, comenzando por posIni, vamos avanzando paso a paso hacia la izquierda. 
//Si no hay ninguno, devolverá el valor tam.
int posHuecoLibreIzquierda(const tArray fila, int tam, int posIni){

	int i = posIni;

	while(!estaVacia(fila,i) && esPosValida(tam,i)){
		i--;
	}

	if(i == tam)
		i = tam;

	return i;
 
}

//Desplaza la pala de la excavadora desde posIni una posición hacia la derecha, empujando desde su posición todos los elementos 
//adyacentes (es decir, no separados por huecos) hacia la derecha, y así, eliminando el primer hueco libre que haya en tal dirección. 
//Recuerda que los materiales empujados no atraviesan los muros del final de la fila. Devuelve un booleano indicando si el 
//desplazamiento ha podido ser realizado. Se considera así si la posición inicial es correcta, aunque no realice ninguna modificación 
//visible sobre la fila.

bool excavadora1Derecha(tArray fila, int tam, int posIni){

	int i = posIni;
	bool retorno = true;
	//Encontrar el primer hueco libre
	while((esPosValida(tam, i) && !estaVacia(fila, i)))
		i++;

	if(esPosValida(tam, i)){
		for(i; i > posIni; i--)
			fila[i] = fila[i-1];
		//Finalmente eliminamos el ultimo elemento
		fila[i] = PROD_NULO;
	}
	else
		retorno = false;

	return retorno;
}

//Desplaza la pala de la excavadora desde posIni una posición hacia la izquierda, empujando desde su posición todos los elementos 
//adyacentes (es decir, no separados por huecos) hacia la derecha, y así, eliminando el primer hueco libre que haya en tal dirección. 
//Recuerda que los materiales empujados no atraviesan los muros del final de la fila. Devuelve un booleano indicando si el 
//desplazamiento ha podido ser realizado. Se considera así si la posición inicial es correcta, aunque no realice ninguna modificación 
//visible sobre la fila.

bool excavadora1Izquierda(tArray fila, int tam, int posIni){

	int i = posIni;
	bool retorno = true;
	//Encontrar el primer hueco libre
	while((esPosValida(tam, i) && !estaVacia(fila, i)))
		i--;

	if(esPosValida(tam, i)){
		for(i; i < posIni; i++)
			fila[i] = fila[i+1];
		//Finalmente eliminamos el ultimo elemento
		fila[posIni] = PROD_NULO;
	}
	else
		retorno = false;

	return retorno;	
}

//Métodos del menú://////////////////////////////////////////////////

//Muestra el menú de opciones, solicita al usuario su respuesta, y devuelve la opción escogida cuando el usuario haya respondido 
//una opción válida.
int menu(){

	bool continua = true;
	int opc;

	int tam;
	tArray fila;
	ofstream fich_out;


	while(continua){

		cout << "1.- Cargar fila de fichero" << endl
				<< "2.- Guarda fila en fichero" << endl
				<< "3.- Usar grúa (1 elemento)" << endl
				<< "4.- Usar excavadora (1 posición derecha)" << endl
				<<  "0.- Salir" << endl << endl;

		cin >> opc;

		if(opc == 0)
			continua = false;
		else
			ejecutarOpc(opc, fila, tam);
	}
}

//Pide al usuario el nombre del fichero del que cargará su fila. Si existe, carga la fila, y si no, la fila se inicializa como vacía.
//Debe informar al usuario sobre si ha logrado realizar la carga, así como mostrar la fila leída.
void ejecutarLeerFichero(tArray fila, int &tam){

	string nombre_fichero;
	ifstream fich_in;
	int i;

	cout << "Introduce el nombre del fichero a cargar" << endl;
	cin >> nombre_fichero;

	fich_in.open(nombre_fichero.c_str() , ios::in);
	
	if(!fich_in.is_open()){
		for(i = 0; i < MAX_PROD; i++)
			fila[i] = PROD_NULO;
		fila[i] = CENTINELA;
		cout << "El fichero no existe" << endl;
	}
	else
		leerFilaFich(fich_in, fila, tam);
}

//Pide al usuario el nombre del fichero en el que se guardará la fila. Si logra abrirlo, guarda en el fichero la fila, usando el 
//formato visto antes. Debe informar al usuario sobre si ha logrado realizar el guardado. 
void ejecutarGuardarFichero(const tArray fila, int tam){

	string nombre_fichero;
	ofstream fich_out;
	int i;

	cout << "Introduce el nombre del fichero a guardar" << endl;
	cin >> nombre_fichero;

	fich_out.open(nombre_fichero.c_str() , ios::out);

	if(!fich_out.is_open())
		cout << "Error en la apertura del fichero" << endl;
	else{
		escribirFilaFich(fich_out, fila, tam);
		cout << "Operacion realizada con exito" << endl;
	}

}

//En esta versión, pregunta al usuario qué posición quiere levantar y en qué posición quiere dejarlo caer. Si es posible, 
//realizará el movimiento. Si el movimiento no fue posible, informará al usuario de ello. Se mostrará cómo queda la fila tras
//el movimiento.
void ejecutarGrua(tArray fila, int tam){

	int posIni, posSoltar, posFin;

	mostrarFila(fila, tam);

	cout << "Introduce la posicion inicial" << endl;
	cin >> posIni;
	cout << "Introduce la posicion final" << endl;
	cin >> posFin;
	cout << "Introduce la posicion en que quieres soltar" << endl;
	cin >> posSoltar;
	
	if(grua(fila, tam, posIni, posFin, posSoltar)){
		cout << "Operacion realizada con exito" << endl;
	}
	else
		cout << "No se ha podido realizar la operacion" << endl;

	mostrarFila(fila, tam);

}

//Pregunta al usuario desde qué posición empujará la excavadora. Entonces lo hace, o bien indica que no lo ha hecho (porque la 
//posición desde la que pidió empujar es inválida). Muestra cómo queda la fila tras el movimiento.
void ejecutarExcavadora(tArray fila, int tam){

	int posIni, numDespla, direccion;

	mostrarFila(fila, tam);

	cout << "Introduce la posicion inicial" << endl;
	cin >> posIni;
	cout << "Introduce el numero de desplazamientos" << endl;
	cin >> numDespla;
	cout << "Introduce la direccion, [0 - Izquierda | 1 - Derecha]" << endl;
	cin >> direccion;
	
	if(excavadora(fila, tam, posIni, numDespla, direccion))
		cout << "Operacion realizada con exito" << endl;
	else
		cout << "No es posible realizar el desplazamiento" << endl;

	mostrarFila(fila, tam);

}

//Dada la opción escogida por el usuario en el menú, la ejecuta.
void ejecutarOpc(int opc, tArray fila, int &tam){

	switch ( opc ){
		
		case 1:
			ejecutarLeerFichero(fila, tam);
  		break;
		
		case 2:
  			ejecutarGuardarFichero(fila, tam);
 	 	break;

 	 	case 3:
			ejecutarGrua(fila, tam);	
 	 	break;

 	 	case 4:
			ejecutarExcavadora(fila, tam);
 	 	break;

		default:
  			cout << "Opcion incorrecta" << endl;
  		break;
	}

}

// NEW FUNCTIONS

//Devuelve si el segmento a levantar no tiene su extremo derecho antes que el izquierdo y si todas las posiciones involucradas son
//válidas en la fila de tamaño tam. Fíjate en que, para comprobar lo segundo, basta con comprobarlo para los cuatro extremos
//involucrados.

bool sonPosicionesPosiblesGrua(int tam, int posIni, int posFin, int posSoltar){

	bool condicion = true;
	int tamanio = posFin - posIni;
 
	if((posIni > posFin) || (posIni < 0) || (posFin >= tam) || ((tamanio + posSoltar) >=  tam))
		condicion = false;
	
	return condicion;
}

//Devuelve si es posible realizar el movimiento de la grúa, es decir, si es posible dejar caer todos los materiales de la fila
//desde posIni hasta posFin a partir de la posición posSoltar.

bool esPosibleGrua(const tArray fila, int tam, int posIni, int posFin, int posSoltar){

	bool condicion = true;
	int tamanio;

	if(sonPosicionesPosiblesGrua(tam, posIni, posFin, posSoltar)){
	
		tamanio = posFin - posIni;
	
		for(int i = posSoltar; i <= (posSoltar + tamanio); i++)
			if(fila[i] != PROD_NULO)
				condicion = false;
	}
	else
		condicion = false;

	return condicion;
}

//Primero se comprueba si el movimiento es posible tal y como descubre la función anterior. Si es así, realiza el movimiento de la
//grúa de la siguiente manera: se ponen en un array auxiliar los elementos a levantar, se ponen huecos en sus correspondientes 
//posiciones de la fila, y después se sueltan los elementos del array auxiliar en la fila, a partir de la posición a soltar.
bool grua(tArray fila, int tam, int posIni, int posFin, int posSoltar){

	bool condicion = true;
	tArray auxiliar;
	int recorrido = posFin - posIni;

	if(esPosibleGrua(fila, tam, posIni, posFin, posSoltar)){
		for(int i = 0; i <= recorrido; i++){
			auxiliar[i] = fila[posIni + i];
			fila[posIni + i] = PROD_NULO;
			fila[posSoltar + i] = auxiliar[i];
		}
	}
	else
		condicion = false;

	return condicion;
}


// MÉTODOS DE EXCAVADORA ///////////////////////////////////////////////////

//Primero se comprueba si el movimiento es posible, es decir, si la posición desde la que empezar a empujar es válida. Si es así, se
//lleva a cabo el movimiento de la excavadora: la excavadora se sitúa en la posición posIni y se mueve numDespla posiciones hacia la 
//dirección empujando los materiales que encuentre a su camino. La implementación se hará en pasadas sucesivas de 1 desplazamiento de
//toda la hilera de materiales empujados en cada una, ocupando un nuevo hueco en cada uno. Fíjate en que la hilera empujada podría 
//hacerse cada vez más grande a lo largo de las pasadas. Si en algún desplazamiento se empujan materiales contra el muro inicial o final, 
//el resto de desplazamientos hasta llegar a numDespla no tienen efecto (ej. si en el primer ejemplo de la página 1 empujásemos desde 
//la posición 14 hacia la derecha 30 posiciones, el resultado sería igual que si lo hiciéramos sólo tres: 4, 6 y 8 quedarían en las 
//posiciones 17, 18 y 19).
bool excavadora(tArray fila, int tam, int posIni, int numDespla, int direccion){

	// int direccion
		// 0 Izquierda
		// 1 Derecha

	bool retorno = true;

	if(direccion == 1){ // Excavadora a la derecha
		for(int i = 0 ; i < numDespla; i++)
			if (posHuecoLibreDerecha(fila, tam, posIni + i))
				excavadora1Derecha(fila, tam, posIni + i);
			else
				retorno = false;

	}
	else{
		for(int i = posIni; i > (posIni - numDespla); i--)
			if (posHuecoLibreIzquierda(fila, tam, i))
				excavadora1Izquierda(fila, tam, i);
			else
				retorno = false;
	}
/*
int posHuecoLibreIzquierda(const tArray fila, int tam, int posIni);
bool excavadora1Izquierda(tArray fila, int tam, int posIni);
void ejecutarExcavadora(tArray fila, int tam);
*/

}
