/*DO WHAT THE FUCK YOU WANT TO PUBLIC LICENSE
Version 2, December 2004

Copyright(C) 2004 Sam Hocevar <sam@hocevar.net>

Everyone is permitted to copy and distribute verbatim or modified
copies of this license document, and changing it is allowed as long
as the name is changed.

DO WHAT THE FUCK YOU WANT TO PUBLIC LICENSE
TERMS AND CONDITIONS FOR COPYING, DISTRIBUTION AND MODIFICATION

0. You just DO WHAT THE FUCK YOU WANT TO.
Authors: Samuel Lapuente Jiménez and Álvaro Lázaro Sevilla
*/






#include <iostream>
#include <conio.h>
#include <time.h>
#include "Barra.h"
#include "Bola.h",ar
#include "Tablero.h"
#include "Archivos.h"
#include "ListaJugadores.h"
#include "login.h"

using namespace std;

// CONSTANTES

const int MAXPUNTOS = 5;	 
/* Maximo de puntos jugables en una partida, se usa este valor por defecto en todos los nuevos jugadores */

const int RATIO = 3;		 
/* Indica cada cuantos rebotes se acelera la velocidad de la bola */

const int CENTRO = ALTO/2 - LONGITUD/2;
/* Indica la posicion de las barras de jugador y cpu al comienzo, dado que las posiciones */

const int ERROR_VUELTA = 1;		
/* Error con el que la cpu se vuelve a recolocar tras darle a la bola */

const int FLUIDEZ = 85;			
/* Velocidad global de refresco del juego (es decir, el retardo del Sleep()) */

const char VACIO = ' ';
/* Representacion de un caracter vacio por pantalla */

const char LLENO = 219;
/* REpresentacion de un caracter todo lleno por pantalla */

// FUNCIONES
void iniciaJuego (tTablero &tab, tBola &bola);
/*
Recibe: un tablero vacio.
Devuelve: un tablero inicializado, con las palas y la bola
Coloca el tablero inicial y prepara la ejecución del juego
*/
bool checkBarra (tTablero tab); 
/*
Recibe: un tablero
Devuelve:
 - True si la bola ha golpeado sobre una de las barras
 - False si la bola no ha golpeado en una de las barras
Comprueba si la bola ha golpeado alguna de las barras
*/

int calcularInclinacion(tTablero tab, int inclinacion); 
/*
Recibe: un tablero y la inclinacion actual
Devuelve: La nueva inclinacion calculada
Calcula la inclinación a la que se debe devolver la bola en función del choque con la barra y la inclinación anterior
*/
void actualizaTablero (tTablero &tab, int posJug, int posCpu, tBola &bola, tBola bolaNueva); 
/*
Recibe: tablero, posicion de la pala del jugador, de la cpu, de la bola y la proxima posicion de la bola.
Devuelve: El tablero modificado en funcion de las posiciones y la bola movida a su siguiente posicion
Establece el tablero nuevo, después de mover los elementos necesarios
*/

bool checkWin(tTablero tab, tBola bola); 
/*
Recibe: un tablero y una bola
Devuelve:
 - True si la bola esta en alguno de los dos extremos
 - False en otro caso
Comprueba si uno de los dos jugadores ha anotado un punto
*/

void moverCpu (tBola bola, int &posCpu, int res); 
/*
Recibe: La bola, la posicion actual de la cpu, el sentido y la inclinacion de la bola y un margen de respuesta generado aleatoriamente
Devuelve: la pala de la cpu colocada en otra posicion (potencialmente mejor)
Algoritmo que mueve la barra de la cpu
*/

bool jugar (tJugador &player); 
/*
Recibe: Un perfil de jugador
Devuelve: 
 - True si ha ganado el jugador
 - False si ha ganado la cpu
Función que se encarga de todo lo referente al desarrollo del juego
*/

int menu (); //Muestra el menu

void bienvenido(); //Muestra el título del juego

void mostrarMarcador(int puntosTot, int puntosJug, int puntosCpu, int color1, int color2); 
/*
Recibe: Los puntos a los que se esta jugando, los puntos que lleva el jugador y los de la cpu, y el color en el que se quiere mostrar cada numero
Devuelve: Nada, muestra el marcador en pantalla
Muestra por pantalla la puntuación así como el número de bolas jugadas y por jugar
Nota:
 - colorX == 0 -> Numero en Blanco
 - colorX == 1 -> Numero en Verde
 - colorX == 2 -> Numero en Rojo
*/

