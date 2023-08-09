#pragma once
#include <SFML/Graphics/Rect.hpp>
#include <lua.hpp>

#define LUA_FLOATRECT_CLASSNAME "FloatRect"
typedef sf::FloatRect Lua_FloatRect;

class LuaExporter;
struct FloatRectExporter
{
    static void createFloatRect(lua_State* L, const Lua_FloatRect& floatRect);
    static int __new(lua_State* L);
    static int __destroy(lua_State* L);
    static int __index(lua_State* L);
    static int __newindex(lua_State* L);
    static int __eq(lua_State* L);

    static int contains(lua_State* L);
    static int intersects(lua_State* L);
    static int getPosition(lua_State* L);
    static int getSize(lua_State* L);

    static LuaExporter toLuaExporter();
};