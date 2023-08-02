#include <InGame/Scenes/DebugScene.hpp>
#include <InGame/Game.hpp>
#include <InGame/Entity.hpp>
#include <InGame/Player.hpp>
#include <InGame/LuaEntity.hpp>


DebugScene::DebugScene(Game* parent):
    ExtendedScene(parent)
{
    setBackgroundColor(sfex::Color::Cyan);
    m_welcomeLabel = tgui::Label::create("Welcome to the debug menu!\n"
    "Various test will go here\n"
    );
    m_welcomeLabel->getRenderer()->setTextColor(sfex::Color::Black);
}

void DebugScene::handleEvent(const sf::Event &e)
{
    if(e.type == sf::Event::Resized)
    {
        // Scale text accordingly when the size changes
        float scale_percentage = getParent()->getScalePercentage();
        m_welcomeLabel->setTextSize(18 * scale_percentage);
    }

    for(auto& entity : m_entities)
    {
        entity->handleEvent(e);
    }
}

void DebugScene::start()
{
    m_f3Clock.restart();
    tgui::GuiSFML* gui = getParent()->getGUI();
    gui->add(m_welcomeLabel);

    m_entities.push_back(std::make_unique<Player>(getParent(), true));
    m_entities.push_back(std::make_unique<Player>(getParent(), false));
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

    for(auto& entity : m_entities)
    {
        entity->update(deltaTime);
    }
}

void DebugScene::lateUpdate(const sf::Time& deltaTime)
{
    for(auto& entity : m_entities)
    {
        entity->lateUpdate(deltaTime);
    }
}

void DebugScene::draw(sf::RenderTarget &target)
{
    for(auto& entity : m_entities)
    {
        entity->render(target);
    }
}

void DebugScene::destroy()
{
    getParent()->getGUI()->removeAllWidgets();
    m_entities.clear();
}
