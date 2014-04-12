#include "Archivos.h"

bool mostrar_archivo (string direccion){
	fstream arch;
	arch.open(direccion);

	if(!arch.is_open())	return false;
	else{				
		string leida;
		getline(arch,leida);
		while (leida != CENTINELA)		
		{
			cout << leida << endl;
			getline(arch,leida);
		}

		cout << endl;

		return true;
	}
}

bool guardar_archivo (string direccion, tListaJugadores jug){
	ofstream arch;
	arch.open(direccion);
	if(!arch.is_open())	return false;

	else{				
		for (int i=0; i < jug.cont; i++){
			arch << jug.jug[i].nombre << endl;
			arch << jug.jug[i].pass << endl;
			arch << jug.jug[i].siglas << endl;
			arch << jug.jug[i].vic << endl;
			arch << jug.jug[i].derr << endl;
			arch << jug.jug[i].maxPunt << endl;
			arch << jug.jug[i].puntosTot << endl;
			arch << jug.jug[i].max_rango << endl;
			arch << jug.jug[i].min_rango << endl;
		}
		arch << CENTINELA;

		return true;
	}
}

bool cargar_archivo (string direccion, tListaJugadores &jug){
	fstream arch;
	arch.open(direccion);
	if(!arch.is_open())	return false;

	else{			
		tJugador aux;
		jug.cont = 0;
		arch >> aux.nombre;
		while ((aux.nombre != CENTINELA) && (jug.cont < MAXJUGADORES)){
				arch >> aux.pass;
				arch >> aux.siglas;
				arch >> aux.vic;
				arch >> aux.derr;
				arch >> aux.maxPunt;
				arch >> aux.puntosTot;
				arch >> aux.max_rango;
				arch >> aux.min_rango;
				jug.jug[jug.cont] = aux;
				jug.cont++;
				arch >> aux.nombre;
		}

		return true;

	}
}
