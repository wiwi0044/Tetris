#pragma once // Evita que el archivo se cargue dos veces (como un escudo)
#include <SDL.h>

// El mismo enum que usas en el menú principal
enum Dificultad { FACIL, MEDIO, DIFICIL };

class JuegoGUI {
private:
    // Atributos privados (como en Java)
    Dificultad dificultadActual;
    float velocidadCaida; // Tiempo en segundos entre cada caída de bloque
    bool juegoActivo;

    // Aquí irían tus variables de SDL que pases o manejes (ej. el renderer)
    SDL_Renderer* renderer;

public:
    // El constructor recibe la dificultad elegida
    JuegoGUI(Dificultad difElegida, SDL_Renderer* ren);

    // Destructor (Esto no existe en Java porque hay Garbage Collector)
    // En C++ sirve para liberar la memoria manualmente cuando el juego termine
    ~JuegoGUI();

    // Métodos públicos
    void inicializarTablero();
    void actualizarLogica();
    void renderizarJuego();
    bool estaActivo() const { return juegoActivo; }
};