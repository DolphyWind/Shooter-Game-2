#include <InGame/Scenes/MainMenuScene.hpp>
#include <InGame/Game.hpp>

namespace sg
{


MainMenuScene::MainMenuScene(Game* parent):
    ExtendedScene(parent), m_titleGradient(2.0)
{
    m_titleLabel = tgui::Label::create(getParent()->getWindowTitle());
    m_titleLabel->getRenderer()->setFont(getParent()->getFontManager()["chunk_five_ex"].tguiFontData);
    m_titleLabel->setTextSize(42);
    m_titleLabel->getRenderer()->setTextColor(m_titleGradient.getCurrentColor());
    m_titleLabel->setPosition("(parent.width - width) / 2", "5%");
    m_titleLabel->getRenderer()->setTextOutlineColor(sfex::Color::Black);
    m_titleLabel->getRenderer()->setTextOutlineThickness(1);

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

    setBackgroundColor(sfex::Color::fromHex(0x5AD9EFFF));
}

MainMenuScene::~MainMenuScene()
{

}

void MainMenuScene::makeMenuButton(tgui::Button::Ptr &buttonPtr, const tgui::String& buttonStr)
{
    buttonPtr = tgui::Button::create(buttonStr);
    buttonPtr->setWidgetName(buttonStr);
    buttonPtr->getRenderer()->setRoundedBorderRadius(Global::menuButtonBorderRadius);
    buttonPtr->getRenderer()->setFont(getParent()->getFontManager()["chunk_five_ex"].tguiFontData);
    buttonPtr->getRenderer()->setTextColor(sfex::Color::Black);
    buttonPtr->getRenderer()->setBackgroundColor(Global::menuButtonColor);
    buttonPtr->getRenderer()->setBackgroundColorHover(
        sfex::Math::lerp(Global::menuButtonColor, sfex::Color::Black, 0.2)
    );
    buttonPtr->getRenderer()->setBackgroundColorDown(
        sfex::Math::lerp(Global::menuButtonColor, sfex::Color::Black, 0.4)
    );
    buttonPtr->setSize("17%","9%");
    buttonPtr->setTextSize(Global::menuButtonCharSize);
    buttonPtr->getRenderer()->setBorders(tgui::Borders(2));
    buttonPtr->getRenderer()->setBorderColor(sfex::Color::Black);
    buttonPtr->setMouseCursor(tgui::Cursor::Type::Hand);
}

void MainMenuScene::pollEvent(const sf::Event& e)
{
    
}

void MainMenuScene::start()
{
    m_f3Clock.restart();

    getParent()->getGUI()->add(m_titleLabel);
    getParent()->getGUI()->add(m_playButton);
    getParent()->getGUI()->add(m_mapMakerButton);
    getParent()->getGUI()->add(m_settingsButton);
    getParent()->getGUI()->add(m_aboutButton);
    getParent()->getGUI()->add(m_quitButton);
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

    getParent()->getGUI()->remove(m_titleLabel);
    getParent()->getGUI()->remove(m_playButton);
    getParent()->getGUI()->remove(m_mapMakerButton);
    getParent()->getGUI()->remove(m_settingsButton);
    getParent()->getGUI()->remove(m_aboutButton);
    getParent()->getGUI()->remove(m_quitButton);
}


}