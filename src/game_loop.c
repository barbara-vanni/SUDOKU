#include <SDL2/SDL.h>
#include "fonctions.h"
#include "strsplit.h"

int mainloop(sudoku *sudoku_tab)
{
    SDL_Event events;
    int quit = 0;

	

    while (!quit)
    {
        while (SDL_PollEvent(&events))
		{
			if (events.type == SDL_QUIT)
				quit = 1;
			else if (events.type == SDL_MOUSEMOTION)
			{
				int x, y;
				SDL_GetMouseState(&x, &y);
				for (int i = 0; i < 9; i++)
				{
					if (x > sudoku_tab->gridPos[i] && x < sudoku_tab->gridPos[i] + CELL_SIZE)
					{
						sudoku_tab->selectedCellX = i;
					}
					if (y > sudoku_tab->gridPos[i] && y < sudoku_tab->gridPos[i] + CELL_SIZE)
					{
						sudoku_tab->selectedCellY = i;
					}
				}
			}
		}
	

	SDL_Point pointA;
	pointA.x = 0;
	pointA.y = 0;

	SDL_Point pointB;
	pointB.x = WINDOW_WIDTH;
	pointB.y = WINDOW_HEIGHT;

	// SDL_Rect rectangle = {WINDOW_WIDTH/2, WINDOW_HEIGHT/2, 300, 100};

	// 	rectangle.x = WINDOW_WIDTH / 2 - rectangle.w / 2;
	// 	rectangle.y = WINDOW_HEIGHT / 2 - rectangle.h / 2;

		SDL_SetRenderDrawColor(sudoku_tab->renderer, 30, 30, 30, 30);
        SDL_RenderClear(sudoku_tab->renderer);

		SDL_SetRenderDrawColor(sudoku_tab->renderer, 160, 232, 163, 91);
        // SDL_RenderDrawRect(sudoku_tab->renderer, &rectangle);

    	for (int g = 1; g < 9; g ++) 
		{
        	SDL_RenderDrawLine(sudoku_tab->renderer, g * CELL_SIZE, 0, g * CELL_SIZE, WINDOW_HEIGHT);
    	}
		for (int h = 1; h < 9; h ++)
		{
        	SDL_RenderDrawLine(sudoku_tab->renderer, 0, h * CELL_SIZE, WINDOW_WIDTH, h * CELL_SIZE);
		}

		SDL_SetRenderDrawColor(sudoku_tab->renderer, 255, 255, 255, 255);
   	 	for (int i = CELL_SIZE * 3; i < WINDOW_WIDTH; i += CELL_SIZE * 3) 
		{
        	SDL_Rect rect = { i, 0, 3, WINDOW_HEIGHT };
        	SDL_RenderFillRect(sudoku_tab->renderer, &rect);
    	}

    	for (int i = CELL_SIZE * 3; i < WINDOW_HEIGHT; i += CELL_SIZE * 3)
		{
        	SDL_Rect rect = { 0, i, WINDOW_WIDTH, 3 };
        	SDL_RenderFillRect(sudoku_tab->renderer, &rect);
    	}

		// SDL_RenderDrawLine(sudoku_tab->renderer, pointA.x, pointA.y, pointB.x, pointB.y/3);
		// SDL_RenderDrawPoint(sudoku_tab->renderer, (WINDOW_WIDTH/2), (WINDOW_HEIGHT/2));
        SDL_RenderPresent(sudoku_tab->renderer);
		// draw_grid(sudoku_tab);
	}
    return FALSE;
}
