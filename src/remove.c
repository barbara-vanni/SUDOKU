#include <stdlib.h>
#include "fonctions.h"
#include <stdio.h>
void remove_numbers(sudoku *sudoku_tab, int clean_numb)
{
    int EMPTY_x;
    int EMPTY_y;

    for (int a = 0; a < clean_numb; a++)
    {
        printf("%d\r", a);
        EMPTY_x = rand() % 9;
        EMPTY_y = rand() % 9;
        if (sudoku_tab->grid[EMPTY_x][EMPTY_y] == 0)
        {
            a--;
            continue;
        }
        int stock = sudoku_tab->grid[EMPTY_x][EMPTY_y];
        sudoku_tab->grid[EMPTY_x][EMPTY_y] = 0;
        for (int i = 0; i < 9; i++)
        {
            for (int j = 0; j < 9; j++)
            {
                sudoku_tab->gridClone[i][j] = sudoku_tab->grid[i][j];
            }
        }
        // if (idiot_solver(sudoku_tab) == 0)
        // {
        //     sudoku_tab->grid[EMPTY_x][EMPTY_y] = stock;
        // }
        if (solver(sudoku_tab, sudoku_tab->gridClone, 0) == 2)
        {
            sudoku_tab->grid[EMPTY_x][EMPTY_y] = stock;
        }
    }
    for (int i = 0; i < 9; i++)
    {
        for (int j = 0; j < 9; j++)
        {
            sudoku_tab->gridClone[i][j] = sudoku_tab->grid[i][j];
        }
    }
    printf("\n");
}