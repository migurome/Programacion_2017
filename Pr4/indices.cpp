#include"indices.h"
#include "checkML.h"

/*Entrada: la tabla.
 *Este métodoinicializa ceros la tabla.
 *Salida: la tabla inicialiazada.
 */

void inicializarTabla(tIndicePalabras& tabla) {
	tabla.tam = 0;
	tabla.cap = 0;
	for (int i = 0; i < MAXI; i++) {
		tabla.lista[i] = new tRegistroIndicePalabras();
		tabla.lista[i]->tam = 0;
	}
}

/*Entrada: la lista.
 *Este método inicializa a cero el tamaño de la lista.
 *Salida: la lista inicializada.
 */
void inicializarListas(tListaCadenas& lista) {
	lista.tam = 0;
	lista.cap = 1;
	lista.lista[lista.tam] = new tRegistro();
}

/*Entrada: la lista.
 *Este método inicializa a cero el tamaño de la lista.
 *Salida: la lista inicializada.
 */

void inicializarTam(tMatriz& L) {
	L.tam = 0;
}

/*Entrada: los arrays tabla, totales y L y el string nombreFichInd con el nombre del primer
 *archivo a leer.
 *Este método rellena la tabla.
 *Salida: los arrays tabla y totales y la matriz rellenos con la información.
 */

void   crearTabla (tIndicePalabras& tabla, tListaCadenas& totales, const string& nombreFichInd, tMatriz & L){
	ifstream fichInd;
	char c;
	string cadena = "";
	string nombre;
	tListaCadenas visitados;
	tListaCadenas noVisitados;
	
	listaVacia(visitados);
	listaVacia(noVisitados);
	listaVacia(totales);
	inicializarTabla(tabla);
	//inicializarTam(L);

	insertar(noVisitados, nombreFichInd);
	insertar(totales, nombreFichInd);

	while (noVisitados.tam != 0) {
		nombre = noVisitados.lista[0] -> cadena;
		fichInd.open(nombre);
		if (fichInd.is_open()) {
			fichInd.get(c);
			while ((!fichInd.eof())) {
				if (isspace(c)) {
					// inserto la cadena en listado de cadena
					if (cadena != "") {
						insertar(tabla, cadena, nombre);
					}
					cadena = "";					// cadena se limpia
				}
				else if (ispunct(c) && (c == '>')) {
					if (buscar(totales, cadena)) {
						int pos = 0;
						int ini = 0;
						for (int j = 0; j < totales.tam; j++) {
							if (totales.lista[j] -> cadena == nombre) {
								ini = j;
							}
						}
						for (int i = 0; i < totales.tam; i++) {
							if (totales.lista[i]-> cadena == cadena) {
								pos = i;
							}
						}
						L.elArray[pos][ini] = 1.0;
						L.tam++;
					}
					else {
						insertar(noVisitados, cadena);
						insertar(totales, cadena);
						//L.tam++;
						int posi = 0;
						int init = 0;
						for (int j = 0; j < totales.tam; j++) {
							if (totales.lista[j]->cadena == nombre) {
								init = j;
							}
						}
						for (int i = 0; i < totales.tam; i++) {
							if (totales.lista[i]->cadena == cadena) {
								posi = i;
							}
						}
						L.elArray[posi][init] = 1.0;
						L.tam++;
					}
					cadena = "";					// cadena se limpia
				}
				else if (c != '<') {
					cadena = cadena + c;
				}
				fichInd.get(c);
			}
			if (cadena != "") {
				insertar(tabla, cadena, nombre);
				cadena = "";
			}
		}
		
		fichInd.close();
		eliminar(noVisitados, 0);
		insertar(visitados, nombre);
		//insertar(totales, nombre);

	}
	

}
