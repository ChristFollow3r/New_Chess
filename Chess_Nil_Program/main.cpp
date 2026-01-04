#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>
#include <iostream>
#include "rectangle.h"
#include "button.h"
#include "gameplay.h"

struct SDLGameState {
    SDL_Window* window;
    SDL_Renderer* renderer;
};

void CleanUp(SDLGameState& game);

int main(int argc, char* argv[]) {

    SDLGameState game;

    // Initializes sdl video subsystem
    if (!SDL_Init(SDL_INIT_VIDEO)) {
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Error", "Error initializing SDL", nullptr);
        return 1;
    }


    
    // Create the window
	int width = 800;
	int height = 600;

	game.window = SDL_CreateWindow("Chess", width, height, 0); // Title, Width, Height, Flags
    if (!game.window) {
        SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Error", "Error creating window", game.window);
        CleanUp(game);
        return 1;
    }

    // Create the renderer
    game.renderer = SDL_CreateRenderer(game.window, nullptr);
    if (!game.renderer) {
        SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Error", "Error creating renderer", game.window);
        CleanUp(game);
        return 1;
    }

    // Load game assets


    // Start the game loop
    bool running = true;
    while (running) {
        SDL_Event event{ 0 };
        while (SDL_PollEvent(&event)) {
            switch (event.type) {
                case SDL_EVENT_QUIT:
                {
                    running = false;
                    break;
                }
            }
        }

        std::vector<std::vector<Rectangle>> board = CreateBoard();
        DrawBoard(game.renderer, board);

        // Perfom drawing commands
        /*SDL_SetRenderDrawColor(game.renderer, 255, 255, 255, 255);*/
       /* SDL_RenderClear(game.renderer);*/

        // Swap buffers and present
        SDL_RenderPresent(game.renderer);

    }

	CleanUp(game);
    return 0;
}

void CleanUp(SDLGameState &game) {
    SDL_DestroyRenderer(game.renderer);
	SDL_DestroyWindow(game.window);
    SDL_Quit();
}