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
    MINMAXINFO minMaxInfo = {0};
    minMaxInfo.ptMinTrackSize.x = windowSize.x;   // Set minimum width
    minMaxInfo.ptMinTrackSize.y = windowSize.y;   // Set minimum height
    SendMessage(windowHandle, WM_GETMINMAXINFO, 0, (LPARAM)&minMaxInfo);

#elif defined (SG_OS_APPLE)
#endif
}

}