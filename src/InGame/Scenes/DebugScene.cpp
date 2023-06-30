#include <InGame/Scenes/DebugScene.hpp>
#include <InGame/Game.hpp>

namespace sg
{

DebugScene::DebugScene(Game* parent):
    ExtendedScene(parent), m_gui(parent->getRenderWindow())
{
    setBackgroundColor(sfex::Color::Cyan);
    m_welcomeLabel = tgui::Label::create("Welcome to the debug menu!\n"
    "Various test will go here\n"
    );
    m_welcomeLabel->getRenderer()->setTextColor(sfex::Color::Black);
    
    m_gui.add(m_welcomeLabel);
}

void DebugScene::pollEvent(const sf::Event &e)
{
    m_gui.handleEvent(e);
}

void DebugScene::start()
{
    m_f3Clock.restart();
}

void DebugScene::update()
{
    if(!sfex::Keyboard::getKey(sfex::Keyboard::Key::F3))
    {
        m_f3Clock.restart();
    }
    if(m_f3Clock.getElapsedTime().asSeconds() > Global::f3Time)
    {
        getParent()->switchScene("main_menu");
    }
}

void DebugScene::lateUpdate()
{

}

void DebugScene::draw(sf::RenderTarget &target)
{
    m_gui.draw();
}

void DebugScene::destroy()
{
    m_gui.setOverrideMouseCursor(tgui::Cursor::Type::Arrow);
}

}