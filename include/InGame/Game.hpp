#pragma once
#include <SFML/Graphics.hpp>
#include <SFEX/SFEX.hpp>
#include <InGame/Scenes/MainMenuScene.hpp>
#include <InGame/Scenes/AboutScene.hpp>
#include <InGame/Scenes/DebugScene.hpp>
#include <OsSpecific/WindowFunctionalities.hpp>
// #include <imgui-SFML.h>
#include <ResourceManagement/TGUIFontManager.hpp>
#include <OsSpecific/Config.hpp>
#include "Version.hpp"


class Game
{
private:
    sf::RenderWindow m_window;
    sf::Uint16 m_FPS;
    sf::Event m_event;

    const sfex::Vec2 m_initialWindowSize;
    const std::string m_windowTitle;
    const sfex::Vec2u m_minWindowSize;
    sf::Time m_deltaTime;
    
    sfex::SceneManager m_defaultSceneManager;
    ExtendedScene* m_currentScene;
    
    tgui::GuiSFML m_gameGui;
    TGUIFontManager m_fontManager;

    const float m_targetAspectRatio;
    sf::Vector2i m_lastWindowPosition;
    sfex::Vec2u m_viewportSize;
    
    Version m_gameVersion;

public:
    Game();
    ~Game();

    void handleEvents();
    void update(const sf::Time& deltaTime);
    void lateUpdate(const sf::Time& deltaTime);
    void render();
    void run();

    void switchScene(const std::string& sceneName);

    void setMaxFPS(sf::Uint16 maxFPS);
    sf::Uint16 getMaxFPS() const;

    void makeMenuButton(tgui::Button::Ptr &buttonPtr, const tgui::String& text);

    sf::RenderWindow& getRenderWindow();
    ExtendedScene* getCurrentScene() const;
    const std::string& getWindowTitle() const;
    TGUIFontManager& getFontManager();
    tgui::GuiSFML* getGUI();
    sfex::Vec2 getInitialWindowSize() const;
    sfex::Vec2u getViewportSize() const;
    float getScalePercentage() const;
};
