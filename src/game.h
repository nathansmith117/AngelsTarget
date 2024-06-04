#include "gameCommon.h"
#include "assets.h"
#include "ui.h"

typedef enum ScreenId {
    MAIN_MENU_SCREEN,
    GAME_SCREEN
} ScreenId;

typedef struct Game {
     // Everything is drawn onto a render texture so it can be scaled nicely.
    RenderTexture screenTexture;

    Assets assets;
    
    ScreenId screenId;

    struct {
        TexturedButton startButton;
    } mainMenu;
} Game;

void initGame(Game* game);
void updateGame(Game* game);
void closeGame(Game* game);

