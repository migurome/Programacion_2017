#include <iostream>
#include <string>
#include "Indices.h"
#include "ListaCadenas.h"
#include "checkML.h"
using namespace std;
void muestraEstado();

int main(){
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	system("chcp 1252");
	tIndicePalabras idx;
	tListaCadenas archivos,totales,visitados, noVisitados,enlace;
	string nomfichero, clave;
	tMatriz L, mp;
	tVector v,vProx;
	bool ok;
	nuevaListaCadenas(totales);
	nuevaListaCadenas(visitados);
	nuevaListaCadenas(noVisitados);
	nuevaListaCadenas(enlace);
	nuevaListaCadenas(archivos);
	nuevaArrayClave(idx);

	cout << "Por favor Introduzca el nombre del fichero raiz a partir del que se creara el indice"<< endl;
	cin >> nomfichero;
	cout << "\nCargando..." << endl;
	crearTabla(idx,nomfichero,totales,visitados,noVisitados,enlace,L);
	cout << "\nTabla indice creada." << endl;
	cout << endl;
	cout << endl;
	for (int i = 0; i < idx.cont; i++){
		cout << idx.arrayClave[i].clave << ":" << "[";
		for (int j = 0; j < idx.arrayClave[i].valor.tam; j++){
			cout << idx.arrayClave[i].valor.arrayCadena[j];
			if (j+1<idx.arrayClave[i].valor.tam){
				cout << ",";
			}
		}
		cout << "]" << endl;
	}
	cout << endl;
	cout << "Matriz L: " << endl;
	imprimir(L);
	cout << "\nTotales: " << endl;
	cout << "[";
	for (int i = 0; i < totales.tam;i++){
		cout << totales.arrayCadena[i];
		if (i + 1 < totales.tam){
			cout << ", ";
		}
	}
	cout <<"]" << endl;
	cout << endl;
	mp = desdeEnlacesAMatriz(L);
	cout << "\nMatriz M : ";
	cout << endl;
	imprimir(mp);
	vProx = vectorPropio(mp);
	cout << "\nVector v :   (";
	imprimir(vProx);
	cout << ")" << endl;
	cout << endl;
	cout << "\nQue palabra quieres buscar? (fin - para terminar) : " << endl;
	cin >> clave;
	while (clave != "fin") {
		cout << "La lista de archivos donde aparece la palabra es: "<<endl;
		archivos=buscar(idx,clave);//la tabla ya esta ordenada
		v = valoresSubLista(archivos,totales,vProx);
		if (archivos.tam!=0){
			for (int i = 0; i < archivos.tam; i++){
				cout << endl;
				cout << archivos.arrayCadena[i] << "(";
				cout << v.datos[i]<<")"<< endl;
			}
		}
		else{
			cout << endl;
			cout << "\nLo sentimos....la palabra buscada no se encuentra en ningun fichero" << endl;
			cout << endl;	
		}

		cout << "\nQue palabra quieres buscar? (fin - para terminar) : " << endl;
		cin >> clave;
	}
	
	cout << "Gracias por usar el buscador." << endl;
	liberarListaCadenas(totales);
	liberarListaCadenas(visitados);
	liberarListaCadenas(noVisitados);
	liberarListaCadenas(enlace);
	liberarListaCadenas(archivos);
	liberarValorTabla(idx);
	liberarArrayClave(idx);
	
	
	return 0;
	_CrtDumpMemoryLeaks();
}



