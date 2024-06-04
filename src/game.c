#include "game.h"

void initGame(Game* game)
{
    InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Angels Target");

    // Screens.
    game->screenId = MAIN_MENU_SCREEN;

    // Screen texture.
    game->screenTexture = LoadRenderTexture(SCREEN_WIDTH, SCREEN_HEIGHT);
}

void drawMainMenu(Game* game)
{
}

void updateGame(Game* game)
{
    BeginDrawing();

    switch (game->screenId)
    {
        case MAIN_MENU_SCREEN:
            drawMainMenu(game);
            break;
        case GAME_SCREEN:
            break;
    }

    EndDrawing();
}

void closeGame(Game* game)
{
    UnloadRenderTexture(game->screenTexture);
    CloseWindow();
}

