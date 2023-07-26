#include <InGame/Scenes/MainMenuScene.hpp>
#include <InGame/Game.hpp>


MainMenuScene::MainMenuScene(Game* parent):
    ExtendedScene(parent), m_titleGradient(2.0)
{
    setBackgroundColor(sfex::Color::Black);

    /// Initialize UI elements
    m_backgroundPanel = tgui::Panel::create();
    m_backgroundPanel->getRenderer()->setBackgroundColor(sfex::Color::fromHex(0x5AD9EFFF));

    m_titleLabel = tgui::Label::create(getParent()->getWindowTitle());
    m_titleLabel->getRenderer()->setFont(getParent()->getFontManager()["chunk_five_ex"].tguiFontData);
    m_titleLabel->setTextSize(Global::titleTextSize);
    m_titleLabel->getRenderer()->setTextColor(m_titleGradient.getCurrentColor());
    m_titleLabel->setPosition("(parent.width - width) / 2", "5%");
    m_titleLabel->getRenderer()->setTextOutlineColor(sfex::Color::Black);
    m_titleLabel->getRenderer()->setTextOutlineThickness(1);

    getParent()->makeMenuButton(m_playButton, "Play");
    m_playButton->setPosition(fmt::format("(parent.width) / 2 - width - {}", MainMenuScene::buttonGap).c_str(), "65%");

    getParent()->makeMenuButton(m_mapMakerButton, "Map Maker");
    m_mapMakerButton->setPosition(fmt::format("Play.x + Play.width + ({} / 2)", MainMenuScene::buttonGap).c_str(), "Play.y");

    getParent()->makeMenuButton(m_settingsButton, "Settings");
    m_settingsButton->setPosition(fmt::format("(parent.width) / 2 - width - {}", MainMenuScene::buttonGap).c_str(), fmt::format("Play.y + Play.height + {}", MainMenuScene::buttonGap).c_str());
    
    getParent()->makeMenuButton(m_aboutButton, "About");
    m_aboutButton->setPosition(fmt::format("Settings.x + Settings.width + ({} / 2)", MainMenuScene::buttonGap).c_str(), "Settings.y");
    m_aboutButton->onPress(&Game::switchScene, getParent(), "about_menu");

    getParent()->makeMenuButton(m_quitButton, "Quit");
    m_quitButton->setPosition("Settings.x + (About.x + About.width - Settings.x - width) / 2", fmt::format("Settings.y + Settings.height + {}", MainMenuScene::buttonGap).c_str());
    m_quitButton->onPress(&sf::RenderWindow::close, std::ref(getParent()->getRenderWindow()));

}

MainMenuScene::~MainMenuScene()
{

}

void MainMenuScene::pollEvent(const sf::Event& e)
{
    if(e.type == sf::Event::Resized)
    {
        // Scale text accordingly when the size changes
        float scale_percentage = getParent()->getScalePercentage();
        m_titleLabel->setTextSize(Global::titleTextSize * scale_percentage);
        m_playButton->setTextSize(Global::menuButtonTextSize * scale_percentage);
        m_mapMakerButton->setTextSize(Global::menuButtonTextSize * scale_percentage);
        m_settingsButton->setTextSize(Global::menuButtonTextSize * scale_percentage);
        m_aboutButton->setTextSize(Global::menuButtonTextSize * scale_percentage);
        m_quitButton->setTextSize(Global::menuButtonTextSize * scale_percentage);
    }
}

void MainMenuScene::start()
{
    m_f3Clock.restart();

    tgui::GuiSFML* gui = getParent()->getGUI();
    gui->add(m_backgroundPanel);
    gui->add(m_titleLabel);
    gui->add(m_playButton);
    gui->add(m_mapMakerButton);
    gui->add(m_settingsButton);
    gui->add(m_aboutButton);
    gui->add(m_quitButton);
}

void MainMenuScene::update()
{
    float deltaTime = getParent()->getDeltaTime();
    m_titleGradient.update(deltaTime);

    m_titleLabel->getRenderer()->setTextColor(m_titleGradient.getCurrentColor());
}

void MainMenuScene::lateUpdate()
{
    float deltaTime = getParent()->getDeltaTime();

    if(!sfex::Keyboard::getKey(sfex::Keyboard::Key::F3))
    {
        m_f3Clock.restart();
    }
    if(m_f3Clock.getElapsedTime().asSeconds() > Global::f3Time)
    {
        getParent()->switchScene("debug_menu");
    }
}

void MainMenuScene::draw(sf::RenderTarget& target)
{
    
}

void MainMenuScene::destroy()
{
    // m_gui.setOverrideMouseCursor(tgui::Cursor::Type::Arrow);

    getParent()->getGUI()->removeAllWidgets();
}