void main (){
	srand(time(NULL));
	bool salir = false;
	bool logeado = false;
	unsigned int pos;				// Posicion en la que se encuentra el jugador en la lista de usuarios
	tJugador player, defaultPlayer;	// Se manejan 2 perfiles, el del jugador y uno por defecto (por si no se quiere loguear o cierra sesion)
	tListaJugadores lista;

	if(!cargar_archivo(JUGADORES,lista)) lista.cont = 0;	// Si no se ha cargado ninguna lista, se crea una nueva

	bienvenido();
	system("cls");
	
	defaultPlayer.nombre = "default";				// Se inicializa el perfil default (este no se modificará nunca)
	defaultPlayer.vic = defaultPlayer.derr = 0;
	defaultPlayer.max_rango = 8;
	defaultPlayer.min_rango = 3;
	defaultPlayer.maxPunt = 0;
	defaultPlayer.siglas = "DEF";
	defaultPlayer.puntosTot = MAXPUNTOS;

	logeado = login(lista,pos);			// Se pide el login
	if (logeado){						// Si se ha logueado, se hace una copia del perfil de la lista
		player = lista.jug[pos];
	}
	else{								// Si no, se trabaja con una copia del default
		cout << "No has iniciado sesion" << endl;
		player = defaultPlayer;
	}

	do{
		switch (menu()){

		case 0: salir = true;
				break;

		case 1:	if(jugar(player)) player.vic++;
				else player.derr++;
				if (logeado){					// Al acabar, si se habia logueado, se actualiza el jugador en la lista (se borra y se mete al final)
					eliminaJugador(lista,pos);
					insertaJugador(lista,player);
					pos = lista.cont - 1;
				}
				system("cls");

				break;

		case 2: system("cls");
				cout << "###############################" << endl;
				cout << "# Tus estadisticas personales #" << endl;
				cout << "###############################" << endl;
				cout << "Nombre: " << player.nombre << "\tSiglas: " << player.siglas << endl;
				cout << "Victorias: " << player.vic;	cout << "\tDerrotas: " << player.derr << endl;
				cout << "Puntuacion maxima conseguida: " << player.maxPunt << endl;
				cout << "CONFIGURACION PREFERIDA: " << endl;
				cout << "Numero de bolas por partida: " << player.puntosTot << endl;
				cout << "Dificultad por defecto: ";
				if (player.max_rango == 12)		cout << "Dificil" << endl;
				else if (player.max_rango == 8) cout << "Media" << endl;
				else							cout << "Facil" << endl;
				cout << endl;
				system("Pause");
				system("cls");

				break;

		case 3: cout << "Seleccione dificultad:" << endl;
				int opcion;

				do{
					cout << "1 - Facil" << endl;
					cout << "2 - Medio" << endl;
					cout << "3 - Dificil" << endl;
					cin >> opcion;
				}while ((opcion < 1) || (opcion > 3));

				if (opcion == 1)		{ player.max_rango = 4; player.min_rango = 2;}
				else if (opcion == 2)	{ player.max_rango = 8; player.min_rango = 3;}
				else					{ player.max_rango = 12; player.min_rango = 4;}

				system("cls");
				break;

		case 4: mostrar_archivo(AYUDA);
				cout << endl;
				system("Pause");
				system("cls");
				break;

		case 5: altaJugador(player);
				if (insertaJugador(lista, player)){
					logeado = true;
					cout << "Registro completado" << endl;
				}
				else {
					cout << "Registro fallido" << endl;
					player = defaultPlayer;
				}
				cout << endl;
				Sleep(1500);
				system("cls");
				break;

		case 6: if (logeado){
					eliminaJugador(lista,pos);
					cout << "Te hemos borrado de nuestra lista de jugadores, te echaremos de menos" << endl;
				}
				player = defaultPlayer;
				logeado = false;
				cout << endl;
				Sleep(1500);
				system("cls");
				break;

		case 7: logeado = login(lista,pos);
				if (logeado) player = lista.jug[pos];
				else player = defaultPlayer;
					
				system("cls");
				break;

		case 8: int num;

				do{
					cout << "Elija a cuantos puntos desea jugar (3 ó 5): ";
					cin >> num;
				} while ((num != 3) && (num != 5));

				player.puntosTot = num;
				
				system("cls");
				break;

		case 9: ordenaLista(lista);
				buscaJugador(lista,player.nombre,pos);

				cout << "### Ranking ATPong ###" << endl;
				for (int i=0; i < lista.cont; i++){
					cout << i+1 << " - " << lista.jug[i].siglas << " -- " << lista.jug[i].maxPunt << endl;
				}

				cout << endl;
				system("Pause");
				system("cls");
				break;
		}
	} while (!salir);

	if (logeado){
		eliminaJugador(lista,pos);
		insertaJugador(lista,player);
		pos = lista.cont - 1;
	}
	if (!guardar_archivo(JUGADORES,lista))
		cout << "No se guardo la lista de jugadores" << endl;

	system("pause");
}
void bienvenido (){
	cout << endl << endl << endl;
	cout << "     ########     ########   ##      ##   ######## " << endl; 
	cout << "     ##     ##   ##      ##  ###     ##  ##      ##" << endl;
	cout << "     ##      ##  ##      ##  ## #    ##  ##      ##" << endl;
	cout << "     ##     ##   ##      ##  ##  #   ##  ##        " << endl;
	cout << "     #######     ##      ##  ##   #  ##  ##    ####" << endl;
	cout << "     ##          ##      ##  ##    # ##  ##      ##" << endl;
	cout << "     ##          ##      ##  ##     ###  ##      ##" << endl;
	cout << "     ##           ########   ##      ##   ######## " << endl;
	cout << endl;

 int tiempo = time(NULL) + 3;
 while (time(NULL) != tiempo);
}

