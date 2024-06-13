#include "gameCommon.h"

#ifndef WORLD_H
#define WORLD_H

#define WORLD_ROWS 20
#define WORLD_COLS 20
#define WORLD_BLOCK_SIZE 160
#define WORLD_MAX_X (WORLD_ROWS * WORLD_BLOCK_SIZE)
#define WORLD_MAX_Y (WORLD_COLS * WORLD_BLOCK_SIZE)

#define NPCS_MIN 15
#define NPCS_MAX 50
#define NPC_SPEED 0.05

// type structure is at each point.
typedef enum StructureID {
    NONE_STRUCTURE,
    HOUSE_STRUCTURE,
    SHOP_STRUCTURE,
    OFFCE_STRUCTURE
} StructureID;

typedef struct Npc {
    Vector2 position;
    Vector2 direction;

    Color color;

    // The place they are heading to.
    int targetRow;
    int targetCol;
} Npc;

typedef struct World {
    StructureID structures[WORLD_ROWS][WORLD_COLS];
    
    Npc npcs[NPCS_MAX];
    int npcCount;
    
    bool showGrid;
} World;

void initWorld(World* world);
void updateWorld(World* world, Game* game);

#endif

