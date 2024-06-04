#include "gameCommon.h"

#ifndef WORLD_H
#define WORLD_H

#define WORLD_ROWS 20
#define WORLD_COLS 20
#define WORLD_BLOCK_SIZE 96
#define WORLD_BLOCK_GAP 64

typedef struct World {
} World;

void initWorld(World* world);
void updateWorld(World* world, Game* game);

#endif
