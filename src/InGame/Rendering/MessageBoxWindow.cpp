#include <InGame/Rendering/MessageBoxWindow.hpp>

namespace sg
{

MessageBoxWindow::MessageBoxWindow(const sfex::Vec2u& windowSize, const tgui::String& title, const tgui::String& message, const std::vector<tgui::String>& buttons):
    m_window(sf::VideoMode(windowSize.x, windowSize.y), title.toStdString()), m_gui(m_window)
{
    m_messageBox = tgui::MessageBox::create("", message);
    m_titlebarHeight = m_messageBox->getRenderer()->getTitleBarHeight();

    m_messageBox->setSize("100%", fmt::format("100% + {}", m_titlebarHeight).c_str());
    m_messageBox->setPosition(0, -m_titlebarHeight);
    m_messageBox->setPositionLocked(true);
    m_messageBox->onButtonPress(&MessageBoxWindow::handleButtonPress, this);
    m_gui.add(m_messageBox);

    /// Buttons
    std::size_t i = 0;
    float total_width = 0.0f;
    for(auto& button : buttons)
    {
        tgui::Button::Ptr newButton = tgui::Button::create(button);
        newButton->setPosition(fmt::format("20 + {} + 5 * {}", total_width, i).c_str(), "100% - height - 20");
        newButton->onPress(&MessageBoxWindow::handleButtonPress, this);
        total_width += newButton->getSize().x;
        m_gui.add(newButton);
        ++i;
    }
}

tgui::String MessageBoxWindow::show()
{
    while(m_window.isOpen())
    {
        sf::Event e;
        while(m_window.pollEvent(e))
        {
            if(e.type == sf::Event::Closed)
            {
                m_window.close();
            }
            m_gui.handleEvent(e);
        }

        m_window.clear();
        m_gui.draw();
        m_window.display();
    }
    return m_buttonString;
}

void MessageBoxWindow::handleButtonPress(const tgui::String& buttonText)
{
    m_buttonString = std::move(buttonText);
    m_window.close();
}

}