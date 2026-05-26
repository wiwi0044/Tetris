// Pieza.h
#pragma once
#include <SDL.h>


class Pieza {
public:
    int matriz[4][4];
    int tipo;
    int color;

    Pieza();
    Pieza(int tipo);
    void inicializar(int tipo);
    void rotar();
    int* getMatriz();
    void dibujarPreview(SDL_Renderer* renderer, int x, int y);
};