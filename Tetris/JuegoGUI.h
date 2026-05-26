// JuegoGUI.h
#pragma once
#include <SDL.h>
#include <SDL_ttf.h>
#include "Jugador.h"
#include "Tablero.h"
#include "InicioGUI.h"

extern "C" int  __stdcall verificarColisionASM(int* tablero, int* pieza, int x, int y);
extern "C" int  __stdcall colocarPiezaASM(int* tablero, int* pieza, int x, int y, int color);
extern "C" int  __stdcall limpiarLineasASM(int* matriz);
extern "C" int __stdcall hayColumnaLlenaASM(int* matriz);

class JuegoGUI {

private:
    SDL_Renderer* renderer;
    TTF_Font* fuente;
    Dificultad dificultadActual;
    float velocidadCaida;
    bool juegoActivo;
    Jugador j1;
    Jugador j2;
    Tablero tablero1;
    Tablero tablero2;
    Uint32 ultimoTick;

    void dibujarTexto(const char* texto, int x, int y, SDL_Color color);
    void renderizar();
    void manejarInput(SDL_Event& e);
    void actualizarLogica();
	void terminarJuego();

public:
    JuegoGUI(Dificultad dif, SDL_Renderer* ren);
    ~JuegoGUI();
    void iniciarPartida();
};