#include <fonctions.h>
#include <display.h>
#include <SDL2/SDL.h>
#include <stdio.h>
#include "strsplit.h"

// Fonction pour afficher les boutons de niveau
// void render_level_buttons(sudoku* sudoku_tab) {
//     if (sudoku_tab->almost_start >= 1 && sudoku_tab->almost_start <= 5) {
//         const int level = sudoku_tab->almost_start;
//         const SDL_Rect level_rect = {MID_MENU_SIZE - 54.5, WINDOW_HEIGHT - 104 * level - 18 * level, 109, 164};
//         SDL_RenderCopy(sudoku_tab->renderer, sudoku_tab->levels[&level - 1], NULL, &level_rect);
//     }
// }

int affichage_level(sudoku* sudoku_tab)
{
    // bouton niveau de 1 à 5
		if (sudoku_tab->almost_start == 1)
		{
			const SDL_Rect level_one = {MID_MENU_SIZE - 34.5, WINDOW_HEIGHT - 104, 69, 104};
			SDL_RenderCopy(sudoku_tab->renderer, sudoku_tab->level_1, NULL, &level_one);
			const SDL_Rect level_two = {MID_MENU_SIZE - 41.5, WINDOW_HEIGHT - 218, 83, 124};
			SDL_RenderCopy(sudoku_tab->renderer, sudoku_tab->level_2, NULL, &level_two);
			const SDL_Rect level_three = {MID_MENU_SIZE - 48, WINDOW_HEIGHT - 362, 96, 144};
			SDL_RenderCopy(sudoku_tab->renderer, sudoku_tab->level_3, NULL, &level_three);
			const SDL_Rect level_four = {MID_MENU_SIZE - 54.5, WINDOW_HEIGHT - 526, 109, 164};
			SDL_RenderCopy(sudoku_tab->renderer, sudoku_tab->level_4, NULL, &level_four);
			const SDL_Rect level_five = {MID_MENU_SIZE - 54.5, WINDOW_HEIGHT - 690, 109, 164};
			SDL_RenderCopy(sudoku_tab->renderer, sudoku_tab->level_5, NULL, &level_five);
		}

		if (sudoku_tab->almost_start == 3)
		{
			// affichage button start
			const SDL_Rect level_1 = {MID_MENU_SIZE - 54.5, WINDOW_HEIGHT - 164, 109, 164};
			SDL_RenderCopy(sudoku_tab->renderer, sudoku_tab->level_1, NULL, &level_1);
			// affichage button finish
			const SDL_Rect butt_fini = {GRID_SIZE + CELL_MARGIN, 5, MENU_SIZE - CELL_MARGIN - BUTTON_WIDTH / 2, BUTTON_HEIGHT};
			SDL_RenderCopy(sudoku_tab->renderer, sudoku_tab->button_finish, NULL, &butt_fini);
		}
		if (sudoku_tab->almost_start == 4)
		{
			// affichage button start
			const SDL_Rect level_2 = {MID_MENU_SIZE - 54.5, WINDOW_HEIGHT - 164, 109, 164};
			SDL_RenderCopy(sudoku_tab->renderer, sudoku_tab->level_2, NULL, &level_2);
			// affichage button finish
			const SDL_Rect butt_fini = {GRID_SIZE + CELL_MARGIN, 5, MENU_SIZE - CELL_MARGIN - BUTTON_WIDTH / 2, BUTTON_HEIGHT};
			SDL_RenderCopy(sudoku_tab->renderer, sudoku_tab->button_finish, NULL, &butt_fini);
		}
		if (sudoku_tab->almost_start == 5)
		{
			// affichage button start
			const SDL_Rect level_3 = {MID_MENU_SIZE - 54.5, WINDOW_HEIGHT - 164, 109, 164};
			SDL_RenderCopy(sudoku_tab->renderer, sudoku_tab->level_3, NULL, &level_3);
			// affichage button finish
			const SDL_Rect butt_fini = {GRID_SIZE + CELL_MARGIN, 5, MENU_SIZE - CELL_MARGIN - BUTTON_WIDTH / 2, BUTTON_HEIGHT};
			SDL_RenderCopy(sudoku_tab->renderer, sudoku_tab->button_finish, NULL, &butt_fini);
		}
		if (sudoku_tab->almost_start == 6)
		{
			// affichage button start
			const SDL_Rect level_4 = {MID_MENU_SIZE - 54.5, WINDOW_HEIGHT - 164, 109, 164};
			SDL_RenderCopy(sudoku_tab->renderer, sudoku_tab->level_4, NULL, &level_4);
			// affichage button finish
			const SDL_Rect butt_fini = {GRID_SIZE + CELL_MARGIN, 5, MENU_SIZE - CELL_MARGIN - BUTTON_WIDTH / 2, BUTTON_HEIGHT};
			SDL_RenderCopy(sudoku_tab->renderer, sudoku_tab->button_finish, NULL, &butt_fini);
		}
		if (sudoku_tab->almost_start == 7)
		{
			// affichage button start
			const SDL_Rect level_5 = {MID_MENU_SIZE - 54.5, WINDOW_HEIGHT - 164, 109, 164};
			SDL_RenderCopy(sudoku_tab->renderer, sudoku_tab->level_5, NULL, &level_5);
			// affichage button finish
			const SDL_Rect butt_fini = {GRID_SIZE + CELL_MARGIN, 5, MENU_SIZE - CELL_MARGIN - BUTTON_WIDTH / 2, BUTTON_HEIGHT};
			SDL_RenderCopy(sudoku_tab->renderer, sudoku_tab->button_finish, NULL, &butt_fini);
		}
}