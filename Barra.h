#ifndef BARRA_H
#define BARRA_H

#include <iostream>
#include "Tablero.h"

using namespace std;

const int LONGITUD = 5; // Valor Impar
const int VELOCIDAD_BARRA_USER = 2; 
const int VELOCIDAD_BARRA_CPU = 2;

const char ARRIBA = 'w'; //72; Va mas rapido con ws que con las felchas
const char ABAJO = 's'; //80;

void moverBarra (int direccion, int &pos);

#endif