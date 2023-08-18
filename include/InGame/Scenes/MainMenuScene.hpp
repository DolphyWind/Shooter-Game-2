#pragma once
// #include <TGUI/Backends/SFML.hpp>
#include <SFEX/SFEX.hpp>
#include <TGUI/TGUI.hpp>
#include <InGame/Scenes/ExtendedScene.hpp>
#include <Random/Random.hpp>
#include <fmt/core.h>
#include <Global.hpp>
#include <InGame/Rendering/MovingGradient.hpp>


class Game;

class MainMenuScene : public ExtendedScene
{
private:
    MovingGradient m_titleGradient;
    
    static constexpr float buttonGap = 10.0;

    tgui::Panel::Ptr m_backgroundPanel;
    tgui::Label::Ptr m_titleLabel;
    tgui::Button::Ptr m_playButton;
    tgui::Button::Ptr m_mapMakerButton;
    tgui::Button::Ptr m_settingsButton;
    tgui::Button::Ptr m_aboutButton;
    tgui::Button::Ptr m_quitButton;

    sf::Clock m_f3Clock;

public:
    MainMenuScene(Game* parent);
    ~MainMenuScene();

    virtual void handleEvent(const sf::Event& e) override;
    virtual void start() override;
    virtual void update(const sf::Time& deltaTime) override;
    virtual void lateUpdate(const sf::Time& deltaTime) override;
    virtual void render(sf::RenderTarget& target) override;
    virtual void destroy() override;
};
