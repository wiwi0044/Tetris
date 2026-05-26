#include "Tablero.h"

extern "C" int __stdcall limpiarLineasASM(int* matriz);
extern "C" void __stdcall llenarTableroASM(int* matriz);

Tablero::Tablero() {
	llenarTableroASM(&matriz[0][0]);
}

int* Tablero::getMatriz() {
    return &matriz[0][0];
}

bool Tablero::estaOcupado(int fila, int col) {
    return matriz[fila][col] != 0;
}

void Tablero::colocarBloque(int fila, int col, int valor) {
    matriz[fila][col] = valor;
}

void Tablero::dibujar(SDL_Renderer* renderer, int x, int y) {
    int tam = 25;

    // Dibujar borde
    SDL_Rect borde = { x - 2, y - 2, 10 * tam + 4, 20 * tam + 4 };
    SDL_SetRenderDrawColor(renderer, 100, 100, 120, 255);
    SDL_RenderDrawRect(renderer, &borde);

    // Dibujar bloques ocupados
    for (int f = 0; f < 20; f++) {
        for (int c = 0; c < 10; c++) {
            if (matriz[f][c] != 0) {
                SDL_Rect bloque = {
                    x + c * tam,
                    y + f * tam,
                    tam - 1,
                    tam - 1
                };
                SDL_SetRenderDrawColor(renderer, 80, 80, 200, 255);
                SDL_RenderFillRect(renderer, &bloque);
            }
        }
    }
}
