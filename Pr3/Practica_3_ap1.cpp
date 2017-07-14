/* Versión del programa desarrollada con VisualStudio, incluye conio.h, por lo que no se puede ejecutar en linux */

#include <locale.h>
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <conio.h>

using namespace std;


const int MAX = 50;

//El tipo enumerado tCasilla nos permite representar las casillas del tablero:
//donde DestinoL, DestinoC y DestinoJ representan posiciones destino que están libres, con caja o con jugador respectivamente.
enum tCasilla {
	Libre = 0,
	Muro = 1,
	DestinoL = 2,
	DestinoC = 3,
	DestinoJ = 4,
	Jugador = 5,
	Caja = 6
};

//El programa usa también un tipo enumerado tTecla con los siguientes valores: Arriba , Abajo , Derecha , Izquierda , Salir y Nada.
enum tTecla {
	Arriba,
	Abajo,
	Derecha,
	Izquierda,
	Salir,
	Nada
};

//Para mantener el estado del tablero el programa usa un array bidimensional de tCasilla. 
//Declara la correspondiente constante MAX=50 y el tipo tTablero para representarlo.
typedef tCasilla tTablero[MAX][MAX];

struct tSokoban {
	tTablero tablero;
	int nfilas;
	int ncolumnas;
	int po_fila_Jugador;
	int pos_columna_Jugador;
	int ncajas;
	int ncajas_destino;
};

struct tJuego {
	tSokoban sokoban;
	int num_movimientos;
	string name_file;
	string level;
};

void inicializa(tJuego &juego);
bool cargarJuego(tJuego & juego);
bool cargarNivel(ifstream &fichero, tSokoban &sokoban, int nivel);
void iniciaCasilla(tSokoban &sokoban, string linea, int tamlinea, int columna);
void mostarValoresTablero(const tTablero tablero, int nfilas, int ncolumnas);
void mostarFigurasTablero(const tTablero tablero, int nfilas, int ncolumnas);
bool esNivelCorrecto(string cadena, int nivel);
tTecla leerTecla();
void hacerMovimiento(tJuego &juego, tTecla tecla);

int main() {

	tJuego game;
	tTecla aux;
	inicializa(game);
	if (!cargarJuego(game))
		cout << "Error al cargar el juego" << endl;

	while ((aux = leerTecla()) != Salir) {
		if (aux == Arriba)
			cout << "Arriba" << endl;
		else if (aux == Abajo)
			cout << "Abajo" << endl;
		else if (aux == Izquierda)
			cout << "Izquierda" << endl;
		else if (aux == Derecha)
			cout << "Derecha" << endl;
		else if (aux == Nada)
			cout << "Nada" << endl;
	}

	system("pause");

	return 0;
}

//Inicializa el tablero , haciendo que todas las MAX x MAX casillas estén libres y el número de movimientos a 0.
void inicializa(tJuego &juego) {

	for (int i = 0; i < MAX; i++)
		for (int j = 0; j < MAX; j++)
			juego.sokoban.tablero[i][j] = Libre;

	juego.num_movimientos = 0;

}

//Solicita al usuario el fichero y el nivel que desea jugar y lo carga desde dicho fichero.
bool cargarJuego(tJuego & juego) {

	string nombre_fichero;
	ifstream fich_in;
	int nivel;
	bool retorno = false;

	cout << "Introduce el nombre del fichero a cargar" << endl;
	cin >> nombre_fichero;
	fich_in.open(nombre_fichero.c_str(), ios::in);

	if (fich_in.is_open()) {
		cout << "Introduce el nivel que quieres jugar" << endl;
		cin >> nivel;
		retorno = cargarNivel(fich_in, juego.sokoban, nivel);
		fich_in.close();

		// Asignacion de parámetros 
		juego.name_file = nombre_fichero;
		juego.level = nivel;
	}
	else
		cout << "El fichero no existe" << endl;

	return retorno;

}

