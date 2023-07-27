#include "fonctions.h"
#include "strsplit.h"
#include <stdio.h>

int solver(sudoku *sudoku_tab)
{
    int x = 0;
    int y = 0;

    if (case_vide(sudoku_tab->grid, &x, &y) == FALSE)
    {
        return TRUE;
    }

    for (int n = 0; n < 9; n++)
    {
        if (test_chiffre(sudoku_tab->range[n], sudoku_tab->grid, x, y) == TRUE)
        {
           sudoku_tab->grid[x][y] = sudoku_tab->range[n];

            if (solver(sudoku_tab) == TRUE)
            {
                return TRUE;
            }

            sudoku_tab->grid[x][y] = 0;
        }
    }
    return FALSE;
}
