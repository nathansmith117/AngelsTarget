#include "util.h"
#include "game.h"

Vector2 getScaledMousePosition()
{
    Vector2 mousePosition = GetMousePosition();
    mousePosition.x *= (float)SCREEN_WIDTH / GetScreenWidth();
    mousePosition.y *= (float)SCREEN_HEIGHT / GetScreenHeight();

    return mousePosition;
}

Vector2 getScaledMouseDelta()
{
    Vector2 mouseDelta = GetMouseDelta();
    mouseDelta.x *= (float)SCREEN_WIDTH / GetScreenWidth();
    mouseDelta.y *= (float)SCREEN_HEIGHT / GetScreenHeight();

    return mouseDelta;
}

