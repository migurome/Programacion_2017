#include "Matriz.h"
#include <cmath>

tMatriz matrizConstante(double x, int n){//Crea una matriz de 𝑛 ∙ 𝑛, en la que todos los valores iniciales son x.
	tMatriz matriz;
	matriz.filas = n;
	matriz.columnas = n;
	for (int i = 0; i < n;i++){
		for (int j = 0; j < n; j++){
			matriz.datos[i][j] = x;
		}
	}
	return matriz;
}

tVector operator*(const tMatriz & m, const tVector & v){//Multiplica una matriz por un vector.
	tVector r;
	r.tam = m.columnas;
	inicializarVector(r);
	for (int i = 0; i < m.columnas; i++){
		for (int j = 0; j < m.filas; j++){
			r.datos[i] += m.datos[i][j] * v.datos[j];///////
		}
	}
	return r;
}
tMatriz operator*(double x, const tMatriz & m){// Obtiene la matriz que se obtiene multiplicando cada elemento de m por x.
	tMatriz matriz;
	matriz.filas = m.filas;
	matriz.columnas = m.columnas;
	for (int i = 0; i < matriz.filas; i++){
		for (int j = 0; j < matriz.columnas; j++){
			matriz.datos[i][j] = m.datos[i][j]*x;
		}
	}
	return matriz;
}
tMatriz operator+(const tMatriz & m1, const tMatriz & m2){// Suma dos matrices.
	tMatriz matrizAux;
	matrizAux.filas = m1.filas;
	matrizAux.columnas = m1.columnas;
	inicializarMatriz(matrizAux);
	for (int i = 0; i < matrizAux.filas; i++){
		for (int j = 0; j < matrizAux.columnas; j++){
			matrizAux.datos[i][j] = m1.datos[i][j]+m2.datos[i][j];
		}
	}
	return matrizAux;
}

void inicializarMatriz(tMatriz &m){//inicializa matriz poniendo todos los valores a 0
	for (int i = 0; i < m.filas; i++){
		for (int j = 0; j < m.columnas; j++){
			m.datos[i][j] = 0;
		}
	}
}
void inicializarVector(tVector &v){//inicializa vector poniendo todos los valores a 0
	for (int i = 0; i < v.tam; i++){//inicializar matriz r
		v.datos[i] = 0;
	}
}

void inicializarMatrizL(tMatriz &m){//devuelve una matriz unitaria
	m.filas = 1;
	m.columnas = 1;
	for (int i = 0; i < m.filas; i++){
		for (int j = 0; j < m.columnas; j++){
			m.datos[i][j] = 0;
		}
	}
}
tMatriz matrizAdyacente(tListaCadenas totales, tListaCadenas enlace,tMatriz &l, string nombreArchivo){
	int k = 0;
	l.filas = totales.tam;
	l.columnas = totales.tam;
	for (int i = 0; i < totales.tam;i++){
		for (int j = 0; j < totales.tam; j++){
			if ((totales.arrayCadena[j] != nombreArchivo) && (l.datos[i][j]!=1)){
				l.datos[i][j]=0.0;
			}
			else if (totales.arrayCadena[j]==nombreArchivo){
				if (buscar(enlace,totales.arrayCadena[k])==true){
					l.datos[i][j] = 1.0;
				}
				k++;
			}
		}
	}
	return l;
}

void imprimir(tMatriz l){//imprime por pantalla la matriz l
	cout << endl;
	for (int i = 0; i < l.filas; i++){
		for (int j = 0; j < l.columnas; j++){
			cout << setw(10)<<l.datos[i][j];	
		}
		cout << endl;
	}

}
void imprimir(tVector v){
	for (int i = 0; i < v.tam; i++){
		cout << v.datos[i];
		if (i + 1 < v.tam){
			cout << setw(10);
		}
	}
}


tMatriz matrizCn(tMatriz l){//Matriz Cn
	tMatriz m;
	m.filas = l.filas;
	m.columnas = l.columnas;
	for (int i = 0; i < l.filas; i++){
		for (int j = 0; j < l.columnas; j++){//tambien puede ser m.columnas
			m.datos[i][j] = 1.0 / m.filas;
		}
	}
	return m;
}

