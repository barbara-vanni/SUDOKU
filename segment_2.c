#include "fonctions.h"
#include "strsplit.h"

int segment_2(sudoku *sudoku_tab)
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

                    if (sudoku_tab->gridass[i][j][n - 1] == TRUE)
                    {
                        for (int q = 0; q < 9; q++)
                        {
                            if (sudoku_tab->gridass[q][j][n - 1] == TRUE)
                            {
                                cube_Lsegment[q / 3]++;
                            }
                            if (sudoku_tab->gridass[i][q][n - 1] == TRUE)
                            {
                                cube_Csegment[q / 3]++;
                            }
                        }
                    }

                    int incr_ligne = 0;
                    int incr_colonne = 0;

                    for (int k = 0; k < 3; k++)
                    {
                        if (cube_Lsegment[k] > 0)
                        {
                            incr_ligne++;
                        }
                        if (cube_Csegment[k] > 0)
                        {
                            incr_colonne++;
                        }
                    }
                    int index_i = i / 3;
                    int index_j = j / 3;
                    int xprime = index_i * 3;
                    int yprime = index_j * 3;

                    if (incr_ligne == 1 && cube_Lsegment[index_i] > 0)
                    {

                        for (int e = xprime; e < xprime + 3; e++)
                        {
                            for (int f = yprime; f < yprime + 3; f++)
                            {
                                if (index_i != e / 3)
                                {
                                    if (sudoku_tab->gridass[e][f][n - 1] == TRUE)
                                        return_value++;
                                    sudoku_tab->gridass[e][f][n - 1] = FALSE;
                                }
                            }
                        }
                    }
                    if (incr_colonne == 1 && cube_Csegment[index_j] > 0)
                    {

                        for (int e = xprime; e < xprime + 3; e++)
                        {
                            for (int f = yprime; f < yprime + 3; f++)
                            {
                                if (index_j != e / 3)
                                {
                                    if (sudoku_tab->gridass[e][f][n - 1] == TRUE)
                                        return_value++;
                                    sudoku_tab->gridass[e][f][n - 1] = FALSE;
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    return return_value;
}