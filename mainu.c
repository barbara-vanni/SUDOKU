#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "strsplit.h"
#include "fonctions.h"
#include <time.h>

// afficher le fichier, utiliser split, créer un tableau d'entier avec les chiffres récupérés

int main(int ac, char **av)
{
    if (ac < 2)
    {
        printf("Usage: %s <file>\n", av[0]);
        return 1;
    }
    FILE *file = fopen(av[1], "r");
    if (!file)
    {
        printf("Error: could not open file %s\n", av[1]);
        return 1;
    }

    sudoku sudoku_tab;
    char line[1024];

    // int gridass[9][9][9]; 
    int j = 0;
    srand(time(NULL));
    // int random_Tab[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};

    while (fgets(line, sizeof(line), file))
    {
        char **tab = strsplit(line, ' ');
        for (int i = 0; tab[i]; i++)
        {
            int num = atoi(tab[i]);
            sudoku_tab.grid[j][i] = num;
            free(tab[i]);
        }
        free(tab);
        j++;
    }
    shuffle_range(&sudoku_tab);
    solver(&sudoku_tab);
    remove_numbers(&sudoku_tab, 82);
    
    for (int j = 0; j < 9; j++)
    {
        for (int i = 0; i < 9; i++)
        {
            printf("%i ", sudoku_tab.grid[j][i]);
        }
        printf("\n");
    }

    return 0;
}