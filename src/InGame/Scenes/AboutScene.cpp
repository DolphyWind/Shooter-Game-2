#include <InGame/Scenes/AboutScene.hpp>
#include <InGame/Game.hpp>

namespace sg
{

AboutScene::AboutScene(Game* parent):
    ExtendedScene(parent)
{
    setBackgroundColor(sfex::Color::Cyan);
}

AboutScene::~AboutScene()
{

}

void AboutScene::pollEvent(const sf::Event& e)
{

}

void AboutScene::start()
{

}

void AboutScene::update()
{
    
}

void AboutScene::lateUpdate()
{

}

void AboutScene::draw(sf::RenderTarget& target)
{

}

void AboutScene::destroy()
{
    // m_gui.setOverrideMouseCursor(tgui::Cursor::Type::Arrow);
}

}