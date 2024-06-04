#include "world.h"
#include "assets.h"
#include "game.h"

void initWorld(World* world)
{
}

void updateWorld(World* world, Game* game)
{
    for (int row = 0; row < WORLD_ROWS; ++row)
    {
        for (int col = 0; col < WORLD_COLS; ++col)
        {
            int x = col * WORLD_BLOCK_SIZE + col * WORLD_BLOCK_GAP;
            int y = row * WORLD_BLOCK_SIZE + row * WORLD_BLOCK_GAP;

            DrawRectangleLinesEx((Rectangle){x, y, WORLD_BLOCK_SIZE, WORLD_BLOCK_SIZE}, 1, WHITE);
        }
    }
}

