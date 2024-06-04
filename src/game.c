#include "game.h"

void initGame(Game* game)
{
    InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Angels Target");

    // Screen texture.
    game->screenTexture = LoadRenderTexture(SCREEN_WIDTH, SCREEN_HEIGHT);

    initAssets(&game->assets);

    // Screens.
    game->screenId = MAIN_MENU_SCREEN;

    // Main menu.
    game->mainMenu.startButton = createTexturedButton(
        &game->assets.textures[BUTTON_BOX_TEXTURE], 
        (Rectangle){110.0, 95.0, 100.0, 50.0},
        "Start",
        WHITE,
        BLUE
    );
}

void drawMainMenu(Game* game)
{
    // Draw background.
    DrawTexture(game->assets.textures[MAIN_MENU_BACKGROUND_TEXTURE], 0, 0, WHITE);

    DrawText("Angels Target", 65, 50, 30, WHITE);

    // Update start button.
    if (updateTexturedButton(&game->mainMenu.startButton))
    {
        game->screenId = GAME_SCREEN;
    }
}

void drawGameScreen(Game* game)
{
    ClearBackground(BLACK);
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
            drawGameScreen(game);
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

