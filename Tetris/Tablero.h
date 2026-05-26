// Tablero.h
#pragma once
#include <SDL.h>

class Tablero {
private:
    int matriz[20][10];
    int xOffset;
    int yOffset;

public:
    Tablero();
    void dibujar(SDL_Renderer* renderer, int x, int y);
    int* getMatriz();
    bool estaOcupado(int fila, int col);
    void colocarBloque(int fila, int col, int valor);
	void terminarJuego();
};