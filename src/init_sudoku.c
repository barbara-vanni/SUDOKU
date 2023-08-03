#include "fonctions.h"
#include "strsplit.h"
#include <stdio.h>
#include <time.h>

int init_sudoku(sudoku *sudoku_tab)
{
    sudoku_tab->time = time(NULL);
    sudoku_tab->running = TRUE;
    sudoku_tab->cell_fill = 0;
    sudoku_tab->empty_cell_init = 0;
    sudoku_tab->almost_finish = 0;

    for (int i = 0; i < 9; i++)
    {
        for (int j = 0; j < 9; j++)
        {
            sudoku_tab->grid[i][j] = 0;
        }
    }

    shuffle_range(sudoku_tab);
    solver(sudoku_tab, sudoku_tab->grid, 0);
    for (int i = 0; i < 9; i++)
    {
        for (int j = 0; j < 9; j++)
        {
            sudoku_tab->gridvalid[i][j] = sudoku_tab->grid[i][j];
        }
    }
    remove_numbers(sudoku_tab);
    sudoku_tab->finish = FALSE;
    return 0;
}

int grille_valid(sudoku *sudoku_tab)
{

    for (int i = 0; i < 9; i++)
    {
        for (int j = 0; j < 9; j++)
        {
            if (sudoku_tab->grid[i][j] != sudoku_tab->gridvalid[i][j])
            {
                return FALSE;
            }
        }
    }
    return TRUE;
}
