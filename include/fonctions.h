#ifndef FONCTIONS_H
#define FONCTIONS_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <time.h>

#define CELL_SIZE 80
#define CELL_MARGIN 6
#define GRID_SIZE (CELL_SIZE * 9)
#define FONT_SIZE (CELL_SIZE - CELL_MARGIN * 2)
#define MENU_SIZE (CELL_SIZE * 3)
#define WINDOW_WIDTH (GRID_SIZE + MENU_SIZE)
#define WINDOW_HEIGHT (GRID_SIZE)

typedef struct s_sudoku
{
    SDL_Window *window;
    SDL_Renderer *renderer;
    SDL_Texture *gridTexture;
    SDL_Texture *cellTextures[9];
    SDL_Texture *victoire;
    // SDL_texture *defaite;
    int gridPos[9];

    int range[9];
    int grid[9][9];
    int gridClone[9][9];
    int gridvalid[9][9];
    int gridass[9][9][9];

    int selectedCellX;
    int selectedCellY;
    int millisec;
    TTF_Font *font;
    int finish;
    time_t time;
    time_t time_deux;

} sudoku;

/*
**  Trouve une case vide
*/
int case_vide(int grid[9][9], int *x, int *y);

int test_chiffre(int n, int grid[9][9], int x, int y);

int solver(sudoku *sudoku_tab, int grid[9][9], int count);

void shuffle_range(sudoku *sudoku_tab);

void remove_numbers(sudoku *sudoku_tab, int clean_numb);

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

#endif