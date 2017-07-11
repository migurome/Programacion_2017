/*

Métodos del menú:
int menu() : Muestra el menú de opciones, solicita al usuario su
respuesta, y devuelve la opción escogida cuando el usuario haya
respondido una opción válida.
void ejecutarLeerFichero(tArray fila, int &tam) : Pide al usuario el
nombre del fichero del que cargará su fila. Si existe, carga la fila, y si no,
la fila se inicializa como vacía. Debe informar al usuario sobre si ha
logrado realizar la carga, así como mostrar la fila leída.
void ejecutarGuardarFichero(const tArray fila, int tam) : Pide al
usuario el nombre del fichero en el que se guardará la fila. Si logra
abrirlo, guarda en el fichero la fila, usando el formato visto antes. Debe
informar al usuario sobre si ha logrado realizar el guardado.
void ejecutarGrua(tArray fila, int tam) : En esta versión, pregunta al
usuario qué posición quiere levantar y en qué posición quiere dejarlo
caer. Si es posible, realizará el movimiento. Si el movimiento no fue
posible, informará al usuario de ello. Se mostrará cómo queda la fila tras
el movimiento.
void ejecutarExcavadora(tArray fila, int tam) : Pregunta al usuario
desde qué posición empujará la excavadora. Entonces lo hace, o bien
indica que no lo ha hecho (porque la posición desde la que pidió empujar
es inválida). Muestra cómo queda la fila tras el movimiento.
void ejecutarOpc(int opc, tArray fila, int &tam) : Dada la opción
escogida por el usuario en el menú, la ejecuta.
Para preparar tu código para la siguiente versión, al terminar la versión 1 es
recomendable que añadas también el movimiento de la excavadora hacia la
izquierda. Crea las dos funciones correspondientes para el avance a la
izquierda, observa que ambas son muy parecidas a las correspondientes
funciones hacia la derecha, y después reemplaza tus versiones de izquierda y de
derecha de cada función por una única función común que logre una cosa u otra
simplemente en función de un nuevo parámetro entero direccion (que
significará derecha si vale 1 e izquierda si vale -1). Generaliza y aprovecha lo
que hay en común, es decir, evita que tu código se limite a escoger entre el
código que desplaza a la izquierda o el que desplaza a la derecha con un if,
evita que tu programa tenga dos fragmentos de código casi idénticos (uno por
dirección). Tus funciones generalizadas para ambas direcciones serán las
siguientes:

int posHuecoLibreDir(const tArray fila, int tam, int posIni, int direccion)
bool excavadora1Dir(tArray fila, int tam, int posIni, int direccion)
Versión 2 del programa. - Vamos a extender las funcionalidades de las
opciones 3 y 4 del menú, de forma que se puedan realizar varios
desplazamientos a la vez con la excavadora o levantar varios materiales a la vez
con la grúa. En el menú, sustituye las antiguas opciones 3 y 4 por las siguientes:
3.- Usar grúa
4.- Usar excavadora
El nuevo movimiento de la grúa (opción 3) deberá preguntar tanto la posición
inicial y final de los materiales a levantar (extremos izquierdo y derecho del
segmento a levantar), como la posición de inicio sobre la que soltarlos. Si el
movimiento no es posible (porque las posiciones de recogida o de caída están
fuera del rango de posiciones válidas de la fila, porque el extremo izquierdo del
segmento a levantar es mayor que su extremo derecho, o porque algún material
caería encima de algún otro), lo indicará al usuario y no se hará nada.
Del mismo modo, la ejecución de la excavadora (opción 4) deberá preguntar la
posición inicial desde la que realizar el desplazamiento, así como la cantidad de
desplazamientos a realizar y en qué dirección realizarlos. Si el movimiento no
es posible (pues la posición inicial desde la que queremos empujar no existe), lo
indicará al usuario y no se hará nada. Además, recuerda que los muros son
infranqueables: si en la dirección del movimiento hay menos huecos libres que
el número de posiciones que se pide desplazar, se realizarán sólo los
desplazamientos posibles.
*/

/****************************************************************************
Para preparar tu código para la siguiente versión, al terminar la versión 1 es
recomendable que añadas también el movimiento de la excavadora hacia la
izquierda. Crea las dos funciones correspondientes para el avance a la
izquierda, observa que ambas son muy parecidas a las correspondientes
funciones hacia la derecha, y después reemplaza tus versiones de izquierda y de
derecha de cada función por una única función común que logre una cosa u otra
simplemente en función de un nuevo parámetro entero direccion (que
significará derecha si vale 1 e izquierda si vale -1). Generaliza y aprovecha lo
que hay en común, es decir, evita que tu código se limite a escoger entre el
código que desplaza a la izquierda o el que desplaza a la derecha con un if,
evita que tu programa tenga dos fragmentos de código casi idénticos (uno por
dirección). Tus funciones generalizadas para ambas direcciones serán las
siguientes:

int posHuecoLibreDir(const tArray fila, int tam, int posIni, int direccion)
bool excavadora1Dir(tArray fila, int tam, int posIni, int direccion)
*/

