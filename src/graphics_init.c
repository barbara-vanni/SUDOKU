#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <stdio.h>
#include <stdlib.h>
#include "fonctions.h"

void init_grid_surface(sudoku *sudoku_tab)
{
    

}

void initGraphics(sudoku *sudoku_tab)
{
    SDL_Init(SDL_INIT_VIDEO);
    TTF_Init();
    sudoku_tab->window = SDL_CreateWindow("sudoku", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN);
    sudoku_tab->renderer = SDL_CreateRenderer(sudoku_tab->window, -1, SDL_RENDERER_ACCELERATED);
	init_grid_surface(sudoku_tab);
    // init_font(sudoku_tab);
}

void quitGraphics(sudoku *sudoku_tab)
{
	SDL_DestroyRenderer(sudoku_tab->renderer);
	SDL_DestroyWindow(sudoku_tab->window);
	// SDL_DestroyTexture(sudoku_tab->gridTexture);
	TTF_Quit();
	SDL_Quit();
    // SDL_DestroyTexture(sudoku_tab->cellTextures[i]);
}
