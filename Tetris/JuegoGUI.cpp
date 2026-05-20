#include "JuegoGUI.h"
#include <iostream>

JuegoGUI::JuegoGUI(Dificultad difElegida, SDL_Renderer* ren)
    : dificultadActual(difElegida), renderer(ren), juegoActivo(true)
{
    // Dependiendo de la dificultad, ajustamos la velocidad
    switch (dificultadActual) {
    case FACIL:
        velocidadCaida = 1.0f; // El bloque cae cada 1 segundo
        std::cout << "[JuegoGUI] Configurado en modo FACIL" << std::endl;
        break;
    case MEDIO:
        velocidadCaida = 0.5f; // Cae cada medio segundo
        std::cout << "[JuegoGUI] Configurado en modo MEDIO" << std::endl;
        break;
    case DIFICIL:
        velocidadCaida = 0.15f; // ¡A toda velocidad!
        std::cout << "[JuegoGUI] Configurado en modo DIFICIL" << std::endl;
        break;
    }

    inicializarTablero();
}

// Destructor: De momento vacío, pero aquí liberarás texturas o memoria de C++
JuegoGUI::~JuegoGUI() {
    std::cout << "[JuegoGUI] Destructor llamado. Limpiando juego..." << std::endl;
}

void JuegoGUI::inicializarTablero() {
    // Aquí preparar matriz del Tetris o llamasr funciones de ensamblador
}

void JuegoGUI::actualizarLogica() {
    // Aquí usarás 'velocidadCaida' junto con el temporizador de SDL (SDL_GetTicks)
    // para saber cuándo mover la pieza hacia abajo de forma automática.
}

void JuegoGUI::renderizarJuego() {
    // dibujar escenario de tetris
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    // codigo dibujado de piezas
}