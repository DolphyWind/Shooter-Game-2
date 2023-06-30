#include <InGame/Scenes/MainMenuScene.hpp>
#include <InGame/Game.hpp>

namespace sg
{


MainMenuScene::MainMenuScene(Game* parent):
    ExtendedScene(parent), m_gui(parent->getRenderWindow()), m_gradientPeriod(2.0f)
{
    m_titleGradient.setKey(0, Random::getRandomColor());
    m_titleGradient.setKey(m_gradientPeriod, Random::getRandomColor());

    m_titleLabel = tgui::Label::create(getParent()->getWindowTitle());
    m_titleLabel->getRenderer()->setFont(getParent()->getFontManager()["chunk_five_ex"].tguiFontData);
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
    m_aboutButton->onPress(&Game::switchScene, getParent(), "about_menu");

    makeMenuButton(m_quitButton, "Quit");
    m_quitButton->setPosition("Settings.x + (About.x + About.width - Settings.x - width) / 2", fmt::format("Settings.y + Settings.height + {}", MainMenuScene::buttonGap).c_str());
    m_quitButton->onPress(&sf::RenderWindow::close, std::ref(getParent()->getRenderWindow()));

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
    static unsigned int charSize = 22;
    static unsigned int borderRadius = 5;

    buttonPtr = tgui::Button::create(buttonStr);
    buttonPtr->setWidgetName(buttonStr);
    buttonPtr->getRenderer()->setRoundedBorderRadius(borderRadius);
    buttonPtr->getRenderer()->setFont(getParent()->getFontManager()["chunk_five_ex"].tguiFontData);
    buttonPtr->getRenderer()->setTextColor(sfex::Color::Black);
    buttonPtr->getRenderer()->setBackgroundColor(buttonColor);
    buttonPtr->getRenderer()->setBackgroundColorHover(
        sfex::Math::lerp(buttonColor, sfex::Color::Black, 0.2)
    );
    buttonPtr->getRenderer()->setBackgroundColorDown(
        sfex::Math::lerp(buttonColor, sfex::Color::Black, 0.4)
    );
    buttonPtr->setSize("17%","9%");
    buttonPtr->setTextSize(charSize);
    buttonPtr->getRenderer()->setBorders(tgui::Borders(2));
    buttonPtr->getRenderer()->setBorderColor(sfex::Color::Black);
    buttonPtr->setMouseCursor(tgui::Cursor::Type::Hand);
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
    float deltaTime = getParent()->getDeltaTime();
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
    float deltaTime = getParent()->getDeltaTime();
}

void MainMenuScene::draw(sf::RenderTarget& target)
{
    m_gui.draw();
}

void MainMenuScene::destroy()
{
    m_gui.setOverrideMouseCursor(tgui::Cursor::Type::Arrow);
}


}