int contarUnos(tMatriz m,int pos){//cuenta el numero de unos que hay en la columna de la matriz, donde pos sera la columna actual
	int cont = 0;
	int j = pos;
	for (int i = 0; i < m.filas;i++){
		if (m.datos[i][j]==1.0){
			cont++;
		}
	}
	return cont;
}

tMatriz matrizPrima1(tMatriz L,tMatriz &m, int pos, int numEnlace){//Para cada Pagina (columna) se divide por el numero de enlaces de la pagina
	int j = pos;
	if (numEnlace != 0){
		for (int i = 0; i < m.filas; i++){
			if (L.datos[i][j] == 1.0){
				m.datos[i][j] = 1.0 / numEnlace;
			}
		}
	}
	else{
		for (int i = 0; i < m.filas; i++){
			m.datos[i][j] = 1.0 / L.filas;
		}	
	}
	return m;
}

void inicializarVectorPR(tVector &v){
	for (int i = 0; i < v.tam; i++){//inicializar matriz r
		v.datos[i] = 1;
	}
}

tMatriz matrizPrima(tMatriz L){//Devuleve la Matriz Prima con todos sus componentes actualizados
	tMatriz m;
	int enlace1 = 0;
	m.filas = L.filas;
	m.columnas = L.columnas;
	inicializarMatriz(m);
	for (int k = 0; k < L.columnas; k++){
		enlace1 = contarUnos(L, k);//cuenta los unos de una columna
		if (enlace1 != 0){
			matrizPrima1(L, m, k, enlace1);
		}
		else{
			matrizPrima1(L, m, k, 0);
		}
	}
	return m;
}
tMatriz matrizResultado(tMatriz cn){//Matriz resultado de multiplicar <1-c> x  Cn
	tMatriz mResultado;
	mResultado = 0.15*cn;
	return mResultado;
}
tMatriz matrizPrimaxC(tMatriz &m,const tMatriz &mResultado){
	m = 0.85*m;//0.85 x Matriz Prima
	m = m + mResultado;
	return m;
}

tVector vectorPropio(const tMatriz &m){
	tVector pr, mxpr;
	double aux;
	bool ok = false;
	mxpr.tam = m.filas;
	inicializarVector(mxpr);
	pr.tam = m.filas;
	inicializarVectorPR(pr);//inicializo el vector con todas sus componentes a uno
	mxpr = m*pr;//producto matriz m *vector de unos
	while (!ok){
		ok = true;
		for (int i = 0; i < pr.tam; i++){
			aux = pr.datos[i] / mxpr.datos[i];
			if (abs(aux - 1.0)>0.00001){
				ok = false;
			}
		}// fin for
		if (!ok){
			pr = mxpr;
			mxpr = m*pr;//producto matriz m *vector de unos
		}
	}//fin while
	double auxb = pr.datos[0];
	//normalizar...
	normaliza(pr,auxb);
	return pr;
}

tVector normaliza(tVector &pr,double numero ){
	for (int i = 0; i < pr.tam; i++){
		pr.datos[i] /= numero;
	}
	return pr;
}

tMatriz desdeEnlacesAMatriz(const tMatriz & L){//Devuelve la matriz M obtenida de L
	tMatriz cn, mp, mResultado;
	cn = matrizCn(L);
	mp = matrizPrima(L);
	mResultado = matrizResultado(cn);
	mp = matrizPrimaxC(mp, mResultado);
	return mp;
}

tVector valoresSubLista(tListaCadenas archivos, tListaCadenas totales, tVector v){
	tVector vector;
	vector.tam = 0;
	string s;
	double aux;
	int pos = -1;
	for (int i = 0; i < archivos.tam;i++){
		s=archivos.arrayCadena[i];
		pos=busqueda(totales,s);//busco en totales y obtengo la posicion
		aux = v.datos[pos];//con esa posicicion obtengo el dato y lo guardo en aux
		vector.tam++;
		vector.datos[i] = aux;
	}
	return vector;
}