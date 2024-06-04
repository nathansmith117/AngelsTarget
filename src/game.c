#include "game.h"

void initGame(Game* game)
{
    InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Angels Target");

    // Screens.
    game->screenId = MAIN_MENU_SCREEN;

    // Screen texture.
    game->screenTexture = LoadRenderTexture(SCREEN_WIDTH, SCREEN_HEIGHT);

    initAssets(&game->assets);
}

void drawMainMenu(Game* game)
{
    ClearBackground(RAYWHITE);
    DrawFPS(0, 0);
}

void updateGame(Game* game)
{

    // Most of the drawing happens on the render texture.
    BeginTextureMode(game->screenTexture);
    
    switch (game->screenId)
    {
        case MAIN_MENU_SCREEN:
            drawMainMenu(game);
            break;
        case GAME_SCREEN:
            break;
    }

    EndTextureMode();

    BeginDrawing();

    // Draw the render texture.
    DrawTexturePro(
        game->screenTexture.texture,
        (Rectangle){0.0, 0.0, game->screenTexture.texture.width, -game->screenTexture.texture.height},
        (Rectangle){0.0, 0.0, GetScreenWidth(), GetScreenHeight()},
        Vector2Zero(),
        0.0,
        WHITE
    );

    EndDrawing();
}

void closeGame(Game* game)
{
    closeAssets(&game->assets);
    
    UnloadRenderTexture(game->screenTexture);
    CloseWindow();
}

