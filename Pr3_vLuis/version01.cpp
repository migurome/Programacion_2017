#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <windows.h>
#include <conio.h>
#include "colores.h"
using namespace std;
const int MAX = 50;
const int MAXH = 10;
const int MAXE = 100;
typedef enum {
	black, dark_blue, dark_green, dark_cyan, dark_red, dark_magenta, dark_yellow,
	light_gray, dark_gray, light_blue, light_green, light_cyan, light_red, light_magenta, light_yellow, white
}tColoresPantalla;
typedef enum{ Libre, Muro, DestinoL, DestinoC, DestinoJ, Jugador, Caja }tCasilla;
typedef enum{ Arriba, Abajo, Derecha, Izquierda, Salir,Nada, Deshacer}tTecla;
typedef tCasilla tTablero[MAX][MAX];

typedef struct{
	tTablero tablero;
	int numFilasTab;
	int numColumnasTab;
	int filJugador;
	int colJugador;
	int numCajasTab;
	int	numCajasDestino;
}tSokoban;

typedef tSokoban arraySokoban[MAXH];

typedef struct{
	tSokoban estado;
	int numMovimientos;
	string nomFichero;
	int nivel;
}tJuego;

typedef struct{
	arraySokoban tableroSokoban;
	int	cont;
}tHistoria;

typedef struct{
	string nombreFichero;
	int nivel;
	int numMovimientos;
}tPartida;

typedef tPartida tExitos[MAXE];

typedef struct{
	string nomJugador;
	tExitos exitos;
	int cont;
}tInfo;

/**Prototipos*/
void muestraMenu();//Se Muestra el menu
int menu();//recibe el numero de opcion solicitada por el usuario
void inicializa(tJuego &juego);//inicializa cada elemento del tablero a Libre, y pone el numero de movimientos del juego a 0
bool cargarJuego(tJuego & juego);//solicita al usuario el fichero y el nivel que desea jugar y lo carga desde dicho fichero.
bool cargarNivel(ifstream &fichero, tSokoban &sokoban, int nivel);//busca en el fichero el nivel solicitado y carga el tablero correspondiente.Devuelve un booleano indicando si lo ha encontrado.
void parsearLetra(tSokoban &sokoban, char letra, int fila, int col);//Se encarga de asignar a cada letra leida del fichero un tipo enumerado de tCasilla a cada elemento de la tabla, es decir si la letra corresponde a '#' lo interpreta como muro e inserta el enumerado a una posicion en la tabla 
void insertarTabla(tSokoban &sokoban, int fila, int col, tCasilla casilla);//inserta en la tabla un elemento de tipo enumerado tCasilla 
bool extraerNivel(ifstream &fichero, tSokoban &sokoban, string cadena, string palabra);// se encarga de leer todos los caracteres correspondiente a ese nivel, e ira insertando elementos a la tabla  
void dibujaCasilla(tCasilla casilla);//Se encarga de dibujar una casilla, asignando a esa casilla un color de tColorPantalla
void dibujar(const tJuego &juego);//Se encarga de dibujar toda la tabla
tColoresPantalla int2Enum(tCasilla casilla);//Se encarga de relacionar cada casilla un tipo enumerado de tColoresPantalla
void setColor(tColoresPantalla color);
void inicializaEstado(tSokoban &estado);//resetea el juego, pone todos los campos del juego a cero,excepto los elementos de la tabla 
tTecla leerTecla();//lee la tecla pulsada 
tTecla detectarTecla(int direccion);//recibe un elemento entero correspondiente al char de la tecla pulsada y se le asigna un elemento de tTecla
void hacerMovimiento(tJuego &juego, tTecla &tecla, tInfo &info,tPartida &partida);//Es el que lleva el flujo principal del movimiento porque desde aqui se encarga de llamar a leerMovimiento que es el encargado de ejecutar y evaluar el movimiento
bool leerMovimiento(tJuego &juego, tTecla tecla, bool &bloq);//es la encargada de evaluar el movimiento y se ejecuta si el movimiento es posible
void ejecutarOpcion(int opcion, tJuego &juego, tInfo &info,tPartida &partida);//ejecuta la opcion solicitada por el usuario
void inicializarJuego(tJuego &juego, tInfo &info, tPartida &partida);//se encarga de empezar el flujo de la dinamica del juego invocando a "hacerMovimiento"
bool validarMovimiento(tJuego &juego, int posFil, int posCol, bool &movCaja);//Valida el movimiento evaluando desde la posicion actual del jugador a la posicion siguiente si es posible realizar el movimiento
bool esPosibleMoverCaja(tJuego &juego, int a, int b);//Evalua si es posible mover la caja, es decir si la posicion siguiente  es un muro o una caja y segun eso devuelve un booleano indicado true si es posible y false en caso contrario
void movimientoArriba(tJuego &juego, bool &bloq);//Es la encargada de ejecutar el movimiento hacia arriba
void movimientoAbajo(tJuego &juego, bool &bloq);//Es la encargada de ejecutar el movimiento hacia abajo
void movimientoIzquierda(tJuego &juego, bool &bloq);//Es la encargada de ejecutar el movimiento hacia la izquierda
void movimientoDerecha(tJuego &juego, bool &bloq);//Es la encargada de ejecutar el movimiento hacia la derecha
void validarPosSiguienteLibre(tJuego &juego, int posFil, int posCol);//valida el movimiento si la proxima posicion esta libre
void validarPosSiguienteMuro(tJuego &juego, int posFil, int posCol);//valida el movimiento si la proxima posicion tiene es un Muro
void validarPosSiguienteDestinoL(tJuego &juego, int posFil, int posCol);//valida el movimiento si la proxima posicion tiene es destinoL
void colorFondo(int color);
void movimientoJugadorCaja(tJuego &juego, int posFil, int posCol, bool &movidoCaja);//Si la caja se puede mover, se mueve jugador a la pos de la caja
void compruebaDespuesCaja(tJuego &juego, int pos1, int pos2);
bool bloqueado(const tJuego &juego);
bool deshacerMovimiento(tJuego &juego);
bool bloqueado(const tJuego &juego, int fila, int col);
void almacenarHistoria(tHistoria &historia, const tJuego &juego);
void inicializarHistoria(tHistoria &historia);
void insertar(tHistoria &historia, const tSokoban &sokoban);
void eliminar(tHistoria &historia);
bool operator==(tPartida partida1, tPartida partida2);
bool operator<(tPartida partida1, tPartida partida2);
istream& operator>> (istream & in, tInfo &info);
void inicializar(tInfo &info);
void ordenarElemento(tInfo &info);
void guardar(const tInfo &info);
int buscar(const tInfo &info, tPartida partida);

