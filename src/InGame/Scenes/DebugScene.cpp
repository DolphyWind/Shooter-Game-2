#include <InGame/Scenes/DebugScene.hpp>
#include <InGame/Game.hpp>

namespace sg
{

DebugScene::DebugScene(Game* parent):
    ExtendedScene(parent)
{
    setBackgroundColor(sfex::Color::Cyan);
    m_welcomeLabel = tgui::Label::create("Welcome to the debug menu!\n"
    "Various test will go here\n"
    );
    m_welcomeLabel->getRenderer()->setTextColor(sfex::Color::Black);
    m_colorPicker = tgui::ColorPicker::create("Color picker");
    m_colorPicker->setPosition(100, 0);
}

void DebugScene::pollEvent(const sf::Event &e)
{
    
}

void DebugScene::start()
{
    m_f3Clock.restart();

    getParent()->getGUI()->add(m_welcomeLabel);
    getParent()->getGUI()->add(m_colorPicker);
}

void DebugScene::update()
{
    if(!sfex::Keyboard::getKey(sfex::Keyboard::Key::F3))
    {
        m_f3Clock.restart();
    }
    if(m_f3Clock.getElapsedTime().asSeconds() > Global::f3Time)
    {
        getParent()->switchScene("main_menu");
    }
    ImGui::Begin("Hello, ImGui!");

    if (ImGui::ColorPicker4("Pick Color", m_colors))
    {
        m_pickedColor.r = m_colors[0] * 255;
        m_pickedColor.g = m_colors[1] * 255;
        m_pickedColor.b = m_colors[2] * 255;
        m_pickedColor.a = m_colors[3] * 255;
        std::cout << m_pickedColor << std::endl;
    }

    ImGui::End();
}

void DebugScene::lateUpdate()
{

}

void DebugScene::draw(sf::RenderTarget &target)
{
    ImGui::SFML::Render(getParent()->getRenderWindow());
}

void DebugScene::destroy()
{
    //m_gui.setOverrideMouseCursor(tgui::Cursor::Type::Arrow);
    getParent()->getGUI()->remove(m_welcomeLabel);
    getParent()->getGUI()->remove(m_colorPicker);
}

}