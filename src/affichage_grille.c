#include <fonctions.h>
#include <display.h>
#include <SDL2/SDL.h>
#include <stdio.h>
#include "strsplit.h"


int affichage_grille(sudoku* sudoku_tab)
{
    // Affichage fond de fenêtre
		SDL_SetRenderDrawColor(sudoku_tab->renderer, 255, 255, 255, 255);
		SDL_RenderClear(sudoku_tab->renderer);

		// Affichage grid
		const SDL_Rect rerect = {0, 0, GRID_SIZE, GRID_SIZE};
		SDL_RenderCopy(sudoku_tab->renderer, sudoku_tab->gridTexture, &rerect, &rerect);
		for (int x = 0; x < 9; x++)
		{
			for (int y = 0; y < 9; y++)
			{
				if (y == sudoku_tab->selectedCellX && x == sudoku_tab->selectedCellY)
				{
					SDL_SetRenderDrawColor(sudoku_tab->renderer, 100, 100, 100, 255);
					SDL_Rect mini_rect = {y * CELL_SIZE, x * CELL_SIZE, CELL_SIZE, CELL_SIZE};
					SDL_RenderFillRect(sudoku_tab->renderer, &mini_rect);
				}

				SDL_Rect rect = {y * CELL_SIZE + CELL_MARGIN, x * CELL_SIZE + CELL_MARGIN, FONT_SIZE, FONT_SIZE};
				if (sudoku_tab->grid[x][y] != 0)
				{
					if (sudoku_tab->gridClone[x][y] != 0)
					{
						SDL_RenderCopy(sudoku_tab->renderer, sudoku_tab->cellTextures[sudoku_tab->grid[x][y] - 1], NULL, &rect);
					}
					else
					{
						SDL_RenderCopy(sudoku_tab->renderer, sudoku_tab->cellTexturesPlayer[sudoku_tab->grid[x][y] - 1], NULL, &rect);

					}
				}
			}
		}
}