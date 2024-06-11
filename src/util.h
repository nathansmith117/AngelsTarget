#include "gameCommon.h"

#ifndef UTIL_H
#define UTIL_H

// Scale from the window to render texture.
Vector2 getScaledMousePosition();
Vector2 getScaledMouseDelta();

// Used for easy printing.
void printVector2(const char* lable, Vector2 vector);

#endif

