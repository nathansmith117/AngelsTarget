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

void printVector2(const char* lable, Vector2 vector)
{
    if (lable == NULL)
    {
        printf("%f %f\n", vector.x, vector.y);
    }
    else
    {
        printf("%s: %f %f\n", lable, vector.x, vector.y);
    }
}

