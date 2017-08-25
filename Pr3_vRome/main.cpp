/* Versión del programa desarrollada con VisualStudio, incluye conio.h, por lo que no se puede ejecutar en linux */

#include <locale.h>
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <conio.h>

using namespace std;
const int MAX = 50;
const int MAXH = 10;

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
	Nada,
	Deshacer
};

//Para mantener el estado del tablero el programa usa un array bidimensional de tCasilla. 
//Declara la correspondiente constante MAX=50 y el tipo tTablero para representarlo.
typedef tCasilla tTablero[MAX][MAX];

struct tSokoban {
	tTablero tablero;
	int nfilas;
	int ncolumnas;
	int pos_fila_Jugador;
	int pos_columna_Jugador;
	int ncajas;
	int ncajas_destino;
};

typedef tSokoban tHistoria[MAXH];

struct tJuego {
	tSokoban sokoban;
	int num_movimientos;
	string name_file;
	string level;
	tHistoria historia;
	int conth;
};

void inicializa(tJuego &juego);
bool cargarJuego(tJuego & juego);
bool cargarNivel(ifstream &fichero, tSokoban &sokoban, int nivel);
tTecla leerTecla();
bool esNivelCorrecto(string cadena, int nivel);
void hacerMovimiento(tJuego &juego, tTecla tecla);
void dibujaCasilla(tCasilla casilla);
void dibujar(const tJuego &juego);
bool esCaja(tSokoban &sokoban, char caracter);
bool esCajaDestino(tSokoban sokoban, char caracter);
bool cargarJuegoPruebas(tJuego &juego);
void guardaHistoria(tJuego &juego, tSokoban actual);
bool deshacerMovimiento(tJuego &juego);
void modificaCasillaTablero(tSokoban &sokoban, int fila, int columna, char caracter);

int main() {

	tJuego game;
	tTecla tecla;
	
	inicializa(game);
	if (!cargarJuegoPruebas(game))
		cout << "Error al cargar el juego" << endl;

	dibujar(game);
	while ((tecla = leerTecla()) != Salir) {
		if (tecla != Deshacer)
			hacerMovimiento(game, tecla);
		else
			deshacerMovimiento(game);

		dibujar(game);

	}

	system("pause");

	return 0;
}

//Inicializa el tablero , haciendo que todas las MAX x MAX casillas estén libres y el número de movimientos a 0.
void inicializa(tJuego &juego) {

	for (int i = 0; i < MAX; i++)
		for (int j = 0; j < MAX; j++)
			juego.sokoban.tablero[i][j] = Libre;

	juego.conth = 0;

	juego.num_movimientos = 0;

}

