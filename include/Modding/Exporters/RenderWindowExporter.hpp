#pragma once
#include <SFML/Graphics.hpp>
#include <lua.hpp>

#define LUA_RENDERWINDOW_CLASSNAME "RenderWindow"
#define LUA_RENDERWINDOW_METATABLENAME LUA_RENDERWINDOW_CLASSNAME"_metatable"
typedef sf::RenderWindow Lua_RenderWindow;

class LuaExporter;
struct RenderWindowExporter
{
    static void createRenderWindow(
        lua_State* L,
        sf::VideoMode mode,
        const std::string title,
        sf::Uint32 style=sf::Style::Default,
        const sf::ContextSettings& settings = sf::ContextSettings()
    );
    static int __new(lua_State* L);
    static int __destroy(lua_State* L);
    static int __index(lua_State* L);

    static int getSize(lua_State* L);
    static int setActive(lua_State* L);
    static int close(lua_State* L);
    static int isOpen(lua_State* L);

    static int getSettings(lua_State* L);
    static int pollEvent(lua_State* L);
    static int waitEvent(lua_State* L);

    static int getPosition(lua_State* L);
    static int setPosition(lua_State* L);
    static int setSize(lua_State* L);
    static int setTitle(lua_State* L);
    static int setIcon(lua_State* L);
    static int setVisible(lua_State* L);
    static int setVerticalSyncEnabled(lua_State* L);
    static int setMouseCursorVisible(lua_State* L);
    static int setMouseCursorGrabbed(lua_State* L);
    static int setMouseCursor(lua_State* L);
    static int setKeyRepeatEnabled(lua_State* L);
    static int setFramerateLimit(lua_State* L);
    static int setJoystickTreshold(lua_State* L);
    static int requestFocus(lua_State* L);
    static int hasFocus(lua_State* L);
    static int display(lua_State* L);
    static int clear(lua_State* L);
    static int setView(lua_State* L);
    static int getView(lua_State* L);
    static int getDefaultView(lua_State* L);
    static int getViewPort(lua_State* L);
    static int mapPixelToCoords(lua_State* L);
    static int mapCoordsToPixel(lua_State* L);
    static int draw(lua_State* L);
    static int pushGLStates(lua_State* L);
    static int popGLStates(lua_State* L);
    static int resetGLStates(lua_State* L);


    static LuaExporter toLuaExporter();
};