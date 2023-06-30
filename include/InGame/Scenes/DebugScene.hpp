#pragma once
#include <InGame/Scenes/ExtendedScene.hpp>
#include <TGUI/TGUI.hpp>

namespace sg
{

class Game;
class DebugScene : public ExtendedScene
{
private:
    tgui::GuiSFML m_gui;
    tgui::Label::Ptr m_welcomeLabel;

    sf::Clock m_f3Clock;
public:
    DebugScene(Game* parent);

    virtual void pollEvent(const sf::Event &e) override;
    virtual void start() override;

    virtual void update() override;
    virtual void lateUpdate() override;

    virtual void draw(sf::RenderTarget &target) override;
    virtual void destroy() override;

};

}