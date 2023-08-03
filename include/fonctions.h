#ifndef FONCTIONS_H
#define FONCTIONS_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <time.h>
#include <SDL2/SDL_image.h>

typedef struct s_sudoku
{
    SDL_Window *window;
    SDL_Renderer *renderer;
    SDL_Texture *button_start;
    SDL_Texture *button_finish;
    SDL_Texture *gridTexture;
    SDL_Texture *cellTextures[9];
    SDL_Texture *cellTexturesPlayer[9];
    SDL_Texture *victoire;
    SDL_Texture *verification;
    SDL_Texture *rectification;
    SDL_Texture *defaite;
    SDL_Texture *new_game;
    SDL_Texture *try_again;
    SDL_Texture *level_1;
    SDL_Texture *level_2;
    SDL_Texture *level_3;
    SDL_Texture *level_4;
    SDL_Texture *level_5;
    int gridPos[9];


    int running;
    int selectedCellX;
    int selectedCellY;
    int millisec;
    TTF_Font *font;
    int finish;
    int almost_finish;
    time_t time;
    time_t time_deux;
    int empty_cell_init;
    int cell_fill;
    int last_x;
    int last_y;
    int almost_start;
    int clean_number;

    int range[9];
    int grid[9][9];
    int gridvalid[9][9];
    int gridass[9][9][9];
    int gridClone[9][9];
} sudoku;

/*
**  Trouve une case vide
*/
int case_vide(int grid[9][9], int *x, int *y);

int test_chiffre(int n, int grid[9][9], int x, int y);

int solver(sudoku *sudoku_tab, int grid[9][9], int count);

void shuffle_range(sudoku *sudoku_tab);

void remove_numbers(sudoku *sudoku_tab);

int idiot_solver(sudoku *sudoku_tab);

int gridass(sudoku *sudoku_tab);

int celib_nu(sudoku *sudoku_tab);

int celib_cache(sudoku *sudoku_tab);

int segment(sudoku *sudoku_tab);

int segment_2(sudoku *sudoku_tab);

void initGraphics(sudoku *sudoku_tab);

void quitGraphics(sudoku *sudoku_tab);

int mainloop(sudoku *sudoku_tab);

int init_sudoku(sudoku *sudoku_tab);

int grille_valid(sudoku *sudoku_tab);

int num_grid(sudoku *sudoku_tab, int num);

void button_start(sudoku *sudoku_tab);

void button_finish(sudoku *sudoku_tab);

void message_verification(sudoku *sudoku_tab);

void message_victoire(sudoku *sudoku_tab);

void message_rectification(sudoku *sudoku_tab);

void message_fin_de_partie(sudoku *sudoku_tab);


#endif