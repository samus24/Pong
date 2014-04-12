#include <iostream>
#include "Bola.h"

using namespace std;

void moverBola (tBola &bola, tBola &bolaNueva){
		if (bola.x + bola.sentido < 0) bolaNueva.x = 0;
		else if (bola.x + bola.sentido > LARGO -1) bolaNueva.x= LARGO -1;
		else bolaNueva.x = bola.x + bola.sentido;

		invertirInclinacion(bola);
		bolaNueva.y = bola.y + bola.inclinacion;
}

bool invertirInclinacion (tBola &bola){
	int nexPos = bola.y + bola.inclinacion;
	if (nexPos < 0 || nexPos > ALTO - 1){
		bola.inclinacion = -bola.inclinacion;
		return true;
	} 
	else return false;
}

void invertirSentido (int &sentido){
	sentido = -sentido;
}

int modificarInclinacion (int valor){
	return valor;
}