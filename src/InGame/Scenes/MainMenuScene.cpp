#include <InGame/Scenes/MainMenuScene.hpp>
#include <InGame/Game.hpp>

namespace sg
{


MainMenuScene::MainMenuScene(Game* parent):
    m_parent(parent), m_gui(parent->getRenderWindow()), m_fontFilename("assets/fonts/chunk_five_ex.ttf"),
    m_gradientPeriod(2.0f)
{
    m_chunkfiveFontSFML = std::make_shared<tgui::BackendFontSFML>();
    if (!m_chunkfiveFontSFML->loadFromFile(m_fontFilename))
    {
        std::cerr << "Font couldn't be loaded!" << std::endl;
        m_parent->getRenderWindow().close();
        return;
    }
    m_chunkFiveFont = tgui::Font(m_chunkfiveFontSFML, m_fontFilename);
    m_titleGradient.setKey(0, Random::getRandomColor());
    m_titleGradient.setKey(m_gradientPeriod, Random::getRandomColor());

    m_titleLabel = tgui::Label::create(m_parent->getWindowTitle());
    m_titleLabel->getRenderer()->setFont(m_chunkFiveFont);
    m_titleLabel->setTextSize(42);
    m_titleLabel->getRenderer()->setTextColor(m_titleGradient(0));
    m_titleLabel->setPosition("(parent.width - width) / 2", "5%");

    makeMenuButton(m_playButton, "Play");
    m_playButton->setPosition(fmt::format("(parent.width) / 2 - width - {}", MainMenuScene::buttonGap).c_str(), "65%");

    makeMenuButton(m_mapMakerButton, "Map Maker");
    m_mapMakerButton->setPosition(fmt::format("Play.x + Play.width + ({} / 2)", MainMenuScene::buttonGap).c_str(), "Play.y");

    makeMenuButton(m_settingsButton, "Settings");
    m_settingsButton->setPosition(fmt::format("(parent.width) / 2 - width - {}", MainMenuScene::buttonGap).c_str(), fmt::format("Play.y + Play.height + {}", MainMenuScene::buttonGap).c_str());
    
    makeMenuButton(m_aboutButton, "About");
    m_aboutButton->setPosition(fmt::format("Settings.x + Settings.width + ({} / 2)", MainMenuScene::buttonGap).c_str(), "Settings.y");
    
    makeMenuButton(m_quitButton, "Quit");
    m_quitButton->setPosition("Settings.x + (About.x + About.width - Settings.x - width) / 2", fmt::format("Settings.y + Settings.height + {}", MainMenuScene::buttonGap).c_str());
    m_quitButton->onPress(&sf::RenderWindow::close, std::ref(m_parent->getRenderWindow()));

    m_gui.add(m_titleLabel);
    m_gui.add(m_playButton);
    m_gui.add(m_mapMakerButton);
    m_gui.add(m_settingsButton);
    m_gui.add(m_aboutButton);
    m_gui.add(m_quitButton);

    setBackgroundColor(sfex::Color::fromHex(0x5AD9EFFF));
}

MainMenuScene::~MainMenuScene()
{

}

void MainMenuScene::makeMenuButton(tgui::Button::Ptr &buttonPtr, const tgui::String& buttonStr)
{
    static sfex::Color buttonColor = sfex::Color::fromHex(0x232CFFFF);
    static sfex::Vec2 buttonSize = {220, 65};
    static unsigned int charSize = 22;
    static unsigned int borderRadius = 5;

    buttonPtr = tgui::Button::create(buttonStr);
    buttonPtr->setWidgetName(buttonStr);
    buttonPtr->getRenderer()->setRoundedBorderRadius(borderRadius);
    buttonPtr->getRenderer()->setFont(m_chunkFiveFont);
    buttonPtr->getRenderer()->setTextColor(sfex::Color::Black);
    buttonPtr->getRenderer()->setBackgroundColor(buttonColor);
    buttonPtr->getRenderer()->setBackgroundColorHover(
        sfex::Math::lerp(buttonColor, sfex::Color::Black, 0.2)
    );
    buttonPtr->getRenderer()->setBackgroundColorDown(
        sfex::Math::lerp(buttonColor, sfex::Color::Black, 0.4)
    );
    buttonPtr->setSize(buttonSize.x, buttonSize.y);
    buttonPtr->setTextSize(charSize);
    buttonPtr->getRenderer()->setBorders(tgui::Borders(2));
    buttonPtr->getRenderer()->setBorderColor(sfex::Color::Black);
}

void MainMenuScene::pollEvent(const sf::Event& e)
{
    m_gui.handleEvent(e);
}

void MainMenuScene::start()
{
    
}

void MainMenuScene::update()
{
    float deltaTime = m_parent->getDeltaTime();
    m_totalGradientTime += deltaTime;

    if(m_totalGradientTime >= m_gradientPeriod)
    {
        m_titleGradient.setKey(0, m_titleGradient.evaluate(m_gradientPeriod));
        m_titleGradient.setKey(m_gradientPeriod, Random::getRandomColor());
        m_totalGradientTime = 0;
    }
    m_titleLabel->getRenderer()->setTextColor(m_titleGradient(m_totalGradientTime));
}

void MainMenuScene::lateUpdate()
{
    float deltaTime = m_parent->getDeltaTime();
}

void MainMenuScene::draw(sf::RenderTarget& target)
{
    m_gui.draw();
}

void MainMenuScene::destroy()
{

}


}