#pragma once
#include <SFEX/General/Keyboard.hpp>
#include <lua.hpp>

#define LUA_JOYSTICK_CLASSNAME "Joystick"

class LuaExporter;
struct JoystickExporter
{

static int isConnected(lua_State* L);
static int getButtonCount(lua_State* L);
static int hasAxis(lua_State* L);
static int getButton(lua_State* L);
static int getButtonDown(lua_State* L);
static int getButtonUp(lua_State* L);
static int getAxisPosition(lua_State* L);

static LuaExporter toLuaExporter();
};