void mostrarPartidas(const tInfo &info);
/**Menu Principal*/
int main(){
	bool existeFichero = true;
	tJuego juego;
	tInfo info;
	tPartida partida;
	int opcion;
	ifstream archivoJugador;
	string nombre,fichero, cadena = ".txt";
	inicializar(info);
	cout << "Introduce tu nombre: ";
	cin >> nombre;
	cout << "Bienvenido "<<nombre<<endl;
	cadena = nombre+cadena;
	system("pause");
	archivoJugador.open(cadena);
	if (!archivoJugador.is_open()) {
		cout << "No se encuentra la informacion del jugador. Se creara una nueva." << endl;
		existeFichero = false;
	}
	else{
		archivoJugador >> info;//inserto los datos de la partida en info
	}
	if (!existeFichero){
		ofstream archivo;
		archivo.open(cadena);
		archivo.close();
	}
	info.nomJugador = nombre;//actualizo la informacion del jugador
	system("pause");
	system("cls");
	cout << endl;
	opcion = menu();
	ejecutarOpcion(opcion,juego,info,partida);
	return 0;
}
void ejecutarOpcion(int opcion,tJuego &juego,tInfo &info,tPartida &partida){
	while (opcion != 0){
		cout << endl;
		switch (opcion){
		case 0:
			break;
		case 1:
			inicializa(juego);
			if (cargarJuego(juego)){
				
				inicializarJuego(juego,info,partida);
			}
			break;
		case 2:
			mostrarPartidas(info);
			break;
		}
		system("pause");
		system("cls");
		opcion = menu();
	}	
}
void inicializarJuego(tJuego &juego, tInfo &info, tPartida &partida){
	tTecla tecla;
	partida.nombreFichero = juego.nomFichero;
	partida.nivel = juego.nivel;
	partida.numMovimientos = 0;
	hacerMovimiento(juego,tecla,info,partida);
}
int menu(){
	int opcion=0;
	muestraMenu();
	cin >> opcion;
	while (opcion < 0 || opcion >2){
		cout << "opcion incorrecta. Introduce una opcion: ";
		cin >> opcion;
	}
	return opcion;
}
void setColor(tColoresPantalla color){
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(handle, color);
}
void inicializaEstado(tSokoban &estado){
	estado.numColumnasTab = 0;
	estado.numFilasTab = 0;
	estado.filJugador = 0;
	estado.colJugador = 0;
	estado.numCajasTab = 0;
	estado.numCajasDestino = 0;
}
void inicializa(tJuego &juego){
	inicializaEstado(juego.estado);
	for (int i = 0; i < MAX; i++){
		for (int j = 0; j < MAX; j++){
			juego.estado.tablero[i][j] = Libre;
			juego.numMovimientos = 0;
			juego.nivel = 0;
		}		
	}
}
bool cargarJuego(tJuego & juego){
	bool ok = false;
	ifstream archivo;	
	string nomFichero;
	int nivel;
	cout << "Introduce el nombre del fichero:" << endl;
	cin >> nomFichero;
	cout << "Introduce el nivel que deseas: " << endl;
	cin >> nivel;
	archivo.open(nomFichero);
	if (!archivo.is_open())
		cout << "Error, no exite o no se ha encontrado el archivo" << endl;
	else{
		juego.nomFichero = nomFichero;
		ok=cargarNivel(archivo,juego.estado,nivel);//Compruebo si el nivel existe
		}
	if (ok == true){
		juego.nivel = nivel;
	}
	else{
		cout << "No existe nivel en el fichero.  Pulse una tecla para continuar...." << endl;
	}
	archivo.close();
	return ok;
	}

