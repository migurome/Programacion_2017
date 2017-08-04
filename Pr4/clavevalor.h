#include<iostream>
#include<iomanip>
#include<string>
#include<fstream>
#include "listacadenas.h"
#include "matriz.h"
using namespace std;


const int MAXI = 15;
typedef string tListadoCadenas[MAXI];
typedef struct {
	string clave;
	tListadoCadenas valor; // nombres de archivo
	int tam;
} tRegistroIndicePalabras;

typedef tRegistroIndicePalabras *tRegPtrIndicePal;

typedef  tRegPtrIndicePal tArrayRegIndice[MAXI];

typedef struct {
	tArrayRegIndice lista;
	int tam;
	int cap;
}tIndicePalabras;

typedef struct {
	int cont;
	tRegPtrIndicePal regTabla;
} tListIndPal;

/*Entrada: array l.
*Calcula el tama�o del array.
*Salida: devuelve el tama�o de la tabla.
*/
int getTamanno(const tIndicePalabras& l);

/*Entrada:el array l y la posicion en la variable pos.
*Busca en el array el registro en la posici�n pos.
*Salida: devuelve el registro en la posici�n pos.
*/
tRegistroIndicePalabras getRegistro(const tIndicePalabras& l, int pos);

/*Entrada: el array l y un string con la palabra s a buscar.
*Busca en el array l en la palabra s.
*Salida: devuelve true si la palabra es una clave en la tabla, y false en caso contrario en una variable booleana.
*/
bool buscar(const tIndicePalabras& l, const  string& s);

/*Entrada: el array l y una palabra en la variable s.
*Este m�todo busca de forma recursiva en que posici�n del array se encuentra la palabra s.
*Salida: la posici�n en la que se encuentra o -1 si no est�.
*/
int getPosicion(const tIndicePalabras& l, const  string& s, int ini, int fin);

/*Entrada: el array idx, la palabra palabra y el fichero nombreArchivo.
*Este m�todo inserta nombreArchivo en la posicion del array en la que est� palabra.
*Salida: el array con el archivo insertado.
*/
void insertar(tIndicePalabras& idx, const string& palabra, const  string& nombreArchivo);

/*Entrada: el array idx.
*Este m�todo muestra por pantalla el array.
*/
void imprimir(const tIndicePalabras & idx);

