#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <OsSpecific/Config.hpp>
#include <SFEX/SFEX.hpp>
#if defined (SG_OS_WINDOWS)
#include <Windows.h>
#elif defined (SG_OS_LINUX)
#include <X11/Xlib.h>
#include <X11/Xutil.h>
#elif defined (SG_OS_APPLE)
// Include apple stuff
#endif

namespace sg
{


class WindowFunctionalities : public sfex::StaticClass
{
public:
    static void setMinimumSize(sf::RenderWindow& window, const sfex::Vec2u& windowSize);

};


}