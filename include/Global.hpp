#pragma once
#include <thirdparty/effolkronium/random.hpp>
#include <SFEX/General/StaticClass.hpp>
#include <SFEX/SFEX.hpp>
#include <SFML/Graphics.hpp>
#include <optional>

using StaticRandom = effolkronium::random_static;
using LocalRandom = effolkronium::random_local;
using ThreadLocalRandom = effolkronium::random_thread_local;


class Global : public sfex::StaticClass
{
public:
    static constexpr float f3Time = 2.0;
    static const sfex::Color menuButtonColor;
    static constexpr unsigned int menuButtonTextSize = 22;
    static constexpr unsigned int menuButtonBorderRadius = 5;
    static constexpr unsigned int titleTextSize = 42;
    static const sf::RenderWindow* mainWindow;
};
