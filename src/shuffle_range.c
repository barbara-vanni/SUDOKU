#include <stdlib.h>
#include "fonctions.h"

void shuffle_range(sudoku *sudoku_tab)
{
    int NUMB;
    for (int i = 0; i < 9; i++)
    {
        sudoku_tab->range[i] = i + 1;
    }

    for (int t = 0; t < 9; t++)
    {
        NUMB = rand() % 9;
        int tmp = sudoku_tab->range[t];
        sudoku_tab->range[t] = sudoku_tab->range[NUMB];
        sudoku_tab->range[NUMB] = tmp;
    }
}