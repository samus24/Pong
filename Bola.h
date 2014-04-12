#ifndef BOLA_H
#define BOLA_H

#include <iostream>
#include "Tablero.h"

using namespace std;

const int VELOCIDAD_BOLA = 1;

typedef struct {
	int x;
	int y;
	int sentido;
	int inclinacion;
} tBola;

void moverBola (tBola &bola, tBola &bolaNueva);

bool invertirInclinacion (tBola &bola);

void invertirSentido (int &sentido);

int modificarInclinacion (int valor);

#endif