#pragma once
#include <SFML/Graphics/Rect.hpp>
#include <lua.hpp>

#define LUA_INTRECT_CLASSNAME "IntRect"
typedef sf::IntRect Lua_IntRect;

class LuaExporter;
struct IntRectExporter
{
    static void createIntRect(lua_State* L, const Lua_IntRect& intRect);
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