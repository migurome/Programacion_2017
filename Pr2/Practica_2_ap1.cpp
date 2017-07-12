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
//Métodos de excavadora:
int posHuecoLibreDerecha(const tArray fila, int tam, int posIni);
bool excavadora1Derecha(tArray fila, int tam, int posIni);
int posHuecoLibreIzquierda(const tArray fila, int tam, int posIni);
bool excavadora1Izquierda(tArray fila, int tam, int posIni);
//Métodos del menú:
int menu();
void ejecutarLeerFichero(tArray fila, int &tam);
void ejecutarGuardarFichero(const tArray fila, int tam);
void ejecutarGrua(tArray fila, int tam);
void ejecutarExcavadora(tArray fila, int tam);
void ejecutarOpc(int opc, tArray fila, int &tam);

int tamanioFichero(const tArray fila);

int main(){
	


	menu();	


 	return 0;
}

// METODOS DE MANEJO DE FILAS //

//CORRECTO//Dada una fila, la muestra en pantalla siguiendo el formato del final de la segunda página.
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

//CORRECTO//Devuelve si la posición pos es válida en la fila de tamaño tam.
bool esPosValida(int tam, int pos){

	bool var = false;

	if(pos < tam)
		var = true;

	return var;
}

//CORRECTO////Devuelve si la posición pos está vacía.
bool estaVacia(const tArray fila, int pos){

	bool var = false;

	if(fila[pos] == PROD_NULO)
		var = true;

	return var;

}

// METODOS DE MANEJO DE FICHEROS //

//CORRECTO//Dado el fichero de lectura abierto fich, carga su contenido en la fila.
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

//CORRECTO//Dado el fichero de escritura abierto fich, guarda en dicho fichero el contenido de la fila.
void escribirFilaFich(ofstream &fich, const tArray fila, int tam){

	if(fich.is_open()){
		for(int i = 0; i < tam; i++)
			fich  << fila[i] << " ";
	}

	fich  << -1;
}

//Métodos de grúa://////////////////////////////////////////////////
//Devuelve cierto si posIni y posSoltar son posiciones válidas de la fila y además es posible dejar caer el contenido de la fila
//CORRECTO//situado en posIni en su posición posSoltar.
bool esPosibleGrua1Entre(const tArray fila, int tam, int posIni,int posSoltar){
	return ( esPosValida(tam, posIni) && esPosValida(tam, posSoltar) && estaVacia(fila, posSoltar) );
}

//CORRECTO PARECE QUE...///Si es posible, realiza el movimiento de la grúa entre las posiciones posIni y posSoltar. Devuelve si el movimiento se ha realizado.
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
//CORRECTO//Si no hay ninguno, devolverá el valor tam.
int posHuecoLibreDerecha(const tArray fila, int tam, int posIni){

	int i = posIni;

	while(!estaVacia(fila,i) && esPosValida(tam,i)){
		i++;
	}

	if(i == tam)
		i = tam;

	return i;
 
}

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

	int posIni, posSoltar;

	mostrarFila(fila, tam);

	cout << "Introduce la posicion que quieres levantar" << endl;
	cin >> posIni;
	cout << "Introduce la posicion en que quieres soltar" << endl;
	cin >> posSoltar;
	
	if(!esPosibleGrua1Entre(fila, tam, posIni, posSoltar))
		cout << "No es posible realizar la operacion" << endl;
	else{
		grua1Elemento(fila, tam, posIni, posSoltar);
		mostrarFila(fila, tam);
		cout << "Operacion realizada con exito" << endl;
	}
}
//Pregunta al usuario desde qué posición empujará la excavadora. Entonces lo hace, o bien indica que no lo ha hecho (porque la 
//posición desde la que pidió empujar es inválida). Muestra cómo queda la fila tras el movimiento.
void ejecutarExcavadora(tArray fila, int tam){

	int posIni;

	mostrarFila(fila, tam);

	cout << "Introduce la posicion inicial" << endl;
	cin >> posIni;
	
	if(posHuecoLibreDerecha(fila, tam, posIni) != tam){
		if(excavadora1Derecha(fila, tam, posIni))
			cout << "Operacion realizada con exito" << endl;
	}
	else
		cout << "No es posible realiizar el desplazamiento" << endl;

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