//Busca en el fichero el nivel solicitado y carga el tablero correspondiente. Devuelve un booleano indicando si lo ha encontrado.
bool cargarNivel(ifstream &fichero, tSokoban &sokoban, int nivel) {

	string linea_fichero;
	ifstream fich_in;
	int i = 0, n_filas = 0, n_colms = 0;
	bool retorno = true, end_of_file = false;

	// Encontramos si el nivel que queremos cargar está en esa línea
	do {
		if (getline(fichero, linea_fichero).eof()) { //No hemos llegado al final del fichero
			end_of_file = true;
			retorno = false;
		}
	} while (!esNivelCorrecto(linea_fichero, nivel) && !end_of_file);

	if (retorno) { // Ha encontrado la linea correcta, podemos continuar, de lo contrario devolvemos un false

		do {

			getline(fichero, linea_fichero);

			//Únicamente necesitamos averiguar el tamanio de las filas una vez
			if (n_filas == 0)
				n_filas = linea_fichero.length();

			iniciaCasilla(sokoban, linea_fichero, linea_fichero.length(), n_colms);
			n_colms++;
		} while (linea_fichero.compare("") != 0);


		//Inicializacion de parámetros del tablero

		sokoban.nfilas = n_filas;
		sokoban.ncolumnas = n_colms;

		mostarFigurasTablero(sokoban.tablero, sokoban.nfilas, sokoban.ncolumnas);
	}

	return retorno;
}


void iniciaCasilla(tSokoban &sokoban, string linea, int tamlinea, int columna) {

	//string caracter;

	for (int i = 0; i < tamlinea; i++) {

		if ((linea.compare(i, 1, "#") == 0))
			sokoban.tablero[columna][i] = Muro;
		else if ((linea.compare(i, 1, "$") == 0))
			sokoban.tablero[columna][i] = Caja;
		else if ((linea.compare(i, 1, ".") == 0))
			sokoban.tablero[columna][i] = DestinoL;
		else if ((linea.compare(i, 1, "@") == 0))
			sokoban.tablero[columna][i] = Jugador;
	}

}

void mostarValoresTablero(const tTablero tablero, int nfilas, int ncolumnas) {

	for (int i = 0; i < ncolumnas; i++) {
		for (int j = 0; j < nfilas; j++)
			cout << tablero[i][j];
		cout << endl;
	}
}

void mostarFigurasTablero(const tTablero tablero, int nfilas, int ncolumnas) {

	for (int i = 0; i < ncolumnas; i++) {
		for (int j = 0; j < nfilas; j++)
			if (tablero[i][j] == 0)			// Libre
				cout << " ";
			else if (tablero[i][j] == 1)	// Muro
				cout << "#";
			else if (tablero[i][j] == 2)	// DestinoL
				cout << ".";
			else if (tablero[i][j] == 3)	// DestinoC
				cout << "*";
			else if (tablero[i][j] == 4)	// DestinoJ
				cout << "$";
			else if (tablero[i][j] == 5)	// Jugador
				cout << "@";
			else if (tablero[i][j] == 6)	// Caja
				cout << "$";
		cout << endl;
	}
}

bool esNivelCorrecto(string cadena, int nivel) {

	bool ret = false;
	string busca = static_cast<ostringstream*>(&(ostringstream() << nivel))->str();

	if (cadena.find(busca) != -1)
		ret = true;

	return ret;
}

//devuelve un valor de tipo tTecla, que puede ser una de las cuatro direcciones si se pulsan las flechas de dirección 
//correspondientes;  el valor Salir, si se pulsa la tecla Esc; o Nada si se pulsa cualquier otra tecla.
tTecla leerTecla() {

	tTecla tecla;
	int tecla_entero;

	cin.sync();

	tecla_entero = _getch(); // Obtenemos el valor de la tecla una primera vez
	tecla_entero = _getch(); // Obtenemos el valor de la tecla una segunda vez

	if (tecla_entero == 27)
		tecla = Salir;
	else if (tecla_entero == 72)
		tecla = Arriba;
	else if (tecla_entero == 80)
		tecla = Abajo;
	else if (tecla_entero == 77)
		tecla = Derecha;
	else if (tecla_entero == 75)
		tecla = Izquierda;
	else
		tecla = Nada;

	return tecla;
}

// Realiza el movimiento del jugador en la dirección indicada.Si no se puede realizar el movimiento, no tiene efecto y 
//no se incrementa tampoco el número de movimientos registrados.

void hacerMovimiento(tJuego &juego, tTecla tecla){
}

//mostarFigurasTablero(sokoban.tablero, sokoban.nfilas, sokoban.ncolumnas);