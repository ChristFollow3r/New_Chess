#pragma once

#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>
#include <iostream>

class Rectangle {

	public:
		Rectangle(SDL_FRect nRect, SDL_Color nColor = { 255, 255, 255, 255 });
		virtual void Render(SDL_Renderer* renderer) const;

		void SetPosition(float x, float y);
		void SetSize(float width, float height);
		SDL_FRect GetRect() const { return rect; };

		~Rectangle() {} // This stays just in case
	protected:
		SDL_FRect rect;
		SDL_Color color;

};