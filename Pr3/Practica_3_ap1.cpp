/*
1. Descripción del juego
La práctica consiste en desarrollar un programa en C++ para jugar al Sokoban, un
conocido rompecabezas creado por el japonés Hiroyuki Imabayashi en 1981, aunque
después se han implementado distintas versiones y variantes. Se puede obtener más
información y ver ejemplos en acción en https://en.wikipedia.org/wiki/Sokoban.
El juego se desarrolla en un tablero que representa un almacén con cajas y un
empleado que debe empujar dichas cajas hasta unas determinadas posiciones destino.
Dependiendo de la dificultad, los tableros tienen asignado un nivel. A continuación se
muestra un posible nivel del juego (imagen tomada de http://sokoban.info/):
El jugador puede moverse en horizontal o en vertical (sin atravesar los muros, ni las
cajas). Puede empujar las cajas a una casilla contigua libre (las cajas no pueden
apilarse, ni desplazar más de una simultáneamente). El puzle está terminado cuando

todas las cajas están en las posiciones destino (marcadas con punto rojo en la imagen
anterior).
El tablero anterior, que se ha cargado desde el fichero levels.txt y tiene nivel 0, lo
podemos representar de la siguiente forma sobre la consola:
Versión 1 del programa
El programa simulará de forma realista la dinámica del juego, aunque en modo de
consola. Inicialmente mostrará un menú con dos opciones:
1. Jugar partida.
0. Salir
La opción 1 permitirá cargar un tablero de un determinado nivel desde el fichero que
indique el usuario. Se podrán jugar partidas hasta que se elija la opción 0.

1. Datos del programa
El tipo enumerado tCasilla nos permite representar las casillas del tablero:
typedef enum tCasilla{Libre,Muro,DestinoL,DestinoC,DestinoJ,Jugador,Caja}
donde DestinoL, DestinoC y DestinoJ representan posiciones destino que están
libres, con caja o con jugador respectivamente.

Para mantener el estado del tablero el programa usa un array bidimensional de
tCasilla . Declara la correspondiente constante MAX=50 y el tipo tTablero para
representarlo.

Define el tipo estructurado tSokoban para describir el estado del tablero, conteniendo:
✓ El tablero de tipo tTablero .
✓ El número de filas nfilas y de columnas ncolumnas del array bidimensional que
está ocupando el tablero (ambas <= MAX ).
✓ La fila y la columna donde se encuentra colocado el jugador.
✓ El número de cajas del tablero.
✓ El número de cajas ya colocadas en casilla destino.
Define también el tipo estructurado tJuego que describe el estado del juego:

El estado del tablero sokoban de tipo tSokoban .
El número de movimientos realizados hasta el momento numMovimientos .
El nombre del fichero nFichero del que se ha cargado el juego.
El nivel que estamos jugando.
El programa usa también un tipo enumerado tTecla con los siguientes valores:
Arriba , Abajo , Derecha , Izquierda , Salir y Nada .


2. Carga de un nivel del juego
Los tableros de juego de los distintos niveles se leerán de un archivo de texto que
puede guardar tantos niveles diferentes como queramos.
Por ejemplo, si el tablero del ejemplo anterior corresponde al nivel 0, en el archivo
tendremos:
Level 0
MIAU

La primera línea define el número del nivel. A continuación aparece una matriz de
caracteres, donde ’#’ representa muro, ’ ’ (blanco) es casilla vacía, ’.’ es casilla destino
libre, ’$’ es caja y @ representa el jugador. Aunque no aparece en este ejemplo, en
otros niveles el carácter ’*’ representa caja en casilla destino y ‘+’ representa jugador
en casilla destino. En este archivo los niveles vendrán separados por una línea vacía.
En el Campus Virtual se proporcionarán varios archivos con un repertorio de niveles,
la mayoría descargados de http://sneezingtiger.com/sokoban/levels.html.

Observa que la matriz de caracteres no es cuadrada, y que los campos nfilas y
ncolumnas quedan determinados por la lectura.
Implementa al menos los siguientes subprogramas:

void inicializa(tJuego &juego) : inicializa el tablero , haciendo que todas las
MAX x MAX casillas estén libres y el número de movimientos a 0.

bool cargarJuego(tJuego & juego) : solicita al usuario el fichero y el nivel
que desea jugar y lo carga desde dicho fichero .
bool cargarNivel(ifstream &fichero, tSokoban &sokoban, int nivel) :
busca en el fichero el nivel solicitado y carga el tablero correspondiente.
Devuelve un booleano indicando si lo ha encontrado.



3. El juego en acción
3.1 Lectura de teclas especiales
Para leer las teclas pulsadas por el usuario implementa el siguiente subprograma:
✓ tTecla leerTecla() : devuelve un valor de tipo tTecla , que puede ser una de las
cuatro direcciones si se pulsan las flechas de dirección correspondientes; el valor
Salir , si se pulsa la tecla Esc; o Nada si se pulsa cualquier otra tecla.
La función leerTecla() detectará la pulsación por parte del usuario de teclas
especiales, concretamente las teclas de flecha (direcciones) y la tecla Esc (salir). La
tecla Esc sí genera un código ASCII (27), pero las de flecha no tienen códigos ASCII
asociados. Cuando se pulsan en realidad se generan dos códigos, uno que indica que se
trata de una tecla especial y un segundo que indica de cuál se trata.
Las teclas especiales no se pueden leer con get() , pues esta función sólo devuelve un
código. Podemos leerlas con la función _getch() , que devuelve un entero y se puede
llamar una segunda vez para obtener el segundo código, si se trata de una tecla
especial. Esta función requiere que se incluya la biblioteca conio.h .
cin.sync();
dir =_getch(); // dir: tipo int
if (dir == 0xe0) {
dir = _getch();
// ...
}
// Si aquí dir es 27, es la tecla Esc
Si el primer código es 0xe0 , se trata de una tecla especial. Sabremos cuál con el
segundo resultado de _getch() . A continuación puedes ver los códigos de cada tecla
especial:
↑ 72
↓ 80
→ 77
← 75
3.2 Movimiento del tablero
Una vez que el usuario indica la dirección, tenemos que realizar el movimiento del
jugador sobre el tablero. Para esto, implementa el siguiente subprograma:


✓ void hacerMovimiento(tJuego &juego, tTecla tecla) : realiza el movimiento
del jugador en la dirección indicada. Si no se puede realizar el movimiento, no
tiene efecto y no se incrementa tampoco el número de movimientos registrados.
Ya tienes todo lo que necesitas para implementar en main() la dinámica del juego.
*/



