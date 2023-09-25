#include <fonctions.h>
#include <display.h>
#include <SDL2/SDL.h>
#include <stdio.h>
#include "strsplit.h"


int affichage_timer(sudoku* sudoku_tab)
{
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
}