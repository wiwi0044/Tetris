// InicioGUI.cpp
#include "InicioGUI.h"
#include "JuegoGUI.h"

InicioGUI::InicioGUI(SDL_Renderer* ren)
    : renderer(ren), salir(false), seleccion(0) {
    fuente = TTF_OpenFont("retro.ttf", 28);
    if (!fuente) {
        // usar fuente del sistema como fallback
        fuente = TTF_OpenFont("C:/Windows/Fonts/arial.ttf", 28);
    }

    fuenteGrande = TTF_OpenFont("retro.ttf", 78);
    
    if (!fuenteGrande) {
        // usar fuente del sistema como fallback
        fuenteGrande = TTF_OpenFont("C:/Windows/Fonts/arial.ttf", 28);
    };
}

InicioGUI::~InicioGUI() {
    if (fuente) { TTF_CloseFont(fuente); fuente = nullptr; }
    if (fuenteGrande) { TTF_CloseFont(fuenteGrande); fuenteGrande = nullptr; }
}

void InicioGUI::dibujarTexto(const char* texto, int x, int y, SDL_Color color, TTF_Font* f) {
    if (!f) return;
    SDL_Surface* surf = TTF_RenderText_Solid(f, texto, color);
    if (!surf) return;
    SDL_Texture* tex = SDL_CreateTextureFromSurface(renderer, surf);
    SDL_Rect dest = { x, y, surf->w, surf->h };
    SDL_RenderCopy(renderer, tex, NULL, &dest);
    SDL_FreeSurface(surf);
    SDL_DestroyTexture(tex);
}

void InicioGUI::renderizar() {
    int W, H;
    SDL_GetRendererOutputSize(renderer, &W, &H);
    int centroX = W / 2;
    int centroY = H / 2;

    SDL_SetRenderDrawColor(renderer, 15, 15, 25, 255);
    SDL_RenderClear(renderer);

    // T E T R I S con colores diferentes
    SDL_Color colores[6] = {
        {255, 50,  50,  255},
        {255, 165, 0,   255},
        {255, 255, 0,   255},
        {50,  255, 50,  255},
        {50,  150, 255, 255},
        {180, 50,  255, 255}
    };
    const char* letras[6] = { "T", "E", "T", "R", "I", "S" };
    int xLetra = centroX - 180;
    for (int i = 0; i < 6; i++) {
        dibujarTexto(letras[i], xLetra, centroY - 300, colores[i], fuenteGrande);
        xLetra += 60;
    }

    SDL_Color blanco = { 255, 255, 255, 255 };
    dibujarTexto("2 JUGADORES", centroX - 100, centroY - 190, blanco, fuente);

    struct { const char* texto; SDL_Color color; } opciones[3] = {
        { "FACIL",   { 50,  255, 50,  255 } },
        { "MEDIO",   { 255, 215, 0,   255 } },
        { "DIFICIL", { 255, 50,  50,  255 } }
    };

    for (int i = 0; i < 3; i++) {
        int y = centroY - 50 + i * 70;
        SDL_Color color = opciones[i].color;
        if (seleccion == i) {
            SDL_Rect fondo = { centroX - 210, y - 8, 400, 50 };
            SDL_SetRenderDrawColor(renderer, color.r / 4, color.g / 4, color.b / 4, 255);
            SDL_RenderFillRect(renderer, &fondo);
            SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, 255);
            SDL_RenderDrawRect(renderer, &fondo);
            dibujarTexto(">", centroX - 240, y, color, fuente);
        }
        dibujarTexto(opciones[i].texto, centroX - 60, y, seleccion == i ? color : blanco, fuente);
    }

    SDL_Color gris = { 150, 150, 150, 255 };
    dibujarTexto("FLECHAS para seleccionar", centroX - 175, centroY + 150, gris, fuente);
    dibujarTexto("ENTER para jugar", centroX - 105, centroY + 190, gris, fuente);

    SDL_RenderPresent(renderer);
}

void InicioGUI::manejarInput(SDL_Event& e) {
    if (e.type == SDL_KEYDOWN) {
        switch (e.key.keysym.sym) {
        case SDLK_UP:
            seleccion = (seleccion - 1 + 3) % 3;
            break;
        case SDLK_DOWN:
            seleccion = (seleccion + 1) % 3;
            break;
        case SDLK_RETURN: {
            Dificultad dif = (Dificultad)seleccion;
            JuegoGUI juego(dif, renderer);
            juego.iniciarPartida();
            break;
        }
        case SDLK_ESCAPE:
            salir = true;
            break;
        }
    }
}

void InicioGUI::mostrar() {
    SDL_Event e;
    while (!salir) {
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_QUIT) salir = true;
            manejarInput(e);
        }
        renderizar();
        SDL_Delay(16);
    }
}

Dificultad InicioGUI::getDificultad() {
    return (Dificultad)seleccion;
}