bool cargarNivel(ifstream &fichero, tSokoban &sokoban, int nivel){
	stringstream s;
	string palabra, cadena = " ";
	bool ok = false;
	s << "Level "<<nivel<<"\r";//uso s y le añado el nivel del usuario, para comparar cada linea del fichero
	palabra = s.str();//se copia en palabra el string de Level y nivel
	while (cadena != palabra && !fichero.eof()){
		getline(fichero, cadena);
		if (cadena == palabra){
			extraerNivel(fichero, sokoban, cadena, palabra);
			ok = true;
		}
	}
	return ok;
}
bool extraerNivel(ifstream &fichero, tSokoban &sokoban,string cadena,string palabra){
	int aux = 0,num,i=0;//i es para ir avanzando las filas
	char letra = ' ';
	bool ok = false;
	while (!ok ){//mientras no termine de leer el nivel o sea el fin del fichero "ok" sera false
		getline(fichero, cadena);
		if (cadena != "\r"){
			num = cadena.length();
			for (int j = 0; j < num; j++){
				letra = cadena[j];
				if(letra !='\r') {//puede ocurrir que solo me coja el salto de linea y no el conjunto de cadenas de la linea que quiero parsear
					parsearLetra(sokoban, cadena[j], i, j);
					aux++;	
				}
			}
			if (sokoban.numColumnasTab<aux){
				sokoban.numColumnasTab = aux;//lo uso para crear la dimension de la tabla porque segun en que fila este el numero de columnas puede variar porque pueden existir tablas de filas y columnas distintas, se queda con el valor mas alto de numero de columnas
			}
			aux = 0;
			i++;
			sokoban.numFilasTab++;//lo uso para crear la dimension de la tabla, cuenta el total de filas 
	    }
		else{
			ok = true;//en el caso de que lea el siguiente linea y sea un espacio en blanco, significa que se acabo de leer todo el nivel del fichero
		}
		if (fichero.eof()){
			ok = true;//es fin del fichero
		}
	}
	return ok;
}
void parsearLetra(tSokoban &sokoban, char letra,int fila,int col){
	tCasilla casilla;
	switch (letra){
	case '#':
		casilla = Muro;
		insertarTabla(sokoban, fila, col,casilla);
		break;
	case '@':
		casilla = Jugador;
		insertarTabla(sokoban, fila, col, casilla);
		sokoban.filJugador = fila;
		sokoban.colJugador = col;
		break;
	case '$':
		casilla = Caja;
		insertarTabla(sokoban, fila, col, casilla);
		sokoban.numCajasTab++;
		break;
	case '.':
		casilla = DestinoL;
		insertarTabla(sokoban, fila, col, casilla);
		break;
	case '*':
		casilla = DestinoC;
		insertarTabla(sokoban, fila, col, casilla);
		sokoban.numCajasDestino++;
		break;
	case '+':
		casilla = DestinoJ;
		insertarTabla(sokoban, fila, col, casilla);
		break;
	}
}
void insertarTabla(tSokoban &sokoban,int fila,int col,tCasilla casilla){
	sokoban.tablero[fila][col] = casilla;		
}
void muestraMenu(){
	cout << "1. Jugar partida" << endl;
	cout << "2. Mostrar partidas ganadas. " << endl;
	cout << "0. Terminar" << endl;
	cout << "Introduce una opcion: ";
}

