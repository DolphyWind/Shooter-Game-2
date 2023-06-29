#include <InGame/Scenes/MainMenuScene.hpp>
#include <InGame/Game.hpp>

namespace sg
{


MainMenuScene::MainMenuScene(Game* parent):
    m_parent(parent), m_gui(parent->getRenderWindow())
{
    
}

MainMenuScene::~MainMenuScene()
{

}

void MainMenuScene::pollEvent(const sf::Event& e)
{
    m_gui.handleEvent(e);
}

void MainMenuScene::start()
{
    
}

void MainMenuScene::update()
{
    float deltaTime = m_parent->getDeltaTime();
}

void MainMenuScene::lateUpdate()
{
    float deltaTime = m_parent->getDeltaTime();
}

void MainMenuScene::draw(sf::RenderTarget& target)
{
    m_gui.draw();
}

void MainMenuScene::destroy()
{

}


}