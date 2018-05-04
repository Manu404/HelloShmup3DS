#include "game.h"

int main(int argc, char **argv)
{
    Game* game = new Game();
    game->Initialize();
    game->Run();
    delete game;
}
