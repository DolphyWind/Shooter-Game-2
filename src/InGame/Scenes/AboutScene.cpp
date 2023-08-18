#include <InGame/Scenes/AboutScene.hpp>
#include <InGame/Game.hpp>


AboutScene::AboutScene(Game* parent):
    ExtendedScene(parent), m_aboutGradient(2.0)
{
    setBackgroundColor(sfex::Color::Black);

    m_backgroundPanel = tgui::Panel::create();
    m_backgroundPanel->getRenderer()->setBackgroundColor(sfex::Color::fromHex(0x5AD9EFFF));

    m_titleLabel = tgui::Label::create("About");
    m_titleLabel->getRenderer()->setFont(getParent()->getFontManager()["chunk_five_ex"].tguiFontData);
    m_titleLabel->setTextSize(42);
    m_titleLabel->getRenderer()->setTextColor(m_aboutGradient.getCurrentColor());
    m_titleLabel->setPosition("(parent.width - width) / 2", "5%");
    m_titleLabel->getRenderer()->setTextOutlineColor(sfex::Color::Black);
    m_titleLabel->getRenderer()->setTextOutlineThickness(1);


    m_aboutDescription = tgui::Label::create("Shooter game is a multiplayer and moddable game\n"
                                                   "write creative stuff here"
    );
    m_aboutDescription->setWidgetName("about_desc");
    m_aboutDescription->setTextSize(25);
    m_aboutDescription->getRenderer()->setFont(getParent()->getFontManager()["chunk_five_ex"].tguiFontData);
    m_aboutDescription->getRenderer()->setTextColor(sfex::Color::Black);
    m_aboutDescription->setPosition("7%", "24%");

    m_developerDescription = tgui::Label::create("Programming: Yunus Emre Aydın\n"
                                                   "Artwork: Yunus Emre Aydın\n"
                                                   "Music & SFX: Yunus Emre Aydın"
    );
    m_developerDescription->setWidgetName("developer_desc");
    m_developerDescription->setTextSize(18);
    m_developerDescription->getRenderer()->setFont(getParent()->getFontManager()["chunk_five_ex"].tguiFontData);
    m_developerDescription->getRenderer()->setTextColor(sfex::Color::Black);
    m_developerDescription->setPosition("7%", "about_desc.y + 300");

    getParent()->makeMenuButton(m_backButton, "Back");
    m_backButton->setPosition("(parent.width - width) / 2", "parent.height - height - 5%");
    m_backButton->onClick([this](){
        getParent()->switchScene("main_menu");
    });
}

AboutScene::~AboutScene()
{

}

void AboutScene::handleEvent(const sf::Event& e)
{
    if(e.type == sf::Event::Resized)
    {
        // Scale text accordingly when the size changes
        float scale_percentage = getParent()->getScalePercentage();
        m_titleLabel->setTextSize(Global::titleTextSize * scale_percentage);
        m_aboutDescription->setTextSize(25 * scale_percentage);
        m_developerDescription->setTextSize(18 * scale_percentage);
        m_backButton->setTextSize(Global::menuButtonTextSize * scale_percentage);
    }
}

void AboutScene::start()
{
    tgui::GuiSFML* gui = getParent()->getGUI();
    gui->add(m_backgroundPanel);
    gui->add(m_titleLabel);
    gui->add(m_aboutDescription);
    gui->add(m_developerDescription);
    gui->add(m_backButton);
}

void AboutScene::update(const sf::Time& deltaTime)
{
    m_aboutGradient.update(deltaTime.asSeconds());
    m_titleLabel->getRenderer()->setTextColor(m_aboutGradient.getCurrentColor());
}

void AboutScene::lateUpdate(const sf::Time& deltaTime)
{

}

void AboutScene::render(sf::RenderTarget& target)
{
    
}

void AboutScene::destroy()
{
    // m_gui.setOverrideMouseCursor(tgui::Cursor::Type::Arrow);
    getParent()->getGUI()->removeAllWidgets();
}
