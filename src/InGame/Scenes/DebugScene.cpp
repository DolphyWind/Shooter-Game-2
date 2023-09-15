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

    m_gameManager.handleEvent(e);
}

void DebugScene::start()
{
    m_f3Clock.restart();
    tgui::GuiSFML* gui = getParent()->getGUI();
    gui->add(m_welcomeLabel);
    gui->add(m_drawCollidersToggle);

    m_gameManager.addEntity<Player>(getParent(), true);
    m_gameManager.addEntity<Player>(getParent(), false);
    m_gameManager.addEntity<LuaEntity>(getParent(), "entity.lua", ".");

    m_gameManager.getEntities()[0]->setPosition({100, 100});
    m_gameManager.getEntities()[1]->setPosition({300, 300});

    ModConfig conf;
    conf.loadFromFile("test_config.json");
    conf.printModConfig();
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

    m_gameManager.update(deltaTime);
}

void DebugScene::lateUpdate(const sf::Time& deltaTime)
{
    m_gameManager.lateUpdate(deltaTime);
}

void DebugScene::render(sf::RenderTarget &target)
{
    m_gameManager.render(target, m_drawCollidersToggle->isDown());
}

void DebugScene::destroy()
{
    getParent()->getGUI()->removeAllWidgets();
    m_gameManager.destroy();
}