void dibujaCasilla(tCasilla casilla){
	tColoresPantalla colorin;
	char c = char(219);
	switch (casilla){
	case Libre:
		colorin = int2Enum(casilla);
		setColor(colorin);
		cout << c<<c;
		break;
	case Muro:
		colorin = int2Enum(casilla);
		setColor(colorin);
		cout << c<<c;
		break;
	case Caja:
		colorin = int2Enum(casilla);
		colorFondo(colorin);
		cout << "()";
		break;
	case Jugador:
		colorin = int2Enum(casilla);
		colorFondo(colorin);
		cout << "00";
		break;
	case DestinoL:
		//colorin = int2Enum(casilla);
		colorFondo(12);
		cout <<"..";
		break;
	case DestinoJ:
		//colorin = int2Enum(casilla);
		colorFondo(4);
		cout <<"00";
		break;
	case DestinoC:
		//colorin = int2Enum(casilla);
		colorFondo(4);
		cout <<"[]";
		break;
	}
}
void dibujar(const tJuego &juego){
	for (int i = 0; i < juego.estado.numFilasTab; i++){
		cout << endl;
		for (int j = 0; j < juego.estado.numColumnasTab; j++){
			dibujaCasilla(juego.estado.tablero[i][j]);
		}
	}
}
tColoresPantalla int2Enum(tCasilla casilla){
	tColoresPantalla salida;
	if (casilla == DestinoL)
		salida = light_red;
	else if (casilla == Jugador)
		salida = dark_gray;
	else if (casilla == Caja)
		salida = light_gray;
	else if (casilla == Muro)
		salida = dark_green;
	else if (casilla == Libre)
		salida = dark_blue;
	else if (casilla == DestinoJ)
		salida = dark_red;
	else if (casilla == DestinoC)
		salida = light_yellow;
	
	return salida;
}
tTecla leerTecla(){
	tTecla tecla = Nada;
	int dir;
	cin.sync();
	dir = _getch(); // dir: tipo int
	if (dir == 0xe0) {
		dir = _getch();
	}
	tecla = detectarTecla(dir);
	return tecla;
}
tTecla detectarTecla(int direccion){
	tTecla salida;
	if (direccion == 72)
		salida = Arriba;
	else if (direccion == 75)
		salida = Izquierda;
	else if (direccion == 77)
		salida = Derecha;
	else if (direccion == 80)
		salida = Abajo;
	else if (direccion == 27)
		salida = Salir;
	else if (direccion == 100)//d
		salida = Deshacer;
	else if (direccion == 68)//D
		salida = Deshacer;
	return salida;
}
void hacerMovimiento(tJuego &juego,tTecla &tecla,tInfo &info,tPartida &partida){
	tHistoria historia,historiaIni;
	bool ok = false,bloq=false;
	tSokoban aux;
	inicializaEstado(aux);//inicializo el sokoban con todos los campos a cero
	inicializarHistoria(historia);
	inicializarHistoria(historiaIni);
	almacenarHistoria(historiaIni, juego);
	system("cls");//limpio la pantalla
	cout << "Fichero: " << juego.nomFichero << " Nivel: " <<juego.nivel<< endl;
	dibujar(juego);
	setColor(white);//el color de las letras vuelvan a tener el color por defecto
	cout << endl;
	cout << "\nNumero de movimientos: " <<juego.numMovimientos << endl;
	tecla = leerTecla();
	while (tecla!=Salir &&!ok){
		leerMovimiento(juego, tecla,bloq);//aqui es donde  se evaluara el movimiento y lo ejecutara
		if (tecla == Deshacer){
			if (historia.cont == 0){
				juego.estado = historiaIni.tableroSokoban[historiaIni.cont - 1];
				cout << "No se puede deshacer" << endl;
			}
			else if (historia.cont >= 1 && historia.cont <MAXH){
				historia.tableroSokoban[historia.cont - 1] = historia.tableroSokoban[historia.cont];//borro la ultima historia
				historia.cont--;
				 if (historia.cont == 0){
					juego.estado = historiaIni.tableroSokoban[historiaIni.cont - 1];
				}
				 else{
					 juego.estado = historia.tableroSokoban[historia.cont - 1];//actualizo el estado del tablero a la penultima historia
				 }
			}
			else if (historia.cont==MAXH){
				int aux1 = historia.cont - MAXH;
				historiaIni.tableroSokoban[historiaIni.cont - 1] = historia.tableroSokoban[aux1];//almaceno el primer elemento de la historia correspondiente 
				historia.tableroSokoban[historia.cont - 1] = historia.tableroSokoban[historia.cont];//borro la ultima historia
				historia.cont--;
				juego.estado = historia.tableroSokoban[historia.cont - 1];//actualizo el estado del tablero a la penultima historia
				//historiaIni.cont++;
				/*if (historia.cont > aux1){
					historia.tableroSokoban[historia.cont - 1] = historia.tableroSokoban[historia.cont];//borro la ultima historia
					historia.cont--;
					juego.estado = historia.tableroSokoban[historia.cont - 1];//actualizo el estado del tablero a la penultima historia
				}*/

			}
		}
		else{
			almacenarHistoria(historia, juego);
			
		}
		system("cls");
		cout << "Fichero: " << juego.nomFichero << " Nivel: " << juego.nivel << endl;
		dibujar(juego);
		setColor(white);//el color de las letras vuelvan a tener el color por defecto
		cout << endl;
		cout << "\nNumero de movimientos: " << juego.numMovimientos << endl;
		if (bloq){
			cout << "te has quedado bloqueado" << endl;
		}
		if (juego.estado.numCajasDestino == juego.estado.numCajasTab){
			ok = true;
			int pos = -1;
			cout << "\n Felicidades!!!!!" << endl;
			partida.numMovimientos = juego.numMovimientos;
			ordenarElemento(info);
			pos=buscar(info,partida);
			if (partida.numMovimientos<info.exitos[pos].numMovimientos){
				info.exitos[pos].numMovimientos = partida.numMovimientos;
			}
			else{
				info.exitos[info.cont] = partida;
				info.cont++;
				ordenarElemento(info);
			}
			guardar(info);
		}
		else{
			tecla = leerTecla();
		}
	}
	if (tecla==Salir){
		cout << "\n hasta otra!!" << endl;
	}
	
}
bool leerMovimiento(tJuego &juego, tTecla tecla, bool &bloq){
	bool ok = false;//ok si ha leido el movimiento
	tTecla ntecla = tecla;
		if (ntecla == Arriba){
			movimientoArriba(juego,bloq);
			ok = true;
		}
		else if (ntecla == Abajo){
			movimientoAbajo(juego,bloq);
			ok = true;
		}
		else if (ntecla == Izquierda){
			movimientoIzquierda(juego,bloq);
			ok = true;
		}
		else if (ntecla == Derecha){
			movimientoDerecha(juego,bloq);
			ok = true;
		}

		else if (ntecla == Deshacer){
			deshacerMovimiento(juego);
			ok = true;
		}
	return ok;
}