/*

Nota, esta versión ya incluye los apartados de eficiencia incluidos en el apartado 3 de la práctica, con lo que podemos dar por 
concluido esa modificación

Fallos: 

Queda por revisar el caso en el que queremos desplazar, con la excavadora, elementos a la posicion 0 de array, en principio
no se puede desplazar completamente elementos a la izquierda, pero si a la derecha.
*/

#include <locale.h>
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
using namespace std;


const int MAX = 50;

//El tipo enumerado tCasilla nos permite representar las casillas del tablero:
//donde DestinoL, DestinoC y DestinoJ representan posiciones destino que están libres, con caja o con jugador respectivamente.
enum tCasilla{
	Libre = 0,
	Muro = 1,
	DestinoL = 2,
	DestinoC = 3,
	DestinoJ = 4,
	Jugador = 5,
	Caja = 6
};

//El programa usa también un tipo enumerado tTecla con los siguientes valores: Arriba , Abajo , Derecha , Izquierda , Salir y Nada.
enum tTecla{
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

struct tSokoban{
	tTablero tablero; 
	int nfilas;
	int ncolumnas;
	int po_fila_Jugador;
	int pos_columna_Jugador;
	int ncajas;
	int ncajas_destino;
};

struct tJuego{
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

int main(){

	tJuego game;

	inicializa(game);
	if(!cargarJuego(game))
		cout << "Error al cargar el juego" << endl;

 	return 0;
}

//Inicializa el tablero , haciendo que todas las MAX x MAX casillas estén libres y el número de movimientos a 0.
void inicializa(tJuego &juego){

	for(int i = 0; i < MAX; i++)
		for(int j = 0; j < MAX; j++)
			juego.sokoban.tablero[i][j] = Libre;

	juego.num_movimientos = 0;

}

//Solicita al usuario el fichero y el nivel que desea jugar y lo carga desde dicho fichero.
bool cargarJuego(tJuego & juego){

	string nombre_fichero;
	ifstream fich_in;
	int nivel;
	bool retorno = false;

	cout << "Introduce el nombre del fichero a cargar" << endl;
	cin >> nombre_fichero;
	fich_in.open(nombre_fichero.c_str() , ios::in);
	
	if(fich_in.is_open()){
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
bool cargarNivel(ifstream &fichero, tSokoban &sokoban, int nivel){

	string linea_fichero;
	ifstream fich_in;
	int i = 0, n_filas = 0, n_colms = 0;
	bool retorno = true, end_of_file = false;
	
	// Encontramos si el nivel que queremos cargar está en esa línea
	do{
		if(getline(fichero, linea_fichero).eof()){ //No hemos llegado al final del fichero
			end_of_file = true;
			retorno = false;
		}
	}
	while(!esNivelCorrecto(linea_fichero, nivel) && !end_of_file); 

	if(retorno){ // Ha encontrado la linea correcta, podemos continuar, de lo contrario devolvemos un false
		
		do{
			
			getline(fichero, linea_fichero);
			
			//Únicamente necesitamos averiguar el tamanio de las filas una vez
			if(n_filas == 0)
				n_filas = linea_fichero.length();

	  		iniciaCasilla(sokoban, linea_fichero, linea_fichero.length(), n_colms);
	  		n_colms++;
		}
		while(linea_fichero.compare("") != 0);


		//Inicializacion de parámetros del tablero

		sokoban.nfilas = n_filas;
		sokoban.ncolumnas = n_colms;

		mostarFigurasTablero(sokoban.tablero, sokoban.nfilas, sokoban.ncolumnas);
	}

	return retorno;
}


void iniciaCasilla(tSokoban &sokoban, string linea, int tamlinea, int columna){

	//string caracter;

	for(int i = 0; i < tamlinea; i++){
				
		if ((linea.compare(i,1,"#") == 0))
			sokoban.tablero[columna][i] = Muro;
		else if ((linea.compare(i,1,"$") == 0))
			sokoban.tablero[columna][i] = Caja;
		else if ((linea.compare(i,1,".") == 0))
			sokoban.tablero[columna][i] = DestinoL;
		else if ((linea.compare(i,1,"@") == 0))
			sokoban.tablero[columna][i] = Jugador;
	}

}

void mostarValoresTablero(const tTablero tablero, int nfilas, int ncolumnas){
		
		for(int i = 0; i < ncolumnas; i++){
			for(int j = 0; j < nfilas; j++)
				cout << tablero[i][j];
			cout << endl;
		}	
}

void mostarFigurasTablero(const tTablero tablero, int nfilas, int ncolumnas){
		
		for(int i = 0; i < ncolumnas; i++){
			for(int j = 0; j < nfilas; j++)
				if(tablero[i][j] == 0)			// Libre
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

bool esNivelCorrecto(string cadena, int nivel){

	bool ret = false;
	string busca = static_cast<ostringstream*>( &(ostringstream() << nivel) )->str();

	if(cadena.find(busca) != -1)
		ret = true;

	return ret;
}


//mostarFigurasTablero(sokoban.tablero, sokoban.nfilas, sokoban.ncolumnas);
