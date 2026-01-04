#pragma once
#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>
#include <iostream>
#include "rectangle.h"

class Button : public Rectangle {

	public:

		Button(SDL_FRect nRect, SDL_Texture* nTexture); // Texture needs a pointer
		void Render(SDL_Renderer *renderer) override; 
		bool isClicked(float mouseX, float mouseY) const;

	private:
		SDL_Texture* texture;
};