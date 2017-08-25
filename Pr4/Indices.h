#ifndef Indices_H
#define Indices_H
#include <algorithm>
#include <cctype>
#include <fstream>
#include "ClaveValor.h"
#include "Matriz.h"



void inicializar(tListaCadenas &visitados, tListaCadenas &noVisitados, tListaCadenas &totales, tListaCadenas &enlace);
void inicializarTabla(tIndicePalabras & tabla);
void crearTabla(tIndicePalabras & tabla, const string &archivoInicial, tListaCadenas & totales, tMatriz & L);	// A partir de archivoInicial, rellena la tabla tabla, tras haberla inicializado(a vacía).
string convertirAMinuscula(string &cadena);
void auxiliarCadena(ifstream &archivo, string &cadena, char &letra);
void leerCadena(ifstream &archivo, string &cadena, char &letra);
void reiniciarCadena(ifstream &archivo, string &cadena, char &letra);
void parsearCaracter(tIndicePalabras & tabla, tListaCadenas &visitados,tListaCadenas &noVisitados, 
tListaCadenas &totales, tListaCadenas &enlace, ifstream &archivo, string &cadena, char &letra, string &nombreArchivo);
#endif