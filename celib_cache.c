#include "fonctions.h"
#include "strsplit.h"

int celib_cache(sudoku *sudoku_tab)
{
    int return_value = 0;

    for (int i = 0; i < 9; i++)
    {
        for (int j = 0; j < 9; j++)
        {
            if (sudoku_tab->gridClone[i][j] == 0)
            {
                int last_table = 0;
                for (int n = 1; n < 10; n++)
                {
                    if (sudoku_tab->gridass[i][j][n - 1] == TRUE)
                    {
                        for (int x = 0; x < 9; x++)
                        {
                            if (sudoku_tab -> gridass[x][j][n-1] == TRUE)
                            {
                                last_table ++;
                            }
                        }
                        if (last_table == 1)
                        {
                                sudoku_tab->gridClone[i][j] = n;
                                return_value ++;
                        }

                        last_table = 0;
                        for (int y = 0; y < 9; y++)
                        {
                            if (sudoku_tab -> gridass[i][y][n-1] == TRUE)
                            {
                                last_table ++;
                            }
                        }
                        if (last_table == 1)
                        {
                                sudoku_tab->gridClone[i][j] = n;
                                return_value ++;
                        }
                        last_table = 0;
                        int _i = 3 * (i / 3);
                        int _j = 3 * (j / 3);

                        for (int x = _i; x < _i + 3; x++)
                        {
                             for (int y = _j; y < _j + 3; y++)
                                {
                                    if (sudoku_tab->gridass[x][y][n-1] == TRUE)
                                    {
                                        last_table ++;
                                    }
                                }
                        }
                        if (last_table == 1)
                        {
                            sudoku_tab->gridClone[i][j] = n;
                            return_value ++;
                        }

                    }
                }
            }
        }
    }
    return return_value;
}