void movimientoArriba(tJuego &juego, bool &bloq){
	int posFil=0, posCol=0,aux=0;
	bool movCaja = false;
	posFil = juego.estado.filJugador;// posFil fila actual del jugador que usare para validar movimiento
	posCol = juego.estado.colJugador;//posCol col actual del jugador que usare para validar movimiento
	posFil--;// si es arriba se avanza  y se resta una fila
	if (validarMovimiento(juego, posFil, posCol, movCaja)){
		juego.estado.filJugador--;//si el movimiento es valido se actualiza el movmiento del jugador
	}
	if (movCaja){//en caso de que la pos siguiente al jugador sea una caja
		aux = posFil;//se usara para posicion destino de la caja en caso de que se mueva
		if (esPosibleMoverCaja(juego, aux - 1, juego.estado.colJugador)){//le paso la siguiente posicion a la caja
			bool movidoCaja = false;
			movimientoJugadorCaja(juego, posFil, posCol,movidoCaja);//le paso la pos Caja, y en la pos caja pongo el jugador
			posFil--;
			compruebaDespuesCaja(juego, aux - 1, juego.estado.colJugador);//pasar la pos despues de la caja y la posFila(pos siguiente donde va DestinoC)
			juego.estado.filJugador--;
			if (movidoCaja){
				//juego.estado.tablero[aux - 1][juego.estado.colJugador] = Caja;//esto es la pos actual de la caja
				int auxFila = aux - 1;//la fila de la caja
				int auxCol = juego.estado.colJugador;//col de la caja
				bool bloq = false;
				bloq = bloqueado(juego,auxFila,auxCol);
			}
		}
	}
}
void movimientoAbajo(tJuego &juego,bool &bloq){
	int posFil = 0, posCol = 0, aux = 0;
	bool movCaja = false;
	posFil = juego.estado.filJugador;
	posCol = juego.estado.colJugador;
	posFil++;//si es abajo retrocede y se suma una fila
	if (validarMovimiento(juego, posFil, posCol, movCaja)){
		juego.estado.filJugador++;
	}
	if (movCaja){
		aux = posFil;//posicion siguiente
		if (esPosibleMoverCaja(juego, aux + 1, juego.estado.colJugador)){//le paso la siguiente posicion a la caja
			bool movidoCaja = false;
			movimientoJugadorCaja(juego, posFil, posCol,movidoCaja);//le paso la pos Caja, y en la pos caja pongo el jugador
			posFil++;
			compruebaDespuesCaja(juego, aux + 1, juego.estado.colJugador);
			juego.estado.filJugador++;
			if (movidoCaja){
				int auxFila = aux + 1;
				int auxCol = juego.estado.colJugador;
				bloq = bloqueado(juego, auxFila, auxCol);
			
			}
		}
	}
}
void movimientoIzquierda(tJuego &juego, bool &bloq){
	int posFil = 0, posCol = 0, aux = 0;
	bool movCaja = false;
	posFil = juego.estado.filJugador;
	posCol = juego.estado.colJugador;
	posCol--;//si es izquierda retrocede una columna
	if (validarMovimiento(juego, posFil, posCol, movCaja)){
		juego.estado.colJugador--;
	}
	if (movCaja){
		aux = posCol;
		if (esPosibleMoverCaja(juego, juego.estado.filJugador, aux - 1)){
			bool movidoCaja = false;
			movimientoJugadorCaja(juego, posFil, posCol,movidoCaja);
			posCol--;
			compruebaDespuesCaja(juego, juego.estado.filJugador, aux - 1);
			juego.estado.colJugador--;
			if (movidoCaja){
				int auxFila = juego.estado.filJugador;
				int auxCol = aux - 1;
				bloq = bloqueado(juego, auxFila, auxCol);
			}
		}
	}
}
void movimientoDerecha(tJuego &juego, bool &bloq){
	int posFil = 0, posCol = 0, aux = 0;
	bool movCaja = false;
	posFil = juego.estado.filJugador;
	posCol = juego.estado.colJugador;
	posCol++;//si es derecha avanza una columna, aumenta poscol para evaluar la siguiente posicion
	if (validarMovimiento(juego, posFil, posCol, movCaja)){
		juego.estado.colJugador++;
	}
	if (movCaja){
		aux = posCol;//columna jugador
		if (esPosibleMoverCaja(juego, juego.estado.filJugador, aux + 1)){//le paso la siguiente posicion a la caja
			bool movidoCaja = false;
			movimientoJugadorCaja(juego,posFil,posCol,movidoCaja);//le paso la siguiente posicion de la caja o destinoC
			posCol++;//avanzo una posicion mas para poner la caja
			compruebaDespuesCaja(juego, juego.estado.filJugador, aux + 1);
			juego.estado.colJugador++;
			if (movidoCaja){
				int auxFila = juego.estado.filJugador;
				int auxCol = aux + 1;
				bloq = bloqueado(juego, auxFila, auxCol);
			}
		}
	}

}

