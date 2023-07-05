#include <InGame/Scenes/DebugScene.hpp>
#include <InGame/Game.hpp>

namespace sg
{

DebugScene::DebugScene(Game* parent):
    ExtendedScene(parent)
{
    setBackgroundColor(sfex::Color::Cyan);
    m_welcomeLabel = tgui::Label::create("Welcome to the debug menu!\n"
    "Various test will go here\n"
    );
    m_welcomeLabel->getRenderer()->setTextColor(sfex::Color::Black);
}

void DebugScene::pollEvent(const sf::Event &e)
{
    
}

void DebugScene::start()
{
    m_f3Clock.restart();

    getParent()->getGUI()->add(m_welcomeLabel);
}

void DebugScene::update()
{
    
}

void DebugScene::lateUpdate()
{

}

void DebugScene::draw(sf::RenderTarget &target)
{

}

void DebugScene::destroy()
{
    //m_gui.setOverrideMouseCursor(tgui::Cursor::Type::Arrow);
    getParent()->getGUI()->remove(m_welcomeLabel);
}

}