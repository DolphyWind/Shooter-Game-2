#include <InGame/Game.hpp>
#include <Modding/ShooterGameExporter.hpp>
#include <Network/RequestManager.hpp>

int main(int argc, char** argv)
{
    ShooterGameExporter::init();
    RequestManager::init();

    Game game;
    game.setMaxFPS(120);
    game.run();
    
    return 0;
}
