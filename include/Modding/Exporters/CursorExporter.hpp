#pragma once

#include <SFML/Graphics.hpp>
#include <lua.hpp>

#define LUA_CURSOR_CLASSNAME "Cursor"
#define LUA_CURSOR_METATABLENAME LUA_CURSOR_CLASSNAME"_metatable"
typedef sf::Cursor Lua_Cursor;

class LuaExporter;
struct CursorExporter
{
    static void createCursor(lua_State* L);
    static int __new(lua_State* L);
    static int __destroy(lua_State* L);
    static int __index(lua_State* L);

    static int loadFromImage(lua_State* L);
    static int loadFromSystem(lua_State* L);

    static LuaExporter toLuaExporter();
};