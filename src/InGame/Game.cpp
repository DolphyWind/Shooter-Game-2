#include <InGame/Game.hpp>

namespace sg
{


Game::Game():
    m_FPS(0), m_windowSize(1280, 720), m_windowTitle("Shooter Game 2"), m_currentScene(nullptr),
    m_minWindowSize(575, 775)
{
    m_window.create(sf::VideoMode(m_windowSize.x, m_windowSize.y), m_windowTitle);
    m_defaultSceneManager.insert({"main_menu", std::make_shared<MainMenuScene>(this)});
    switchScene("main_menu");
}

Game::~Game()
{
    m_window.close();
}

void Game::handleEvents()
{
    while(m_window.pollEvent(m_event))
    {
        if(m_event.type == sf::Event::Closed)
        {
            m_window.close();
        }
        else if(m_event.type == sf::Event::Resized)
        {
            sfex::Vec2 newSize = {m_event.size.width, m_event.size.height};
            // if(newSize.x < m_minWindowSize.x) newSize.x = m_minWindowSize.x;
            // if(newSize.y < m_minWindowSize.y) newSize.y = m_minWindowSize.y;
            
            // m_window.setSize(newSize);

            const sf::View& currentView = m_window.getView();
            m_window.setView(sf::View(currentView.getCenter(), newSize));
        }
        m_defaultSceneManager.pollEvent(m_event);
    }
}

void Game::update(float deltaTime)
{
    m_defaultSceneManager.update();
}

void Game::lateUpdate(float deltaTime)
{
    getCurrentScene()->lateUpdate();
}

void Game::render()
{
    m_window.clear(getCurrentScene()->getBackgroundColor());
    m_defaultSceneManager.draw(getRenderWindow());
    m_window.display();
}

void Game::run()
{
    sf::Clock frameClock;
    float total_time = 0.0f;
    
    if(!m_FPS)
    {
        while(m_window.isOpen())
        {
            handleEvents();

            m_deltaTime = total_time = frameClock.restart().asSeconds();
            update(total_time);
            lateUpdate(total_time);

            render();
        }
    }
    else
    {
        float frameTime = 1/float(m_FPS);
        m_deltaTime = frameTime;

        while(m_window.isOpen())
        {
            handleEvents();

            total_time += frameClock.restart().asSeconds();
            while(total_time >= frameTime)
            {
                update(frameTime);
                lateUpdate(frameTime);
                total_time -= frameTime;
            }

            render();
        }
    }
}

void Game::switchScene(const std::string& sceneName)
{
    m_defaultSceneManager.setActiveScene(sceneName);
    m_currentScene = dynamic_cast<ExtendedScene*>(m_defaultSceneManager.getActiveScene().value_or(nullptr).get());
}

void Game::setMaxFPS(sf::Uint16 maxFPS)
{
    m_FPS = maxFPS;
    m_window.setFramerateLimit(m_FPS);
}

sf::Uint16 Game::getMaxFPS() const
{
    return m_FPS;
}

sf::RenderWindow& Game::getRenderWindow()
{
    return m_window;
}

float Game::getDeltaTime() const
{
    return m_deltaTime;
}

ExtendedScene* Game::getCurrentScene() const
{
    return m_currentScene;
}

const std::string& Game::getWindowTitle() const
{
    return m_windowTitle;
}


}