bool bloqueado(const tJuego &juego,int auxFila,int auxCol){
	bool ok = false;
	int contB = 0;
	int contizqDer = 0;
	int contarrAbj = 0;
	if (juego.estado.tablero[auxFila - 1][auxCol] == Muro){//compruebo una pos arriba de la caja
		contB++;
		contarrAbj++;
	}
	if (juego.estado.tablero[auxFila][auxCol - 1] == Muro){//compruebo una pos izquierda de la caja
		contB++;
		contizqDer++;
	}
	if (juego.estado.tablero[auxFila][auxCol + 1] == Muro){//compruebo una pos derecha de la caja
		contB++;
		contizqDer++;
	}

	if (juego.estado.tablero[auxFila + 1][auxCol] == Muro){//compruebo una pos abajo de la caja
		contB++;
		contarrAbj++;
	}

	if (contarrAbj>0 && contizqDer == 2){
		//cout << "te has quedado bloqueado";
		ok = true;
	}
	if (contizqDer == 2 && contarrAbj == 1){
		//cout << "te has quedado bloqueado";
		ok = true;
	}
	if (contarrAbj == 1 && contizqDer == 1){
		//cout << "te has quedado bloqueado";
		ok = true;
	}
	return ok;
}

bool validarMovimiento(tJuego &juego,int posFil,int posCol,bool &movCaja){//juego, fila y columna del jugador a validar y se actualizara movCaja 
	int aux = 0;
	bool ok = false;
	tCasilla casilla;
	casilla=juego.estado.tablero[posFil][posCol];//obtengo la casilla de la pos siguiente a validar
	switch (casilla){
	case Libre://Si en la posicion siguiente se encuentra Libre
		validarPosSiguienteLibre(juego,posFil,posCol);
		ok = true;//se ha realizado el movimiento 
		break;
	case Muro://Si en la posicion siguiente se encuentra Muro
		validarPosSiguienteMuro(juego,posFil,posCol);
		break;
	case Caja://La posicion siguiente es caja
		movCaja = true;
		break;

	case DestinoL://Si en la posicion siguiente se encuentra DestinoL
		validarPosSiguienteDestinoL(juego,posFil,posCol);
		ok = true;//se ha realizado el movimiento 
		break;
	case DestinoC://Si en la posicion siguiente se encuentra DestinoC
		movCaja = true;
		break;
	}
	return ok;
}

