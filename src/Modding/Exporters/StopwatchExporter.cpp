#include <Modding/Exporters/StopwatchExporter.hpp>
#include <Modding/LuaExporter.hpp>
#include "Modding/LuaHelper.hpp"

void StopwatchExporter::createStopwatch(lua_State *L, const Lua_Stopwatch& stopwatch)
{
    void* data = lua_newuserdata(L, sizeof(Lua_Stopwatch));
    new (data) Lua_Stopwatch(stopwatch);
    luaL_getmetatable(L, LUA_STOPWATCH_METATABLENAME);
    lua_setmetatable(L, -2);
}

int StopwatchExporter::__new(lua_State *L)
{
    createStopwatch(L, Lua_Stopwatch());
    return 1;
}

int StopwatchExporter::__destroy(lua_State *L)
{
    Lua_Stopwatch* stopwatchPtr = static_cast<Lua_Stopwatch*>( LuaHelper::checkudata_WithError(L, 1, LUA_STOPWATCH_METATABLENAME) );
    stopwatchPtr->~Lua_Stopwatch();
    return 0;
}

int StopwatchExporter::__index(lua_State *L)
{
    Lua_Stopwatch* stopwatchPtr = static_cast<Lua_Stopwatch*>( LuaHelper::checkudata_WithError(L, 1, LUA_STOPWATCH_METATABLENAME) );
    std::string indexStr = luaL_checkstring(L, 2);

    lua_getglobal(L, LUA_STOPWATCH_CLASSNAME);
    lua_pushstring(L, indexStr.c_str());
    lua_rawget(L, -2);
    return 1;
}

int StopwatchExporter::getElapsedTime(lua_State *L)
{
    Lua_Stopwatch* stopwatchPtr = static_cast<Lua_Stopwatch*>( LuaHelper::checkudata_WithError(L, 1, LUA_STOPWATCH_METATABLENAME) );
    lua_pushnumber(L, stopwatchPtr->getElapsedTime().asSeconds());
    return 1;
}

int StopwatchExporter::pause(lua_State *L)
{
    Lua_Stopwatch* stopwatchPtr = static_cast<Lua_Stopwatch*>( LuaHelper::checkudata_WithError(L, 1, LUA_STOPWATCH_METATABLENAME) );
    stopwatchPtr->pause();
    return 0;
}

int StopwatchExporter::resume(lua_State *L)
{
    Lua_Stopwatch* stopwatchPtr = static_cast<Lua_Stopwatch*>( LuaHelper::checkudata_WithError(L, 1, LUA_STOPWATCH_METATABLENAME) );
    stopwatchPtr->resume();
    return 0;
}

int StopwatchExporter::restart(lua_State *L)
{
    Lua_Stopwatch* stopwatchPtr = static_cast<Lua_Stopwatch*>( LuaHelper::checkudata_WithError(L, 1, LUA_STOPWATCH_METATABLENAME) );
    stopwatchPtr->restart();
    return 0;
}

int StopwatchExporter::isPaused(lua_State *L)
{
    Lua_Stopwatch* stopwatchPtr = static_cast<Lua_Stopwatch*>( LuaHelper::checkudata_WithError(L, 1, LUA_STOPWATCH_METATABLENAME) );
    lua_pushboolean(L, stopwatchPtr->isPaused());
    return 1;
}

LuaExporter StopwatchExporter::toLuaExporter()
{
    LuaExporter exporter(
        LUA_STOPWATCH_CLASSNAME,
        StopwatchExporter::__new,
        {
            {"getElapsedTime", StopwatchExporter::getElapsedTime},
            {"pause", StopwatchExporter::pause},
            {"resume", StopwatchExporter::resume},
            {"restart", StopwatchExporter::restart},
            {"isPaused", StopwatchExporter::isPaused},
        },
        {
            {"__gc", StopwatchExporter::__destroy},
            {"__index", StopwatchExporter::__index},
        }
    );

    return exporter;
}