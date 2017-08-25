#include "ListaCadenas.h"

int getTamanno(const tListaCadenas & l){// Devuelve el tamaño de la lista.
	return l.tam;
}
string getCadena(const tListaCadenas & l, int pos){// Devuelve una cadena en la posición pos.
	return l.arrayCadena[pos];
}

void insertar(tListaCadenas & l, const string & s){// Inserta un elemento al final de la lista.
	if (l.tam<=CADENAS){
		l.arrayCadena[l.tam] = s;
		l.tam++;
	}
}
bool buscar(const tListaCadenas & l, const string & s){//Devuelve true si la cadena está en la lista, y false si no.
	bool encontrado = false;
	int i = 0;
	while (i < l.tam &&!encontrado){
		if (l.arrayCadena[i]==s){
			encontrado = true;
		}
		else{
			i++;
		}
	}
	return encontrado;
}

void eliminar(tListaCadenas & l, int pos){// Elimina el elemento en la posición pos.
	for (int i = pos; i < l.tam; i++){
		l.arrayCadena[i] = l.arrayCadena[i+1];
	}
	l.tam--;
}

void eliminarEnlace(tListaCadenas & l){// Elimina el elemento en la posición pos.
	for (int i = 0; i < l.tam; i++){
		l.arrayCadena[i] = "";
	}
	l.tam=0;
}

void imprimir(const tListaCadenas & l){// Imprime los elementos de la lista
	for (int i = 0; i < l.tam;i++){
		cout << l.arrayCadena[i] << setw(10) << endl;
	}
}
void inicializarListaCadenas(tListaCadenas &listaCadenas){
	listaCadenas.tam = 0;
}

void ordenarElemento(tListaCadenas &l){ //Ordenacion por el metodo de la burbuja
	bool ok = true;
	int i = 0;
	while (i<l.tam - 1 && ok){ //desde el primero hasta el penultimo
		ok = false;
		for (int j = l.tam - 1; j>i; j--){
			if (l.arrayCadena[j]<l.arrayCadena[j - 1]){
				ok = true;
				string tmp = l.arrayCadena[j];
				l.arrayCadena[j] = l.arrayCadena[j - 1];
				l.arrayCadena[j - 1] = tmp;
			}
		}
		if (ok){
			i++;
		}
	}
}

int buscarBinario(const tListaCadenas &l, const string &cadena){
	bool encontrado = false;
	int ini = 0, fin = l.tam - 1,mitad=0, pos = -1;
	while (ini<=fin && !encontrado){
		mitad = (ini + fin )/ 2;
		if (cadena == l.arrayCadena[mitad]){
			encontrado = true;
			pos = mitad;
		}
		else if (cadena<l.arrayCadena[mitad]){
			fin = mitad - 1;
		}
		else{
			ini = mitad + 1;
		}
	}
	return pos;
}

int busqueda(const tListaCadenas &l, const string &cadena){
	int i = 0;
	bool encontrado = false;
	while (i<l.tam && !encontrado){
		if (l.arrayCadena[i]==cadena){
			encontrado = true;
		}
		else{
			i++;
		}
	}
	if (!encontrado){
		i = -1;
	}
	return i;
}