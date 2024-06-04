#include "game.h"
#include "util.h"

void initGame(Game* game)
{
    InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Angels Target");
    SetWindowState(FLAG_WINDOW_RESIZABLE | FLAG_VSYNC_HINT);

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

    // Camera.
    game->camera = (Camera2D){
        .offset = (Vector2){SCREEN_WIDTH / 2.0, SCREEN_HEIGHT / 2.0},
        .target = Vector2Zero(),
        .rotation = 0.0,
        .zoom = 1.0
    };

    // World.
    initWorld(&game->world);
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

void updateGameCamera(Game* game)
{
    Camera2D* camera = &game->camera;

    // Scroll camera.
    if (IsMouseButtonDown(MOUSE_LEFT_BUTTON))
    {
        camera->target = Vector2Add(getScaledMouseDelta(), camera->target);
    }

    // Hide and show mouse when scrolling.
    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
    {
        DisableCursor();
    }
    else if (IsMouseButtonReleased(MOUSE_LEFT_BUTTON))
    {
        EnableCursor();
    }

    // Zoom
    camera->zoom = 1.0;
}

void drawGameScreen(Game* game)
{
    ClearBackground(BLACK);

    updateGameCamera(game);

    BeginMode2D(game->camera);

    //DrawTexture(game->assets.textures[CHARACTER_TEXTURE], 0, 0, WHITE);
    updateWorld(&game->world, game);

    EndMode2D();
}

void drawScreenTexture(Game* game)
{
    int windowWidth = GetScreenWidth();
    int windowHeight = GetScreenHeight();
    
    // Get render texture to window.
    int screenWidth = game->screenTexture.texture.width;
    int screenHeight = game->screenTexture.texture.height;
	float scale;

	if ((float)windowWidth / windowHeight > (float)SCREEN_WIDTH / SCREEN_HEIGHT)
		scale = (float)windowHeight / screenHeight;
	else
		scale = (float)windowWidth / screenWidth;

	float width = screenWidth * scale;
	float height = screenHeight  * scale;

	Rectangle destRect = (Rectangle){windowWidth / 2.0 - width / 2.0, windowHeight / 2.0 - height / 2.0, width, height};

    // Draw the texture
    DrawTexturePro(
        game->screenTexture.texture,
        (Rectangle){0.0, 0.0, screenWidth, -screenHeight},
        destRect,
        Vector2Zero(),
        0.0,
        WHITE
    );

    if (!FloatEquals((float)windowWidth / windowHeight, (float)SCREEN_WIDTH / SCREEN_HEIGHT))
	{
	    DrawRectangleLinesEx(destRect, 1, WHITE);
	}
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
    drawScreenTexture(game);

    EndDrawing();
}

void closeGame(Game* game)
{
    closeAssets(&game->assets);
    
    UnloadRenderTexture(game->screenTexture);
    CloseWindow();
}

