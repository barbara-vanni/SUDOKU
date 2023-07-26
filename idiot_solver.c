#include "fonctions.h"
#include "strsplit.h"
#include <stdio.h>

int idiot_solver(sudoku *sudoku_tab)
{
    int running = 1;
    int segments = 1;
    int x = 0;
    int y = 0;

    gridass(sudoku_tab);
    while (running || segments)
    {
        running = 0;
        segments = 0;
        segments += segment(sudoku_tab);
        segments += segment_2(sudoku_tab);
        running += celib_nu(sudoku_tab);
        running += celib_cache(sudoku_tab);
        if (running != 0)
        {
            gridass(sudoku_tab);
        }
    }

    if (case_vide(sudoku_tab->gridClone, &x, &y) == FALSE)
    {
        return TRUE;
    }
    return FALSE;
}