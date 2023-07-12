#include <InGame/Game.hpp>

namespace sg
{


Game::Game():
    m_FPS(0), m_initialWindowSize(1280, 720), m_windowTitle("Shooter Game 2"), m_currentScene(nullptr),
    m_minWindowSize(1024, 576), m_targetAspectRatio(16.0f / 9.0f)
{
    if (!m_fontManager.loadFromFile("chunk_five_ex", "assets/fonts/chunk_five_ex.ttf"))
    {
        MessageBoxWindow({350, 165}, "Error!", "Cannot open \"assets/fonts/chunk_five_ex.ttf\"", {"Ok"}).show();
        return;
    }

    m_window.create(sf::VideoMode(m_initialWindowSize.x, m_initialWindowSize.y), m_windowTitle);
    WindowFunctionalities::setMinimumSize(m_window, m_minWindowSize);
    m_lastWindowPosition = m_window.getPosition();
    m_gameGui.setTarget(m_window);
    
    m_defaultSceneManager.insert( {"main_menu", std::make_shared<MainMenuScene>(this)} );
    m_defaultSceneManager.insert( {"about_menu", std::make_shared<AboutScene>(this)} );
    m_defaultSceneManager.insert( {"debug_menu", std::make_shared<DebugScene>(this)} );
    
    switchScene("main_menu");
}

Game::~Game()
{
    if(m_window.isOpen()) m_window.close();
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
            sfex::Vec2u newSize = {m_event.size.width, m_event.size.height};
            
            // Draw vertical bar if the aspect ratio is different than m_targetAspectRatio
            float area_based_on_width = newSize.x * newSize.x / m_targetAspectRatio;
            float area_based_on_height = newSize.y * newSize.y * m_targetAspectRatio;

            const sf::View& currentView = m_window.getView();
            sf::View newView;
            newView.setCenter(currentView.getCenter());
            m_viewportSize = newSize;

            if(area_based_on_width < area_based_on_height)
            {
                newView.setSize(newSize.y * m_targetAspectRatio, newSize.y);
                
                // Horizontal bars
                // borderPercentage is the ratio of the width of the black bars to the width of the screen
                float targetHeight = newSize.x / m_targetAspectRatio;
                m_viewportSize.y = targetHeight;
                float cameraPercentage = targetHeight / newSize.y;
                float borderPercentage = (1 - cameraPercentage);
                
                newView.setViewport({0.0f, borderPercentage / 2.0f, 1.0f, 1.0f - borderPercentage});
                m_gameGui.setRelativeViewport({0.0f, borderPercentage / 2.0f, 1.0f, 1.0f - borderPercentage});
            }
            else
            {
                newView.setSize(newSize.x, newSize.x / m_targetAspectRatio);
                m_viewportSize = {newSize.x, newSize.x / m_targetAspectRatio};

                // Vertical bars
                // Percentage is the ratio of the height of the black bars to the height of the screen
                float targetWidth = newSize.y * m_targetAspectRatio;
                m_viewportSize.x = targetWidth;
                float cameraPercentage = targetWidth / newSize.x;
                float borderPercentage = (1 - cameraPercentage);
                
                newView.setViewport({borderPercentage / 2.0f, 0.0f, 1.0f - borderPercentage, 1.0f});
                m_gameGui.setRelativeViewport({borderPercentage / 2.0f, 0.0f, 1.0f - borderPercentage, 1.0f});
            }
            // std::cout << (sfex::Vec2)newView.getSize() << std::endl;
            newView.setSize(newSize);
            m_window.setView(newView);

            // Reposition the window after resizing on windows
#if defined(SG_OS_WINDOWS)
            bool newSizeLessThanMinimum = false;

            if(newSize.x < m_minWindowSize.x)
            {
                newSize.x = m_minWindowSize.x;
                newSizeLessThanMinimum = true;
            }
            if(newSize.y < m_minWindowSize.y)
            {
                newSize.y = m_minWindowSize.y;
                newSizeLessThanMinimum = true;
            }

            if(newSizeLessThanMinimum)
            {
                m_window.setSize(newSize);
                m_window.setPosition(m_lastPosition);
            }
#endif
        }
        ImGui::SFML::ProcessEvent(m_window, m_event);
        m_defaultSceneManager.pollEvent(m_event);
        m_gameGui.handleEvent(m_event);
        m_lastWindowPosition = m_window.getPosition();
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
    m_gameGui.draw();
    m_window.display();
}

void Game::run()
{
    sf::Clock frameClock;
    float total_time = 0.0f;
    ImGui::SFML::Init(m_window);
    
    if(!m_FPS)
    {
        while(m_window.isOpen())
        {
            handleEvents();

            m_deltaTime = total_time = frameClock.restart().asSeconds();
            ImGui::SFML::Update(m_window, sf::seconds(m_deltaTime));
    
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
                ImGui::SFML::Update(m_window, sf::seconds(frameTime));
                update(frameTime);
                lateUpdate(frameTime);
                total_time -= frameTime;
            }

            render();
        }
    }

    ImGui::SFML::Shutdown();
}

void Game::switchScene(const std::string& sceneName)
{
    m_defaultSceneManager.setActiveScene(sceneName);    
    m_currentScene = dynamic_cast<ExtendedScene*>(m_defaultSceneManager.getActiveScene().value_or(nullptr).get());
    m_window.setView(m_window.getView());
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

void Game::makeMenuButton(tgui::Button::Ptr &buttonPtr, const tgui::String& buttonStr)
{
    buttonPtr = tgui::Button::create(buttonStr);
    buttonPtr->setWidgetName(buttonStr);
    buttonPtr->getRenderer()->setRoundedBorderRadius(Global::menuButtonBorderRadius);
    buttonPtr->getRenderer()->setFont(getFontManager()["chunk_five_ex"].tguiFontData);
    buttonPtr->getRenderer()->setTextColor(sfex::Color::Black);
    buttonPtr->getRenderer()->setBackgroundColor(Global::menuButtonColor);
    buttonPtr->getRenderer()->setBackgroundColorHover(
        sfex::Math::lerp(Global::menuButtonColor, sfex::Color::Black, 0.2)
    );
    buttonPtr->getRenderer()->setBackgroundColorDown(
        sfex::Math::lerp(Global::menuButtonColor, sfex::Color::Black, 0.4)
    );
    buttonPtr->setSize("17%","9%");
    buttonPtr->setTextSize(Global::menuButtonTextSize);
    buttonPtr->getRenderer()->setBorders(tgui::Borders(2));
    buttonPtr->getRenderer()->setBorderColor(sfex::Color::Black);
    buttonPtr->setMouseCursor(tgui::Cursor::Type::Hand);
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

TGUIFontManager& Game::getFontManager()
{
    return m_fontManager;
}

tgui::GuiSFML* Game::getGUI()
{
    return &m_gameGui;
}

sfex::Vec2 Game::getInitialWindowSize() const
{
    return m_initialWindowSize;
}

sfex::Vec2u Game::getViewportSize() const
{
    return m_viewportSize;
}

float Game::getScalePercentage() const
{
    // UI scaling factor
    return std::sqrt((getViewportSize().x * getViewportSize().y) / (getInitialWindowSize().x * getInitialWindowSize().y));
}

}