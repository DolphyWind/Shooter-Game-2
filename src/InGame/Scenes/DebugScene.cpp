#include <InGame/Scenes/DebugScene.hpp>
#include <InGame/Game.hpp>


DebugScene::DebugScene(Game* parent):
    ExtendedScene(parent)
{
    setBackgroundColor(sfex::Color::Black);
    m_welcomeLabel = tgui::Label::create("Welcome to the debug menu!\n"
    "Various test will go here\n"
    );
    m_welcomeLabel->getRenderer()->setTextColor(sfex::Color::Black);

    m_backgroundPanel = tgui::Panel::create();
    m_backgroundPanel->getRenderer()->setBackgroundColor(sfex::Color::Cyan);
}

void DebugScene::handleEvent(const sf::Event &e)
{
    if(e.type == sf::Event::Resized)
    {
        // Scale text accordingly when the size changes
        float scale_percentage = getParent()->getScalePercentage();
        m_welcomeLabel->setTextSize(18 * scale_percentage);
    }
}

void DebugScene::start()
{
    m_f3Clock.restart();
    tgui::GuiSFML* gui = getParent()->getGUI();
    gui->add(m_backgroundPanel);
    gui->add(m_welcomeLabel);
}

void DebugScene::update(const sf::Time& deltaTime)
{
    if(!sfex::Keyboard::getKey(sfex::Keyboard::Key::F3))
    {
        m_f3Clock.restart();
    }
    if(sfex::Keyboard::getKey(sfex::Keyboard::Key::F3) && m_f3Clock.getElapsedTime().asSeconds() > Global::f3Time)
    {
        getParent()->switchScene("main_menu");
    }
}

void DebugScene::lateUpdate(const sf::Time& deltaTime)
{

}

void DebugScene::draw(sf::RenderTarget &target)
{

}

void DebugScene::destroy()
{
    //m_gui.setOverrideMouseCursor(tgui::Cursor::Type::Arrow);
    getParent()->getGUI()->removeAllWidgets();
}
