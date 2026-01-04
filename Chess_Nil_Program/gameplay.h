#pragma once
#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>
#include <iostream>
#include "rectangle.h"
#include "button.h"
#include <vector>

std::vector<std::vector<Rectangle>> CreateBoard(); // Should this be a 2D vector of buttons?
void DrawBoard(SDL_Renderer *renderer, const std::vector<std::vector<Rectangle>>& board);
void Gameplay();