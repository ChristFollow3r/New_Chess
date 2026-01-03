#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>
#include <iostream>
#include "rectangle.h"

Rectangle::Rectangle(SDL_FRect nRect) : rect(nRect) {}

void Rectangle::Render(SDL_Renderer* renderer) {
	if (!renderer) return;

	SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);

	SDL_RenderFillRect(renderer, &rect); 
}

void Rectangle::SetPosition(float x, float y) {
	rect.x = x;
	rect.y = y;
}

void Rectangle::SetSize(float width, float height) {
	rect.w = width;
	rect.h = height;
}