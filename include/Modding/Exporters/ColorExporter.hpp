#pragma once
#include <SFEX/Graphics/Color.hpp>
#include <lua.hpp>

#define LUA_COLOR_CLASSNAME "Color"
typedef sfex::Color Lua_Color;

class LuaExporter;
struct ColorExporter
{
    static void createColor(lua_State* L, const sfex::Color& color);
    static int __new(lua_State* L);
    static int __destroy(lua_State* L);
    static int __index(lua_State* L);
    static int __newindex(lua_State* L);
    static int __toString(lua_State* L);
    static int __add(lua_State* L);
    static int __sub(lua_State* L);
    static int __mul(lua_State* L);
    static int __div(lua_State* L);
    static int __eq(lua_State* L);

    static int toHex(lua_State* L);
    static int toGrayscale(lua_State* L);
    static int mixColors(lua_State* L);

    static LuaExporter toLuaExporter();
};
