#include "ClaveValor.h"

int getTamanno(const tIndicePalabras & l){//Devuelve el tamaño de la tabla.
	return l.cont;
}

tRegistroIndicePalabras getRegistro(const tIndicePalabras & l, int pos){// Devuelve el registro en la posición pos.
	return l.arrayClave[pos];
}

bool esta(const tIndicePalabras & l, const string & s){// Devuelve true si la palabra es una clave en la tabla, y false en caso contrario.
	bool encontrado = false;
	int i = 0;
	while (i < l.cont &&!encontrado){
		if (l.arrayClave[i].clave == s){
			encontrado = true;
		}
		else{
			i++;
		}
	}
	return encontrado;
}
//Es necesario que la lista tIndicePalabras este antes ordenada para aplicar la Busqueda Binaria
tListaCadenas buscar(const tIndicePalabras  & l, const string & s){//dada una clave que está en la tabla devuelve la lista de cadenas asociada a esa clave.
	tListaCadenas listaCadenas;
	inicializarListaCadenas(listaCadenas);
	int pos = -1;
	int ini = 0, mitad = 0, fin = l.cont -1;
	bool encontrado = false;
	while (ini<=fin &&!encontrado){
		mitad = (ini + fin) / 2;

		if (s==l.arrayClave[mitad].clave){
			encontrado = true;
			pos = mitad;
			listaCadenas = l.arrayClave[pos].valor;
		}
		else if (s < l.arrayClave[mitad].clave){
			fin = mitad - 1;
		}
		else{
			ini = mitad + 1;
		}
	}
	return listaCadenas;
}

/*tListaCadenas buscar(const tIndicePalabras  & l, const string & s){
	tListaCadenas listaCadenas;
	inicializarListaCadenas(listaCadenas);
	int pos = -1;
	int ini = 0, mitad = 0, fin = l.cont - 1;
	bool encontrado = false;
	if (ini <= fin) {//Es valido poner ini < fin siempre en cuando que fin=lista.contador
		int mitad = (ini + fin) / 2;
		if (s == l.arrayClave[mitad].clave){ //si la compra tiene la misma fecha y hora 
			pos = mitad;
			encontrado = true;
			listaCadenas = l.arrayClave[pos].valor;
		}
		else
		if (s < l.arrayClave[mitad].clave)
			listaCadenas = buscar(l, s);//
		else
			listaCadenas = buscar(l, s);
	}
	return listaCadenas;
}
*/





//Busqueda Binaria, devuelve la posicion donde esta la clave dentro de la lista tIndicePalabras
int buscarPos(const tIndicePalabras & l, const string & s, bool& encontrado){//dada una clave que está en la tabla devuelve la lista de cadenas asociada a esa clave.
	int pos = -1;
	int ini = 0, mitad = 0, fin = l.cont - 1;
	while (ini <= fin &&!encontrado){
		mitad = (ini + fin) / 2;

		if (s == l.arrayClave[mitad].clave){
			encontrado = true;
			pos = mitad;
		}
		else if (s < l.arrayClave[mitad].clave){
			fin = mitad - 1;
		}
		else{
			ini = mitad + 1;
		}
	}
	return pos;
}


void insertar(tIndicePalabras & idx, const string & palabra, const string &nombreArchivo){// inserto en la tabla(idx) la clave (palabra) y el nombreArchivo (arrayCadena[i]) dentro de valor
	bool encontrado = false;
	ordenarElemento(idx);//ordenamos la lista por clave
	if (idx.cont == idx.capacidad){
		ampliar(idx);
	};

	int pos = buscarPos(idx,palabra,encontrado);//busco la pos en la tabla(idx) segun la clave
	if (encontrado){//en caso de que la clave ya este en la tabla
		bool ok = true;
		if (idx.arrayClave[pos].valor.tam == idx.arrayClave[pos].valor.capacidad){
			ok = false;//en caso de que lista cadenas este lleno
		}
		else{
			if (buscar(idx.arrayClave[pos].valor, nombreArchivo)==false){//si es false(no hay nombre archivo) inserta nombre del archivo
				idx.arrayClave[pos].valor.arrayCadena[idx.arrayClave[pos].valor.tam] = nombreArchivo;
				idx.arrayClave[pos].valor.tam++;
			}
			
		}
	}
	else{//en caso de que la clave no esta en la tabla, entoces creamos uno
		
		if (idx.cont < idx.capacidad){


			idx.arrayClave[idx.cont].clave = palabra;
			idx.arrayClave[idx.cont].valor.tam = 0;
			nuevaListaCadenas(idx.arrayClave[idx.cont].valor);
			idx.arrayClave[idx.cont].valor.arrayCadena[idx.arrayClave[idx.cont].valor.tam] = nombreArchivo;
			idx.arrayClave[idx.cont].valor.tam++;
			idx.cont++;
		}
	}
	ordenarElemento(idx);//ordenamos la lista por clave

}


void ordenarElemento(tIndicePalabras &idx){ //Ordenacion por el metodo de la burbuja
	bool ok = true;
	int i = 0;
	while (i<idx.cont-1 && ok){ //desde el primero hasta el penultimo
		ok = false;
		for (int j = idx.cont - 1;j>i;j--){
			if (idx.arrayClave[j].clave<idx.arrayClave[j-1].clave){//comparas las claves 
				ok = true;
				tRegistroIndicePalabras tmp = idx.arrayClave[j];
				idx.arrayClave[j] = idx.arrayClave[j - 1];
				idx.arrayClave[j - 1] = tmp;
			}
		}
		if (ok){
			i++;
		}
	}
}

void imprimir(const tIndicePalabras & idx){//Imprime la tabla.
	for (int i = 0; i < idx.cont; i++){
		cout << setw(10) << idx.arrayClave[i].clave;
		imprimir(idx.arrayClave[i].valor);
		cout << endl;
	}
}


void liberarValorTabla(tIndicePalabras & idx){
	for (int i = 0; i < idx.cont; i++){
		delete[] idx.arrayClave[i].valor.arrayCadena;
		idx.arrayClave[i].valor.tam = 0;
		idx.arrayClave[i].valor.arrayCadena = nullptr;
	}
}
void nuevaArrayClave(tIndicePalabras & idx){
	idx.cont = 0;
	idx.capacidad = CLAVE;
	idx.arrayClave = new tRegistroIndicePalabras[idx.capacidad];
}

void liberarArrayClave(tIndicePalabras & idx){
	delete[] idx.arrayClave;
	idx.cont = 0;
	idx.arrayClave=nullptr;
}

void ampliar(tIndicePalabras &idx){
	tRegistroIndicePalabras *aux = new tRegistroIndicePalabras[(idx.capacidad * 3) / 2 + 1];
	for (int i = 0; i < idx.cont; i++){
		aux[i] = idx.arrayClave[i];
	}
	delete[] idx.arrayClave;
	idx.arrayClave = aux;//copia la direccion de aux
	idx.capacidad = (idx.capacidad * 3) / 2 + 1;
	aux = nullptr;
}
