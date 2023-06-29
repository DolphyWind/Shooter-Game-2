#pragma once
#include <SFEX/SFEX.hpp>
#include <TGUI/TGUI.hpp>
#include <InGame/Scenes/ExtendedScene.hpp>

namespace sg
{

class Game;

class MainMenuScene : public ExtendedScene
{
private:
    tgui::GuiSFML m_gui;
    Game* m_parent;
public:
    MainMenuScene(Game* parent);
    ~MainMenuScene();

    virtual void pollEvent(const sf::Event& e) override;
    virtual void start() override;
    virtual void update() override;
    virtual void lateUpdate() override;
    virtual void draw(sf::RenderTarget& target) override;
    virtual void destroy() override;
};


}