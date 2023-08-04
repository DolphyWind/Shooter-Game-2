#include <InGame/Game.hpp>
#include <Modding/ShooterGameExporter.hpp>
#include <Network/RequestManager.hpp>

int main(int argc, char** argv)
{
    RequestManager::init();
#ifdef SFEX_USE_UPDATE_BASED_INPUT_HANDLING
std::cout << "11" << std::endl;
#endif

    Game game;
    game.setMaxFPS(120);
    game.run();
    
    return 0;
}
