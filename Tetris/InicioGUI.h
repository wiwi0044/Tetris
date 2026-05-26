#pragma once
#include <SDL.h>
#include <SDL_ttf.h>

enum Dificultad { FACIL, MEDIO, DIFICIL };

class InicioGUI {
private:
    SDL_Renderer* renderer;
    TTF_Font* fuente = nullptr;
    TTF_Font* fuenteGrande = nullptr;
    int seleccion;
    bool salir;
    void dibujarTexto(const char* texto, int x, int y, SDL_Color color, TTF_Font* f);
    void renderizar();
    void manejarInput(SDL_Event& e);
public:
    InicioGUI(SDL_Renderer* ren);
    ~InicioGUI();
    void mostrar();
    Dificultad getDificultad();
};