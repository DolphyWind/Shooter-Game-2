#include <InGame/Game.hpp>

namespace sg
{


Game::Game():
    m_FPS(0), m_windowSize(1280, 720), m_windowTitle("Shooter Game 2")
{
    m_window.create(sf::VideoMode(m_windowSize.x, m_windowSize.y), m_windowTitle);
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
            const sf::View& currentView = m_window.getView();
            m_window.setView(sf::View(currentView.getCenter(), newSize));
        }
        // Loop through all game objects and call their handleEvent methods.
    }
}

void Game::update(float deltaTime)
{
    // Loop through all game objects and call their update methods.
}

void Game::lateUpdate(float deltaTime)
{
    // Loop through all game objects and call their lateUpdate methods.
}

void Game::render()
{
    m_window.clear();
    // Loop through all game objects and call their render methods.
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

            total_time = frameClock.restart().asSeconds();
            update(total_time);
            lateUpdate(total_time);

            render();
        }
    }
    else
    {
        float frameTime = 1/float(m_FPS);

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

void Game::setMaxFPS(sf::Uint16 maxFPS)
{
    m_FPS = maxFPS;
    m_window.setFramerateLimit(m_FPS);
}

sf::Uint16 Game::getMaxFPS()
{
    return m_FPS;
}


}