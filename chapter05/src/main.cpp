#include "game.h"

int main(int argc, char const* argv[]) {
    Game game;
    if (game.Initialize()) {
        game.RunLoop();
    }

    game.Shutdown();
}
