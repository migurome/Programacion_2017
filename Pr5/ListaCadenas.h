#ifndef ListaCadenas_H
#define ListaCadenas_H
#include<string>
#include<iostream>
#include<iomanip>
using namespace std;
const int CADENAS = 2;

typedef struct{
	string *arrayCadena;
	int tam;
	int capacidad;
}tListaCadenas;//para representarlas listas de archivos donde podemos encontrar cada palabra

int getTamanno(const tListaCadenas & l);// Devuelve el tamaño de la lista.
string getCadena(const tListaCadenas & l, int pos);// Devuelve una cadena en la posición pos.
void insertar(tListaCadenas & l, const string & s);// Inserta un elemento al final de la lista.
bool buscar(const tListaCadenas & l, const string & s);//Devuelve true si la cadena está en la lista, y false si no.
void eliminar(tListaCadenas & l, int pos);// Elimina el elemento en la posición pos.
void imprimir(const tListaCadenas & l);// Imprime los elementos de la lista
void inicializarListaCadenas(tListaCadenas &listaCadenas);
void eliminarEnlace(tListaCadenas & l);
void ordenarElemento(tListaCadenas &l);
int buscarBinario(const tListaCadenas &l, const string &cadena);
int busqueda(const tListaCadenas &l, const string &cadena);
void nuevaListaCadenas(tListaCadenas  &listaCadenas);
void liberarListaCadenas(tListaCadenas & listaCadenas);
void ampliar(tListaCadenas &listaCadenas);
#endif