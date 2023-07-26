#pragma once
#include <InGame/Rendering/MovingGradient.hpp>
#include <InGame/Scenes/ExtendedScene.hpp>
#include <TGUI/TGUI.hpp>
#include <thirdparty/imgui/imgui.h>
#include <imgui-SFML.h>


class Game;
class AboutScene : public ExtendedScene
{
private:
    MovingGradient m_aboutGradient;
    
    tgui::Panel::Ptr m_backgroundPanel;
    tgui::Label::Ptr m_titleLabel;
    tgui::Label::Ptr m_aboutDescription;
    tgui::Label::Ptr m_developerDescription;

    tgui::Button::Ptr m_backButton;
public:
    AboutScene(Game* parent);
    ~AboutScene();

    virtual void pollEvent(const sf::Event &e) override;
    virtual void start() override;

    virtual void update() override;
    virtual void lateUpdate() override;

    virtual void draw(sf::RenderTarget &target) override;
    virtual void destroy() override;
};
