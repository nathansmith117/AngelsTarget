#include "util.h"
#include "game.h"

Vector2 getScaledMousePosition()
{
    Vector2 mousePosition = GetMousePosition();
    mousePosition.x *= (float)SCREEN_WIDTH / GetScreenWidth();
    mousePosition.y *= (float)SCREEN_HEIGHT / GetScreenHeight();

    return mousePosition;
}

