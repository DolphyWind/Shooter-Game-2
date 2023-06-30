#pragma once
#include <SFEX/SFEX.hpp>
#include <TGUI/TGUI.hpp>
#include <InGame/Scenes/ExtendedScene.hpp>
#include <Random/Random.hpp>
#include <fmt/core.h>

namespace sg
{

class Game;

class MainMenuScene : public ExtendedScene
{
private:
    tgui::GuiSFML m_gui;
    Game* m_parent;

    const std::string m_fontFilename;
    std::shared_ptr<tgui::BackendFontSFML> m_chunkfiveFontSFML;
    tgui::Font m_chunkFiveFont;

    static constexpr float buttonGap = 10.0;
    sfex::Gradient<sfex::Color> m_titleGradient;
    const float m_gradientPeriod;
    float m_totalGradientTime;
    
    tgui::Label::Ptr m_titleLabel;
    tgui::Button::Ptr m_playButton;
    tgui::Button::Ptr m_mapMakerButton;
    tgui::Button::Ptr m_settingsButton;
    tgui::Button::Ptr m_aboutButton;
    tgui::Button::Ptr m_quitButton;

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