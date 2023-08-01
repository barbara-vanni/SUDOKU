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
	if (grille_valid(sudoku_tab) == TRUE)
	{
		// printf("nickel\n");
		sudoku_tab->finish = TRUE;
	}
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
					const SDL_Point click = {events.motion.x,events.motion.y};
					const SDL_Rect butt = {WINDOW_WIDTH - MENU_SIZE / 2 - BUTTON_WIDTH / 2, GRID_SIZE - BUTTON_HEIGHT, BUTTON_WIDTH, BUTTON_HEIGHT};

					if (SDL_PointInRect(&click, &butt) == SDL_TRUE)
					{
						init_sudoku(sudoku_tab);
					}
				}
				break;

			case SDL_KEYDOWN:
				if (events.key.keysym.sym >= SDLK_1 && events.key.keysym.sym <= SDLK_9)
				{
					if (sudoku_tab->grid[sudoku_tab->selectedCellY][sudoku_tab->selectedCellX] == 0)
					{
						num_grid(sudoku_tab, events.key.keysym.sym - SDLK_0);
					}
				}
				else if (events.key.keysym.sym >= 1073741913 && events.key.keysym.sym <= 1073741921)
				{
					if (sudoku_tab->grid[sudoku_tab->selectedCellY][sudoku_tab->selectedCellX] == 0)
					{
						num_grid(sudoku_tab, events.key.keysym.sym - 1073741912);
					}
				}
				else if (events.key.keysym.sym == SDLK_DELETE || events.key.keysym.sym == SDLK_BACKSPACE)
				{
					if (sudoku_tab->gridClone[sudoku_tab->selectedCellY][sudoku_tab->selectedCellX] == 0)
					{
						sudoku_tab->grid[sudoku_tab->selectedCellY][sudoku_tab->selectedCellX] = 0;
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
				if (sudoku_tab->grid[x][y] != 0)
				{
					SDL_Rect rect = {y * CELL_SIZE + CELL_MARGIN, x * CELL_SIZE + CELL_MARGIN, FONT_SIZE, FONT_SIZE};
					SDL_RenderCopy(sudoku_tab->renderer, sudoku_tab->cellTextures[sudoku_tab->grid[x][y] - 1], NULL, &rect);
				}
			}
		}

		// affichage button start
		SDL_SetRenderDrawColor(sudoku_tab->renderer, 0, 0, 0, 0);
		const SDL_Rect butt = {WINDOW_WIDTH - MENU_SIZE / 2 - BUTTON_WIDTH / 2, GRID_SIZE - BUTTON_HEIGHT, BUTTON_WIDTH, BUTTON_HEIGHT};
		SDL_RenderCopy(sudoku_tab->renderer, sudoku_tab->button_start, NULL, &butt);

		// affichage button finish
		SDL_SetRenderDrawColor(sudoku_tab->renderer, 0, 0, 0, 0);
		const SDL_Rect butt_fini = {GRID_SIZE + CELL_MARGIN, 0, MENU_SIZE - CELL_MARGIN - BUTTON_WIDTH/2, BUTTON_HEIGHT};
		SDL_RenderCopy(sudoku_tab->renderer, sudoku_tab->button_finish, NULL, &butt_fini);

		if (sudoku_tab->finish == FALSE && sudoku_tab->running == TRUE)
		{
			sudoku_tab->time_deux = time(NULL);
			unsigned long long int t = difftime(sudoku_tab->time_deux, sudoku_tab->time);
			// printf("%s \r", asctime(gmtime(&t)));
			struct tm *time_info;
			char timeString[9];

			time_info = localtime(&t);
			strftime(timeString, sizeof(timeString), "%M:%S", time_info);
			SDL_Surface *timer_Surface = TTF_RenderText_Blended(sudoku_tab->font, timeString, (SDL_Color){150, 0, 0, 255});
			SDL_Texture *timer_Texture = SDL_CreateTextureFromSurface(sudoku_tab->renderer, timer_Surface);

			SDL_Rect timerrect = {WINDOW_WIDTH - MENU_SIZE / 2 - 45, (CELL_SIZE - 25) , 80, 50};
			SDL_RenderCopy(sudoku_tab->renderer, timer_Texture, NULL, &timerrect);

			SDL_FreeSurface(timer_Surface);
			SDL_DestroyTexture(timer_Texture);

			printf("%s \r", timeString);
		}

		if (sudoku_tab->finish == TRUE)
		{
			SDL_Rect rect = {0, GRID_SIZE / 2 - FONT_SIZE / 2, GRID_SIZE, FONT_SIZE * 2};
			SDL_RenderCopy(sudoku_tab->renderer, sudoku_tab->victoire, NULL, &rect);
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
