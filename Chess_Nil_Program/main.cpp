#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>
#include <iostream>
#include "rectangle.h"
#include "button.h"

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
	SDL_Texture* texture = IMG_LoadTexture(game.renderer, "Assets/playButton.png");
    float texW, texH;
    SDL_GetTextureSize(texture, &texW, &texH);

    float scale = 1.0f;
    SDL_FRect buttonRect = { 300.0f, 200.0f, texW * scale, texH * scale };  
    Button playButton(buttonRect, texture);

    float x = 400;
	float y = 300;
	float w = 80;
	float h = 80;
	SDL_FRect tempRect = { x, y, w, h };
	Rectangle tempRectangle(tempRect); // Just to test the Rectangle class

    if (!texture) {
        std::cout << "ERROR loading image: " << std::endl;
        SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Error", "Error loading image", nullptr);
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

        if (event.type == SDL_EVENT_MOUSE_BUTTON_DOWN && event.button.button == SDL_BUTTON_LEFT) {
            float x = (float)event.button.x;
            float y = (float)event.button.y;
            if (playButton.isClicked(x, y)) {
                std::cout << "Button was clicked\n";
            }
        }

        }

        // Perfom drawing commands
        SDL_SetRenderDrawColor(game.renderer, 255, 255, 255, 255);
        SDL_RenderClear(game.renderer);

        //float texWidth;
        //float texHeight;
		//SDL_FRect rect = { (width - texWidth) / 5, (height - texHeight) / 5, texWidth, texHeight }; // Goes on the top left

		tempRectangle.Render(game.renderer); // Prints the rectangle
		/*SDL_RenderTexture(game.renderer, texture, nullptr, &rect);*/
        playButton.Render(game.renderer);
        // Swap buffers and present
        SDL_RenderPresent(game.renderer);

    }

	SDL_DestroyTexture(texture);
	CleanUp(game);
    return 0;
}

void CleanUp(SDLGameState &game) {
    SDL_DestroyRenderer(game.renderer);
	SDL_DestroyWindow(game.window);
    SDL_Quit();
}