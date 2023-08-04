#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "fonctions.h"
#include "strsplit.h"
#include "display.h"
#include <stdio.h>
#include <time.h>

int num_grid(sudoku *sudoku_tab, int num)
{
	sudoku_tab->grid[sudoku_tab->selectedCellY][sudoku_tab->selectedCellX] = num;
	int x, y;
	if (!case_vide(sudoku_tab->grid, &x, &y))
	{
		sudoku_tab->almost_finish = TRUE;
	}
	sudoku_tab->cell_fill++;
	return 0;
}

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
			case SDL_MOUSEBUTTONDOWN:
				event_mouse_button_down(sudoku_tab, &events);
				break;

			case SDL_KEYDOWN:
				event_keydown(sudoku_tab, &events);
				break;
			}
		}
		
		affichage_grille(sudoku_tab);
		affichage_level(sudoku_tab);

		
		if (sudoku_tab->almost_start == 0)
		{
			// affichage button start
			const SDL_Rect butt = {MID_MENU_SIZE - 54.5, WINDOW_HEIGHT - 164, 109, 164};
			SDL_RenderCopy(sudoku_tab->renderer, sudoku_tab->button_start, NULL, &butt);
			// affichage button finish
			const SDL_Rect butt_fini = {GRID_SIZE + CELL_MARGIN, 5, MENU_SIZE - CELL_MARGIN - BUTTON_WIDTH / 2, BUTTON_HEIGHT};
			SDL_RenderCopy(sudoku_tab->renderer, sudoku_tab->button_finish, NULL, &butt_fini);
		}

		if (sudoku_tab->running)
		{
			sudoku_tab->count++;
			// Affichage Jauge de progression
			const int line_y_end = WINDOW_HEIGHT - 164;
			const int line_max_height = line_y_end - BUTTON_HEIGHT;
			int line_heigt = line_max_height * sudoku_tab->cell_fill / sudoku_tab->empty_cell_init;
			// SDL_SetRenderDrawColor(sudoku_tab->renderer, 255, 127, 0, 0);
			// SDL_Rect jauge = {GRID_SIZE + MENU_SIZE / 2 - 2, line_y_end - line_heigt, 5, line_heigt};
			// SDL_RenderFillRect(sudoku_tab->renderer, &jauge);
			animated_cat(sudoku_tab, line_y_end - line_heigt);
		}

		affichage_timer(sudoku_tab);
		// Bouton de verification
		if (sudoku_tab->almost_finish == TRUE && sudoku_tab->finish == 0)
		{
			SDL_SetRenderDrawColor(sudoku_tab->renderer, 30, 30, 30, 30);
			SDL_Rect verif = {GRID_SIZE + CELL_MARGIN, GRID_SIZE / 2 - FONT_SIZE / 2 - CELL_SIZE, MENU_SIZE - CELL_MARGIN * 2, FONT_SIZE * 2};
			SDL_RenderFillRect(sudoku_tab->renderer, &verif);
			SDL_RenderCopy(sudoku_tab->renderer, sudoku_tab->verification, NULL, &verif);

			SDL_SetRenderDrawColor(sudoku_tab->renderer, 30, 30, 30, 30);
			SDL_Rect rectif = {GRID_SIZE + CELL_MARGIN, GRID_SIZE / 2 - FONT_SIZE / 2 + CELL_SIZE, MENU_SIZE - CELL_MARGIN * 2, FONT_SIZE * 2};
			SDL_RenderFillRect(sudoku_tab->renderer, &rectif);
			SDL_RenderCopy(sudoku_tab->renderer, sudoku_tab->rectification, NULL, &rectif);
		}
		// Message de victoire quand c'est bon
		if (sudoku_tab->finish == 1)
		{
			SDL_SetRenderDrawColor(sudoku_tab->renderer, 30, 30, 30, 30);
			SDL_Rect rect = {0, GRID_SIZE / 2 - FONT_SIZE / 2, GRID_SIZE, FONT_SIZE * 2};
			SDL_RenderFillRect(sudoku_tab->renderer, &rect);
			SDL_RenderCopy(sudoku_tab->renderer, sudoku_tab->victoire, NULL, &rect);

			SDL_SetRenderDrawColor(sudoku_tab->renderer, 30, 30, 30, 30);
			SDL_Rect verif = {GRID_SIZE + CELL_MARGIN, GRID_SIZE / 2 - FONT_SIZE / 2 - CELL_SIZE, MENU_SIZE - CELL_MARGIN * 2, FONT_SIZE * 2};
			SDL_RenderFillRect(sudoku_tab->renderer, &verif);
			SDL_RenderCopy(sudoku_tab->renderer, sudoku_tab->verification, NULL, &verif);

			SDL_SetRenderDrawColor(sudoku_tab->renderer, 30, 30, 30, 30);
			SDL_Rect try_again = {GRID_SIZE + CELL_MARGIN, GRID_SIZE / 2 - FONT_SIZE / 2 + CELL_SIZE, MENU_SIZE - CELL_MARGIN * 2, FONT_SIZE * 2};
			SDL_RenderFillRect(sudoku_tab->renderer, &try_again);
			SDL_RenderCopy(sudoku_tab->renderer, sudoku_tab->try_again, NULL, &try_again);

			SDL_SetRenderDrawColor(sudoku_tab->renderer, 30, 30, 30, 30);
			SDL_Rect new_game = {GRID_SIZE + CELL_MARGIN, GRID_SIZE / 2 - FONT_SIZE / 2 - CELL_SIZE, MENU_SIZE - CELL_MARGIN * 2, FONT_SIZE * 2};
			SDL_RenderFillRect(sudoku_tab->renderer, &new_game);
			SDL_RenderCopy(sudoku_tab->renderer, sudoku_tab->new_game, NULL, &new_game);
		}
		if (sudoku_tab->finish == 2)
		{
			SDL_SetRenderDrawColor(sudoku_tab->renderer, 30, 30, 30, 30);
			SDL_Rect rect = {0, GRID_SIZE / 2 - FONT_SIZE / 2, GRID_SIZE, FONT_SIZE * 2};
			SDL_RenderFillRect(sudoku_tab->renderer, &rect);
			SDL_RenderCopy(sudoku_tab->renderer, sudoku_tab->defaite, NULL, &rect);

			SDL_SetRenderDrawColor(sudoku_tab->renderer, 30, 30, 30, 30);
			SDL_Rect try_again = {GRID_SIZE + CELL_MARGIN, GRID_SIZE / 2 - FONT_SIZE / 2 + CELL_SIZE, MENU_SIZE - CELL_MARGIN * 2, FONT_SIZE * 2};
			SDL_RenderFillRect(sudoku_tab->renderer, &try_again);
			SDL_RenderCopy(sudoku_tab->renderer, sudoku_tab->try_again, NULL, &try_again);

			SDL_SetRenderDrawColor(sudoku_tab->renderer, 30, 30, 30, 30);
			SDL_Rect new_game = {GRID_SIZE + CELL_MARGIN, GRID_SIZE / 2 - FONT_SIZE / 2 - CELL_SIZE, MENU_SIZE - CELL_MARGIN * 2, FONT_SIZE * 2};
			SDL_RenderFillRect(sudoku_tab->renderer, &new_game);
			SDL_RenderCopy(sudoku_tab->renderer, sudoku_tab->new_game, NULL, &new_game);
		}

		SDL_RenderPresent(sudoku_tab->renderer);
	}
	return FALSE;
}
