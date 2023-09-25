#include <fonctions.h>
#include <display.h>
#include <SDL2/SDL.h>
#include <stdio.h>
#include "strsplit.h"


int event_keydown(sudoku *sudoku_tab, SDL_Event *events)
{
    if (events->key.keysym.sym >= SDLK_1 && events->key.keysym.sym <= SDLK_9)
				{
					if (sudoku_tab->grid[sudoku_tab->selectedCellY][sudoku_tab->selectedCellX] == 0)
					{
						sudoku_tab->last_x = sudoku_tab->selectedCellX;
						sudoku_tab->last_y = sudoku_tab->selectedCellY;
						num_grid(sudoku_tab, events->key.keysym.sym - SDLK_0);
					}
				}
				else if (events->key.keysym.sym >= 1073741913 && events->key.keysym.sym <= 1073741921)
				{
					if (sudoku_tab->grid[sudoku_tab->selectedCellY][sudoku_tab->selectedCellX] == 0)
					{
						sudoku_tab->last_x = sudoku_tab->selectedCellX;
						sudoku_tab->last_y = sudoku_tab->selectedCellY;
						num_grid(sudoku_tab, events->key.keysym.sym - 1073741912);
					}
				}
				else if ((events->key.keysym.sym == SDLK_DELETE || events->key.keysym.sym == SDLK_BACKSPACE) && sudoku_tab->almost_finish == 0)
				{
					if (sudoku_tab->gridClone[sudoku_tab->selectedCellY][sudoku_tab->selectedCellX] == 0 && sudoku_tab->grid[sudoku_tab->selectedCellY][sudoku_tab->selectedCellX] != 0)
					{
						sudoku_tab->grid[sudoku_tab->selectedCellY][sudoku_tab->selectedCellX] = 0;
						sudoku_tab->cell_fill--;
					}
				}

				else if (events->key.keysym.sym == SDLK_SPACE)
				{
					init_sudoku(sudoku_tab);
				}
}