int menu (){
	int opcion;

	do {
		cout << "##################" << endl;
		cout << "# MENU PRINCIPAL #" << endl;
		cout << "##################" << endl;
		cout << "1 - Jugar" << endl;
		cout << "2 - Ver estadisticas" << endl;
		cout << "3 - Cambiar dificultad" << endl;
		cout << "4 - Ayuda" << endl;
		cout << "5 - Unirse al juego" << endl;
		cout << "6 - Me quiero borrar" << endl;
		cout << "7 - Iniciar mi sesion" << endl;
		cout << "8 - Cofiguracion del juego" << endl;
		cout << "9 - Ver el ranking ATPong" << endl;
		cout << "0 - Salir" << endl;
		cin.sync();
		cin >> opcion;
	} while ((opcion < 0) || (opcion > 9));

	return opcion;
}

bool jugar (tJugador &player){
	tTablero tab;
	bool fin = false;
	char c = '1';
	int tiempoEnPausa = 0;
	int puntosJug = 0, puntosCpu = 0;
	int posJug = (ALTO/2 - LONGITUD/2);
	int posCpu = posJug;
	int cuentaRebotes = 0;
	int res = int(floor(rand() / (RAND_MAX + 1.0) * (player.max_rango-(player.min_rango)) + (player.min_rango)));
	tBola bola, nuevaBola;
	nuevaBola.x = 0;
	nuevaBola.y = 0;
	do{
		posJug = (ALTO/2 - LONGITUD/2);
		posCpu = posJug;
		nuevaBola.x = 0;
		nuevaBola.y = 0;
		cuentaRebotes = 0;

		iniciaJuego(tab,bola);
		system("cls");
		mostrarMarcador(player.puntosTot, puntosJug, puntosCpu,0,0);

		HANDLE hOut;
		CONSOLE_CURSOR_INFO ConCurInf;
		hOut = GetStdHandle(STD_OUTPUT_HANDLE);
		ConCurInf.dwSize = 10;
		ConCurInf.bVisible = FALSE;
		SetConsoleCursorInfo(hOut, &ConCurInf);

		int comienzo = time(NULL);

		do{
			c = '1';
			if(kbhit()){
				c = getch();
			}
			moverBarra(c,posJug);
			moverCpu(bola,posCpu,res);
			moverBola(bola, nuevaBola);
			actualizaTablero(tab, posJug, posCpu, bola, nuevaBola);

			if (checkBarra(tab)){
				invertirSentido(bola.sentido);
				if(bola.sentido > 0) res = int(floor(rand() / (RAND_MAX + 1.0) * (player.max_rango-(player.min_rango)) + (player.min_rango)));
				bola.inclinacion = calcularInclinacion(tab, bola.inclinacion);
				cuentaRebotes++;
				if (cuentaRebotes % RATIO == 0 && cuentaRebotes >= RATIO){
					if (bola.sentido < 0) bola.sentido -= 1;	// Se aumenta la velocidad de la bola cada RATIO rebotes
					else			 bola.sentido +=1;
				}
			}
			else fin = checkWin(tab,bola);

			mostrarTablero(tab);
			Sleep(FLUIDEZ);
			if (c == 'p'){
				int t1 = time(NULL);
				c = '1';
				do{
					if(kbhit())
						c = getch();
				}while(c != 'p');
				int t2 = time(NULL);
				tiempoEnPausa += t2-t1;
			}
		} while (!fin && c != 'q');
		if (c != 'q'){
			int final = time(NULL);

			int tiempo = final - comienzo - tiempoEnPausa;
			tiempoEnPausa = 0;
			int puntuacion = tiempo * tiempo /10;

			if (player.max_rango == 12)		puntuacion *= 2;
			else if (player.max_rango == 8)	puntuacion *= 1;
			else							puntuacion /= 2;

			if (bola.x != 0) puntuacion += 500;

			if (puntuacion > player.maxPunt) player.maxPunt = puntuacion;

			if (bola.x == 0){
				puntosCpu++;	// Pierdes
				mostrarMarcador(player.puntosTot,puntosJug,puntosCpu,0,1);
			}
			else{
				puntosJug++;	// Ganas
				mostrarMarcador(player.puntosTot,puntosJug,puntosCpu,1,0);
			}
		}
	} while ((puntosCpu + puntosJug < player.puntosTot) && c != 'q'); 

	if (puntosJug > puntosCpu)	mostrarMarcador(player.puntosTot,puntosJug,puntosCpu,1,2);
	else						mostrarMarcador(player.puntosTot,puntosJug,puntosCpu,2,1);
	Sleep(1000);

	if ((puntosJug > puntosCpu) && c != 'q')	return true;
	else										return false;
}

