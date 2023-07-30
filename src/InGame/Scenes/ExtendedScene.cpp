#include <InGame/Scenes/ExtendedScene.hpp>
#include <InGame/Game.hpp>

ExtendedScene::ExtendedScene(Game* parent)
{
    m_parent = parent;
}

void ExtendedScene::handleEvent(const sf::Event& e)
{
    sfex::Scene::handleEvent(e);
}

void ExtendedScene::start()
{
    sfex::Scene::start();
}

void ExtendedScene::update(const sf::Time& deltaTime)
{
    sfex::Scene::update(deltaTime);
}

void ExtendedScene::lateUpdate(const sf::Time& deltaTime)
{
    
}

void ExtendedScene::draw(sf::RenderTarget& target)
{
    sfex::Scene::draw(target);
}


void ExtendedScene::destroy()
{
    sfex::Scene::destroy();
}

void ExtendedScene::setBackgroundColor(const sfex::Color& color)
{
    m_backgroundColor = color;
}

sfex::Color ExtendedScene::getBackgroundColor()
{
    return m_backgroundColor;
}

Game* ExtendedScene::getParent()
{
    return m_parent;
}
