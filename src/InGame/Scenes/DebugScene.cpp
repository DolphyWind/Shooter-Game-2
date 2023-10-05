#include <InGame/Scenes/DebugScene.hpp>
#include <InGame/Game.hpp>
#include <InGame/Entity.hpp>
#include <InGame/Player.hpp>
#include <InGame/LuaEntity.hpp>
#include <Modding/ModConfig.hpp>


DebugScene::DebugScene(Game* parent):
    ExtendedScene(parent)
{
    setBackgroundColor(sfex::Color::Cyan);
    m_welcomeLabel = tgui::Label::create("Welcome to the debug menu!\n"
    "Various test will go here\n"
    );
    m_welcomeLabel->getRenderer()->setTextColor(sfex::Color::Black);

    m_drawCollidersToggle = tgui::ToggleButton::create("Draw colliders", false);
    m_drawCollidersToggle->setPosition(0, "100% - height");
}

void DebugScene::handleEvent(const sf::Event &e)
{
    if(e.type == sf::Event::Resized)
    {
        // Scale text accordingly when the size changes
        float scale_percentage = getParent()->getScalePercentage();
        m_welcomeLabel->setTextSize(18 * scale_percentage);
    }

    Global::defaultGameManager.handleEvent(e);
}

void DebugScene::start()
{
    m_f3Clock.restart();
    tgui::GuiSFML* gui = getParent()->getGUI();
    gui->add(m_welcomeLabel);
    gui->add(m_drawCollidersToggle);

    Global::defaultGameManager.addEntity<Player>(getParent(), true);
    Global::defaultGameManager.addEntity<Player>(getParent(), false);
    Global::defaultGameManager.addEntity<LuaEntity>(getParent(), "coremod", "wall", "entity.lua", ".");
    Global::defaultGameManager.moveNewEntities();

    Global::defaultGameManager.getEntities()[0]->setPosition({100, 100});
    Global::defaultGameManager.getEntities()[1]->setPosition({300, 300});
    Global::defaultGameManager.getEntities()[2]->setPosition({0, 0});
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

    Global::defaultGameManager.update(deltaTime);
}

void DebugScene::lateUpdate(const sf::Time& deltaTime)
{
    Global::defaultGameManager.lateUpdate(deltaTime);
}

void DebugScene::render(sf::RenderTarget &target)
{
    Global::defaultGameManager.render(target, m_drawCollidersToggle->isDown());
}

void DebugScene::destroy()
{
    getParent()->getGUI()->removeAllWidgets();
    Global::defaultGameManager.destroy();
}
