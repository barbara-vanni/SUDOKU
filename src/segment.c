#include "fonctions.h"
#include "strsplit.h"

int segment(sudoku *sudoku_tab)
{
    int return_value = 0;

    for (int i = 0; i < 9; i++)
    {
        for (int j = 0; j < 9; j++)
        {
            if (sudoku_tab->gridClone[i][j] == 0)
            {
                for (int n = 1; n < 10; n++)
                {
                    int cube_Lsegment[3];
                    int cube_Csegment[3];

                    for (int b = 0; b < 3; b++)
                    {
                        cube_Lsegment[b] = 0;
                        cube_Csegment[b] = 0;
                    }

                    int _i = 3 * (i / 3);
                    int _j = 3 * (j / 3);

                    for (int x = _i; x < _i + 3; x++)
                    {
                        for (int y = _j; y < _j + 3; y++)
                        {
                            if (sudoku_tab->gridass[x][y][n - 1] == TRUE)
                            {
                                cube_Lsegment[x % 3]++;
                                cube_Csegment[y % 3]++;
                            }
                        }
                    }
                    int lastx = 0;
                    int lasty = 0;
                    int incr_ligne = 0;
                    int incr_colonne = 0;

                    for (int k = 0; k < 3; k++)
                    {
                        if (cube_Lsegment[k] > 0)
                        {
                            incr_ligne++;
                            lastx = k;
                        }
                        if (cube_Csegment[k] > 0)
                        {
                            incr_colonne++;
                            lasty = k;
                        }
                    }
                    int index_i = i / 3;
                    int index_j = j / 3;
                    int xprime = index_i *3 + lastx;
                    int yprime = index_j *3 + lasty;

                    if (incr_ligne == 1 && cube_Lsegment[lastx] > 1)
                    {
                        for (int e = 0; e < 9; e++)
                        {
                            if (index_i != e / 3)
                            {
                                if (sudoku_tab->gridass[e][yprime][n - 1] == TRUE)
                                    return_value++;
                                sudoku_tab->gridass[e][yprime][n - 1] = FALSE;
                            }
                        }
                    }
                    if (incr_colonne == 1 && cube_Csegment[lasty] > 1)
                    {
                        for (int f = 0; f < 9; f++)
                        {
                            if (index_j != f / 3)
                            {
                                if (sudoku_tab->gridass[xprime][f][n - 1] == TRUE)
                                    return_value++;
                                sudoku_tab->gridass[xprime][f][n - 1] = FALSE;
                            }
                        }
                    }
                }
            }
        }
    }
    return return_value;
}