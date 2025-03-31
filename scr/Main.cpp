#include "../include/Game.h"

int main(int argc, char* argv[]) {
    Game& game = Game::GetInstance("202014486", 1200, 900);
    game.Run();
    return 0;
}