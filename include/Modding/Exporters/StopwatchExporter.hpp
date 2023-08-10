#pragma once
#include <SFEX/General/Stopwatch.hpp>
#include <lua.hpp>

#define LUA_STOPWATCH_CLASSNAME "Stopwatch"
#define LUA_STOPWATCH_METATABLENAME LUA_STOPWATCH_CLASSNAME"_metatable"
typedef sfex::Stopwatch Lua_Stopwatch;

class LuaExporter;
struct StopwatchExporter
{
    static void createStopwatch(lua_State* L, const Lua_Stopwatch& stopwatch);
    static int __new(lua_State* L);
    static int __destroy(lua_State* L);
    static int __index(lua_State* L);

    static int getElapsedTime(lua_State* L);
    static int pause(lua_State* L);
    static int resume(lua_State* L);
    static int restart(lua_State* L);
    static int isPaused(lua_State* L);

    static LuaExporter toLuaExporter();
};