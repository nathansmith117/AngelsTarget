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

    game->hoverRow = 0;
    game->hoverCol = 0;
}

void updateMainMenu(Game* game)
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
        camera->target = Vector2Add(
            Vector2Scale(getScaledMouseDelta(), 1.0 / camera->zoom),
            camera->target
        );
    }

    camera->target.x = Clamp(camera->target.x, 0.0, WORLD_MAX_X);
    camera->target.y = Clamp(camera->target.y, 0.0, WORLD_MAX_Y);

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
    float zoomSpeed = 0.05;
    camera->zoom += GetMouseWheelMove() * zoomSpeed;
    camera->zoom = Clamp(camera->zoom, zoomSpeed, 1.0);
}

void updateGameControls(Game* game)
{
    if (IsKeyPressed(KEY_G))
    {
        game->world.showGrid = !game->world.showGrid;
    }
}

// Things you are hovering your mouse over.
void updateGameMouseHover(Game* game)
{
    World* world = &game->world;
    Camera2D* camera = &game->camera;

    Vector2 mousePosition = getScaledMousePosition();

    // Get row and col from mouse position.
    int mouseRow = (mousePosition.y - (camera->offset.y - (camera->target.y * camera->zoom))) / camera->zoom;
    int mouseCol = (mousePosition.x - (camera->offset.x - (camera->target.x * camera->zoom))) / camera->zoom;
    mouseRow /= WORLD_BLOCK_SIZE;
    mouseCol /= WORLD_BLOCK_SIZE;

    // Out of bounds.
    if (mouseRow < 0 || mouseRow >= WORLD_ROWS || mouseCol < 0 || mouseCol >= WORLD_COLS)
    {
        return;
    }

    game->hoverRow = mouseRow;
    game->hoverCol = mouseCol;
}

// What to display info about.
enum {
    SIDE_INFO_NONE,
    SIDE_INFO_NPC,
    SIDE_INFO_STRUCTURE
};

void drawGameSideInfo(Game* game)
{
    World* world = &game->world;
    int hoverRow = game->hoverRow;
    int hoverCol = game->hoverCol;
    
    int type = SIDE_INFO_NONE;

    // Search for a npc.
    Npc* npcOver = NULL;

    for (int i = 0; i < world->npcCount; ++i)
    {
        Npc* npc = &world->npcs[i];
    }

    if (npcOver != NULL)
    {
        type = SIDE_INFO_NPC;
    }
    else // Check for structure.
    {
        if (world->structures[hoverRow][hoverCol] != NONE_STRUCTURE)
        {
            type = SIDE_INFO_STRUCTURE;
        }
    }

    switch (type)
    {
        case SIDE_INFO_NONE:
            puts("none");
            break;
        case SIDE_INFO_NPC:
            puts("npc");
            break;
        case SIDE_INFO_STRUCTURE:
            puts("structure");
            break;
        default:
            break;
    }
}

void updateGameScreen(Game* game)
{
    ClearBackground(BLACK);

    updateGameCamera(game);
    updateGameMouseHover(game);
    updateGameControls(game);

    BeginMode2D(game->camera);

    updateWorld(&game->world, game);
    drawGameSideInfo(game);

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
            updateMainMenu(game);
            break;
        case GAME_SCREEN:
            updateGameScreen(game);
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

