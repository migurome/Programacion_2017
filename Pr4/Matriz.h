#ifndef Matriz_H
#define Matriz_H
#include "ListaCadenas.h"
const int MAX_TAM = 10;

typedef struct{
	int filas, columnas;
	double datos[MAX_TAM][MAX_TAM];
} tMatriz;

typedef struct {
	int tam;
	double datos[MAX_TAM];
} tVector;

tVector vectorPropio(const tMatriz & m, double epsilon);
tVector normaliza(const tVector& v1);
tMatriz matrizConstante(double x, int n);//Crea una matriz de 𝑛 ∙ 𝑛, en la que todos los valores iniciales son x.
tVector operator*(const tMatriz & m, const tVector & v);//Multiplica una matriz por un vector.
tMatriz operator*(double x, const tMatriz & m);// Obtiene la matriz que se obtiene multiplicando cada elemento de m por x.
tMatriz operator+(const tMatriz & m1, const tMatriz & m2);// Suma dos matrices.
tMatriz desdeEnlacesAMatriz(const tMatriz & L);// Devuelve la matriz M obtenida de L como en la introducción de la sección 4.
tVector normaliza(const tVector & v);// Devuelve un vector proporcional a v con la primera componente igual a 1.0.
void inicializarMatriz(tMatriz &m);
void inicializarVector(tVector &v);
void inicializarMatrizL(tMatriz &m);
tMatriz matrizAdyacente(tListaCadenas totales, tListaCadenas enlace, tMatriz &l, string nombreArchivo);
void imprimir(tMatriz l);
tMatriz matrizCn(tMatriz l);
int contarUnos(tMatriz m, int pos);
tMatriz matrizPrima1(tMatriz L,tMatriz &m, int pos, int numEnlace);
void inicializarVectorPR(tVector &v);
tVector normaliza(tVector &v, double numero);
tMatriz matrizPrima(tMatriz L);
tMatriz matrizResultado(tMatriz cn);
tMatriz matrizPrimaxC(tMatriz &m, const tMatriz &mResultado);
tVector vectorPropio(const tMatriz &m);//M es una matriz tal que todas sus columnas suman 1, devuelve un vector v con la primera componente igual a 1 tal que 𝑀 ∙ 𝑣 ≃ 𝑣.
void imprimir(tVector v);
tVector valoresSubLista(tListaCadenas archivos, tListaCadenas totales, tVector v);

#endif