#include <locale.h>
#include <iostream>
#include <string>
#include <fstream>
using namespace std;

const int MAX_ELEM = 25;
typedef double tArray[MAX_ELEM];

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
//Métodos del menú:
int menu();
void ejecutarLeerFichero(tArray fila, int &tam);
void ejecutarGuardarFichero(const tArray fila, int tam);
void ejecutarGrua(tArray fila, int tam);
void ejecutarExcavadora(tArray fila, int tam);
void ejecutarOpc(int opc, tArray fila, int &tam);


int main(){

	tArray fila;
	int tam;
	ifstream fich_in;
	ofstream fich_out;

	fich_in.open("fichero.txt");
	fich_out.open("salida.txt");

	leerFilaFich(fich_in, fila, tam);
	escribirFilaFich(fich_out, fila, tam);
	mostrarFila(fila, tam);	

	excavadora1Derecha(fila, tam, 0);

	fich_in.close();
	fich_out.close();

 	return 0;
}

// METODOS DE MANEJO DE FILAS //

//CORRECTO//Dada una fila, la muestra en pantalla siguiendo el formato del final de la segunda página.
void mostrarFila(const tArray fila, int tam){

	// MOSTRAR EL CONTENIDO DEL ARRAY
	for(int i = 0; i < tam; i++){
		if(fila[i] < 10)
			cout << " ";

		if(fila[i] != 0)
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

	if(fila[pos] == 0)
		var = true;

	return var;

}

// METODOS DE MANEJO DE FICHEROS //

//CORRECTO//Dado el fichero de lectura abierto fich, carga su contenido en la fila.
void leerFilaFich(ifstream &fich, tArray fila, int &tam){

	int i = 0, elem = 0;

	//Leo los elementos del fichero hasta que llegue a su tamaño máximo o hasta que encuentre un -1
	if(fich.is_open()){
		for(i = 0; (i < MAX_ELEM) && (elem != -1); i++){
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
		fila[posIni] = 0;
		realizado = true;
	}

	return realizado;
}

//Métodos de excavadora://////////////////////////////////////////////////
//Devuelve la posición del primer hueco libre de la fila si, comenzando por posIni, vamos avanzando paso a paso hacia la derecha. 
//CORRECTO//Si no hay ninguno, devolverá el valor tam.
int posHuecoLibreDerecha(const tArray fila, int tam, int posIni){

	int i = posIni;

	while(fila[i] != 0 && fila[i] != -1){
		i++;
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
	//Encontrar el primer hueco libre
	while((esPosValida(tam, i) && !estaVacia(fila, i)))
		i++;

	if(esPosValida(tam, i)){
		for(i; i > posIni; i--)
			fila[i] = fila[i-1];
	}

	//Finalmente eliminamos el ultimo elemento
	fila[i] = 0;

	mostrarFila(fila, tam);	
}

//Métodos del menú://////////////////////////////////////////////////
//Muestra el menú de opciones, solicita al usuario su respuesta, y devuelve la opción escogida cuando el usuario haya respondido 
//una opción válida.
int menu();
//Pide al usuario el nombre del fichero del que cargará su fila. Si existe, carga la fila, y si no, la fila se inicializa como vacía.
//Debe informar al usuario sobre si ha logrado realizar la carga, así como mostrar la fila leída.
void ejecutarLeerFichero(tArray fila, int &tam);
//Pide al usuario el nombre del fichero en el que se guardará la fila. Si logra abrirlo, guarda en el fichero la fila, usando el 
//formato visto antes. Debe informar al usuario sobre si ha logrado realizar el guardado. 
void ejecutarGuardarFichero(const tArray fila, int tam);
//En esta versión, pregunta al usuario qué posición quiere levantar y en qué posición quiere dejarlo caer. Si es posible, 
//realizará el movimiento. Si el movimiento no fue posible, informará al usuario de ello. Se mostrará cómo queda la fila tras
//el movimiento.
void ejecutarGrua(tArray fila, int tam);
//Pregunta al usuario desde qué posición empujará la excavadora. Entonces lo hace, o bien indica que no lo ha hecho (porque la 
//posición desde la que pidió empujar es inválida). Muestra cómo queda la fila tras el movimiento.
void ejecutarExcavadora(tArray fila, int tam);
//Dada la opción escogida por el usuario en el menú, la ejecuta.
void ejecutarOpc(int opc, tArray fila, int &tam);	