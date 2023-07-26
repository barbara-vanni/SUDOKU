#ifndef FONCTIONS_H
#define FONCTIONS_H


typedef struct s_sudoku
{

    int             range[9];
    int             grid[9][9];
    int             gridClone[9][9];
    int             gridass[9][9][9];
}                   sudoku;

/*
**  Trouve une case vide
*/
int case_vide(int grid[9][9], int *x, int *y);

int test_chiffre(int n, sudoku *sudoku_tab, int x, int y);

int solver(sudoku *sudoku_tab);

void shuffle_range(sudoku *sudoku_tab);

void remove_numbers(sudoku *sudoku_tab, int clean_numb);

int idiot_solver(sudoku *sudoku_tab);

int gridass (sudoku *sudoku_tab);

int celib_nu (sudoku *sudoku_tab);

int celib_cache (sudoku *sudoku_tab);

int segment (sudoku *sudoku_tab);


#endif