void iniciaJuego (tTablero &tab, tBola &bola){
	int a = rand()%2;

	bola.x = LARGO/2;
	bola.y = ALTO/2;

	if (a == 0) bola.sentido = -VELOCIDAD_BOLA;
	else bola.sentido = VELOCIDAD_BOLA;

	bola.inclinacion = 0;
	for (int i=0; i < ALTO; i++){
		for (int j=0; j < LARGO; j++){
			tab[j][i] = ESPACIO;
		}
	}

	a = (ALTO/2 - LONGITUD/2);
	for (int i=0; i < LONGITUD; i++){
		tab[0][a+i] = BARRA;
		tab[LARGO-1][a+i] = BARRA;
	}

	tab[LARGO/2][ALTO/2] = BOLA;
}

void actualizaTablero (tTablero &tab, int posJug, int posCpu, tBola &bola, tBola nuevaBola){
	tab[bola.x][bola.y] = ESPACIO;

	for (int i=0; i < ALTO; i++){
		tab[0][i] = ESPACIO;
		tab[LARGO-1][i] = ESPACIO;
	}

	for (int i=0; i < LONGITUD; i++){
		tab[0][posJug+i] = BARRA;
		tab[LARGO-1][posCpu+i] = BARRA;
	}

	bola.x = nuevaBola.x;
	bola.y = nuevaBola.y;
	tab[nuevaBola.x][nuevaBola.y] = BOLA;
}

bool checkBarra (tTablero tab){
	int cont = 0;

	for (int i = 0; i < ALTO; i++){
		if (tab[0][i] == BARRA)
			cont++;
		if (tab[LARGO-1][i] == BARRA)
			cont++;
	}

	if (cont < LONGITUD*2)
		return true;

	else
		return false;
}

int calcularInclinacion(tTablero tab, int inclinacion){
	bool fin = false;
	int cont = 0;
	int i=0;

	do{
		if(tab[0][i] == BARRA)
			cont++;
		else if (tab[0][i] == BOLA)
			fin = true;
		i++;
	} while (!fin && i < ALTO);

	if (!fin){
		cont = 0;
		i = 0;

		do{
		if(tab[LARGO-1][i] == BARRA)
			cont++;
		else if (tab[LARGO-1][i] == BOLA)
			fin = true;
		i++;
		} while (!fin && i < ALTO);

	}
	if (cont == LONGITUD / 2) return inclinacion;	  // Si la bola da en mitad de la barra, se devuelve con rebote natural 	
	else if (cont == 0) return -2;			         // Si da arriba del todo, se devuelve muy hacia arriba							
	else if (cont == LONGITUD) return 2;	    	// Si da abajo del todo, se devuelve muy hacia abajo							
	else if (cont < LONGITUD / 2) return -1;	   // Si da en la mitad superior, se devuelve hacia arriba
	else return 1;	 					          // Si da en la mitad inferior, se devuelve hacia abajo
}

