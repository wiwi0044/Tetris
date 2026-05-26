// Pieza.cpp
#include "Pieza.h"
#include <cstdlib>
#include <SDL.h>

extern "C" int __stdcall rotarPiezaASM(int* matriz);
extern "C" void __stdcall inicializarPiezaASM(int* matriz, int tipo);


Pieza::Pieza() {
    tipo = rand()%7;
    inicializar(tipo);
}


void Pieza::inicializar(int t) {
	inicializarPiezaASM(&matriz[0][0], t);
    color = t + 1;
}

void Pieza::rotar() {
    rotarPiezaASM(&matriz[0][0]);
}

void Pieza::dibujarPreview(SDL_Renderer* renderer, int x, int y) {
    int tam = 18;
    SDL_SetRenderDrawColor(renderer, 200, 200, 200, 255);
    for (int f = 0; f < 4; f++) {
        for (int c = 0; c < 4; c++) {
            if (matriz[f][c] != 0) {
                SDL_Rect bloque = { x + c * tam, y + f * tam, tam - 1, tam - 1 };
                SDL_RenderFillRect(renderer, &bloque);
            }
        }
    }
}

int* Pieza::getMatriz() {
    return &matriz[0][0];
}