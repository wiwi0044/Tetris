// JuegoGUI.cpp
#include "JuegoGUI.h"
#include <string>
#include <SDL.h>
#include <iostream>
#include <stdio.h>

JuegoGUI::JuegoGUI(Dificultad dif, SDL_Renderer* ren)
    : dificultadActual(dif), renderer(ren), juegoActivo(true),
    j1(1, 1, 3), j2(2, 2, 3), ultimoTick(0) {

    fuente = TTF_OpenFont("retro.ttf", 24);

    switch (dificultadActual) {
    case FACIL:   velocidadCaida = 1000.0f; break;
    case MEDIO:   velocidadCaida = 500.0f;  break;
    case DIFICIL: velocidadCaida = 100.0f;  break;
    default:      velocidadCaida = 1000.0f; break;
    }

    ultimoTick = SDL_GetTicks();
}

JuegoGUI::~JuegoGUI() {
    if (fuente) TTF_CloseFont(fuente);
}

void JuegoGUI::dibujarTexto(const char* texto, int x, int y, SDL_Color color) {
    if (!fuente) return;
    SDL_Surface* surf = TTF_RenderText_Solid(fuente, texto, color);
    if (!surf) return;
    SDL_Texture* tex = SDL_CreateTextureFromSurface(renderer, surf);
    SDL_Rect dest = { x, y, surf->w, surf->h };
    SDL_RenderCopy(renderer, tex, NULL, &dest);
    SDL_FreeSurface(surf);
    SDL_DestroyTexture(tex);
}

void JuegoGUI::manejarInput(SDL_Event& e) {
    if (e.type == SDL_KEYDOWN) {
        switch (e.key.keysym.sym) {
            // Jugador 1
        case SDLK_a:
            if (!verificarColisionASM(tablero1.getMatriz(), j1.piezaActual.getMatriz(), j1.getX() - 1, j1.getY()))
                j1.setX(j1.getX() - 1);
            break;
        case SDLK_d:
            if (!verificarColisionASM(tablero1.getMatriz(), j1.piezaActual.getMatriz(), j1.getX() + 1, j1.getY()))
                j1.setX(j1.getX() + 1);
            break;
        case SDLK_s:
            if (!verificarColisionASM(tablero1.getMatriz(), j1.piezaActual.getMatriz(), j1.getX(), j1.getY() + 1))
                j1.setY(j1.getY() + 1);
            break;
        case SDLK_w:
            j1.piezaActual.rotar();
            if (verificarColisionASM(tablero1.getMatriz(), j1.piezaActual.getMatriz(), j1.getX(), j1.getY()))
                j1.piezaActual.rotar();
            break;

            // Jugador 2
        case SDLK_LEFT:
            if (!verificarColisionASM(tablero2.getMatriz(), j2.piezaActual.getMatriz(), j2.getX() - 1, j2.getY()))
                j2.setX(j2.getX() - 1);
            break;
        case SDLK_RIGHT:
            if (!verificarColisionASM(tablero2.getMatriz(), j2.piezaActual.getMatriz(), j2.getX() + 1, j2.getY()))
                j2.setX(j2.getX() + 1);
            break;
        case SDLK_DOWN:
            if (!verificarColisionASM(tablero2.getMatriz(), j2.piezaActual.getMatriz(), j2.getX(), j2.getY() + 1))
                j2.setY(j2.getY() + 1);
            break;
        case SDLK_UP:
            j2.piezaActual.rotar();
            if (verificarColisionASM(tablero2.getMatriz(), j2.piezaActual.getMatriz(), j2.getX(), j2.getY()))
                j2.piezaActual.rotar();
            break;

        case SDLK_ESCAPE:
            juegoActivo = false;
            break;
        }
    }
}


void JuegoGUI::actualizarLogica() {
    Uint32 ahora = SDL_GetTicks();
    if (ahora - ultimoTick < (Uint32)velocidadCaida) return;
    ultimoTick = ahora;

    int nuevoY1 = j1.getY() + 1;
    int colision1 = verificarColisionASM(tablero1.getMatriz(), j1.piezaActual.getMatriz(), j1.getX(), nuevoY1);
    if (colision1) {
        colocarPiezaASM(tablero1.getMatriz(), j1.piezaActual.getMatriz(), j1.getX(), j1.getY(), j1.colorAsignado);
        int lineas1 = limpiarLineasASM(tablero1.getMatriz());
        if (lineas1 > 0) j1.aumentarPuntaje(lineas1 * 100);
        j1.nuevaPieza();
    }
    else {
        j1.setY(nuevoY1);
    }

    int nuevoY2 = j2.getY() + 1;
    int colision2 = verificarColisionASM(tablero2.getMatriz(), j2.piezaActual.getMatriz(), j2.getX(), nuevoY2);
    if (colision2) {
        colocarPiezaASM(tablero2.getMatriz(), j2.piezaActual.getMatriz(), j2.getX(), j2.getY(), j2.colorAsignado);
        int lineas2 = limpiarLineasASM(tablero2.getMatriz());
        if (lineas2 > 0) j2.aumentarPuntaje(lineas2 * 100);
        j2.nuevaPieza();
    }
    else {
        j2.setY(nuevoY2);
    }
}

