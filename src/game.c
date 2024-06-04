#include "game.h"

void initGame(Game* game)
{
    InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Narcissist Cleansing");

    // Screens.
    game->screenId = MAIN_MENU_SCREEN;
}

void updateGame(Game* game)
{
    BeginDrawing();

    switch (game->screenId)
    {
        case MAIN_MENU_SCREEN:
            break;
        case GAME_SCREEN:
            break;
    }

    EndDrawing();
}

void closeGame(Game* game)
{
    CloseWindow();
}

