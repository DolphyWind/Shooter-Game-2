#include <InGame/Scenes/ExtendedScene.hpp>

namespace sg
{


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


}