void JuegoGUI::renderizar() {
    int W, H;
    SDL_GetRendererOutputSize(renderer, &W, &H);

    int centroX = W / 2;
    int tabAncho = 10 * 25;  // 250px
    int tabAlto = 20 * 25;   // 500px
    int tabY = 200;

    int xTab1 = centroX - tabAncho - 60;  // tablero izquierdo
    int xTab2 = centroX + 60;             // tablero derecho

    SDL_SetRenderDrawColor(renderer, 25, 25, 30, 255);
    SDL_RenderClear(renderer);

    SDL_Color blanco = { 255, 255, 255, 255 };
    SDL_Color amarillo = { 255, 215, 0,   255 };
    SDL_Color rojo = { 255, 50,  50,  255 };

    std::string p1 = std::to_string(j1.getPuntaje());
    std::string p2 = std::to_string(j2.getPuntaje());

    // Puntajes
    dibujarTexto("JUGADOR 1", xTab1+40, 150, blanco);
    dibujarTexto(p1.c_str(), xTab1 + 200, 150, amarillo);
    dibujarTexto("JUGADOR 2", xTab2+40, 150, blanco);
    dibujarTexto(p2.c_str(), xTab2 + 200, 150, amarillo);

    // Boton salir centrado arriba
    SDL_Rect btnSalir = { centroX - 722, 780, 160, 40 };
    SDL_SetRenderDrawColor(renderer, 50, 50, 70, 255);
    SDL_RenderFillRect(renderer, &btnSalir);
    SDL_SetRenderDrawColor(renderer, rojo.r, rojo.g, rojo.b, 255);
    SDL_RenderDrawRect(renderer, &btnSalir);
    dibujarTexto("[ESC] SALIR", centroX - 720, 790, rojo);

    // Preview J1 a la izquierda del tablero 1
    int prevX1 = xTab1 - 100;
    SDL_Rect prevJ1 = { prevX1, 200, 80, 80 };
    SDL_SetRenderDrawColor(renderer, 50, 50, 70, 255);
    SDL_RenderFillRect(renderer, &prevJ1);
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderDrawRect(renderer, &prevJ1);
    dibujarTexto("NEXT", prevX1, 175, blanco);
    j1.siguientePieza.dibujarPreview(renderer, prevX1 + 5, 205);

    // Preview J2 a la derecha del tablero 2
    int prevX2 = xTab2 + tabAncho + 20;
    SDL_Rect prevJ2 = { prevX2, 200, 80, 80 };
    SDL_SetRenderDrawColor(renderer, 50, 50, 70, 255);
    SDL_RenderFillRect(renderer, &prevJ2);
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderDrawRect(renderer, &prevJ2);
    dibujarTexto("NEXT", prevX2, 175, blanco);
    j2.siguientePieza.dibujarPreview(renderer, prevX2 + 5, 205);

    // Tableros y jugadores
    tablero1.dibujar(renderer, xTab1, tabY);
    tablero2.dibujar(renderer, xTab2, tabY);
    j1.dibujar(renderer, xTab1, tabY);
    j2.dibujar(renderer, xTab2, tabY);

    SDL_RenderPresent(renderer);
}

void JuegoGUI::iniciarPartida() {
    j1.nuevaPieza();
    j2.nuevaPieza();

    SDL_Event e;
    while (juegoActivo) {
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_QUIT) juegoActivo = false;
            manejarInput(e);
        }
        actualizarLogica();
        renderizar();
        SDL_Delay(16);
    }
}


void JuegoGUI::terminarJuego() {
	int t1=hayColumnaLlenaASM(tablero1.getMatriz());
	int t2 = hayColumnaLlenaASM(tablero2.getMatriz());

    if (t1) {
		std::cout << "perdio el 1";
    }

    if (t2) {

    }
}