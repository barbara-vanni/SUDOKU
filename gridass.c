#include "fonctions.h"
#include "strsplit.h"

int gridass (sudoku *sudoku_tab)
{
    for (int i = 0; i < 9; i++)
    {
        for (int j = 0; j < 9; j++)
        {
            if (sudoku_tab->gridClone[i][j] == 0)
            {
                for (int n = 1; n < 10; n++)
                {
                    if (test_chiffre(n, sudoku_tab, i, j) == TRUE)
                    {
                        sudoku_tab->gridass[i][j][n-1] = TRUE;
                    }
                    else 
                    {
                        sudoku_tab->gridass[i][j][n-1] = FALSE;
                    }

                }
            }
        }
    }
    return 0;
}
