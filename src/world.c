#include "world.h"
#include "assets.h"
#include "game.h"

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
    // Update controls.
    player->velocity = (Vector2){0.0, 0.0};

    if (IsKeyDown(KEY_W))
    {
        player->velocity.y -= PLAYER_SPEED;
    }
    if (IsKeyDown(KEY_S))
    {
        player->velocity.y += PLAYER_SPEED;
    }
    if (IsKeyDown(KEY_A))
    {
        player->velocity.x -= PLAYER_SPEED;
    }
    if (IsKeyDown(KEY_D))
    {
        player->velocity.x += PLAYER_SPEED;
    }

    // Apply velocity.
    player->position = Vector2Add(
        Vector2Scale(player->velocity, GetFrameTime()),
        player->position
    );
    
    Texture2D texture = game->assets.textures[CHARACTER_TEXTURE];
    
    // Update camera.
    player->camera.target = (Vector2){player->position.x + texture.width / 2.0,
        player->position.y + texture.height / 2.0};
    
    // Draw player.
    DrawTextureV(texture, player->position, WHITE);

    DrawRectangleRec((Rectangle){0.0, 0.0, 20.0, 20.0}, WHITE);
}

void initWorld(World* world)
{
}

void updateWorld(World* world, Game* game)
{
}

