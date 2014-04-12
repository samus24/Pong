#ifndef LOGIN_H
#define LOGIN_H

#include <iostream>
#include "ListaJugadores.h"

using namespace std;

const int INTENTOS = 3;	// Máximo de intentos para la contraseña

bool login (const tListaJugadores &lista, unsigned int &indice);

bool checkName(const tListaJugadores &lista, unsigned int &indice);

bool checkPass(const tListaJugadores &lista, unsigned int i);

#endif