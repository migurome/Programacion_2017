#ifndef ClaveValor_H
#define ClaveValor_H
#include "ListaCadenas.h"
#include<string>
using namespace std;

const int CLAVE=200;
typedef struct{
	string clave;//palabra
	tListaCadenas valor;//para representarlas listas de archivos donde podemos encontrar cada palabra
}tRegistroIndicePalabras;

typedef tRegistroIndicePalabras tArrayClave[CLAVE];
typedef struct{
	tArrayClave arrayClave;
	int cont;
}tIndicePalabras;

int getTamanno(const tIndicePalabras & l);//Devuelve el tamaño de la tabla.
tRegistroIndicePalabras getRegistro(const tIndicePalabras & l, int pos);// Devuelve el registro en la posición pos.
bool esta(const tIndicePalabras & l, const string & s);// Devuelve true si la palabra es una clave en la tabla, y false en caso contrario.
tListaCadenas buscar(const tIndicePalabras & l, const string & s);//dada una clave que está en la tabla devuelve la lista de cadenas asociada a esa clave.
void insertar(tIndicePalabras & idx, const string & palabra, const string &nombreArchivo);// Si palabra es ya una clave de la tabla, añade nombreArchivo a la lista de archivos correspondiente.Si no, crea un registro nuevo con esa información
void imprimir(const tIndicePalabras & idx);//Imprime la tabla.
int buscarPos(const tIndicePalabras & l, const string & s, bool& encontrado);//realiza una busqueda Binaria y devuelve la posicion de la clave buscada
void ordenarElemento(tIndicePalabras & idx);//ordena la tabla segun la clave
#endif