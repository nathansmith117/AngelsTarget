#include "gameCommon.h"

#define UI_BUTTON_NAME_MAX 50
#define UI_BUTTON_DEFAULT_FONT_SIZE 20

#ifndef UI_H
#define UI_H

typedef struct TexturedButton {
    Texture* texture; // Can be in a animation or assets.
    Rectangle rect;

    char message[UI_BUTTON_NAME_MAX];
    size_t messageLength;

    Color backgroundColor;
    Color foregroundColor;

    int fontSize;

    bool isPressed;
} TexturedButton;

// Buttons don't need to be freed from memory. The button doesn't handle the texture memory.
TexturedButton createTexturedButton(Texture* texture, Rectangle rect, const char* message,
                                    Color backgroundColor, Color foregroundColor);
bool updateTexturedButton(TexturedButton* button);

#endif

