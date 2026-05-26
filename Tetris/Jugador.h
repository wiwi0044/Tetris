#pragma once
#include <SDL.h>
#include "Pieza.h"

class Jugador {
public:
    int ID_Jugador;
    int colorAsignado;
    int xActual;
    int yActual;
    int puntaje;
    Pieza siguientePieza;
    Pieza piezaActual;

    Jugador(int id, int color, int xInicio);
    void dibujar(SDL_Renderer* renderer, int xOffset, int yOffset);
    void nuevaPieza();
    void aumentarPuntaje(int puntos);
    int getPuntaje();
    int getX();
    int getY();
    void setX(int x);
    void setY(int y);
};