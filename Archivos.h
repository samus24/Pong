#ifndef ARCHIVOS_H
#define ARCHIVOS_H

#include <iostream>
#include <string>
#include <fstream>
#include "ListaJugadores.h"

using namespace std;

const string CENTINELA = "XXX";
const string AYUDA = "help.txt";
const string JUGADORES = "jugadores.txt";

bool mostrar_archivo (string direccion);

bool guardar_archivo (string direccion, tListaJugadores jug);

bool cargar_archivo (string direccion, tListaJugadores &jug);

#endif

