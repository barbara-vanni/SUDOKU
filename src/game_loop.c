#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "fonctions.h"
#include "strsplit.h"
#include "display.h"
#include <stdio.h>
#include <time.h>

int num_grid(sudoku *sudoku_tab, int num)
{
	// if (sudoku_tab->almost_finish == TRUE)
	// {
	// 	return FALSE;
	// }
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
				if (events.button.button == SDL_BUTTON_LEFT)
				{
					const SDL_Point click = {events.motion.x, events.motion.y};
					const SDL_Rect butt = {MID_MENU_SIZE - 54.5, WINDOW_HEIGHT - 164, 109, 164};
					SDL_Rect verif = {GRID_SIZE + CELL_MARGIN, GRID_SIZE / 2 - FONT_SIZE / 2 - CELL_SIZE, MENU_SIZE - CELL_MARGIN * 2, FONT_SIZE * 2};
					SDL_Rect rectif = {GRID_SIZE + CELL_MARGIN, GRID_SIZE / 2 - FONT_SIZE / 2 + CELL_SIZE, MENU_SIZE - CELL_MARGIN * 2, FONT_SIZE * 2};
					SDL_Rect try_again = {GRID_SIZE + CELL_MARGIN, GRID_SIZE / 2 - FONT_SIZE / 2 + CELL_SIZE, MENU_SIZE - CELL_MARGIN * 2, FONT_SIZE * 2};
					SDL_Rect new_game = {GRID_SIZE + CELL_MARGIN, GRID_SIZE / 2 - FONT_SIZE / 2 - CELL_SIZE, MENU_SIZE - CELL_MARGIN * 2, FONT_SIZE * 2};
					const SDL_Rect level_one = {MID_MENU_SIZE - 34.5, WINDOW_HEIGHT - 104, 69, 104};
					const SDL_Rect level_two = {MID_MENU_SIZE - 41.5, WINDOW_HEIGHT - 218, 83, 124};
					const SDL_Rect level_three = {MID_MENU_SIZE - 48, WINDOW_HEIGHT - 362, 96, 144};
					const SDL_Rect level_four = {MID_MENU_SIZE - 54.5, WINDOW_HEIGHT - 526, 109, 164};
					const SDL_Rect level_five = {MID_MENU_SIZE - 54.5, WINDOW_HEIGHT - 690, 109, 164};

					if (SDL_PointInRect(&click, &level_one) == SDL_TRUE && sudoku_tab->almost_start == 1)
					{
						sudoku_tab->clean_number = 15;
						init_sudoku(sudoku_tab);
						sudoku_tab->almost_start = 3;
					}
					if (SDL_PointInRect(&click, &level_two) == SDL_TRUE && sudoku_tab->almost_start == 1)
					{
						sudoku_tab->clean_number = 30;
						init_sudoku(sudoku_tab);
						sudoku_tab->almost_start = 4;
					}
					if (SDL_PointInRect(&click, &level_three) == SDL_TRUE && sudoku_tab->almost_start == 1)
					{
						sudoku_tab->clean_number = 45;
						init_sudoku(sudoku_tab);
						sudoku_tab->almost_start = 5;
					}
					if (SDL_PointInRect(&click, &level_four) == SDL_TRUE && sudoku_tab->almost_start == 1)
					{
						sudoku_tab->clean_number = 60;
						init_sudoku(sudoku_tab);
						sudoku_tab->almost_start = 6;
					}
					if (SDL_PointInRect(&click, &level_five) == SDL_TRUE && sudoku_tab->almost_start == 1)
					{
						sudoku_tab->clean_number = 75;
						init_sudoku(sudoku_tab);
						sudoku_tab->almost_start = 7;
					}

					if (SDL_PointInRect(&click, &butt) == SDL_TRUE && sudoku_tab->almost_start == 0)
					{
						sudoku_tab->almost_start = 1;
					}

					if (sudoku_tab->finish > 0 && SDL_PointInRect(&click, &new_game) == SDL_TRUE)
					{
						sudoku_tab->almost_start = 1;
					}

					if (sudoku_tab->finish > 0 && SDL_PointInRect(&click, &try_again) == SDL_TRUE)
					{
						sudoku_tab->time = time(NULL);
						sudoku_tab->finish = 0;
						sudoku_tab->almost_finish = 0;
						sudoku_tab->cell_fill = 0;
						for (int i = 0; i < 9; i++)
						{
							for (int j = 0; j < 9; j++)
							{
								sudoku_tab->grid[i][j] = sudoku_tab->gridClone[i][j];
							}
						}
					}

					if (sudoku_tab->almost_finish == 1 && SDL_PointInRect(&click, &verif) == SDL_TRUE)
					{
						if (grille_valid(sudoku_tab))
						{

							sudoku_tab->finish = 1;
						}
						else
						{
							sudoku_tab->finish = 2;
						}
					}

					if (sudoku_tab->almost_finish == 1 && SDL_PointInRect(&click, &rectif) == SDL_TRUE)
					{
						sudoku_tab->grid[sudoku_tab->last_y][sudoku_tab->last_x] = 0;
						sudoku_tab->cell_fill--;
						sudoku_tab->almost_finish = FALSE;
					}

					if (sudoku_tab->almost_start >= 2 && SDL_PointInRect(&click, &level_one) == SDL_TRUE)
					{

						sudoku_tab->almost_start = 0;
						init_sudoku(sudoku_tab);
					}
				}
				break;

			case SDL_KEYDOWN:
				if (events.key.keysym.sym >= SDLK_1 && events.key.keysym.sym <= SDLK_9)
				{
					if (sudoku_tab->grid[sudoku_tab->selectedCellY][sudoku_tab->selectedCellX] == 0)
					{
						sudoku_tab->last_x = sudoku_tab->selectedCellX;
						sudoku_tab->last_y = sudoku_tab->selectedCellY;
						num_grid(sudoku_tab, events.key.keysym.sym - SDLK_0);
					}
				}
				else if (events.key.keysym.sym >= 1073741913 && events.key.keysym.sym <= 1073741921)
				{
					if (sudoku_tab->grid[sudoku_tab->selectedCellY][sudoku_tab->selectedCellX] == 0)
					{
						sudoku_tab->last_x = sudoku_tab->selectedCellX;
						sudoku_tab->last_y = sudoku_tab->selectedCellY;
						num_grid(sudoku_tab, events.key.keysym.sym - 1073741912);
					}
				}
				else if ((events.key.keysym.sym == SDLK_DELETE || events.key.keysym.sym == SDLK_BACKSPACE) && sudoku_tab->almost_finish == 0)
				{
					if (sudoku_tab->gridClone[sudoku_tab->selectedCellY][sudoku_tab->selectedCellX] == 0 && sudoku_tab->grid[sudoku_tab->selectedCellY][sudoku_tab->selectedCellX] != 0)
					{
						sudoku_tab->grid[sudoku_tab->selectedCellY][sudoku_tab->selectedCellX] = 0;
						sudoku_tab->cell_fill--;
					}
				}

				else if (events.key.keysym.sym == SDLK_SPACE)
				{
					init_sudoku(sudoku_tab);
				}

				break;
			}
		}

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
						// SDL_SetRenderDrawColor(sudoku_tab->renderer, 150, 150, 150, 255);
						// SDL_Rect mini_recta = {y * CELL_SIZE + 5, x * CELL_SIZE + 5, FONT_SIZE, FONT_SIZE};
						// SDL_RenderFillRect(sudoku_tab->renderer, &mini_recta);
						// SDL_RenderCopy(sudoku_tab->renderer, sudoku_tab->cellTextures[sudoku_tab->grid[x][y] - 1], NULL, &mini_recta);
					}
				}
			}
		}

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
			SDL_SetRenderDrawColor(sudoku_tab->renderer, 0, 0, 0, 0);
			const SDL_Rect level_1 = {MID_MENU_SIZE - 54.5, WINDOW_HEIGHT - 164, 109, 164};
			SDL_RenderCopy(sudoku_tab->renderer, sudoku_tab->level_1, NULL, &level_1);
			// affichage button finish
			SDL_SetRenderDrawColor(sudoku_tab->renderer, 0, 0, 0, 0);
			const SDL_Rect butt_fini = {GRID_SIZE + CELL_MARGIN, 5, MENU_SIZE - CELL_MARGIN - BUTTON_WIDTH / 2, BUTTON_HEIGHT};
			SDL_RenderCopy(sudoku_tab->renderer, sudoku_tab->button_finish, NULL, &butt_fini);
		}
		if (sudoku_tab->almost_start == 4)
		{
			// affichage button start
			SDL_SetRenderDrawColor(sudoku_tab->renderer, 0, 0, 0, 0);
			const SDL_Rect level_2 = {MID_MENU_SIZE - 54.5, WINDOW_HEIGHT - 164, 109, 164};
			SDL_RenderCopy(sudoku_tab->renderer, sudoku_tab->level_2, NULL, &level_2);
			// affichage button finish
			SDL_SetRenderDrawColor(sudoku_tab->renderer, 0, 0, 0, 0);
			const SDL_Rect butt_fini = {GRID_SIZE + CELL_MARGIN, 5, MENU_SIZE - CELL_MARGIN - BUTTON_WIDTH / 2, BUTTON_HEIGHT};
			SDL_RenderCopy(sudoku_tab->renderer, sudoku_tab->button_finish, NULL, &butt_fini);
		}
		if (sudoku_tab->almost_start == 5)
		{
			// affichage button start
			SDL_SetRenderDrawColor(sudoku_tab->renderer, 0, 0, 0, 0);
			const SDL_Rect level_3 = {MID_MENU_SIZE - 54.5, WINDOW_HEIGHT - 164, 109, 164};
			SDL_RenderCopy(sudoku_tab->renderer, sudoku_tab->level_3, NULL, &level_3);
			// affichage button finish
			SDL_SetRenderDrawColor(sudoku_tab->renderer, 0, 0, 0, 0);
			const SDL_Rect butt_fini = {GRID_SIZE + CELL_MARGIN, 5, MENU_SIZE - CELL_MARGIN - BUTTON_WIDTH / 2, BUTTON_HEIGHT};
			SDL_RenderCopy(sudoku_tab->renderer, sudoku_tab->button_finish, NULL, &butt_fini);
		}
		if (sudoku_tab->almost_start == 6)
		{
			// affichage button start
			SDL_SetRenderDrawColor(sudoku_tab->renderer, 0, 0, 0, 0);
			const SDL_Rect level_4 = {MID_MENU_SIZE - 54.5, WINDOW_HEIGHT - 164, 109, 164};
			SDL_RenderCopy(sudoku_tab->renderer, sudoku_tab->level_4, NULL, &level_4);
			// affichage button finish
			SDL_SetRenderDrawColor(sudoku_tab->renderer, 0, 0, 0, 0);
			const SDL_Rect butt_fini = {GRID_SIZE + CELL_MARGIN, 5, MENU_SIZE - CELL_MARGIN - BUTTON_WIDTH / 2, BUTTON_HEIGHT};
			SDL_RenderCopy(sudoku_tab->renderer, sudoku_tab->button_finish, NULL, &butt_fini);
		}
		if (sudoku_tab->almost_start == 7)
		{
			// affichage button start
			SDL_SetRenderDrawColor(sudoku_tab->renderer, 0, 0, 0, 0);
			const SDL_Rect level_5 = {MID_MENU_SIZE - 54.5, WINDOW_HEIGHT - 164, 109, 164};
			SDL_RenderCopy(sudoku_tab->renderer, sudoku_tab->level_5, NULL, &level_5);
			// affichage button finish
			SDL_SetRenderDrawColor(sudoku_tab->renderer, 0, 0, 0, 0);
			const SDL_Rect butt_fini = {GRID_SIZE + CELL_MARGIN, 5, MENU_SIZE - CELL_MARGIN - BUTTON_WIDTH / 2, BUTTON_HEIGHT};
			SDL_RenderCopy(sudoku_tab->renderer, sudoku_tab->button_finish, NULL, &butt_fini);
		}
		if (sudoku_tab->almost_start == 0)
		{
			// affichage button start
			SDL_SetRenderDrawColor(sudoku_tab->renderer, 0, 0, 0, 0);
			const SDL_Rect butt = {MID_MENU_SIZE - 54.5, WINDOW_HEIGHT - 164, 109, 164};
			SDL_RenderCopy(sudoku_tab->renderer, sudoku_tab->button_start, NULL, &butt);
			// affichage button finish
			SDL_SetRenderDrawColor(sudoku_tab->renderer, 0, 0, 0, 0);
			const SDL_Rect butt_fini = {GRID_SIZE + CELL_MARGIN, 5, MENU_SIZE - CELL_MARGIN - BUTTON_WIDTH / 2, BUTTON_HEIGHT};
			SDL_RenderCopy(sudoku_tab->renderer, sudoku_tab->button_finish, NULL, &butt_fini);
		}

		if (sudoku_tab->running)
		{
			// Affichage Jauge de progression
			const int line_y_end = WINDOW_HEIGHT - BUTTON_HEIGHT;
			const int line_max_height = line_y_end - BUTTON_HEIGHT;
			int line_heigt = line_max_height * sudoku_tab->cell_fill / sudoku_tab->empty_cell_init;
			SDL_SetRenderDrawColor(sudoku_tab->renderer, 0, 0, 0, 0);
			SDL_Rect jauge = {GRID_SIZE + MENU_SIZE / 2 - 2, line_y_end - line_heigt, 5, line_heigt};
			SDL_RenderFillRect(sudoku_tab->renderer, &jauge);
		}

		// Affichage du timer
		if (sudoku_tab->finish == FALSE && sudoku_tab->running == TRUE)
		{
			sudoku_tab->time_deux = time(NULL);
			unsigned long long int t = difftime(sudoku_tab->time_deux, sudoku_tab->time);
			// printf("%s \r", asctime(gmtime(&t)));
			struct tm *time_info;
			char timeString[9];

			time_info = localtime((time_t *)&t);
			strftime(timeString, sizeof(timeString), "%M:%S", time_info);
			SDL_Surface *timer_Surface = TTF_RenderText_Blended(sudoku_tab->font, timeString, (SDL_Color){150, 0, 0, 255});
			SDL_Texture *timer_Texture = SDL_CreateTextureFromSurface(sudoku_tab->renderer, timer_Surface);

			SDL_Rect timerrect = {WINDOW_WIDTH - MENU_SIZE / 2 - 45, (CELL_SIZE - 25), 80, 50};
			SDL_RenderCopy(sudoku_tab->renderer, timer_Texture, NULL, &timerrect);

			SDL_FreeSurface(timer_Surface);
			SDL_DestroyTexture(timer_Texture);

			// printf("%s \r", timeString);
		}

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
