#pragma once

#include <SFEX/Numeric/Vector2.hpp>
#include <lua.hpp>

#define LUA_MOUSE_CLASSNAME "Mouse"

class LuaExporter;
struct MouseExporter
{

static int getButton(lua_State* L);
static int getButtonDown(lua_State* L);
static int getButtonUp(lua_State* L);
static int getPosition(lua_State* L);
static int setPosition(lua_State* L);

static LuaExporter toLuaExporter();

};