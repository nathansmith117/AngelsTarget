#include "gameCommon.h"

typedef enum ScreenId {
    MAIN_MENU_SCREEN,
    GAME_SCREEN
} ScreenId;

typedef struct Game {
    ScreenId screenId;

    // Everything is drawn onto a render texture so it can be scaled nicely.
    RenderTexture screenTexture;
} Game;

void initGame(Game* game);
void updateGame(Game* game);
void closeGame(Game* game);

