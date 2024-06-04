#include "world.h"

void initPlayer(Player* player)
{
    player->position = Vector2Zero();
    player->velocity = Vector2Zero();

    player->camera = (Camera2D){
        .offset = (Vector2){SCREEN_WIDTH / 2.0, SCREEN_HEIGHT / 2.0},
        .target = Vector2Zero(),
        .rotation = 0.0,
        .zoom = 1.0
    };
}

void updatePlayer(Player* player, Game* game)
{
}

void initWorld(World* world)
{
}

void updateWorld(World* world, Game* game)
{
}

