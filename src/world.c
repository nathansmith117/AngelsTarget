#include "world.h"
#include "assets.h"
#include "game.h"
#include "util.h"

void initWorld(World* world)
{
    SetRandomSeed(time(NULL));

    // Generate random world.
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

    // Generate npcs.
    world->npcCount = GetRandomValue(NPCS_MIN, NPCS_MAX);

    for (int i = 0; i < world->npcCount; ++i)
    {
        Npc* npc = &world->npcs[i];
        
        npc->position = (Vector2){GetRandomValue(0, WORLD_MAX_X), GetRandomValue(0, WORLD_MAX_Y)};
        npc->direction = Vector2Zero();
        
        Color colors[] = {RED, BLUE, GREEN, YELLOW, ORANGE, GRAY, WHITE};
        npc->color = colors[GetRandomValue(0, sizeof(colors) / sizeof(Color) - 1)];

        npc->targetRow = -1;
        npc->targetCol = -1;
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

void updateNpc(World* world, Npc* npc, Game* game)
{
    bool retarget = false;
    Vector2 target = (Vector2){npc->targetCol * WORLD_BLOCK_SIZE, npc->targetRow * WORLD_BLOCK_SIZE};

    // Target hasn't been set yet.
    if (npc->targetRow== -1)
    {
        retarget = true;
    }

    if (Vector2Distance(npc->position, target) <= WORLD_BLOCK_SIZE / 2.0) // At position.
    {
        retarget = true;
    }
    else
    {
        float frameTime = GetTime();
        npc->position = Vector2Add(npc->position, Vector2Scale(npc->direction, frameTime * NPC_SPEED));
    }

    // Set a new target.
    if (retarget)
    {
        SetRandomSeed(clock());
        npc->targetRow = GetRandomValue(0, WORLD_ROWS);
        npc->targetCol = GetRandomValue(0, WORLD_COLS);
        target = (Vector2){npc->targetCol * WORLD_BLOCK_SIZE, npc->targetRow * WORLD_BLOCK_SIZE};
        
        npc->direction = Vector2Normalize(Vector2Subtract(target, npc->position));
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

    // Draw and update npcs.
    Texture npcTexture = game->assets.textures[CHARACTER_TEXTURE];
    
    for (int i = 0; i < world->npcCount; ++i)
    {
        Npc* npc = &world->npcs[i];

        // Draw it.
        DrawTextureV(npcTexture, npc->position, npc->color);

        // Update it.
        updateNpc(world, npc, game);
    }
}

