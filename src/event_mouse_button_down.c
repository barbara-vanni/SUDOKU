#include <fonctions.h>
#include <display.h>
#include <SDL2/SDL.h>
#include <stdio.h>
#include "strsplit.h"


int event_mouse_button_down(sudoku *sudoku_tab, SDL_Event *events)
{
    if (events->button.button == SDL_BUTTON_LEFT)
    {
        const SDL_Point click = {events->motion.x, events->motion.y};
        const SDL_Rect butt = {MID_MENU_SIZE - 54.5, WINDOW_HEIGHT - 164, 109, 164};
        SDL_Rect verif = {GRID_SIZE + CELL_MARGIN, GRID_SIZE / 2 - FONT_SIZE / 2 - CELL_SIZE, MENU_SIZE - CELL_MARGIN * 2, FONT_SIZE * 2};
        SDL_Rect rectif = {GRID_SIZE + CELL_MARGIN, GRID_SIZE / 2 - FONT_SIZE / 2 + CELL_SIZE, MENU_SIZE - CELL_MARGIN * 2, FONT_SIZE * 2};
        SDL_Rect try_again = {GRID_SIZE + CELL_MARGIN, GRID_SIZE / 2 - FONT_SIZE / 2 + CELL_SIZE, MENU_SIZE - CELL_MARGIN * 2, FONT_SIZE * 2};
        SDL_Rect new_game = {GRID_SIZE + CELL_MARGIN, GRID_SIZE / 2 - FONT_SIZE / 2 - CELL_SIZE, MENU_SIZE - CELL_MARGIN * 2, FONT_SIZE * 2};
        const SDL_Rect level_one = {MID_MENU_SIZE - 34.5, WINDOW_HEIGHT - 104, 69, 104};
        const SDL_Rect level_two = {MID_MENU_SIZE - 41.5, WINDOW_HEIGHT - 218, 83, 124};
        const SDL_Rect level_three = {MID_MENU_SIZE - 48, WINDOW_HEIGHT - 362, 96, 144};
        const SDL_Rect level_four = {MID_MENU_SIZE - 54.5, WINDOW_HEIGHT - 526, 109, 164};
        const SDL_Rect level_five = {MID_MENU_SIZE - 54.5, WINDOW_HEIGHT - 690, 109, 164};

        int test = 0;

        if (SDL_PointInRect(&click, &level_one) == SDL_TRUE && sudoku_tab->almost_start == 1)
        {
            test = 1;
            sudoku_tab->clean_number = 15;
            init_sudoku(sudoku_tab);
            sudoku_tab->almost_start = 3;
        }
        if (SDL_PointInRect(&click, &level_two) == SDL_TRUE && sudoku_tab->almost_start == 1)
        {
            test = 1;
            sudoku_tab->clean_number = 30;
            init_sudoku(sudoku_tab);
            sudoku_tab->almost_start = 4;
        }
        if (SDL_PointInRect(&click, &level_three) == SDL_TRUE && sudoku_tab->almost_start == 1)
        {
            test = 1;
            sudoku_tab->clean_number = 45;
            init_sudoku(sudoku_tab);
            sudoku_tab->almost_start = 5;
        }
        if (SDL_PointInRect(&click, &level_four) == SDL_TRUE && sudoku_tab->almost_start == 1)
        {
            test = 1;
            sudoku_tab->clean_number = 60;
            init_sudoku(sudoku_tab);
            sudoku_tab->almost_start = 6;
        }
        if (SDL_PointInRect(&click, &level_five) == SDL_TRUE && sudoku_tab->almost_start == 1)
        {
            test = 1;
            sudoku_tab->clean_number = 75;
            init_sudoku(sudoku_tab);
            sudoku_tab->almost_start = 7;
        }

        if (SDL_PointInRect(&click, &butt) == SDL_TRUE && sudoku_tab->almost_start == 0 && !test)
        {
            sudoku_tab->almost_start = 1;
        }

        if (sudoku_tab->finish > 0 && SDL_PointInRect(&click, &new_game) == SDL_TRUE && !test)
        {
            sudoku_tab->almost_start = 0;
            sudoku_tab->time = time(NULL);
            sudoku_tab->finish = 0;
            sudoku_tab->almost_finish = 0;
            sudoku_tab->cell_fill = 0;
        }

        if (sudoku_tab->finish > 0 && SDL_PointInRect(&click, &try_again) == SDL_TRUE)
        {
            sudoku_tab->time = time(NULL);
            sudoku_tab->finish = 0;
            sudoku_tab->almost_finish = 0;
            sudoku_tab->cell_fill = 0;
            for (int i = 0; i < 9; i++)
            {
                for (int j = 0; j < 9; j++)
                {
                    sudoku_tab->grid[i][j] = sudoku_tab->gridClone[i][j];
                }
            }
        }

        if (sudoku_tab->almost_finish == 1 && SDL_PointInRect(&click, &verif) == SDL_TRUE && !test)
        {
            if (grille_valid(sudoku_tab))
            {

                sudoku_tab->finish = 1;
            }
            else
            {
                sudoku_tab->finish = 2;
            }
        }

        if (sudoku_tab->almost_finish == 1 && SDL_PointInRect(&click, &rectif) == SDL_TRUE && !test)
        {
            sudoku_tab->grid[sudoku_tab->last_y][sudoku_tab->last_x] = 0;
            sudoku_tab->cell_fill--;
            sudoku_tab->almost_finish = FALSE;
        }

        if (sudoku_tab->almost_start > 2 && SDL_PointInRect(&click, &butt) == SDL_TRUE && !test)
        {

            sudoku_tab->almost_start = 0;
            init_sudoku(sudoku_tab);
        }
    }
}