void validarPosSiguienteLibre(tJuego &juego,int posFil,int posCol){// le paso de la pos siguiente
	if (juego.estado.tablero[juego.estado.filJugador][juego.estado.colJugador] == Jugador){//si la casilla de posicion actual es Jugador
		juego.estado.tablero[posFil][posCol] = Jugador;//sabemos que la posicion siguiente es libre, entonces en la pos libre se pone jugador
		juego.estado.tablero[juego.estado.filJugador][juego.estado.colJugador] = Libre;//y en la pos jugador se pone libre
	}
	else if (juego.estado.tablero[juego.estado.filJugador][juego.estado.colJugador] == DestinoJ){
		juego.estado.tablero[posFil][posCol] = Jugador;//sabemos que la pos siguiente es libre
		juego.estado.tablero[juego.estado.filJugador][juego.estado.colJugador] = DestinoL;
	}
	juego.numMovimientos++;//se actualiza el movimiento
}
void validarPosSiguienteMuro(tJuego &juego, int posFil, int posCol){
	//posicion actual es jugador
	if (juego.estado.tablero[juego.estado.filJugador][juego.estado.colJugador] == Jugador){//posicion actual es jugador
		juego.estado.tablero[juego.estado.filJugador][juego.estado.colJugador] = Jugador;//se queda en la misma posicion
	}
	else if (juego.estado.tablero[juego.estado.filJugador][juego.estado.colJugador] == DestinoJ){//posicion actual es destino jugador
		juego.estado.tablero[juego.estado.filJugador][juego.estado.colJugador] = DestinoJ;//se queda en la misma posicion
	}
}
void validarPosSiguienteDestinoL(tJuego &juego, int posFil, int posCol){
	if (juego.estado.tablero[juego.estado.filJugador][juego.estado.colJugador] == Jugador){
		juego.estado.tablero[posFil][posCol] = DestinoJ;
		juego.estado.tablero[juego.estado.filJugador][juego.estado.colJugador] = Libre;//posicion actual
	}
	else if (juego.estado.tablero[juego.estado.filJugador][juego.estado.colJugador] == DestinoJ){//posicion actual
		juego.estado.tablero[posFil][posCol] = DestinoJ;
		juego.estado.tablero[juego.estado.filJugador][juego.estado.colJugador] = DestinoL;//posicion siguiente
	}
	juego.numMovimientos++;
}

bool esPosibleMoverCaja(tJuego &juego,int a, int b){//Si despues de la caja hay muro u otra caja
	tCasilla casilla;
	bool ok = true;
	casilla = juego.estado.tablero[a][b];//la posicion siguiente a la caja
	switch (casilla){
	case Muro:
		ok = false;
		break;
	case Caja:
		ok = false;
		break;
	case DestinoC:
		ok = false;
		break;
	case DestinoL:
		ok = true;
		break;
	case Libre:
		ok = true;
		break;
	}//switch
	return ok;
}
void colorFondo(int color) {
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(handle, 15 | (color << 4));
}

void movimientoJugadorCaja(tJuego &juego, int posFil, int posCol,bool &movidoCaja){//le paso fil y col caja

	if (juego.estado.tablero[posFil][posCol] == Caja){//pos actual de la caja
		if (juego.estado.tablero[juego.estado.filJugador][juego.estado.colJugador] == Jugador){//
			juego.estado.tablero[posFil][posCol] = Jugador; //donde estaba la pos caja se pone a jugador
			juego.estado.tablero[juego.estado.filJugador][juego.estado.colJugador] = Libre;//donde estaba las pos jugador se pone a libre
			movidoCaja = true;
		}
		else if (juego.estado.tablero[juego.estado.filJugador][juego.estado.colJugador] == DestinoJ){
			juego.estado.tablero[posFil][posCol] = Jugador;
			juego.estado.tablero[juego.estado.filJugador][juego.estado.colJugador] = DestinoL;
		}
		
		juego.numMovimientos++;
	}
	else if (juego.estado.tablero[posFil][posCol] == DestinoC){//pos actual de Destinocaja
		if (juego.estado.tablero[juego.estado.filJugador][juego.estado.colJugador]==DestinoJ){
			juego.estado.tablero[posFil][posCol] = DestinoJ;
			juego.estado.tablero[juego.estado.filJugador][juego.estado.colJugador] = DestinoL;
			juego.estado.numCajasDestino--;
			
		}
		else if (juego.estado.tablero[juego.estado.filJugador][juego.estado.colJugador] == Jugador){
			juego.estado.tablero[posFil][posCol] = DestinoJ;
			juego.estado.tablero[juego.estado.filJugador][juego.estado.colJugador] = Libre;
			juego.estado.numCajasDestino--;
		}
		juego.numMovimientos++;
	}
}

void compruebaDespuesCaja(tJuego &juego, int pos1, int pos2){//le paso la posicion despues de la caja o DestinoC
	//si la pos despues de la caja es libre se pone caja
	if (juego.estado.tablero[pos1][pos2] == Libre){
		//if(juego.estado.tablero[posActual1][posActual2]==DestinoC){juego.estado.numCajasDestino--;}
		juego.estado.tablero[pos1][pos2] = Caja;//la pos donde estaba libre se pone la caja

	}
	//si la pos despues de la caja es DestinoL se pone caja
	else if (juego.estado.tablero[pos1][pos2] == DestinoL){
		juego.estado.tablero[pos1][pos2] = DestinoC;//la pos donde estaba libre se pone la caja
		juego.estado.numCajasDestino++;
	}

}

