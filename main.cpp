#include "Game.h"

int main() {
    Game game;
    game.Inits();

    while(!WindowShouldClose()) {
        game.Run();
    }
    
    return 0;
}