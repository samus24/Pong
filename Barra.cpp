#include <iostream>
#include "Barra.h"

using namespace std;

void moverBarra (int direccion, int &pos){
	if (direccion == ARRIBA){
		pos -= VELOCIDAD_BARRA_USER;
	}
	else if (direccion == ABAJO){
		pos += VELOCIDAD_BARRA_USER;
	}
	if (pos < 0) pos = 0;
	if (pos > ALTO-LONGITUD) pos = ALTO-LONGITUD;
}

