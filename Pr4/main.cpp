// Grupo 7:
// Aina Mora
// Amalia Regueira

#include<iostream>
#include<iomanip>
#include<string>
#include<fstream>
#include "checkML.h"

using namespace std;

#include"indices.h"

/*Entrada: un string con el nombre del archivo, nFich.
 *Este método abre un fichero.
 *Salida: un booleano, cierto o falso en la vairable abierto, indicando si se ha abierto el fichero o no.
 */

bool intentarAbrir(string nFich) {
	bool abierto = false;
	ifstream fich;
	nFich = nFich + ".txt";
	fich.open(nFich);
	if (fich.is_open()) {
		abierto = true;
	}
	fich.close();
	return abierto;
}

/*Este método solicita el nombre de un archivo.
 *Salida: el nombre del fichero en la variable nFich.
 */

string pedirNombreFichero() {
	string nFich;
	bool abierto = false;
	while (! abierto) {
		cout << "Por favor, introduzca el nombre del fichero raíz a partir del que se creará el índice : " << endl;
		cin >> nFich;
		abierto = intentarAbrir(nFich);
	}
	return nFich;
}

/*Entrada: la matriz L.
 *Este metodo muestra la amtriz por pantalla.
 */

void imprimirMatriz(tMatriz L) {
	for (int i = 0; i < L.tam; i++) {
		for (int j = 0; j < L.tam; j++) {
			cout << L.elArray[i][j] <<" ";
		}
		cout << endl;
	}
}

/*Entrada: la matriz L.
 *Este método coloca ceros en toda la matriz.
 *Salida: la matriz con ceros.
 */


/*
	void inicializarMatriz(tMatriz& L) {
	for (int i = 0; i < MAX_TAM; i++) {
		for (int j = 0; j < MAX_TAM; j++) {
			L.elArray[i][j] = 0;
		}
	}
}
*/


/*Entrada: el nombre del fichero, los array tabla y totales y la matriz L.
 *Este método crea la tabla con las claves y la url a partir de un fichero inical.
 *Salida: los arrays tabla y totales y la matriz L con toda la información.
 */

void abrirFicheroIndice( string nombreFichInd, tIndicePalabras& tabla,tListaCadenas& totales, tMatriz& L) {
	nombreFichInd = nombreFichInd + ".txt";
	crearTabla(tabla,totales, nombreFichInd, L);  // se hace en el crear tabla la apertura del fichero
	//imprimir(tabla);
	//imprimirMatriz(L);
	cout << endl;
}

/*Entrada: una cadena en el string palabra
 *Este método convierte las mayusculas en minúsculas.
 */

void convertirMin(string& palabra) {
	for (int i = 0; palabra[i] != 0; i++ ) {
		palabra[i] = tolower(palabra[i]);
	}
}

/*Este método solicita una palabra y la convierte en minúsculas.
 *Salida: la palabra en la variable palabra.
 */

string pedirPalabra() {
	string palabra;
	cout << "Por favor, introduzca palabra a buscar ('fin' para salir) " << endl;
	cin >> palabra;
	convertirMin(palabra);
	return palabra;
}

/*Entrada: los arrays paraOrdenar y ordenarD.
 *Este método ordena los arrays y los imprime.
 *Salida: los arrays ordenados.
 */

void ordenarArray(tListaCadenas& paraOrdenar, tVector& ordenarD) {
	double aux;
	string auxC;

	for (int i = 0; i < ordenarD.tam; i++) {
		if ((ordenarD.v[i] < ordenarD.v[i + 1]))  {  
			aux = ordenarD.v[i];
			auxC = (paraOrdenar.lista[i] -> cadena);
			ordenarD.v[i] = ordenarD.v[i + 1];
			paraOrdenar.lista[i] = paraOrdenar.lista[i + 1];
			ordenarD.v[i + 1] = aux;
			paraOrdenar.lista[i + 1] -> cadena = auxC;
		}
	}
	// el siguiente for es para imprimir las listas
	for (int j = 0; j < ordenarD.tam; j++) { 
		cout << "Encontrado en " << paraOrdenar.lista[j]->cadena << " " << ordenarD.v[j] << endl;
		cout << endl;
	}
}

/*Entrada: el array paraOrdenar.
 *Este metodo vacia el array.
 *Salida: el array sin nada.
 */

void limpiar(tListaCadenas& paraOrdenar) {
	for (int i = 0; i < MAX; i++) {
		paraOrdenar.lista[i] = new tRegistro();
	}
	paraOrdenar.tam = 0;
}

/*Entrada: el array ordenarD.
 *Este método coloca 0 en todo el array.
 *Salida el array lleno de ceros.
 */


	void limpiarD(tVector& ordenarD) {
	for (int i = 0; i < ordenarD.tam; i++) {
		ordenarD.v[i] = 0;
	}
	ordenarD.tam = 0;
	}



/*Entrada:los arrays tabla y totales, la matriz L y una palabra en palabra.
 *Este método busca la palabra en la tabla y luego encuentra su posición en la matriz.
 */


void leer(const tIndicePalabras& tabla, string palabra, tMatriz& L, tListaCadenas totales) { // 

	int pos;
	int posM;
	int entrado = 0;
	int cont;
	bool encontrado;
	tListaCadenas paraOrdenar;
	tVector ordenarD;
	listaVacia(paraOrdenar);
	ordenarD.tam = 0;
	tRegistroIndicePalabras reg;
	while (palabra != "fin") {
		pos = getPosicion(tabla, palabra,0, tabla.tam);
		if (pos != -1) {
			reg = getRegistro(tabla, pos);
			for (int i = 0; i < tabla.lista[pos]->tam; i++) {
				if (buscar(totales, tabla.lista[pos]->valor[i])) {
					cont = 0;
					encontrado = false;
					while ((!encontrado) && (cont < totales.tam)) {
						if (totales.lista[cont] -> cadena == tabla.lista[pos]->valor[i]) {
							encontrado = true;
						}
						cont++;
					}
					posM = cont - 1;
				}

				insertar(paraOrdenar, tabla.lista[pos]->valor[i]);
				insertarD(ordenarD, L.elArray[posM][posM]);
			}
		}
		else {
			cout << "Palabra no encontrada " << endl;
		}
		ordenarArray(paraOrdenar, ordenarD);
		cout << endl;
		limpiar(paraOrdenar);
		limpiarD(ordenarD);
		palabra = pedirPalabra();
		cout << endl;
	}
}

/*Este programa funciona como un buscador, lee un fichero y los que esten relacionados, te solicita
 *una palabra, la busca y te indica en que archivos está y su relevancia.
 */

int main() {
	setlocale(LC_ALL, "spanish");
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	string nombreFichInd;
	string palabra;
	tRegistro cosa;
	tIndicePalabras tabla;
	tMatriz L;
	tListaCadenas totales;
	tMatriz auxEnlaces;
	tVector v;
	nombreFichInd = pedirNombreFichero();
	L = matrizConstante(0.0, MAX_TAM);
	abrirFicheroIndice(nombreFichInd, tabla, totales, L);
	auxEnlaces = desdeEnlacesAMatriz(L);
	palabra = pedirPalabra();
	cosa.cadena = palabra;
	cout << endl;
	leer(tabla, cosa.cadena, auxEnlaces, totales);
	//  
	return 0;

}