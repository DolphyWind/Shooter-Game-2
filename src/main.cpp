#include <SFML/Graphics.hpp>
#include <TGUI/TGUI.hpp>
#include <fmt/core.h>
#include <clip/clip.h>
#include <pprint/pprint.hpp>
#include <box2d/box2d.h>
#include <iostream>
#include <curl/curl.h>

int main(int argc, char** argv)
{
    sf::RenderWindow window(sf::VideoMode(200, 200), "SFML works!");
    tgui::GuiSFML gui(window);
    tgui::Button::Ptr testButton = tgui::Button::create("Click Me!");

    bool pressed = false;
    testButton->onPress([&](){
        if(pressed) return;
        tgui::MessageBox::Ptr messageBox = tgui::MessageBox::create("Thanks!", "You've pressed me!", {"Ok", "Close"});
        messageBox->setWidgetName("msgBox");
        messageBox->onButtonPress([&](tgui::String buttonStr){
            if(buttonStr == "Ok")
            {
                gui.remove(gui.get("msgBox"));
                pressed = false;
            }
            else if(buttonStr == "Close")
            {
                window.close();
            }
        });
        messageBox->setPosition("(parent.width - width) / 2", "(parent.height - height) / 2");

        gui.add(messageBox);
        pressed = true;
    });
    gui.add(testButton);

    while (window.isOpen())
    {
        sf::Event event{};
        while (window.pollEvent(event))
        {
            gui.handleEvent(event);
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();

        gui.draw();
        window.display();
    }

    return 0;
}