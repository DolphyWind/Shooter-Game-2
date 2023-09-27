#include <Global.hpp>
#include <InGame/GameManager.hpp>

const sfex::Color Global::menuButtonColor = sfex::Color::fromHex(0x232CFFFF);
const sf::RenderWindow* Global::mainWindow = nullptr;
ModManager Global::defaultModManager(fs::current_path() / "mods");
GameManager Global::defaultGameManager(nullptr);