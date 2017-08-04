#include"clavevalor.h"
#include "checkML.h"

/*Entrada: array l.
 *Calcula el tamaño del array.
 *Salida: devuelve el tamaño de la tabla.
 */

int getTamanno(const tIndicePalabras& l) {
	return l.tam;

}

/*Entrada:el array l y la posicion en la variable pos.
 *Busca en el array el registro en la posición pos.
 *Salida: devuelve el registro en la posición pos.
 */

tRegistroIndicePalabras  getRegistro(const tIndicePalabras & l, int pos) {
	tRegistroIndicePalabras r;
	r = *l.lista[pos];
	return r;
}

/*Entrada: el array l y un string con la palabra s a buscar.
 *Busca en el array l en la palabra s.
 *Salida: devuelve true si la palabra es una clave en la tabla, y false en caso contrario en una variable booleana.
 */

bool buscar(const tIndicePalabras& l, const  string& s) {
	bool encontrado = false;
	int i = 0;
	while ((!encontrado) && (i < l.tam)) {
		if (l.lista[i]->clave == s) {
			encontrado = true;
		}
		i++;
	}
	return encontrado;
}

/*Entrada: el array l y una palabra en la variable s.
 *Este método busca en que posición del array se encuentra la palabra s.
 *Salida: la posición en la que se encuentra o -1 si no está.
 */

int getPosicion(const tIndicePalabras& l, const  string& s, int ini, int fin) {
	int mitad;
	if (ini <= fin) {
		mitad = (ini + fin) / 2;
		if (l.lista[mitad]->clave == s) {
			return mitad;
		}
		else {
			if (l.lista[mitad]->clave < s) {
				ini = mitad + 1;
				return getPosicion(l, s, ini, fin);
			}
			else if (l.lista[mitad]->clave > s) {
				fin = mitad - 1;
				return getPosicion(l, s, ini, fin);
			}
		}

	}
	else {
		return -1;
	}
}

void aumentaCapacidadTabla(tIndicePalabras & l) {
	tListIndPal aux;
	aux.regTabla = new tRegistroIndicePalabras[3 * l.cap / 2 + 1];
	aux.cont = 0;

	for (int i = 0; i<l.tam; i++) {
		aux.regTabla[i] = *(l.lista[i]);
	}
	l.lista[0] = aux.regTabla;
	l.cap = 3 * l.cap / 2 + 1;
}

/*Entrada: el array idx, la palabra palabra y el fichero nombreArchivo.
 *Este método inserta nombreArchivo en la posicion del array en la que está palabra.
 *Salida: el array con el archivo insertado.
 */

void  insertar(tIndicePalabras& idx, const string& palabra, const  string&	nombreArchivo) {

	if (idx.cap == idx.tam) {
		aumentaCapacidadTabla(idx);
	}

	bool encontrado;
	bool aGuardarEncontrado = false;
	int pos;
	int aGuardar = 0;
	encontrado = buscar(idx, palabra);
	if (palabra != "") {
		if (encontrado == true) {
			pos = getPosicion(idx, palabra, 0, idx.tam);
			idx.lista[pos]->valor[idx.lista[pos]->tam] = nombreArchivo;
			idx.lista[pos]->tam++;
		}
		else {
			if ((idx.tam > 0) && (idx.lista[idx.tam - 1]->clave  < palabra)) {
				idx.lista[idx.tam]->clave = palabra;
				idx.lista[idx.tam]->valor[idx.lista[idx.tam]->tam] = nombreArchivo;
				idx.lista[idx.tam]->tam++;
				idx.tam++;
			}
			else {
				for (int i = 0; i < idx.tam; i++) {
					if ((palabra < idx.lista[i]->clave) && (aGuardarEncontrado == false)) {
						aGuardar = i;
						aGuardarEncontrado = true;
					}
				}
				if (idx.tam != 0) {
					for (int j = idx.tam; j >= aGuardar; j--) {
						*idx.lista[j + 1] = *idx.lista[j];
					}
				}
				
				idx.lista[aGuardar]->clave = palabra;
				idx.lista[aGuardar]->valor[0] = nombreArchivo;
				idx.lista[aGuardar]->tam = 1;
				idx.tam++;
			}

		}
	}
	
}

/*Entrada: el array idx.
 *Este método muestra por pantalla el array.
 */

void  imprimir(const tIndicePalabras& idx) {
	for (int i = 0; i < idx.tam; i++) {
		cout << idx.lista[i]->clave << endl;
		for (int j = 0; j <= idx.lista[i]->tam; j++) {
			cout << idx.lista[i]->valor[j] << endl;
		}
		cout << endl;
	}
}