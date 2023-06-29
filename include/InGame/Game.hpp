#pragma once
#include <SFML/Graphics.hpp>
#include <SFEX/SFEX.hpp>
#include <InGame/Scenes/MainMenuScene.hpp>

namespace sg
{


class Game
{
private:
    sf::RenderWindow m_window;
    sf::Uint16 m_FPS;
    sf::Event m_event;

    const sfex::Vec2 m_windowSize;
    const std::string m_windowTitle;
    float m_deltaTime;
    
    sfex::SceneManager m_defaultSceneManager;
    ExtendedScene* m_currentScene;

public:
    Game();
    ~Game();

    void handleEvents();
    void update(float deltaTime);
    void lateUpdate(float deltaTime);
    void render();
    void run();

    void switchScene(const std::string& sceneName);

    void setMaxFPS(sf::Uint16 maxFPS);
    sf::Uint16 getMaxFPS() const;

    sf::RenderWindow& getRenderWindow();
    float getDeltaTime() const;
    ExtendedScene* getCurrentScene() const;
};


};