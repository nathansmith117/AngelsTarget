#include "gameCommon.h"

#ifndef WORLD_H
#define WORLD_H

#define WORLD_ROWS 20
#define WORLD_COLS 20
#define WORLD_BLOCK_SIZE 160

// type structure is at each point.
typedef enum StructureID {
    NONE_STRUCTURE,
    HOUSE_STRUCTURE,
    STORE_STRUCTURE
} StructureID;

typedef struct World {
    StructureID structures[WORLD_ROWS][WORLD_COLS];
    bool showGrid;
} World;

void initWorld(World* world);
void updateWorld(World* world, Game* game);

#endif

