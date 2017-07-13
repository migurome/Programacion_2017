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
Práctica 3
Página 1Fundamentos de la programación 2016/2017
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
Práctica 3
Página 2Fundamentos de la programación 2016/2017
Define el tipo estructurado tSokoban para describir el estado del tablero, conteniendo:
✓ El tablero de tipo tTablero .
✓ El número de filas nfilas y de columnas ncolumnas del array bidimensional que
está ocupando el tablero (ambas <= MAX ).
✓ La fila y la columna donde se encuentra colocado el jugador.
✓ El número de cajas del tablero.
✓ El número de cajas ya colocadas en casilla destino.
Define también el tipo estructurado tJuego que describe el estado del juego:
✓
✓
✓
✓
El estado del tablero sokoban de tipo tSokoban .
El número de movimientos realizados hasta el momento numMovimientos .
El nombre del fichero nFichero del que se ha cargado el juego.
El nivel que estamos jugando.
El programa usa también un tipo enumerado tTecla con los siguientes valores:
Arriba , Abajo , Derecha , Izquierda , Salir y Nada .
2. Visualización del tablero
Cada vez que vayas a visualizar el estado del tablero borra primero el contenido de la
ventana de consola, de forma que siempre se muestre el tablero en la misma posición y
la sensación sea más visual. Para borrar la consola utiliza:
system("cls");
Por defecto, el color de primer plano, aquel con el que se muestran los trazos de los
caracteres, es blanco, mientras que el color de fondo es negro. Podemos cambiar esos
colores, por supuesto, aunque debemos hacerlo utilizando rutinas que son específicas
de Visual Studio, por lo que debemos ser conscientes de que el programa no será
portable a otros compiladores.
Disponemos de 16 colores diferentes entre los que elegir, con valores de 0 a 15, tanto
para el primer plano como para el fondo. El 0 es el negro y el 15 es el blanco. Los
demás son azul, verde, cian, rojo, magenta, amarillo y gris, en dos versiones, oscuro y
claro.
Visual Studio incluye una biblioteca, Windows.h , que tiene, entre otras, rutinas para la
consola. Una de ellas es SetConsoleTextAttribute() , que permite ajustar los colores
de fondo y primer plano. Incluye en el programa esa biblioteca y esta rutina:
void colorFondo(int color) {
HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
SetConsoleTextAttribute(handle, 15 | (color << 4));
}
Práctica 3
Página 3Fundamentos de la programación 2016/2017
Basta proporcionar un color para el fondo (1 a 14) y esa rutina lo establecerá, con el
color de primer plano en blanco (15). Debes cambiar el color de fondo cada vez que
tengas que dibujar una casilla y volverlo a poner a negro (0) a continuación.
Al menos debes implementar estos subprogramas:
✓ void dibujaCasilla(tCasilla casilla) : muestra una casilla del tablero.
✓ void dibujar(const tJuego &juego) : muestra el tablero del juego, el nombre
del fichero desde que se ha cargado, su nivel y el número de movimientos
realizados.
2. Carga de un nivel del juego
Los tableros de juego de los distintos niveles se leerán de un archivo de texto que
puede guardar tantos niveles diferentes como queramos.
Por ejemplo, si el tablero del ejemplo anterior corresponde al nivel 0, en el archivo
tendremos:
Level 0
###################
#####
###########
#####$ ###########
##### $###########
### $ $ ##########
### # ## ##########
#
# ## ##### ..#
# $ $
..#
##### ### #@## ..#
#####
#########
###################
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
✓ void inicializa(tJuego &juego) : inicializa el tablero , haciendo que todas las
MAX x MAX casillas estén libres y el número de movimientos a 0.
Práctica 3
Página 4Fundamentos de la programación 2016/2017
✓ bool cargarJuego(tJuego & juego) : solicita al usuario el fichero y el nivel
que desea jugar y lo carga desde dicho fichero .
✓ bool cargarNivel(ifstream &fichero, tSokoban &sokoban, int nivel) :
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
Práctica 3
Página 5Fundamentos de la programación 2016/2017
✓ void hacerMovimiento(tJuego &juego, tTecla tecla) : realiza el movimiento
del jugador en la dirección indicada. Si no se puede realizar el movimiento, no
tiene efecto y no se incrementa tampoco el número de movimientos registrados.
Ya tienes todo lo que necesitas para implementar en main() la dinámica del juego.
*/
