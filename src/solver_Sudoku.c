#include "fonctions.h"
#include "strsplit.h"
#include <stdio.h>

int solver(sudoku *sudoku_tab, int grid[9][9], int count)
{
    int x = 0;
    int y = 0;

    if (case_vide(grid, &x, &y) == FALSE)
    {
        return count+1;
    }

    for (int n = 0; n < 9; n++)
    {
        if (test_chiffre(sudoku_tab->range[n], grid, x, y) == TRUE)
        {
            grid[x][y] = sudoku_tab->range[n];

            if ((count = solver(sudoku_tab, grid, count)) > 1)
            {
                return count;
            }

            grid[x][y] = 0;
        }
    }
    return count;
}
