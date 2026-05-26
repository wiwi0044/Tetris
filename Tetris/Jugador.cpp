#include "Jugador.h"

extern "C" int  __stdcall getPuntajeASM(int* punteroPuntaje);
extern "C" void __stdcall aumentarPuntajeASM(int* punteroPuntaje, int aumento);

Jugador::Jugador(int id, int color, int xInicio)
    : ID_Jugador(id), colorAsignado(color),
    xActual(xInicio), yActual(0), puntaje(0) {
}

void Jugador::nuevaPieza() {
    piezaActual = siguientePieza;
	siguientePieza = Pieza();
    xActual = 3;
    yActual = 0;
}

int Jugador::getPuntaje() {
    return getPuntajeASM(&puntaje);
}

void Jugador::aumentarPuntaje(int puntos) {
    aumentarPuntajeASM(&puntaje, puntos);
}

int Jugador::getX() { return xActual; }
int Jugador::getY() { return yActual; }
void Jugador::setX(int x) { xActual = x; }
void Jugador::setY(int y) { yActual = y; }

void Jugador::dibujar(SDL_Renderer* renderer, int xOffset, int yOffset) {
    int tam = 25;
    if (colorAsignado == 1)
        SDL_SetRenderDrawColor(renderer, 255, 50, 50, 255);
    else
        SDL_SetRenderDrawColor(renderer, 50, 255, 50, 255);
    for (int f = 0; f < 4; f++) {
        for (int c = 0; c < 4; c++) {
            if (piezaActual.matriz[f][c] != 0) {
                SDL_Rect bloque = {
                    xOffset + (xActual + c) * tam,
                    yOffset + (yActual + f) * tam,
                    tam - 1,
                    tam - 1
                };
                SDL_RenderFillRect(renderer, &bloque);
            }
        }
    }
}