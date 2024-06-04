#include "gameCommon.h"

#define PLAYER_SPEED 50.0

#ifndef WORLD_H
#define WORLD_H

typedef struct Player {
    Vector2 position;
    Vector2 velocity;
    
    Camera2D camera;
} Player;

typedef struct World {
} World;

void initPlayer(Player* player);
void updatePlayer(Player* player, Game* game);

void initWorld(World* world);
void updateWorld(World* world, Game* game);

#endif
