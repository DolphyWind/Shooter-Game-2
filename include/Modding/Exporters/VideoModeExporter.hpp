#pragma once
#include <SFML/Graphics.hpp>
#include <lua.hpp>

#define LUA_VIDEOMODE_CLASSNAME "VideoMode"
#define LUA_VIDEOMODE_METATABLENAME LUA_VIDEOMODE_CLASSNAME"_metatable"
typedef sf::VideoMode Exported_VideoMode;

class LuaExporter;
struct VideoModeExporter
{
    static void createVideoMode(lua_State* L, const Exported_VideoMode& videoMode);
    static int __new(lua_State* L);
    static int __destroy(lua_State* L);
    static int __index(lua_State* L);
    static int __newindex(lua_State* L);
    static int __eq(lua_State* L);
    static int __lt(lua_State* L);
    static int __le(lua_State* L);

    static int isValid(lua_State* L);
    static int getDesktopMode(lua_State* L);
    static int getFullscreenModes(lua_State* L);

    static LuaExporter toLuaExporter();
};