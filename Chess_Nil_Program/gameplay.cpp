#include "gameplay.h"
#include "rectangle.h"

std::vector<std::vector<Rectangle>> CreateBoard() {

	std::vector<std::vector<Rectangle>> board; // Maybe this should be a vector of structs

	SDL_Color light = { 240, 217, 181, 255 };
	SDL_Color dark = { 181, 136, 99, 255 };

	float xPosition = 0.0f;
	float yPosition = 0.0f;
	float squareWidth = 50.0f;
	float squareHeight = 50.0f;

	for (int i = 0; i < 8; i++)
	{
		xPosition = 0.0f;
		std::vector<Rectangle> rows;
		for (int j = 0; j < 8; j++)
		{
			SDL_FRect rect = {xPosition, yPosition, squareWidth, squareHeight};
			if (i % 2 == 0)
			{
				SDL_Color color = (j % 2 == 0) ? light : dark;
				Rectangle square(rect, color);
				rows.push_back(square);
			}
			else {
				SDL_Color color = (j % 2 == 1) ? light : dark;
				Rectangle square(rect, color);
				rows.push_back(square);
			}
			xPosition += squareWidth;
		}
		board.push_back(rows);
		yPosition += squareHeight;
	}

	return board;
}

void DrawBoard(SDL_Renderer* renderer, const std::vector<std::vector<Rectangle>>& board) {

	for (const auto& row : board) {
		for (const auto& square : row) {
			square.Render(renderer);
		}
	}

}