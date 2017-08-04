#include"listacadenas.h"
#include "checkML.h"

/*Entrada: el array l.
 *Devuelve el tamaño de la lista.
 *Salida: una variable con el tamaño del array l.
 */

int  getTamanno(const tListaCadenas& l) {
	return l.tam;
}

/*Entrada: el array l y la variable pos con la posición de la cadena.
 *Devuelve una cadena en la posición pos.
 *Salida: la cadena del array l.
 */

string  getCadena(const tListaCadenas& l, int pos) {
	return l.lista[pos]-> cadena;
}


void listaVacia(tListaCadenas& result) {
	
	result.tam = 0;
	result.cap = 1;
	for (int i = 0; i < MAX; i++) {
		result.lista[i] = new tRegistro();
	}
	
}

void aumentaCapacidad(tListaCadenas & l) {
	tList aux;
	aux.regLista = new tRegistro [3 * l.cap / 2 + 1];
	aux.cont = 0;

	for (int i = 0; i<l.tam; i++)
		aux.regLista[i] = *(l.lista[i]);
	
	l.lista[0] = aux.regLista;
	l.cap = 3 * l.cap / 2 + 1;
}

/*Entrada: el array s y una variable del tipo string con la palabra a insertar.
 *Inserta un elemento al final de la lista.
 */

void insertar(tListaCadenas& l, const string& s) {
	if (l.cap == l.tam)
		aumentaCapacidad(l);
	
	(*l.lista[l.tam]).cadena = s;
	//l.lista[l.tam] -> cadena = s;
	l.tam++;

}

/*Entrada: el array l y la palabra s.
 * Busca en el array la palabra s.
 *Salida: devuelve true si la cadena está en la lista, y false si no, en una variable booleana.
 */

bool buscar(const tListaCadenas& l, const string& s) {
	bool encontrado = false;
	int i = 0;

	while ((!encontrado) && (i < l.tam)) {
		if (l.lista[i] -> cadena == s) {
			encontrado = true;
		}
		i = i + 1;
	}
	return encontrado;
}

/*Entrada: el array l y la posicion en la variable pos.
 *Elimina el elemento en la posición pos.
 */

void  eliminar(tListaCadenas& l, int pos) {
	for (int i = 0; i <= l.tam; i++) {
		l.lista[i] = l.lista[i + 1];
	}
	l.tam--;
}

/*Entrada: el array l.
 *Imprime los elementos de la lista.
 */

void  imprimir(const tListaCadenas& l) {
	for (int i = 0; i < l.tam; i++) {
		cout << l.lista[i] << endl;
	}
}






void listaVacia(int n, tListaCadenas& result) {
	
	result.lista[result.tam] = new tRegistro();
	result.tam = 0;
	result.cap = n;
}




void aniadir(tListaCadenas & l, tRegPtr e) {
	if (l.cap == l.tam) {
		aumentaCapacidad(l);
	}
	l.lista[l.tam] = e;
	l.tam++;
}

/*
	tListaCadenas eliminarUltimo(tListaCadenas & l) {
		l.tam--;
	}
*/

/*
void liberar(tListaCadenas & l) {
delete[] l.lista;
l.tam = 0;
l.cap = 0;
//l.lista = NULL;

}


void copiar(const tListaCadenas &fuente, tListaCadenas &destino) {
if (destino.lista != NULL) { liberar(destino); }
destino = fuente;
destino.lista[destino.tam] = *(new tRegPtr[fuente.cap]);
for (int i = 0; i<fuente.tam; i++) {
destino.lista[i] = fuente.lista[i];
}
}


*/