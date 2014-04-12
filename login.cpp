#include "login.h"

bool login (const tListaJugadores &lista,unsigned int &indice){
	bool ok = false;			// Si todo (nombre y pass) son correctos esto será true
	bool existe = false;		// Si el nombre es válido será true

	existe = checkName(lista, indice);		// Se verifica si existe (y de paso el tipo y posicion)
	if(existe){					// Si existe
		ok = checkPass(lista, indice);	// Se verifica la contraseña
	}
	else
		cout << "El usuario no existe" << endl;	// Se muestra mensaje de error y se reintenta

	return ok;
}

bool checkName(const tListaJugadores &lista, unsigned int &indice){
	indice = 0;
	bool existe = false;
	string nombre;

	cout << "Introduzca sus datos ('salir' o 's' para salir)" << endl;
	cout << "Usuario: ";
	cin >> nombre;
	existe = buscaJugador(lista,nombre,indice);	

	return existe;
}
	
bool checkPass(const tListaJugadores &lista, unsigned int i){
	bool ok = false;
	int intentos = INTENTOS;
	string passEsperado, pass;	

	passEsperado = lista.jug[i].pass;	// Se usa como passEsperado la contraseña del jugador
	do{
		cout << "Contraseña, (" << intentos << " intentos): ";	// Se muestran los intentos y se pide la password
		cin >> pass; 
		if (pass == passEsperado)		// Si coinciden las cadenas
			ok = true;							// Se da de paso al jugador
		else									// si se falla se resta un intento
			intentos --;									
	} while ((!ok) && (intentos > 0));

	return ok;
}