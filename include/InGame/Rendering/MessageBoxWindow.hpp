#pragma once
// #include <TGUI/Backends/SFML.hpp>
#include <SFML/Graphics.hpp>
#include <TGUI/Backend/SFML-Graphics.hpp>
#include <fmt/core.h>
#include <TGUI/TGUI.hpp>
#include <SFEX/SFEX.hpp>

namespace sg
{

class MessageBoxWindow
{
public:
    MessageBoxWindow(const sfex::Vec2u& windowSize, const tgui::String& title, const tgui::String& message, const std::vector<tgui::String>& buttons={});
    
    [[maybe_unused]] tgui::String show();
    void handleButtonPress(const tgui::String& buttonText);
private:
    sf::RenderWindow m_window;
    tgui::Gui m_gui;
    tgui::MessageBox::Ptr m_messageBox;
    float m_titlebarHeight;
    tgui::String m_buttonString;
};

}