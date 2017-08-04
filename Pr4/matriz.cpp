#include "matriz.h"
#include "checkML.h"

void insertarD(tVector& l, const double& s) {
	l.v[l.tam] = s;
	l.tam = l.tam + 1;
}

/*Entrada: el numero x y n.
 *Crea una matriz de n * n , en la que todos los valores iniciales son x.
 */

tMatriz matrizConstante(double x, int n) {
	tMatriz m;
	m.tam = 0;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			m.elArray[i][j] = x;
		}
	}
	return m;
}

/*Entrada: la matriz m y el vector v.
 *Multiplica una matriz por un vector.
 *Salida: la matriz multiplicada.
 */

tVector operadorPor(const tMatriz & m, const tVector & v) {
	tVector vAux;
	double suma = 0;
	int cont = 0;
	for (int i = 0; i < m.tam; i++) {
		for (int j = 0; j < v.tam; j++) {
			suma = suma + (m.elArray[i][j] * v.v[j]);
		}
		vAux.v[cont] = suma;
		cont++;
	}
	return vAux;
}

/*Entrada: el numero x y la matriz m.
 *Multiplica una matriz por un numero.
 *Salida: la matriz multiplicada.
 */

tMatriz operadorPor(double x, const tMatriz & m) { // multiplica la matriz por el valor double obtenido
	tMatriz mAux;
	mAux = matrizConstante(0.0, MAX_TAM);
	for (int i = 0; i < m.tam; i++) {
		for (int j = 0; j < m.tam; j++) {
			mAux.elArray[i][j] = m.elArray[i][j] * x;
		}
		mAux.tam++;
	}
	return mAux;
}

/*Entrada: las matrices m1 y m2.
 *Suma dos matrices.
 *Salida: el resultado de la suma.
 */
tMatriz operadorMas(const tMatriz & m1, const tMatriz & m2) { // para hacer la suma de las matrices
	tMatriz mR;
	mR = matrizConstante(0.0, MAX_TAM);
	for (int i = 0; i < m1.tam; i++) {
		for (int j = 0; j < m1.tam; j++) {
			mR.elArray[i][j] = m1.elArray[i][j] + m2.elArray[i][j];
		}
		mR.tam++;
	}
	return mR;
}


/*Entrada: la matriz M y la columna correspondiente.
 *Obtiene el numero de enlaces que hay en una columna.
 *Salida: el numero de enlaces en la variable cont.
 */

double contarEnlaces(const tMatriz& L, int j) {
	int cont = 0;
	for (int i = 0; i < L.tam; i++) {
		if (L.elArray[i][j] == 1.0) {
			cont++;
		}
	}
	return cont;
}

/*Entrada: la matriz M.
 *Obtiene una matriz de la introduccion de la seccion 4 en M.
 *Salida: la matriz obtenida.
 */

tMatriz desdeEnlacesAMatriz(const tMatriz & L) {
	tMatriz mTrans;
	tMatriz sumatorio;
	tMatriz sumEnlaces;
	double contEnlaces;
	mTrans = matrizConstante(0.0, MAX_TAM);
	sumatorio = matrizConstante(0.0, MAX_TAM);
	sumEnlaces = matrizConstante(0.0, MAX_TAM);
	for (int i = 0; i < L.tam; i++) {
		for (int j = 0; j < L.tam; j++) {
			contEnlaces = contarEnlaces(L, j);
			if ((L.elArray[i][j] == 0) || (contarEnlaces == 0)) {
				sumatorio.elArray[i][j] = 1 - C;
				sumEnlaces.elArray[i][j] = 1 - C;
			}
			else {
				sumatorio.elArray[i][j] = L.elArray[i][j] / contEnlaces;
				sumEnlaces.elArray[i][j] = L.elArray[i][j] / contEnlaces;
			}

		}
		sumatorio.tam++;
		sumEnlaces.tam++;
	}
	sumEnlaces = operadorPor(1 - C, sumEnlaces);
	sumatorio = operadorPor(C, sumatorio);
	mTrans = operadorMas(sumEnlaces, sumatorio);
	return mTrans;
}

/*Entrada: el vector v.
 *Calcula un vector proporcional a v con la primera componente igual a 1.0.
 *Salida: el vector calculado.
 */

tVector normaliza(const tVector & v) {
	tVector final;
	double primerValor;
	primerValor = v.v[0];
	for (int i = 0; i < v.tam; i++) {
		final.v[i] = v.v[i] / primerValor;
	}
	return final;
}

/*Entrada: matriz M.
 *Coloco a  uno si la suma de las columnas es uno y si no un cero en el vector.
 *Salida: el vector.
 */

tVector vectorPropio(const tMatriz & M) { // aplicar matriz al vector(de todo 1) hasta que se produce un vector que sea igual al vector
	tVector aux;
	tVector a;
	tVector soloUnos;
	double suma = 0;
	for (int i = 0; i < M.tam; i++) {
		soloUnos.v[i] = 1.0;
	}
	aux = operadorPor(M, soloUnos);
	while (aux.v != soloUnos.v) {
		aux = operadorPor(M, soloUnos);
	}
	a = normaliza(aux);
	return aux; // esto lo que hace es el XA = X => soloUnos*M = aux
}