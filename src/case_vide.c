#include "strsplit.h"
#include "fonctions.h"

int case_vide(int grid[9][9], int *x, int *y)
{
    for (*x = 0; *x < 9; (*x)++)
    {
        for (*y = 0; *y < 9; (*y)++)
        {
            if (grid[*x][*y] == 0)
            {
                return TRUE;
            }
        }
    }
    return FALSE;
} 