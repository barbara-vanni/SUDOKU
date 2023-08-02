#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>
#include <stdlib.h>
#include "fonctions.h"
#include "display.h"

void init_grid_surface(sudoku *sudoku_tab)
{
    sudoku_tab->gridTexture = SDL_CreateTexture(sudoku_tab->renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, GRID_SIZE, GRID_SIZE);
    SDL_SetRenderTarget(sudoku_tab->renderer, sudoku_tab->gridTexture);

    SDL_SetRenderDrawColor(sudoku_tab->renderer, 30, 30, 30, 30);
    SDL_RenderClear(sudoku_tab->renderer);

    SDL_SetRenderDrawColor(sudoku_tab->renderer, 160, 232, 163, 91);

    for (int g = 1; g < 9; g++)
    {
        SDL_RenderDrawLine(sudoku_tab->renderer, g * CELL_SIZE, 0, g * CELL_SIZE, GRID_SIZE);
    }
    for (int h = 1; h < 9; h++)
    {
        SDL_RenderDrawLine(sudoku_tab->renderer, 0, h * CELL_SIZE, GRID_SIZE, h * CELL_SIZE);
    }

    SDL_SetRenderDrawColor(sudoku_tab->renderer, 255, 255, 255, 255);
    for (int i = CELL_SIZE * 3; i < GRID_SIZE; i += CELL_SIZE * 3)
    {
        SDL_Rect rect = {i, 0, 3, GRID_SIZE};
        SDL_RenderFillRect(sudoku_tab->renderer, &rect);
    }

    for (int i = CELL_SIZE * 3; i < GRID_SIZE; i += CELL_SIZE * 3)
    {
        SDL_Rect rect = {0, i, GRID_SIZE, 3};
        SDL_RenderFillRect(sudoku_tab->renderer, &rect);
    }

    SDL_SetRenderTarget(sudoku_tab->renderer, NULL);
}

void font_police(sudoku *sudoku_tab)
{
    TTF_Font *font = TTF_OpenFont("Montserrat-BoldItalic.ttf", FONT_SIZE);

    for (int d = 0; d < 9; d++)
    {
        char string[2];
        string[0] = d + '1';
        string[1] = 0;
        SDL_Surface *text = TTF_RenderText_Blended(font, string, (SDL_Color){0, 255, 0, 255});
        sudoku_tab->cellTextures[d] = SDL_CreateTextureFromSurface(sudoku_tab->renderer, text);
        SDL_FreeSurface(text);
        SDL_Surface *texti = TTF_RenderText_Blended(font, string, (SDL_Color){255, 255, 0, 255});
        sudoku_tab->cellTexturesPlayer[d] = SDL_CreateTextureFromSurface(sudoku_tab->renderer, texti);
        SDL_FreeSurface(texti);
    }

    TTF_CloseFont(font);
}

void message_victoire(sudoku *sudoku_tab)
{
    // victoire
    SDL_Surface *text_mess = TTF_RenderText_Blended(sudoku_tab->font, "BRAVO!", (SDL_Color){255, 0, 0, 255});
    sudoku_tab->victoire = SDL_CreateTextureFromSurface(sudoku_tab->renderer, text_mess);
    SDL_FreeSurface(text_mess);
    //  defaite 
    SDL_Surface *text_mess_def = TTF_RenderText_Blended(sudoku_tab->font, "PAS OUF!", (SDL_Color){255, 0, 0, 255});
    sudoku_tab->defaite = SDL_CreateTextureFromSurface(sudoku_tab->renderer, text_mess_def);
    SDL_FreeSurface(text_mess_def);
}

void message_verification(sudoku *sudoku_tab)
{
    SDL_Surface *text_verif = TTF_RenderText_Blended(sudoku_tab->font, "VERIF ?", (SDL_Color){255, 255, 255, 255});
    sudoku_tab->verification = SDL_CreateTextureFromSurface(sudoku_tab->renderer, text_verif);
    SDL_FreeSurface(text_verif);
}

void message_rectification(sudoku *sudoku_tab)
{
    SDL_Surface *text_rectif = TTF_RenderText_Blended(sudoku_tab->font, "RECTIF ?", (SDL_Color){255, 255, 255, 255});
    sudoku_tab->rectification = SDL_CreateTextureFromSurface(sudoku_tab->renderer, text_rectif);
    SDL_FreeSurface(text_rectif);
}


void button_start(sudoku *sudoku_tab)
{
    SDL_Surface *image = IMG_Load("press_start.png");
    sudoku_tab->button_start = SDL_CreateTextureFromSurface(sudoku_tab->renderer, image);
    SDL_FreeSurface(image);
}

void button_finish(sudoku *sudoku_tab)
{
    SDL_Surface *image_finish = IMG_Load("button_finish.png");
    sudoku_tab->button_finish = SDL_CreateTextureFromSurface(sudoku_tab->renderer, image_finish);
    SDL_FreeSurface(image_finish);
}

void initGraphics(sudoku *sudoku_tab)
{
    SDL_Init(SDL_INIT_VIDEO);
    TTF_Init();
    IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG);
    sudoku_tab->font = TTF_OpenFont("Montserrat-ExtraBold.ttf", FONT_SIZE * 2);
    sudoku_tab->window = SDL_CreateWindow("sudoku", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN);
    sudoku_tab->renderer = SDL_CreateRenderer(sudoku_tab->window, -1, SDL_RENDERER_ACCELERATED);
    init_grid_surface(sudoku_tab);
    button_start(sudoku_tab);
    button_finish(sudoku_tab);
    font_police(sudoku_tab);
    message_victoire(sudoku_tab);
    message_verification(sudoku_tab);
    message_rectification(sudoku_tab);
    sudoku_tab->time = time(NULL);
    sudoku_tab->running = 0;
}

void quitGraphics(sudoku *sudoku_tab)
{
    TTF_CloseFont(sudoku_tab->font);
    SDL_DestroyTexture(sudoku_tab->button_start);
    SDL_DestroyTexture(sudoku_tab->button_finish);
    SDL_DestroyTexture(sudoku_tab->verification);
    SDL_DestroyTexture(sudoku_tab->rectification);
    SDL_DestroyTexture(sudoku_tab->gridTexture);
    for (int i = 0; i < 9; i++)
    {
        SDL_DestroyTexture(sudoku_tab->cellTextures[i]);
        SDL_DestroyTexture(sudoku_tab->cellTexturesPlayer[i]);
    }
    SDL_DestroyRenderer(sudoku_tab->renderer);
    SDL_DestroyWindow(sudoku_tab->window);
    IMG_Quit();
    TTF_Quit();
    SDL_Quit();
}
