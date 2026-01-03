#include <SDL3/SDL.h>  // This will be red/underlined at first — normal!
#include <SDL3_image/SDL_image.h>
#include <iostream>

struct SDLState {
    SDL_Window* window;
    SDL_Renderer* renderer;
};

void CleanUp(SDLState& state);

int main(int argc, char* argv[]) {

    SDLState game;

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
	SDL_Texture* texture = IMG_LoadTexture(game.renderer, "Assets/playButton.png");
    if (!texture) {
        std::cout << "ERROR cargando imagen: " << std::endl;
        SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Error imagen", "Image Error", nullptr);
        CleanUp(game);
        return 1;
    }

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

        // Perfom drawing commands
        SDL_SetRenderDrawColor(game.renderer, 255, 255, 255, 255);
        SDL_RenderClear(game.renderer);

        float texWidth;
        float texHeight;
		SDL_GetTextureSize(texture, &texWidth, &texHeight);
		SDL_FRect rect = { (width - texWidth) / 5, (height - texHeight) / 5, texWidth, texHeight }; // Goes on the top left

		SDL_RenderTexture(game.renderer, texture, nullptr, &rect);

        // Swap buffers and present
        SDL_RenderPresent(game.renderer);
    }

	SDL_DestroyTexture(texture);
	CleanUp(game);
    return 0;
}

void CleanUp(SDLState &game) {
    SDL_DestroyRenderer(game.renderer);
	SDL_DestroyWindow(game.window);
    SDL_Quit();
}