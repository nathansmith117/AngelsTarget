#include "gameCommon.h"
#include "game.h"

Game game;

void updateFrame() {
	updateGame(&game);
}

int main(int argc, char ** argv) {
	initGame(&game);

#ifdef PLATFORM_WEB
    emscripten_set_main_loop(updateFrame, 0, 1);
#else
    while (!WindowShouldClose()) {
        updateFrame();
    }
#endif

	closeGame(&game);
	return 0;
}
