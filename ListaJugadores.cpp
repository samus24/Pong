#include "ListaJugadores.h"

bool insertaJugador (tListaJugadores &lista, tJugador jug){
	if (lista.cont < MAXJUGADORES){
		lista.jug[lista.cont] = jug;
		lista.cont++;

		return true;
	}
	else return false;
}

void eliminaJugador (tListaJugadores &lista, unsigned int pos){
	for(int i = pos; i < lista.cont; i++){			// Se mueven los jugadores posteriores a el llenando el "hueco" que deja
		lista.jug[i] = lista.jug[i+1];
	}
	lista.cont--;
}

bool buscaJugador (tListaJugadores lista, string nombre, unsigned int &pos){
	int i = 0;
	bool encontrado = false;
	while ((i < lista.cont) && !encontrado){		// Búsqueda normal
		if(nombre == lista.jug[i].nombre){
			encontrado = true;
			pos = i;
		}
		else i++;
	}

	return encontrado;
}

void altaJugador (tJugador &jug){
		string aux;
		cout << "Introduzca su nombre: ";
		cin >> jug.nombre;

		do{
			cout << "Introduzca una contraseña: ";
			cin >> aux;
			cout << "Repita contraseña: ";
			cin >> jug.pass;
		} while (aux != jug.pass);

		do{
			cout << "Introduzca unas siglas (3 caracteres): ";
			cin >> jug.siglas;
		} while (jug.siglas.length() != 3);

		for(int i = 0; i < 3; i++) jug.siglas[i] = toupper(jug.siglas[i]);

		jug.vic = 0;
		jug.derr = 0;
		jug.maxPunt = 0;
		jug.max_rango = 8;
		jug.min_rango = 3;
		jug.puntosTot = 5;
}

void ordenaLista (tListaJugadores &jug){	
	bool inter = true;
    int i = 0;

	while ((i < jug.cont - 1) && inter) {	// Método de la burbuja 
		inter = false;
		for (int j = jug.cont - 1; j > i; j--){
			if (jug.jug[j].maxPunt > jug.jug[j - 1].maxPunt) {
				tJugador tmp;
				tmp = jug.jug[j];
				jug.jug[j] = jug.jug[j - 1];
				jug.jug[j - 1] = tmp;
				inter = true;
			}
		}
		if (inter) i++;
	}
	
}