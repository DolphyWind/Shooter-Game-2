#include <OsSpecific/WindowFunctionalities.hpp>

namespace sg
{

void WindowFunctionalities::setMinimumSize(sf::RenderWindow &window, const sfex::Vec2u &windowSize)
{
    sf::WindowHandle windowHandle = window.getSystemHandle();
#if defined (SG_OS_LINUX)
    XSizeHints *size_hints = XAllocSizeHints();
    size_hints->flags = PMinSize;
    size_hints->min_width = windowSize.x;  // Set minimum width
    size_hints->min_height = windowSize.y; // Set minimum height
    
    Display* display = XOpenDisplay(NULL);
    XWindowAttributes window_attributes;
    XGetWindowAttributes(display, windowHandle, &window_attributes);

    // Get the display of the window
    Display *window_display = window_attributes.screen->display;
    XSetNormalHints(window_display, windowHandle, size_hints);
    XCloseDisplay(display);
#elif defined (SG_OS_WINDOWS)
    // AFAIK Windows does not have a function that sets the minimum size of the window.
    // I tried a lot of ways to implment it but none of them worked. So it is implemented
    // in Game::handleEvents by checking size and resizing accurdingly. It is not one to one
    // but it is OK
#elif defined (SG_OS_APPLE)
#endif
}

}