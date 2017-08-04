#include<iostream>
#include<iomanip>
#include<string>
#include<fstream>
#include <stddef.h>

using namespace std;
typedef struct {
	string cadena;
}tRegistro;

typedef tRegistro *tRegPtr;

const int MAX = 15;
typedef tRegPtr tLista[MAX];

typedef struct {
	int cap ;
	int tam;
	tLista lista;
} tListaCadenas;

typedef struct {
	int cont;
	tRegPtr regLista;
} tList;

/*Entrada: el array l.
*Devuelve el tamaño de la lista.
*Salida: una variable con el tamaño del array l.
*/
int getTamanno(const tListaCadenas& l);

/*Entrada: el array l y la variable pos con la posición de la cadena.
*Devuelve una cadena en la posición pos.
*Salida: la cadena del array l.
*/
string getCadena(const tListaCadenas& l, int pos);

/*Entrada: el array s y una variable del tipo string con la palabra a insertar.
*Inserta un elemento al final de la lista.
*/
void insertar(tListaCadenas& l, const string& s);

/*Entrada: el array l y la palabra s.
* Busca en el array la palabra s.
*Salida: devuelve true si la cadena está en la lista, y false si no, en una variable booleana.
*/
bool buscar(const tListaCadenas& l, const string& s);

/*Entrada: el array l y la posicion en la variable pos.
*Elimina el elemento en la posición pos.
*/
void eliminar(tListaCadenas& l, int pos);

/*Entrada: el array l.
*Imprime los elementos de la lista.
*/
void imprimir(const tListaCadenas& l);
/*Entrada: la lista sin inicializar.
*inicializa la lista a vacio.
*/
void listaVacia(tListaCadenas& result);
