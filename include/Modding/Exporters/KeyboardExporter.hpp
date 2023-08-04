#pragma once

#include <SFEX/Numeric/Vector2.hpp>
#include <lua.hpp>

#define LUA_KEYBOARD_CLASSNAME "Keyboard"

class LuaExporter;
struct KeyboardExporter
{

static int getKey(lua_State* L);
static int getKeyDown(lua_State* L);
static int getKeyUp(lua_State* L);

static LuaExporter toLuaExporter();

};