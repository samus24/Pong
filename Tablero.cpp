#include "Tablero.h"

using namespace std;

void mostrarTablero (tTablero tab){

	HANDLE nuestroBuffer = (HANDLE)GetStdHandle(STD_OUTPUT_HANDLE);
	COORD dwBufferSize = { ILARGO, IALTO };
	COORD dwBufferCoord = { 0, 0 };
	SMALL_RECT rcRegion = { 0, 0, ILARGO-1, IALTO-1 };
	CHAR_INFO pant [IALTO][ILARGO];
	ReadConsoleOutput( nuestroBuffer, (CHAR_INFO *)pant, dwBufferSize,dwBufferCoord, &rcRegion );
	
	for(int k = 0; k < LARGO+2; k++){
		pant[HUECO_ARRIBA-1][k+HUECO_LADO-1].Char.AsciiChar = ARR_CHAR;
		pant[HUECO_ARRIBA-1][k+HUECO_LADO-1].Attributes = FOREGROUND_BLUE | FOREGROUND_INTENSITY;
	}

	for(int i=0; i < ALTO; i++){
		pant[i+HUECO_ARRIBA][HUECO_LADO-1].Char.AsciiChar = IZQ_CHAR;
		pant[i+HUECO_ARRIBA][HUECO_LADO-1].Attributes = FOREGROUND_BLUE | FOREGROUND_INTENSITY;
		for(int j = 0; j < LARGO; j++){
			if (j == LARGO/2){
				if (tab[j][i] == BOLA) {
					pant[i+HUECO_ARRIBA][j+HUECO_LADO].Char.AsciiChar = BOLA_CHAR;
					pant[i+HUECO_ARRIBA][j+HUECO_LADO].Attributes = FOREGROUND_RED | BACKGROUND_BLUE | BACKGROUND_INTENSITY;
				}
				else {
					pant[i+HUECO_ARRIBA][j+HUECO_LADO].Char.AsciiChar = RED_CHAR;
					pant[i+HUECO_ARRIBA][j+HUECO_LADO].Attributes = FOREGROUND_BLUE | FOREGROUND_INTENSITY;
				}
			}
			else{
				switch(tab[j][i]){
					case ESPACIO:
						pant[i+HUECO_ARRIBA][j+HUECO_LADO].Char.AsciiChar = ' ';
						pant[i+HUECO_ARRIBA][j+HUECO_LADO].Attributes = BACKGROUND_GREEN | BACKGROUND_INTENSITY;
						break;
					case BARRA:
						pant[i+HUECO_ARRIBA][j+HUECO_LADO].Char.AsciiChar = BARRA_CHAR;
						pant[i+HUECO_ARRIBA][j+HUECO_LADO].Attributes = FOREGROUND_RED;
						break;
					case BOLA:
						pant[i+HUECO_ARRIBA][j+HUECO_LADO].Char.AsciiChar = BOLA_CHAR;
						pant[i+HUECO_ARRIBA][j+HUECO_LADO].Attributes = FOREGROUND_RED | BACKGROUND_GREEN | BACKGROUND_INTENSITY;
						break;
				}
			}
		}
		pant[i+HUECO_ARRIBA][LARGO+HUECO_LADO].Char.AsciiChar = DER_CHAR;
		pant[i+HUECO_ARRIBA][LARGO+HUECO_LADO].Attributes = FOREGROUND_BLUE | FOREGROUND_INTENSITY;
	}

	for(int i = 0; i < LARGO+2; i++){
		pant[ALTO+HUECO_ARRIBA][i+HUECO_LADO-1].Char.AsciiChar = ABJ_CHAR;
		pant[ALTO+HUECO_ARRIBA][i+HUECO_LADO-1].Attributes = FOREGROUND_BLUE | FOREGROUND_INTENSITY;
	}

	WriteConsoleOutput( nuestroBuffer, (CHAR_INFO *)pant, dwBufferSize,dwBufferCoord, &rcRegion );
}