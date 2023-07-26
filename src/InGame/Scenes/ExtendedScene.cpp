#include <InGame/Scenes/ExtendedScene.hpp>
#include <InGame/Game.hpp>

ExtendedScene::ExtendedScene(Game* parent)
{
    m_parent = parent;
}

void ExtendedScene::pollEvent(const sf::Event& e)
{
    sfex::Scene::pollEvent(e);
}

void ExtendedScene::start()
{
    sfex::Scene::start();
}

void ExtendedScene::update()
{
    sfex::Scene::update();
}

void ExtendedScene::lateUpdate()
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
