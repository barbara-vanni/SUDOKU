#include <SDL2/SDL.h>
#include "fonctions.h"
#include "strsplit.h"
#include <stdio.h>
int mainloop(sudoku *sudoku_tab)
{
	SDL_Event events;
	int quit = 0;

	while (!quit)
	{
		while (SDL_PollEvent(&events))
		{
			switch (events.type)
			{
			case SDL_QUIT:
				quit = 1;
				break;
			case SDL_MOUSEMOTION:
				int x, y;
				SDL_GetMouseState(&x, &y);
				sudoku_tab->selectedCellX = x / CELL_SIZE;
				sudoku_tab->selectedCellY = y / CELL_SIZE;
				break;

			case SDL_KEYDOWN:
				if (events.key.keysym.sym >= SDLK_1 && events.key.keysym.sym <= SDLK_9)
				{
					if (sudoku_tab->grid[sudoku_tab->selectedCellY][sudoku_tab->selectedCellX] == 0)
					{
						sudoku_tab->grid[sudoku_tab->selectedCellY][sudoku_tab->selectedCellX] = events.key.keysym.sym - SDLK_0;
					}
				}
				else if (events.key.keysym.sym >= 1073741913 && events.key.keysym.sym <= 1073741921)
				{
					if (sudoku_tab->grid[sudoku_tab->selectedCellY][sudoku_tab->selectedCellX] == 0)
					{
						sudoku_tab->grid[sudoku_tab->selectedCellY][sudoku_tab->selectedCellX] = events.key.keysym.sym - 1073741912;
					}
				}
				else if (events.key.keysym.sym == SDLK_DELETE || events.key.keysym.sym == SDLK_BACKSPACE)
				{
					sudoku_tab->grid[sudoku_tab->selectedCellY][sudoku_tab->selectedCellX] = 0;
				}
				break;
			}
		}
		// SDL_SetRenderDrawColor(sudoku_tab->renderer, 255, 255, 255, 255);
		SDL_RenderClear(sudoku_tab->renderer);
		SDL_RenderCopy(sudoku_tab->renderer, sudoku_tab->gridTexture, NULL, NULL);
		for (int x = 0; x < 9; x++)
		{
			for (int y = 0; y < 9; y++)
			{
				if (x == sudoku_tab->selectedCellX && y == sudoku_tab->selectedCellY)
				{
					SDL_SetRenderDrawColor(sudoku_tab->renderer, 100, 100, 100, 255);
					SDL_Rect mini_rect = {x * CELL_SIZE, y * CELL_SIZE, CELL_SIZE, CELL_SIZE};
					SDL_RenderFillRect(sudoku_tab->renderer, &mini_rect);
				}
				if (sudoku_tab->grid[x][y] != 0)
				{
					SDL_Rect rect = {y * CELL_SIZE + CELL_MARGIN, x * CELL_SIZE + CELL_MARGIN, FONT_SIZE, FONT_SIZE};
					SDL_RenderCopy(sudoku_tab->renderer, sudoku_tab->cellTextures[sudoku_tab->grid[x][y] - 1], NULL, &rect);
				}
			}
		}
		SDL_RenderPresent(sudoku_tab->renderer);

		// SDL_Rect rectangle = {WINDOW_WIDTH/2, WINDOW_HEIGHT/2, 300, 100};

		// 	rectangle.x = WINDOW_WIDTH / 2 - rectangle.w / 2;
		// 	rectangle.y = WINDOW_HEIGHT / 2 - rectangle.h / 2;
		// SDL_RenderDrawRect(sudoku_tab->renderer, &rectangle);

		// SDL_RenderDrawLine(sudoku_tab->renderer, pointA.x, pointA.y, pointB.x, pointB.y/3);
		// SDL_RenderDrawPoint(sudoku_tab->renderer, (WINDOW_WIDTH/2), (WINDOW_HEIGHT/2));
		// draw_grid(sudoku_tab);
	}
	return FALSE;
}