void almacenarHistoria(tHistoria &historia, const tJuego &juego){
	if(historia.cont<MAXH){
		historia.tableroSokoban[historia.cont] = juego.estado;
		historia.cont++;
	}
	else {//(historia.cont == MAXH)
		eliminar(historia);
		insertar(historia,juego.estado);
	}
}

bool bloqueado(const tJuego &juego){//que indica si alguna de las cajas no colocadas en destino ha quedado atrapada en una esquina
	return true;
}

bool deshacerMovimiento(tJuego &juego){
	bool ok = false;
	if (juego.numMovimientos > 0){
		juego.numMovimientos--;
		ok = true;
	}	
	return ok;
}
void inicializarHistoria(tHistoria &historia){
	for (int i = 0; i < MAXH;i++){
		inicializaEstado(historia.tableroSokoban[i]);
	}
	historia.cont = 0;
}

void insertar(tHistoria &historia, const tSokoban &sokoban){
	if (historia.cont<MAXH){
		historia.tableroSokoban[historia.cont] = sokoban;
		historia.cont++;
	}
}
void eliminar(tHistoria &historia){
	for (int i = 0; i < historia.cont;i++){
		historia.tableroSokoban[i] = historia.tableroSokoban[i+1];
	}
	historia.cont--;
}

bool operator==(tPartida partida1, tPartida partida2){
	return ((partida1.nombreFichero == partida2.nombreFichero) && (partida1.nivel == partida2.nivel));
}

bool operator<(tPartida partida1, tPartida partida2){
	bool menor=false;
	if (partida1.nombreFichero < partida2.nombreFichero){
		menor = true;
	}	
	else{
		if (partida1.nombreFichero == partida2.nombreFichero){
			if (partida1.nivel<partida2.nivel)
				menor = true;
			else
				menor = false;
		}
		else{
			menor = false;
		}
	}	
return menor;
}

istream& operator>> (istream & in, tInfo &info){
	int i = 0;
	string cadena;
	while (!in.eof()&&i<MAXE){
		in >> info.exitos[i].nombreFichero;
		in >> info.exitos[i].nivel;
		in >> info.exitos[i].numMovimientos;
		info.cont++;
		i++;
	}
	return in;
}
void inicializar(tInfo &info){
	for (int i = 0; i < MAXE;i++){
		info.exitos[i].nombreFichero = "";
		info.exitos[i].nivel = 0;
		info.exitos[i].numMovimientos = 0;
	}
	info.cont = 0;
}
void ordenarElemento(tInfo &info){//ordenación por el metodo de la burbuja
	bool ok=true;
	int i = 0;
	while (i<info.cont-1 && ok){
		ok = false;
		for (int j = info.cont - 1; j>i;j--){
			if (info.exitos[j]<info.exitos[j-1]){
				ok = true;
				tPartida tmp=info.exitos[j];
				info.exitos[j] = info.exitos[j-1];
				info.exitos[j - 1] = tmp;
			}
		}
		if (ok){
			i++;
		}
	}
}

void guardar(const tInfo &info) {//ya estara ordenado
	ofstream archivo;
	string cadena = ".txt";
	cadena = info.nomJugador + cadena;
	archivo.open(cadena);
	for (int i = 0; i < info.cont; i++) {
		archivo << info.exitos[i].nombreFichero<<" ";
		archivo << info.exitos[i].nivel << " ";
		archivo << info.exitos[i].numMovimientos << endl;
	}
	archivo.close();
}

int buscar(const tInfo &info,tPartida partida){//busqueda en lista ordenada
	bool encontrado = false;
	int pos = -1;
	int ini = 0, mitad = 0, fin = info.cont-1;
	while (ini<=fin && !encontrado){
		mitad = (ini +fin) / 2;
		if (partida==info.exitos[mitad]){
			encontrado = true;
			pos = mitad;
		}
		else if (partida<info.exitos[mitad]){
			fin = mitad - 1;
		}
		else{
			ini = mitad + 1;
		}
	}
	return pos;
}
void mostrarPartidas(const tInfo &info){
	cout << endl;
	cout << setw(15) << "Fichero"<<setw(15)<<"Nivel"<<setw(15)<<"Movimiento"<<endl;
	cout << endl;
	for (int i = 0; i < info.cont;i++){
		cout << setw(15) << info.exitos[i].nombreFichero << setw(15) << info.exitos[i].nivel << setw(15) << info.exitos[i].numMovimientos << endl;
	}
	cout << endl;
}