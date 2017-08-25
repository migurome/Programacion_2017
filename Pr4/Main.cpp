#include <iostream>
#include <string>
#include "Indices.h"
using namespace std;
void muestraEstado();

int main(){
	tIndicePalabras idx;
	string nomfichero,clave;
	tListaCadenas archivos,totales;
	tMatriz L, mp;
	tVector v,vProx;
	bool ok;
	cout << "Por favor Introduzca el nombre del fichero raiz a partir del que se creara el indice"<< endl;
	cin >> nomfichero;
	cout << "\nCargando..." << endl;
	crearTabla(idx,nomfichero,totales,L);
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
			//cout << endl;
			//imprimir(archivos);
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
	return 0;
}



