#include<iostream>
#include<iomanip>
#include<string>
#include<fstream>
#include"clavevalor.h"
using namespace std;

/*Entrada: los arrays tabla, totales y L y el string nombreFichInd con el nombre del primer
*archivo a leer.
*Este m�todo rellena la tabla.
*Salida: los arrays tabla y totales y la matriz rellenos con la informaci�n.
*/
void crearTabla(tIndicePalabras& tabla, tListaCadenas & totales, const string& nombreFichInd, tMatriz & L);
