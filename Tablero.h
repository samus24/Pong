#ifndef TABLERO_H
#define TABLERO_H

#include <iostream>
#include <Windows.h>

using namespace std;

const int ALTO = 30;
const int LARGO = 60;
const int IALTO = 50;
const int ILARGO = 80;

const int HUECO_ARRIBA = 9;
const int HUECO_LADO = 3;

const char BARRA_CHAR = 219;
const char BOLA_CHAR = 254;
const char RED_CHAR = 177;
const char ARR_CHAR = 220;
const char ABJ_CHAR = 223;
const char IZQ_CHAR = 219;
const char DER_CHAR = 219;

typedef enum tCasilla {ESPACIO, BOLA, BARRA};

typedef tCasilla tTablero [LARGO][ALTO];

void mostrarTablero (tTablero tab);

#endif