#pragma once
#include <SFML/Graphics.hpp>
#include <lua.hpp>

#define LUA_CONTEXTSETTINGS_CLASSNAME "ContextSettings"
#define LUA_CONTEXTSETTINGS_METATABLENAME LUA_CONTEXTSETTINGS_CLASSNAME"_metatable"
typedef sf::ContextSettings Exported_ContextSettings;

class LuaExporter;
struct ContextSettingsExporter
{
    static void createContextSetting(lua_State* L, const Exported_ContextSettings& settings);
    static int __new(lua_State* L);
    static int __destroy(lua_State* L);
    static int __index(lua_State* L);
    static int __newindex(lua_State* L);

    static LuaExporter toLuaExporter();
};