#include <stdio.h>
#include <stdlib.h>

int countwords(char *str, char delimiter)
{
    int i = 0;
    int count = 0;
    while (str[i] == delimiter)
        i++;
    while (str[i])
    {
        while (str[i] && str[i] != delimiter)
            i++;
        count++;
        while (str[i] == delimiter)
            i++;
    }
    return count;
}

char **strsplit(char *str, char delimiter)
{
    int i = 0;
    int number = 0;
    char **tab;
    tab = (char **)malloc(sizeof(char *) * (countwords(str, delimiter) + 1));
    while (str[i] == delimiter)
        i++;
    while (str[i])
    {
        int len = 0;
        while (str[i + len] != 0 && str[i + len] != delimiter)
            len++;
        tab[number] = (char *)malloc(sizeof(char) * (len + 1));
        for (int j = 0; j < len; j++)
            tab[number][j] = str[i + j];
        tab[number][len] = '\0';
        i += len;
        while (str[i] == delimiter)
            i++;
        number++;
    }
    tab[number] = NULL;
    return tab;
}