#ifndef LISTA_JUGADORES
#define LISTA_JUGADORES

#include <iostream>
#include <string>
#include <string.h>

using namespace std;

const int MAXJUGADORES = 20;

typedef struct{
	string nombre;
	string pass;
	string siglas;
	int vic;
	int derr;
	int maxPunt;
	int puntosTot;
	int max_rango;
	int min_rango;
} tJugador;

typedef tJugador tArrayJug [MAXJUGADORES];

typedef struct{
	tArrayJug jug;
	int cont;	
} tListaJugadores;

bool insertaJugador (tListaJugadores &lista, tJugador jug);

void eliminaJugador (tListaJugadores &lista, unsigned int pos);

bool buscaJugador (tListaJugadores lista, string nombre, unsigned int &pos);

void altaJugador (tJugador &jug);

void ordenaLista (tListaJugadores &jug);

#endif