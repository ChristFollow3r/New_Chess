#include "button.h"

Button::Button(SDL_FRect nRect, SDL_Texture* nTexture) : Rectangle(nRect), texture(nTexture) {} // Why do I need Rectangle rect here?

void Button::Render(SDL_Renderer* renderer) {
	if (!renderer || !texture) return;
	if (texture) SDL_RenderTexture(renderer, texture, nullptr, &rect);
}

bool Button::isClicked(float mouseX, float mouseY) const {
	SDL_FPoint point = { mouseX, mouseY };
	return SDL_PointInRectFloat (&point, &rect);
}
