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

void crearTabla(tIndicePalabras & tabla, const string &nombreArchivoInicial, tListaCadenas & totales, tListaCadenas & visitados, tListaCadenas & noVisitados, tListaCadenas & enlace, tMatriz & L){//A partir de archivoInicial, rellena la tabla tabla, tras haberla inicializado(a vacía).
	ifstream archivo;
	string cadena, nombreArchivo;
	tMatriz m,cn,mResultado;
	tVector v,vProx;
	char letra;
	bool ok = false;
	inicializarTabla(tabla);
	inicializar(visitados, noVisitados,totales,enlace);//Inicializar visitados, no-visitados y totales a listas vacías
	if (visitados.tam<visitados.capacidad){//compruebo si visitados esta lleno
		insertar(noVisitados, nombreArchivoInicial);//inserto en noVisitados nombreArchivoInicial
		insertar(totales, nombreArchivoInicial);//inserto en visitados nombreArchivoInicial
		inicializarMatrizL(L);//iniciar la matriz L a tamaño 1 con un cero
		while (noVisitados.tam != 0){//mientras exista ficheros en noVisitados inserto en visitados
			nombreArchivo = noVisitados.arrayCadena[0];//nombreArchivo 
			insertar(visitados, nombreArchivo);//inserto en visitados el nombreArchivo 
			eliminar(noVisitados, 0);//eliminar desde el ultimo elemento hasta el primero
			eliminarEnlace(enlace);
			archivo.open(nombreArchivo);//Abrir Fichero
			archivo.get(letra);
			while (!archivo.eof()){
				leerCadena(archivo, cadena, letra);//se encarga de crear la cadena hasta que aparezca <, signo de puntuacion o espacio en blanco
				parsearCaracter(tabla, visitados, totales, enlace,noVisitados , archivo, cadena, letra, nombreArchivo);
			}
			archivo.close();
			matrizAdyacente(totales,enlace,L,nombreArchivo);	
		}
	}
}


string convertirAMinuscula(string &cadena){
	std::transform(cadena.begin(), cadena.end(), cadena.begin(),[](unsigned char c) { 
		return std::tolower(c);
	});
	return cadena;
}

void auxiliarCadena(ifstream &archivo, string &cadena, char &letra){//voy creando la cadena caracter a caracter
	cadena = cadena + letra;
	archivo.get(letra);//uso .get porque procesa los espacios en blanco
}

void reiniciarCadena(ifstream &archivo,string &cadena, char &letra){
	archivo.get(letra);
	cadena = "";
}
void leerCadena(ifstream &archivo, string &cadena, char &letra){//se encarga de crear la palabra hasta que aparezca < o signo de puntuacion o espacio en blanco
	while (letra != '<' && !ispunct(letra) && !isspace(letra)){//si no es simbolo < ni signo de puntuacion ni espacion en blanco
		auxiliarCadena(archivo, cadena, letra);
	}
}

void parsearCaracter(tIndicePalabras & tabla, tListaCadenas &visitados, tListaCadenas &totales, tListaCadenas &enlace,tListaCadenas &noVisitados, ifstream &archivo, string &cadena, char &letra, string &nombreArchivo){
	
	if ((isspace(letra) && cadena != "") || (ispunct(letra) && cadena != "")){	// la siguiente letra leida es un espacio en blanco y la cadena sea una palabra no vacia
		convertirAMinuscula(cadena);//convierto la cadena a minuscula
		insertar(tabla, cadena, nombreArchivo);//inserto en la tabla, la clave y el nombre del archivo donde esta la clave
		reiniciarCadena(archivo, cadena, letra);
	}
	else if (letra == '<'){//en caso de que sea un enlace, contruyo el nombre del enlace
		reiniciarCadena(archivo, cadena, letra);
		while (letra != '>'){
			auxiliarCadena(archivo, cadena, letra);
		}
		insertar(enlace, cadena);
		if ((buscar(visitados, cadena) == false) && (buscar(noVisitados, cadena) == false)){
			insertar(noVisitados, cadena);
			insertar(totales, cadena);
		}
		reiniciarCadena(archivo, cadena, letra);
	}
	else {
		archivo.get(letra);
	}
}