bool checkWin(tTablero tab, tBola bola){
	if ((bola.x == 0) || (bola.x == LARGO-1))
		return true;

	else
		return false;

}

void moverCpu (tBola bola, int &posCpu, int res){
	if (bola.sentido < 0){
		if(posCpu < CENTRO + ERROR_VUELTA || posCpu < CENTRO - ERROR_VUELTA){
			posCpu += VELOCIDAD_BARRA_CPU;
		}
		if(posCpu > CENTRO + ERROR_VUELTA || posCpu > CENTRO - ERROR_VUELTA){
			posCpu -= VELOCIDAD_BARRA_CPU;
		}
	}

	if (bola.sentido > 0){
		int centroBarra = posCpu + LONGITUD/2;
		int respuesta_cpu = res;

		if (bola.x > LARGO/respuesta_cpu){
			if (bola.inclinacion == 0){
				posCpu = bola.y - LONGITUD+1; 
			}
			else{
				if(bola.y < centroBarra && bola.inclinacion < 0){
					posCpu -= VELOCIDAD_BARRA_CPU;
				}
				if(bola.y > centroBarra && bola.inclinacion > 0){
					posCpu += VELOCIDAD_BARRA_CPU;
				}
			}
		}
		if (posCpu < 0) posCpu = 0;
		if (posCpu > (ALTO-LONGITUD)) posCpu = ALTO-LONGITUD;
	}
}

