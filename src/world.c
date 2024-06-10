#include "world.h"
#include "assets.h"
#include "game.h"

void initWorld(World* world)
{
    SetRandomSeed(time(NULL));
    
    for (int row = 0; row < WORLD_ROWS; ++row)
    {
        for (int col = 0; col < WORLD_COLS; ++col)
        {
            world->structures[row][col] = NONE_STRUCTURE;

            if (GetRandomValue(1, 5) == 1)
            {
                world->structures[row][col] = HOUSE_STRUCTURE;
            }
        }
    }

    world->showGrid = false;
}

void drawWorldStructure(StructureID structureID, int row, int col)
{
    int x = col * WORLD_BLOCK_SIZE;
    int y = row * WORLD_BLOCK_SIZE;

    switch (structureID)
    {
        case NONE_STRUCTURE:
            DrawRectangleRec((Rectangle){x, y, WORLD_BLOCK_SIZE, WORLD_BLOCK_SIZE}, DARKGREEN);
            break;
        case HOUSE_STRUCTURE:
            DrawRectangleRec((Rectangle){x, y, WORLD_BLOCK_SIZE, WORLD_BLOCK_SIZE}, DARKGREEN);
            DrawRectangleRec((Rectangle){x + 32, y + 32, 96, 96}, DARKGRAY);
            break;
        case STORE_STRUCTURE:
            break;
        default:
            break;
    }
}

void updateWorld(World* world, Game* game)
{
    for (int row = 0; row < WORLD_ROWS; ++row)
    {
        for (int col = 0; col < WORLD_COLS; ++col)
        {
            int x = col * WORLD_BLOCK_SIZE;
            int y = row * WORLD_BLOCK_SIZE;

            drawWorldStructure(world->structures[row][col], row, col);

            if (world->showGrid)
            {
                DrawRectangleLinesEx((Rectangle){x, y, WORLD_BLOCK_SIZE, WORLD_BLOCK_SIZE}, 1.0 / game->camera.zoom, WHITE);   
            }
        }
    }
}

