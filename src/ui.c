#include "ui.h"
#include "game.h"
#include "util.h"

TexturedButton createTexturedButton(Texture* texture, Rectangle rect, const char* message,
                                    Color backgroundColor, Color foregroundColor)
{
    TexturedButton button;
    button.texture = texture;
    button.rect = rect;

    strncpy((char*)button.message, message, UI_BUTTON_NAME_MAX);
    button.messageLength = strnlen(button.message, UI_BUTTON_NAME_MAX);

    button.backgroundColor = backgroundColor;
    button.foregroundColor = foregroundColor;
    button.fontSize = UI_BUTTON_DEFAULT_FONT_SIZE;
    button.isPressed = false;

    return button;
}

bool updateTexturedButton(TexturedButton* button)
{
    // Draw the button.
    DrawTexturePro(
        *button->texture,
        (Rectangle){0.0, 0.0, button->texture->width, button->texture->height},
        button->rect,
        Vector2Zero(),
        0.0,
        button->backgroundColor
    );

    // Draw text centered in button if we have a message.
    if (button->message[0] != '\0')
    {
        DrawText(
            button->message,
            button->rect.x + (button->rect.width / 2.0 - (button->messageLength * button->fontSize / 4.0)),
            button->rect.y + (button->rect.height / 2.0 - button->fontSize / 2.0),
            button->fontSize,
            button->foregroundColor
        );
    }

    button->isPressed = false;

    // Outline and detect click stuff.
    if (CheckCollisionPointRec(getScaledMousePosition(), button->rect))
    {
        // Draw outline thingy.
        if (IsMouseButtonDown(MOUSE_LEFT_BUTTON))
        {
            DrawRectangleLinesEx(button->rect, 2, button->foregroundColor);
        }

        // Is clicked.
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
        {
            button->isPressed = true;
        }
    }

    return button->isPressed;
}

