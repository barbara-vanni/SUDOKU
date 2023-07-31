#include "fonctions.h"
#include "strsplit.h"
#include <stdio.h>
#include <time.h>


int init_sudoku(sudoku *sudoku_tab)
{
    sudoku_tab->time = time(NULL);
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
    remove_numbers(sudoku_tab, 1);
    sudoku_tab->finish = FALSE;
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
