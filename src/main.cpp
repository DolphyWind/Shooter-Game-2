#include <InGame/Game.hpp>

int main(int argc, char** argv)
{
    sg::Game game;
    game.setMaxFPS(120);
    game.run();
    
    return 0;
}