void mostrarMarcador(int puntosTot, int puntosJug, int puntosCpu, int color1, int color2){
	HANDLE nuestroBuffer = (HANDLE)GetStdHandle(STD_OUTPUT_HANDLE);
	COORD dwBufferSize = { ILARGO, IALTO };
	COORD dwBufferCoord = { 0, 0 };
	SMALL_RECT rcRegion = { 0, 0, ILARGO-1, IALTO-1 };
	CHAR_INFO pant [IALTO][ILARGO];
	ReadConsoleOutput( nuestroBuffer, (CHAR_INFO *)pant, dwBufferSize,dwBufferCoord, &rcRegion );

	int x = 1, y = LARGO/2 - 1;

	if (color1 == 2){
		for(int i=0; i < 5; i++)
			for(int j=0; j < 3; j++)
				pant[x+i][y+j].Attributes = FOREGROUND_RED | FOREGROUND_INTENSITY;
	}
	else if (color1 == 1){
		for(int i=0; i < 5; i++)
			for(int j=0; j < 3; j++)
				pant[x+i][y+j].Attributes = FOREGROUND_GREEN | FOREGROUND_INTENSITY;
	}
	else{
		for(int i=0; i < 5; i++)
			for(int j=0; j < 3; j++)
				pant[x+i][y+j].Attributes = FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_BLUE;
	}
	
	switch(puntosJug){
	case 0:
		pant[x][y].Char.AsciiChar = LLENO;			pant[x][y+1].Char.AsciiChar = LLENO;	pant[x][y+2].Char.AsciiChar = LLENO;
		pant[x+1][y].Char.AsciiChar = LLENO;		pant[x+1][y+1].Char.AsciiChar = VACIO;	pant[x+1][y+2].Char.AsciiChar = LLENO;
		pant[x+2][y].Char.AsciiChar = LLENO;		pant[x+2][y+1].Char.AsciiChar = VACIO;	pant[x+2][y+2].Char.AsciiChar = LLENO;
		pant[x+3][y].Char.AsciiChar = LLENO;		pant[x+3][y+1].Char.AsciiChar = VACIO;	pant[x+3][y+2].Char.AsciiChar = LLENO;
		pant[x+4][y].Char.AsciiChar = LLENO;		pant[x+4][y+1].Char.AsciiChar = LLENO;	pant[x+4][y+2].Char.AsciiChar = LLENO;
		break;

	case 1: 
		pant[x][y].Char.AsciiChar = VACIO;			pant[x][y+1].Char.AsciiChar = VACIO;	pant[x][y+2].Char.AsciiChar = LLENO;
		pant[x+1][y].Char.AsciiChar = VACIO;		pant[x+1][y+1].Char.AsciiChar = VACIO;	pant[x+1][y+2].Char.AsciiChar = LLENO;
		pant[x+2][y].Char.AsciiChar = VACIO;		pant[x+2][y+1].Char.AsciiChar = VACIO;	pant[x+2][y+2].Char.AsciiChar = LLENO;
		pant[x+3][y].Char.AsciiChar = VACIO;		pant[x+3][y+1].Char.AsciiChar = VACIO;	pant[x+3][y+2].Char.AsciiChar = LLENO;
		pant[x+4][y].Char.AsciiChar = VACIO;		pant[x+4][y+1].Char.AsciiChar = VACIO;	pant[x+4][y+2].Char.AsciiChar = LLENO;
		break;

	case 2:
		pant[x][y].Char.AsciiChar = LLENO;			pant[x][y+1].Char.AsciiChar = LLENO;	pant[x][y+2].Char.AsciiChar = LLENO;
		pant[x+1][y].Char.AsciiChar = VACIO;		pant[x+1][y+1].Char.AsciiChar = VACIO;	pant[x+1][y+2].Char.AsciiChar = LLENO;
		pant[x+2][y].Char.AsciiChar = LLENO;		pant[x+2][y+1].Char.AsciiChar = LLENO;	pant[x+2][y+2].Char.AsciiChar = LLENO;
		pant[x+3][y].Char.AsciiChar = LLENO;		pant[x+3][y+1].Char.AsciiChar = VACIO;	pant[x+3][y+2].Char.AsciiChar = VACIO;
		pant[x+4][y].Char.AsciiChar = LLENO;		pant[x+4][y+1].Char.AsciiChar = LLENO;	pant[x+4][y+2].Char.AsciiChar = LLENO;
		break;

	case 3:
		pant[x][y].Char.AsciiChar = LLENO;			pant[x][y+1].Char.AsciiChar = LLENO;	pant[x][y+2].Char.AsciiChar = LLENO;
		pant[x+1][y].Char.AsciiChar = VACIO;		pant[x+1][y+1].Char.AsciiChar = VACIO;	pant[x+1][y+2].Char.AsciiChar = LLENO;
		pant[x+2][y].Char.AsciiChar = LLENO;		pant[x+2][y+1].Char.AsciiChar = LLENO;	pant[x+2][y+2].Char.AsciiChar = LLENO;
		pant[x+3][y].Char.AsciiChar = VACIO;		pant[x+3][y+1].Char.AsciiChar = VACIO;	pant[x+3][y+2].Char.AsciiChar = LLENO;
		pant[x+4][y].Char.AsciiChar = LLENO;		pant[x+4][y+1].Char.AsciiChar = LLENO;	pant[x+4][y+2].Char.AsciiChar = LLENO;
		break;

	case 4:
		pant[x][y].Char.AsciiChar = LLENO;			pant[x][y+1].Char.AsciiChar = VACIO;	pant[x][y+2].Char.AsciiChar = LLENO;
		pant[x+1][y].Char.AsciiChar = LLENO;		pant[x+1][y+1].Char.AsciiChar = VACIO;	pant[x+1][y+2].Char.AsciiChar = LLENO;
		pant[x+2][y].Char.AsciiChar = LLENO;		pant[x+2][y+1].Char.AsciiChar = LLENO;	pant[x+2][y+2].Char.AsciiChar = LLENO;
		pant[x+3][y].Char.AsciiChar = VACIO;		pant[x+3][y+1].Char.AsciiChar = VACIO;	pant[x+3][y+2].Char.AsciiChar = LLENO;
		pant[x+4][y].Char.AsciiChar = VACIO;		pant[x+4][y+1].Char.AsciiChar = VACIO;	pant[x+4][y+2].Char.AsciiChar = LLENO;
		break;

	case 5:
		pant[x][y].Char.AsciiChar = LLENO;			pant[x][y+1].Char.AsciiChar = LLENO;	pant[x][y+2].Char.AsciiChar = LLENO;
		pant[x+1][y].Char.AsciiChar = LLENO;		pant[x+1][y+1].Char.AsciiChar = VACIO;	pant[x+1][y+2].Char.AsciiChar = VACIO;
		pant[x+2][y].Char.AsciiChar = LLENO;		pant[x+2][y+1].Char.AsciiChar = LLENO;	pant[x+2][y+2].Char.AsciiChar = LLENO;
		pant[x+3][y].Char.AsciiChar = VACIO;		pant[x+3][y+1].Char.AsciiChar = VACIO;	pant[x+3][y+2].Char.AsciiChar = LLENO;
		pant[x+4][y].Char.AsciiChar = LLENO;		pant[x+4][y+1].Char.AsciiChar = LLENO;	pant[x+4][y+2].Char.AsciiChar = LLENO;
		break;
	}

	pant[2][LARGO/2+HUECO_LADO].Char.AsciiChar = LLENO;
	pant[4][LARGO/2+HUECO_LADO].Char.AsciiChar = LLENO;
	x = 1; 
	y = LARGO/2 + HUECO_LADO + 2;

	if (color2 == 2){
		for(int i=0; i < 5; i++)
			for(int j=0; j < 3; j++)
				pant[x+i][y+j].Attributes = FOREGROUND_RED | FOREGROUND_INTENSITY;
	}
	else if (color2 == 1){
		for(int i=0; i < 5; i++)
			for(int j=0; j < 3; j++)
				pant[x+i][y+j].Attributes = FOREGROUND_GREEN | FOREGROUND_INTENSITY;
	}
	else{
		for(int i=0; i < 5; i++)
			for(int j=0; j < 3; j++)
				pant[x+i][y+j].Attributes = FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_BLUE;
	}

	switch(puntosCpu){
	case 0:
		pant[x][y].Char.AsciiChar = LLENO;			pant[x][y+1].Char.AsciiChar = LLENO;	pant[x][y+2].Char.AsciiChar = LLENO;
		pant[x+1][y].Char.AsciiChar = LLENO;		pant[x+1][y+1].Char.AsciiChar = VACIO;	pant[x+1][y+2].Char.AsciiChar = LLENO;
		pant[x+2][y].Char.AsciiChar = LLENO;		pant[x+2][y+1].Char.AsciiChar = VACIO;	pant[x+2][y+2].Char.AsciiChar = LLENO;
		pant[x+3][y].Char.AsciiChar = LLENO;		pant[x+3][y+1].Char.AsciiChar = VACIO;	pant[x+3][y+2].Char.AsciiChar = LLENO;
		pant[x+4][y].Char.AsciiChar = LLENO;		pant[x+4][y+1].Char.AsciiChar = LLENO;	pant[x+4][y+2].Char.AsciiChar = LLENO;
		break;

	case 1: 
		pant[x][y].Char.AsciiChar = VACIO;			pant[x][y+1].Char.AsciiChar = VACIO;	pant[x][y+2].Char.AsciiChar = LLENO;
		pant[x+1][y].Char.AsciiChar = VACIO;		pant[x+1][y+1].Char.AsciiChar = VACIO;	pant[x+1][y+2].Char.AsciiChar = LLENO;
		pant[x+2][y].Char.AsciiChar = VACIO;		pant[x+2][y+1].Char.AsciiChar = VACIO;	pant[x+2][y+2].Char.AsciiChar = LLENO;
		pant[x+3][y].Char.AsciiChar = VACIO;		pant[x+3][y+1].Char.AsciiChar = VACIO;	pant[x+3][y+2].Char.AsciiChar = LLENO;
		pant[x+4][y].Char.AsciiChar = VACIO;		pant[x+4][y+1].Char.AsciiChar = VACIO;	pant[x+4][y+2].Char.AsciiChar = LLENO;
		break;

	case 2:
		pant[x][y].Char.AsciiChar = LLENO;			pant[x][y+1].Char.AsciiChar = LLENO;	pant[x][y+2].Char.AsciiChar = LLENO;
		pant[x+1][y].Char.AsciiChar = VACIO;		pant[x+1][y+1].Char.AsciiChar = VACIO;	pant[x+1][y+2].Char.AsciiChar = LLENO;
		pant[x+2][y].Char.AsciiChar = LLENO;		pant[x+2][y+1].Char.AsciiChar = LLENO;	pant[x+2][y+2].Char.AsciiChar = LLENO;
		pant[x+3][y].Char.AsciiChar = LLENO;		pant[x+3][y+1].Char.AsciiChar = VACIO;	pant[x+3][y+2].Char.AsciiChar = VACIO;
		pant[x+4][y].Char.AsciiChar = LLENO;		pant[x+4][y+1].Char.AsciiChar = LLENO;	pant[x+4][y+2].Char.AsciiChar = LLENO;
		break;

	case 3:
		pant[x][y].Char.AsciiChar = LLENO;			pant[x][y+1].Char.AsciiChar = LLENO;	pant[x][y+2].Char.AsciiChar = LLENO;
		pant[x+1][y].Char.AsciiChar = VACIO;		pant[x+1][y+1].Char.AsciiChar = VACIO;	pant[x+1][y+2].Char.AsciiChar = LLENO;
		pant[x+2][y].Char.AsciiChar = LLENO;		pant[x+2][y+1].Char.AsciiChar = LLENO;	pant[x+2][y+2].Char.AsciiChar = LLENO;
		pant[x+3][y].Char.AsciiChar = VACIO;		pant[x+3][y+1].Char.AsciiChar = VACIO;	pant[x+3][y+2].Char.AsciiChar = LLENO;
		pant[x+4][y].Char.AsciiChar = LLENO;		pant[x+4][y+1].Char.AsciiChar = LLENO;	pant[x+4][y+2].Char.AsciiChar = LLENO;
		break;

	case 4:
		pant[x][y].Char.AsciiChar = LLENO;			pant[x][y+1].Char.AsciiChar = VACIO;	pant[x][y+2].Char.AsciiChar = LLENO;
		pant[x+1][y].Char.AsciiChar = LLENO;		pant[x+1][y+1].Char.AsciiChar = VACIO;	pant[x+1][y+2].Char.AsciiChar = LLENO;
		pant[x+2][y].Char.AsciiChar = LLENO;		pant[x+2][y+1].Char.AsciiChar = LLENO;	pant[x+2][y+2].Char.AsciiChar = LLENO;
		pant[x+3][y].Char.AsciiChar = VACIO;		pant[x+3][y+1].Char.AsciiChar = VACIO;	pant[x+3][y+2].Char.AsciiChar = LLENO;
		pant[x+4][y].Char.AsciiChar = VACIO;		pant[x+4][y+1].Char.AsciiChar = VACIO;	pant[x+4][y+2].Char.AsciiChar = LLENO;
		break;

	case 5:
		pant[x][y].Char.AsciiChar = LLENO;			pant[x][y+1].Char.AsciiChar = LLENO;	pant[x][y+2].Char.AsciiChar = LLENO;
		pant[x+1][y].Char.AsciiChar = LLENO;		pant[x+1][y+1].Char.AsciiChar = VACIO;	pant[x+1][y+2].Char.AsciiChar = VACIO;
		pant[x+2][y].Char.AsciiChar = LLENO;		pant[x+2][y+1].Char.AsciiChar = LLENO;	pant[x+2][y+2].Char.AsciiChar = LLENO;
		pant[x+3][y].Char.AsciiChar = VACIO;		pant[x+3][y+1].Char.AsciiChar = VACIO;	pant[x+3][y+2].Char.AsciiChar = LLENO;
		pant[x+4][y].Char.AsciiChar = LLENO;		pant[x+4][y+1].Char.AsciiChar = LLENO;	pant[x+4][y+2].Char.AsciiChar = LLENO;
		break;
	}

	if (puntosTot == 3){
		for (int i=0; i < puntosTot; i++){
			pant[7][LARGO/2+HUECO_LADO-1 + i].Char.AsciiChar = BOLA_CHAR;
			pant[7][LARGO/2+HUECO_LADO-1 + i].Attributes = FOREGROUND_GREEN | FOREGROUND_INTENSITY;
		}

		int bolasGastadas = puntosJug + puntosCpu;

		for (int i=0; i < bolasGastadas; i++){
			pant[7][LARGO/2+HUECO_LADO-1 + i].Char.AsciiChar = BOLA_CHAR;
			pant[7][LARGO/2+HUECO_LADO-1 + i].Attributes = FOREGROUND_RED | FOREGROUND_INTENSITY;
		}
	}

	else{
		for (int i=0; i < puntosTot; i++){
			pant[7][LARGO/2+HUECO_LADO-2 + i].Char.AsciiChar = BOLA_CHAR;
			pant[7][LARGO/2+HUECO_LADO-2 + i].Attributes = FOREGROUND_GREEN | FOREGROUND_INTENSITY;
		}

		int bolasGastadas = puntosJug + puntosCpu;

		for (int i=0; i < bolasGastadas; i++){
			pant[7][LARGO/2+HUECO_LADO-2 + i].Char.AsciiChar = BOLA_CHAR;
			pant[7][LARGO/2+HUECO_LADO-2 + i].Attributes = FOREGROUND_RED | FOREGROUND_INTENSITY;
		}
	}

	WriteConsoleOutput( nuestroBuffer, (CHAR_INFO *)pant, dwBufferSize,dwBufferCoord, &rcRegion );
}

