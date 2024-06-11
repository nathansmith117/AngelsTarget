#include "world.h"
#include "assets.h"
#include "game.h"
#include "util.h"

void initWorld(World* world)
{
    SetRandomSeed(time(NULL));
    
    for (int row = 0; row < WORLD_ROWS; ++row)
    {
        for (int col = 0; col < WORLD_COLS; ++col)
        {
            switch (GetRandomValue(1, 12))
            {
                case 1:
                case 2:
                    world->structures[row][col] = HOUSE_STRUCTURE;
                    break;
                case 3:
                    world->structures[row][col] = SHOP_STRUCTURE;
                    break;
                case 4:
                    world->structures[row][col] = OFFCE_STRUCTURE;
                    break;
                default:
                    world->structures[row][col] = NONE_STRUCTURE;
                    break;
            }
        }
    }

    world->showGrid = false;
}

void drawWorldStructure(StructureID structureID, int row, int col, Game* game)
{
    int x = col * WORLD_BLOCK_SIZE;
    int y = row * WORLD_BLOCK_SIZE;

    Texture grass = game->assets.textures[GRASS_TEXTURE];

    switch (structureID)
    {
        case NONE_STRUCTURE:
            DrawTexture(grass, x, y, WHITE);
            break;
        case HOUSE_STRUCTURE:
            DrawTexture(grass, x, y, WHITE);
            Texture house = game->assets.textures[HOUSE_TEXTURE];
            DrawTexture(house, x + 32, y + 32, WHITE);
            break;
        case SHOP_STRUCTURE:
            DrawTexture(grass, x, y, WHITE);
            Texture shop = game->assets.textures[SHOP_TEXTURE];
            DrawTexture(shop, x + 32, y + 32, WHITE);
            break;
        case OFFCE_STRUCTURE:
            DrawTexture(grass, x, y, WHITE);
            Texture offce = game->assets.textures[OFFCE_TEXTURE];
            DrawTexture(offce, x + 32, y + 5, WHITE);
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

            drawWorldStructure(world->structures[row][col], row, col, game);

            if (world->showGrid)
            {
                DrawRectangleLinesEx((Rectangle){x, y, WORLD_BLOCK_SIZE, WORLD_BLOCK_SIZE}, 1.0 / game->camera.zoom, BLUE);   
            }
        }
    }
}

