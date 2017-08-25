#include "Indices.h"

void inicializar(tListaCadenas &visitados, tListaCadenas &noVisitados, tListaCadenas &totales, tListaCadenas &enlace){

	visitados.tam = 0;
	noVisitados.tam = 0;
	totales.tam = 0;
	enlace.tam = 0;

}

void inicializarTabla(tIndicePalabras & tabla){
	tabla.cont = 0;
}

void crearTabla(tIndicePalabras & tabla, const string &archivoInicial, tListaCadenas & totales, tMatriz & L){//A partir de archivoInicial, rellena la tabla tabla, tras haberla inicializado(a vacía).
	
	ifstream archivo;
	tListaCadenas visitados, noVisitados,enlace;
	string cadena, nombreArchivo;
	tMatriz m, cn, mResultado;
	tVector v, vProx;
	char letra;
	
	inicializarTabla(tabla);
	inicializar(visitados, noVisitados,totales,enlace);				//Inicializar visitados, no-visitados y totales a listas vacías
	
	if (visitados.tam < CADENAS){									//compruebo si visitados esta lleno
		
		insertar(noVisitados, archivoInicial);						//meter el archivo inicial en no visitados
		insertar(totales, archivoInicial);							//meter el archivo inicial en totales
		inicializarMatrizL(L);										//iniciar la matriz L a tamaño 1 con un cero
		
		while (noVisitados.tam != 0){								//mientras exista ficheros en noVisitados inserto en visitados
			
			nombreArchivo = noVisitados.arrayCadena[0];
			insertar(visitados, nombreArchivo);						//meter en visitados, por el momento se mantiene el archivo en totales
			eliminar(noVisitados, 0);								//eliminar desde el ultimo elemento hasta el primero
			eliminarEnlace(enlace);
			archivo.open(nombreArchivo);							//Abrir Fichero
			archivo.get(letra);
			
			while ( !archivo.eof() ){
				leerCadena(archivo, cadena, letra);
				parsearCaracter(tabla, visitados, totales, enlace,noVisitados , archivo, cadena, letra, nombreArchivo);
			}

			archivo.close();
			matrizAdyacente(totales, enlace, L, nombreArchivo);	
		}
	}
}


string convertirAMinuscula(string &cadena){
	std::transform(cadena.begin(), cadena.end(), cadena.begin(),[](unsigned char c) { 
		return std::tolower(c);
	});

	return cadena;
}

void auxiliarCadena(ifstream &archivo, string &cadena, char &letra){
	
	cadena = cadena + letra;
	archivo.get(letra);														// uso .get porque procesa los espacios en blanco

}

void reiniciarCadena(ifstream &archivo,string &cadena, char &letra){

	archivo.get(letra);
	cadena = "";

}

void leerCadena(ifstream &archivo, string &cadena, char &letra){

	while (letra != '<' && !ispunct(letra) && !isspace(letra))
		auxiliarCadena(archivo, cadena, letra);

}

void parsearCaracter(tIndicePalabras & tabla, tListaCadenas &visitados, tListaCadenas &totales, tListaCadenas &enlace,tListaCadenas &noVisitados, ifstream &archivo, string &cadena, char &letra, string &nombreArchivo){
	
	if ((isspace(letra) && cadena != "") || (ispunct(letra) && cadena != "")){	// inserto clave
		convertirAMinuscula(cadena);
		insertar(tabla, cadena, nombreArchivo);
		reiniciarCadena(archivo, cadena, letra);
	}
	else if (letra == '<'){
		
		reiniciarCadena(archivo, cadena, letra);
		
		while (letra != '>')
			auxiliarCadena(archivo, cadena, letra);
		
		insertar(enlace, cadena);

		if ((buscar(visitados, cadena) == false) && (buscar(noVisitados, cadena) == false)){
			insertar(noVisitados, cadena);
			insertar(totales, cadena);
		}
		
		reiniciarCadena(archivo, cadena, letra);
	}
	else 
		archivo.get(letra);
}