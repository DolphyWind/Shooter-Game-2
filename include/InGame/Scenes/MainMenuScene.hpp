#pragma once
// #include <TGUI/Backends/SFML.hpp>
#include <SFEX/SFEX.hpp>
#include <TGUI/Backend/SFML-Graphics.hpp>
#include <TGUI/TGUI.hpp>
#include <InGame/Scenes/ExtendedScene.hpp>
#include <Random/Random.hpp>
#include <fmt/core.h>
#include <Global.hpp>
#include <InGame/Rendering/MovingGradient.hpp>

namespace sg
{

class Game;

class MainMenuScene : public ExtendedScene
{
private:
    MovingGradient m_titleGradient;
    
    static constexpr float buttonGap = 10.0;

    tgui::Label::Ptr m_titleLabel;
    tgui::Button::Ptr m_playButton;
    tgui::Button::Ptr m_mapMakerButton;
    tgui::Button::Ptr m_settingsButton;
    tgui::Button::Ptr m_aboutButton;
    tgui::Button::Ptr m_quitButton;

    sf::Clock m_f3Clock;

    void makeMenuButton(tgui::Button::Ptr &buttonPtr, const tgui::String& buttonStr);
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