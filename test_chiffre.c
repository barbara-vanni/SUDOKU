#include "strsplit.h"
#include "fonctions.h"

int test_chiffre(int n, sudoku *sudoku_tab, int x, int y)
{
    for (int i = 0; i < 9; i++)
    {
        if (sudoku_tab->grid[i][y] == n)
        {
            return FALSE;
        }
    }

    for (int j = 0; j < 9; j++)
    {
        if (sudoku_tab->grid[x][j] == n)
        {
            return FALSE;
        }
    }

    int _i = 3 * (x / 3);
    int _j = 3 * (y / 3);

    for (int i = _i; i < _i + 3; i++)
    {
        for (int j = _j; j < _j + 3; j++)
        {
            if (sudoku_tab->grid[i][j] == n)
                return FALSE;
        }
    }
    return TRUE;
}