//Solicita al usuario el fichero y el nivel que desea jugar y lo carga desde dicho fichero.
bool cargarJuego(tJuego &juego) {

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

bool cargarJuegoPruebas(tJuego &juego) {

	string nombre_fichero = "niveles.txt";
	ifstream fich_in;
	int nivel = 10;
	bool retorno = false;

	fich_in.open(nombre_fichero.c_str(), ios::in);

	if (fich_in.is_open()) {
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
	bool end_of_file = false, nivel_encontrado = true, nivel_cargado = true;

	// Encontramos si el nivel que queremos cargar está en esa línea
	do 
	{
		if (getline(fichero, linea_fichero).eof()) { //No hemos llegado al final del fichero
			end_of_file = true; 
			nivel_encontrado = false;
		}
	} 
	while (!esNivelCorrecto(linea_fichero, nivel) && !end_of_file);

	// Una vez hemos encotrado el nivel hay que cargarlo correctamente 
		
		string fila_fichero;
		int columna = 0, tam_fila = 0;
		sokoban.ncajas = 0;
		sokoban.ncajas_destino = 0;

		if (nivel_encontrado) {
			
			do
			{
				getline(fichero, fila_fichero);
				for (int i = 0; i < fila_fichero.length(); i++){ // Recorremos todos los elementos de la cadena
					
					modificaCasillaTablero(sokoban, i, columna, fila_fichero.at(i));
					
					if (tam_fila == 0)
						tam_fila = fila_fichero.size();
					
					if (esCaja(sokoban, fila_fichero.at(i)))
						sokoban.ncajas++;

					if (esCajaDestino(sokoban, fila_fichero.at(i)))
						sokoban.ncajas_destino++;

				}
					columna++;
			} while (fila_fichero.compare("") != 0);

			//inicializar parámetros fila / columna de juego
			sokoban.ncolumnas = columna;
			sokoban.nfilas = tam_fila;
		}

	return nivel_encontrado && nivel_cargado;
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
	else if (tecla_entero == 100 || tecla_entero == 68)
		tecla = Deshacer;
	else
		tecla = Nada;

	return tecla;
}

// Realiza el movimiento del jugador en la dirección indicada.Si no se puede realizar el movimiento, no tiene efecto y 
//no se incrementa tampoco el número de movimientos registrados.

void hacerMovimiento(tJuego &juego, tTecla tecla) {

	tCasilla casilla_destino;
	tCasilla casilla_destino_caja;

	int fila_destino, columna_destino;

	guardaHistoria(juego, juego.sokoban);

	if (tecla == Arriba) {

		casilla_destino = juego.sokoban.tablero[juego.sokoban.pos_columna_Jugador - 1][juego.sokoban.pos_fila_Jugador];

		if (casilla_destino == Libre) { // El jugador no tiene objetos delante

			juego.sokoban.tablero[juego.sokoban.pos_columna_Jugador][juego.sokoban.pos_fila_Jugador] = Libre;
			juego.sokoban.pos_columna_Jugador--;
			juego.sokoban.tablero[juego.sokoban.pos_columna_Jugador][juego.sokoban.pos_fila_Jugador] = Jugador;
			juego.num_movimientos++;
		}
	}
	else if (tecla == Abajo) {

		casilla_destino = juego.sokoban.tablero[juego.sokoban.pos_columna_Jugador + 1][juego.sokoban.pos_fila_Jugador];

		if (casilla_destino == Libre ) {
			juego.sokoban.tablero[juego.sokoban.pos_columna_Jugador][juego.sokoban.pos_fila_Jugador] = Libre;
			juego.sokoban.pos_columna_Jugador++;
			juego.sokoban.tablero[juego.sokoban.pos_columna_Jugador][juego.sokoban.pos_fila_Jugador] = Jugador;
			juego.num_movimientos++;
		}
	}
	else if (tecla == Derecha) {

		casilla_destino = juego.sokoban.tablero[juego.sokoban.pos_columna_Jugador][juego.sokoban.pos_fila_Jugador + 1];

		if (casilla_destino == Libre) {
			juego.sokoban.tablero[juego.sokoban.pos_columna_Jugador][juego.sokoban.pos_fila_Jugador] = Libre;
			juego.sokoban.pos_fila_Jugador++;
			juego.sokoban.tablero[juego.sokoban.pos_columna_Jugador][juego.sokoban.pos_fila_Jugador] = Jugador;
			juego.num_movimientos++;
		}
	}
	else if (tecla == Izquierda) {

		casilla_destino = juego.sokoban.tablero[juego.sokoban.pos_columna_Jugador][juego.sokoban.pos_fila_Jugador - 1];

		if (casilla_destino == Libre) {
			juego.sokoban.tablero[juego.sokoban.pos_columna_Jugador][juego.sokoban.pos_fila_Jugador] = Libre;
			juego.sokoban.pos_fila_Jugador--;
			juego.sokoban.tablero[juego.sokoban.pos_columna_Jugador][juego.sokoban.pos_fila_Jugador] = Jugador;
			juego.num_movimientos++;
		}
	}

}

// Muestra una casilla del tablero.
void dibujaCasilla(tCasilla casilla) {

	if (casilla == 0)		// Libre
		cout << " ";
	
	else if (casilla == 1)	// Muro
		cout << "#";
	
	else if (casilla == 2)	// DestinoL
		cout << ".";
	
	else if (casilla == 3)	// DestinoC
		cout << "*";
	
	else if (casilla == 4)	// DestinoJ
		cout << "+";
	
	else if (casilla == 5)	// Jugador
		cout << "@";
	
	else if (casilla == 6)	// Caja
		cout << "$";

}
// Muestra el tablero del juego, el nombre del fichero desde que se ha cargado, su nivel y el número de movimientos realizados.
void dibujar(const tJuego &juego) {
	
	for (int i = 0; i < juego.sokoban.ncolumnas; i++) {
		for (int j = 0; j <= juego.sokoban.nfilas; j++)
		dibujaCasilla(juego.sokoban.tablero[i][j]);
		cout << endl;
	}	
}

bool esCaja(tSokoban &sokoban, char caracter) {

	bool retorno = false;

	if (caracter == '$')
		retorno = true;

	return retorno;
}

bool esCajaDestino(tSokoban sokoban, char caracter) {

	bool retorno = false;

	if (caracter == '*')
		retorno = true;

	return retorno;
}

void modificaCasillaTablero(tSokoban &sokoban, int fila, int columna, char caracter){

	if (caracter == '#')
		sokoban.tablero[columna][fila] = Muro;

	else if (caracter == ' ')
		sokoban.tablero[columna][fila] = Libre;

	else if (caracter == '@')
		sokoban.tablero[columna][fila] = Jugador;

	else if (caracter == '$')
		sokoban.tablero[columna][fila] = Caja;

	else if (caracter == '.')
		sokoban.tablero[columna][fila] = DestinoL;

	else if (caracter == '*')
		sokoban.tablero[columna][fila] = DestinoC;

	else if (caracter == '+')
		sokoban.tablero[columna][fila] = DestinoJ;


	if (caracter == '@' || caracter == '+') {
		sokoban.pos_columna_Jugador = columna;
		sokoban.pos_fila_Jugador = fila;
	}
}

void guardaHistoria(tJuego &juego, tSokoban actual) {

	tSokoban aux;
	
	if(juego.conth < 9)
		juego.conth++;

	for (int i = juego.conth; i > 0; i--)
		juego.historia[i] = juego.historia[i - 1];

	juego.historia[0] = actual;

}

bool deshacerMovimiento(tJuego &juego) {

	bool retorno = true;

	tSokoban aux;
	if (juego.conth > 0) {

		juego.sokoban = juego.historia[0];
		juego.conth--;

		for (int i = 0; i < juego.conth; i++)
			juego.historia[i] = juego.historia[i + 1];

		juego.historia[juego.conth] = aux;
	}
	else
		retorno = false;

	return retorno;
}