#pragma once
#include <SFML/Graphics.hpp>
#include <lua.hpp>

#define LUA_EVENT_CLASSNAME "Event"
#define LUA_EVENT_METATABLENAME LUA_EVENT_CLASSNAME"_metatable"
typedef sf::Event Lua_Event;

class LuaExporter;
struct EventExporter
{
    static void createEvent(lua_State* L, const Lua_Event& event);
    static int __new(lua_State* L);
    static int __destroy(lua_State* L);
    static int __index(lua_State* L);
    
    static LuaExporter toLuaExporter();
};