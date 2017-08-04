#include<iostream>
#include<iomanip>
#include<string>
#include<fstream>

using namespace std;

const int MAX_TAM = 15;
const double C = 0.85;
typedef double tV[MAX_TAM][MAX_TAM];

typedef struct {
	int tam;
	tV elArray;
}tMatriz;

typedef double tArray[MAX_TAM];

typedef struct {
	int tam;
	tArray v;
}tVector;


void insertarD(tVector& l, const double& s);

/*Entrada: el numero x y n.
*Crea una matriz de n * n , en la que todos los valores iniciales son x.
*/
tMatriz matrizConstante(double x, int n);

/*Entrada: la matriz m y el vector v.
*Multiplica una matriz por un vector.
*Salida: la matriz multiplicada por el vector.
*/
tVector operadorPor(const tMatriz & m, const tVector & v);

/*Entrada: el numero x y la matriz m.
*Multiplica una matriz por un numero.
*Salida: la matriz multiplicada.
*/
tMatriz operadorPor(double x, const tMatriz & m);

/*Entrada: las matrices m1 y m2.
*Suma dos matrices.
*Salida: el resultado de la suma de las 2 matrices.
*/
tMatriz operadorMas(const tMatriz & m1, const tMatriz & m2);

/*Entrada: la matriz M.
*Obtiene la matriz de la introduccion de la seccion 4 en M.
*Salida: la matriz obtenida.
*/
tMatriz desdeEnlacesAMatriz(const tMatriz & L);

/*Entrada: el vector v.
*Calcula un vector proporcional a v con la primera componente igual a 1.0.
*Salida: el vector calculado.
*/
tVector normaliza(const tVector & v);

/*Entrada: matriz M.
*Coloco a  uno si la suma de las columnas es uno y si no un cero en el vector.
*Salida: el vector.
*/
tVector vectorPropio(const tMatriz & M);