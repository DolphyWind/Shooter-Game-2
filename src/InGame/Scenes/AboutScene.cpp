#include <InGame/Scenes/AboutScene.hpp>
#include <InGame/Game.hpp>

namespace sg
{

AboutScene::AboutScene(Game* parent):
    ExtendedScene(parent), m_aboutGradient(2.0)
{
    setBackgroundColor(sfex::Color::fromHex(0x5AD9EFFF));
    m_titleLabel = tgui::Label::create("About");
    m_titleLabel->getRenderer()->setFont(getParent()->getFontManager()["chunk_five_ex"].tguiFontData);
    m_titleLabel->setTextSize(42);
    m_titleLabel->getRenderer()->setTextColor(m_aboutGradient.getCurrentColor());
    m_titleLabel->setPosition("(parent.width - width) / 2", "5%");

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
    m_developerDescription->setPosition("7%", "about_desc.y + 250");

    m_backButton = tgui::Button::create("Back");
    m_backButton->setWidgetName("back_button");
    m_backButton->getRenderer()->setRoundedBorderRadius(5);
    m_backButton->getRenderer()->setFont(getParent()->getFontManager()["chunk_five_ex"].tguiFontData);
    m_backButton->getRenderer()->setTextColor(sfex::Color::Black);
    m_backButton->getRenderer()->setBackgroundColor(Global::menuButtonColor);
    m_backButton->getRenderer()->setBackgroundColorHover(
        sfex::Math::lerp(Global::menuButtonColor, sfex::Color::Black, 0.2)
    );
    m_backButton->getRenderer()->setBackgroundColorDown(
        sfex::Math::lerp(Global::menuButtonColor, sfex::Color::Black, 0.4)
    );
    m_backButton->setSize("17%","9%");
    m_backButton->setTextSize(Global::menuButtonCharSize);
    m_backButton->getRenderer()->setBorders(tgui::Borders(2));
    m_backButton->getRenderer()->setBorderColor(sfex::Color::Black);
    m_backButton->setMouseCursor(tgui::Cursor::Type::Hand);
    m_backButton->setPosition("(parent.width - width) / 2", "parent.height - height - 5%");
    m_backButton->onClick([this](){
        getParent()->switchScene("main_menu");
    });
}

AboutScene::~AboutScene()
{

}

void AboutScene::pollEvent(const sf::Event& e)
{
    
}

void AboutScene::start()
{
    getParent()->getGUI()->add(m_titleLabel);
    getParent()->getGUI()->add(m_aboutDescription);
    getParent()->getGUI()->add(m_developerDescription);
    getParent()->getGUI()->add(m_backButton);
}

void AboutScene::update()
{
    float deltaTime = getParent()->getDeltaTime();

    m_aboutGradient.update(deltaTime);
    m_titleLabel->getRenderer()->setTextColor(m_aboutGradient.getCurrentColor());
}

void AboutScene::lateUpdate()
{

}

void AboutScene::draw(sf::RenderTarget& target)
{
    
}

void AboutScene::destroy()
{
    // m_gui.setOverrideMouseCursor(tgui::Cursor::Type::Arrow);
    getParent()->getGUI()->remove(m_titleLabel);
    getParent()->getGUI()->remove(m_aboutDescription);
    getParent()->getGUI()->remove(m_developerDescription);
    getParent()->getGUI()->remove(m_backButton);
}

}