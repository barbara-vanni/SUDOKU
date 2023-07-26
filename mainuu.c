#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "strsplit.h"

void *reallocTable(void *ptr, size_t len, size_t elemSize, size_t originalSize, void *newElem)
{
    size_t size = len * elemSize;
    if (size + elemSize > originalSize)
    {
        void *newTable = malloc(size * 2);
        memcpy(newTable, ptr, size);
        memcpy(newTable + size, newElem, elemSize);
        free(ptr);
        return newTable;
    }
    memcpy(ptr + size, newElem, elemSize);
    return ptr;
}

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

    char line[1024];

    int **grid = (int **)malloc(sizeof(int *) * 9);
    int j = 0;

    while (fgets(line, sizeof(line), file))
    {
        char **tab = strsplit(line, ' ');
        int *Arr = (int *)malloc(sizeof(int) * 9);
        for (int i = 0; tab[i]; i++)
        {
            int num = atoi(tab[i]);
            Arr[i] = num;
            free(tab[i]);
        }
        free(tab);
        grid[j] = Arr;
        j++;
    }
    for (int j = 0; j < 9; j++)
    {
        for (int i = 0; i < 9; i++)
        {
            printf("%i ", grid[j][i]);
        }
        printf("\n");
    }

    return 0;
}