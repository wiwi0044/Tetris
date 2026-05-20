#include <SDL.h>
#include <SDL_ttf.h>
#include <iostream>
#include "JuegoGUI.h" 

// Definimos los estados del juego y los niveles de dificultad
enum GameState { MENU, PLAYING, QUIT };

int main(int argc, char* argv[]) {
    // Inicializar video de SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cerr << "Error al inicializar SDL: " << SDL_GetError() << std::endl;
        return -1;
    }

    // Inicializar el motor de texto de forma segura
    if (TTF_Init() == -1) {
        std::cerr << "Error al inicializar SDL_ttf: " << TTF_GetError() << std::endl;
    }

    SDL_Window* window = SDL_CreateWindow("Tetris - by Mancinas & Espinoza",
        SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
        800, 600, SDL_WINDOW_SHOWN);
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    // --- CARGA DE FUENTES CON RUTAS RELATIVAS (Para que no falle con tu compañero) ---
    TTF_Font* fuente = TTF_OpenFont("retro.ttf", 24);
    if (!fuente) fuente = TTF_OpenFont("retro", 24);
    if (!fuente) fuente = TTF_OpenFont("../retro.ttf", 24);

    TTF_Font* fuenteTetris = TTF_OpenFont("retro.ttf", 64);
    if (!fuenteTetris) fuenteTetris = TTF_OpenFont("retro", 64);
    if (!fuenteTetris) fuenteTetris = TTF_OpenFont("../retro.ttf", 64);

    TTF_Font* fuenteSubtitulo = TTF_OpenFont("retro.ttf", 28);
    if (!fuenteSubtitulo) fuenteSubtitulo = TTF_OpenFont("retro", 28);
    if (!fuenteSubtitulo) fuenteSubtitulo = TTF_OpenFont("../retro.ttf", 28);

    GameState currentState = MENU;
    Dificultad nivelSeleccionado = FACIL; // Por defecto inicia en Fácil
    bool running = true;
    SDL_Event event;

    while (running) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) running = false;

            if (currentState == MENU && event.type == SDL_KEYDOWN) {
                switch (event.key.keysym.sym) {
                case SDLK_UP:
                    if (nivelSeleccionado == MEDIO) nivelSeleccionado = FACIL;
                    else if (nivelSeleccionado == DIFICIL) nivelSeleccionado = MEDIO;
                    break;
                case SDLK_DOWN:
                    if (nivelSeleccionado == FACIL) nivelSeleccionado = MEDIO;
                    else if (nivelSeleccionado == MEDIO) nivelSeleccionado = DIFICIL;
                    break;
                case SDLK_RETURN:
                    currentState = PLAYING;
                    if (nivelSeleccionado == FACIL) std::cout << "Iniciando Tetris en modo: FACIL" << std::endl;
                    if (nivelSeleccionado == MEDIO) std::cout << "Iniciando Tetris en modo: MEDIO" << std::endl;
                    if (nivelSeleccionado == DIFICIL) std::cout << "Iniciando Tetris en modo: DIFICIL" << std::endl;
                    break;
                }
            }
        }

        // --- RENDERIZADO ---
        SDL_SetRenderDrawColor(renderer, 10, 10, 25, 255); // Fondo azul oscuro retro
        SDL_RenderClear(renderer);

        if (currentState == MENU) {
            // Paleta de Colores de la Interfaz
            SDL_Color colorBlanco = { 255, 255, 255, 255 };
            SDL_Color colorGris = { 100, 100, 110, 255 };
            SDL_Color colorVerde = { 0,   255, 100, 255 }; // Fácil
            SDL_Color colorAmarillo = { 255, 230, 0,   255 }; // Medio
            SDL_Color colorRojo = { 255, 50,  50,  255 }; // Difícil

            // 1. --- DIBUJAR PALABRA "TETRIS" ---
            if (fuenteTetris) {
                const char* letrasTetris[] = { "T", "E", "T", "R", "I", "S" };
                SDL_Color coloresTetris[] = {
                    { 255, 50,  50,  255 },
                    { 50,  255, 50,  255 },
                    { 50,  255, 255, 255 },
                    { 255, 255, 50,  255 },
                    { 255, 50,  255, 255 },
                    { 255, 150, 50,  255 }
                };

                int totalLetras = 6;
                int anchoLetraGiga = 48;
                int espacioLetrasGiga = 6;
                int anchoTotalTetris = (totalLetras * anchoLetraGiga) + ((totalLetras - 1) * espacioLetrasGiga);
                int xInicioTetris = 400 - (anchoTotalTetris / 2);
                int yPosTetris = 40;

                for (int i = 0; i < totalLetras; i++) {
                    SDL_Surface* surfLetra = TTF_RenderText_Solid(fuenteTetris, letrasTetris[i], coloresTetris[i]);
                    if (surfLetra) {
                        SDL_Texture* textLetra = SDL_CreateTextureFromSurface(renderer, surfLetra);
                        SDL_Rect rectLetra = { xInicioTetris + (i * (anchoLetraGiga + espacioLetrasGiga)), yPosTetris, surfLetra->w, surfLetra->h };
                        SDL_RenderCopy(renderer, textLetra, NULL, &rectLetra);
                        SDL_FreeSurface(surfLetra);
                        SDL_DestroyTexture(textLetra);
                    }
                }
            }

            // 1B. --- DIBUJAR SUBTÍTULO "2 JUGADORES" ---
            if (fuenteSubtitulo) {
                SDL_Color colorSubtitulo = { 210, 215, 240, 255 };
                SDL_Surface* surfSub = TTF_RenderText_Solid(fuenteSubtitulo, "2 JUGADORES", colorSubtitulo);
                if (surfSub) {
                    SDL_Texture* textSub = SDL_CreateTextureFromSurface(renderer, surfSub);
                    SDL_Rect rectSub = { 400 - (surfSub->w / 2), 125, surfSub->w, surfSub->h };
                    SDL_RenderCopy(renderer, textSub, NULL, &rectSub);
                    SDL_FreeSurface(surfSub);
                    SDL_DestroyTexture(textSub);
                }
            }

            // 2. --- BOTÓN: NIVEL FÁCIL ---
            SDL_Rect btnFacil = { 260, 240, 280, 50 };
            SDL_Color colorTextoFacil = colorBlanco;

            if (nivelSeleccionado == FACIL) {
                SDL_SetRenderDrawColor(renderer, 0, 255, 100, 255);
                colorTextoFacil = colorVerde;
            }
            else {
                SDL_SetRenderDrawColor(renderer, 50, 50, 70, 255);
            }
            SDL_RenderDrawRect(renderer, &btnFacil);

            if (fuente) {
                SDL_Surface* surfFacil = TTF_RenderText_Solid(fuente, "NIVEL FACIL", colorTextoFacil);
                if (surfFacil) {
                    SDL_Texture* textFacil = SDL_CreateTextureFromSurface(renderer, surfFacil);
                    SDL_Rect rectFacil = { btnFacil.x + (btnFacil.w / 2) - (surfFacil->w / 2), btnFacil.y + (btnFacil.h / 2) - (surfFacil->h / 2), surfFacil->w, surfFacil->h };
                    SDL_RenderCopy(renderer, textFacil, NULL, &rectFacil);
                    SDL_FreeSurface(surfFacil);
                    SDL_DestroyTexture(textFacil);
                }
            }

            // 3. --- BOTÓN: NIVEL MEDIO ---
            SDL_Rect btnMedio = { 260, 310, 280, 50 };
            SDL_Color colorTextoMedio = colorBlanco;

            if (nivelSeleccionado == MEDIO) {
                SDL_SetRenderDrawColor(renderer, 255, 230, 0, 255);
                colorTextoMedio = colorAmarillo;
            }
            else {
                SDL_SetRenderDrawColor(renderer, 50, 50, 70, 255);
            }
            SDL_RenderDrawRect(renderer, &btnMedio);

            if (fuente) {
                SDL_Surface* surfMedio = TTF_RenderText_Solid(fuente, "NIVEL MEDIO", colorTextoMedio);
                if (surfMedio) {
                    SDL_Texture* textMedio = SDL_CreateTextureFromSurface(renderer, surfMedio);
                    SDL_Rect rectMedio = { btnMedio.x + (btnMedio.w / 2) - (surfMedio->w / 2), btnMedio.y + (btnMedio.h / 2) - (surfMedio->h / 2), surfMedio->w, surfMedio->h };
                    SDL_RenderCopy(renderer, textMedio, NULL, &rectMedio);
                    SDL_FreeSurface(surfMedio);
                    SDL_DestroyTexture(textMedio);
                }
            }

            // 4. --- BOTÓN: NIVEL DIFÍCIL ---
            SDL_Rect btnDificil = { 260, 380, 280, 50 };
            SDL_Color colorTextoDificil = colorBlanco;

            if (nivelSeleccionado == DIFICIL) {
                SDL_SetRenderDrawColor(renderer, 255, 50, 50, 255);
                colorTextoDificil = colorRojo;
            }
            else {
                SDL_SetRenderDrawColor(renderer, 50, 50, 70, 255);
            }
            SDL_RenderDrawRect(renderer, &btnDificil);

            if (fuente) {
                SDL_Surface* surfDificil = TTF_RenderText_Solid(fuente, "NIVEL DIFICIL", colorTextoDificil);
                if (surfDificil) {
                    SDL_Texture* textDificil = SDL_CreateTextureFromSurface(renderer, surfDificil);
                    SDL_Rect rectDificil = { btnDificil.x + (btnDificil.w / 2) - (surfDificil->w / 2), btnDificil.y + (btnDificil.h / 2) - (surfDificil->h / 2), surfDificil->w, surfDificil->h };
                    SDL_RenderCopy(renderer, textDificil, NULL, &rectDificil);
                    SDL_FreeSurface(surfDificil);
                    SDL_DestroyTexture(textDificil);
                }
            }

            // 5. --- TEXTO INFERIOR DE CONTROL ---
            if (fuente) {
                SDL_Surface* surfControles = TTF_RenderText_Solid(fuente, "SELECCIONE CON LAS FLECHAS Y PULSE ENTER", colorGris);
                if (surfControles) {
                    SDL_Texture* textControles = SDL_CreateTextureFromSurface(renderer, surfControles);
                    SDL_Rect rectControles = { 400 - (surfControles->w / 2), 520, surfControles->w, surfControles->h };
                    SDL_RenderCopy(renderer, textControles, NULL, &rectControles);
                    SDL_FreeSurface(surfControles);
                    SDL_DestroyTexture(textControles);
                }
            }
            SDL_RenderPresent(renderer); // Mostrar el menú
        }
        else {
            
            JuegoGUI miJuego(nivelSeleccionado, renderer);

            // Bucle exclusivo mientras el juego esté activo
            while (miJuego.estaActivo() && running) {
                SDL_Event juegoEvent;
                while (SDL_PollEvent(&juegoEvent)) {
                    if (juegoEvent.type == SDL_QUIT) {
                        running = false; // Detener el programa completo
                    }

                    // Aquí capturarás las flechas (Izquierda, Derecha, etc.) para mover las piezas
                    // y se las enviarás a los métodos de tu clase.
                }

                // Limpiamos pantalla con color gris oscuro transicional
                SDL_SetRenderDrawColor(renderer, 30, 30, 40, 255);
                SDL_RenderClear(renderer);

                miJuego.actualizarLogica();
                miJuego.renderizarJuego();

                // Dibujar el cuadro en pantalla
                SDL_RenderPresent(renderer);
                SDL_Delay(16); // Límite para correr a ~60 fotogramas por segundo
            }

            // Si salimos del bucle de juego porque perdimos, regresamos al menú principal
            currentState = MENU;
        }
    }

    // Limpieza ordenada de memoria
    if (fuente) TTF_CloseFont(fuente);
    if (fuenteTetris) TTF_CloseFont(fuenteTetris);
    if (fuenteSubtitulo) TTF_CloseFont(fuenteSubtitulo);
    TTF_Quit();

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}