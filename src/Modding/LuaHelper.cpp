#include <Modding/LuaHelper.hpp>

void LuaHelper::push(lua_State* L, int val)
{
    lua_pushinteger(L, val);
}

void LuaHelper::push(lua_State* L, double val)
{
    lua_pushnumber(L, val);
}

void LuaHelper::push(lua_State* L, float val)
{
    lua_pushnumber(L, val);
}

void LuaHelper::push(lua_State* L, bool val)
{
    lua_pushboolean(L, val);
}

void LuaHelper::push(lua_State* L, const std::string& val)
{
    lua_pushstring(L, val.c_str());
}

void LuaHelper::push(lua_State* L, const char* val)
{
    lua_pushstring(L, val);
}

void LuaHelper::push(lua_State* L, void* val)
{
    lua_pushlightuserdata(L, val);
}

void LuaHelper::push(lua_State* L, void* val, const std::string& metatableName)
{
    lua_pushlightuserdata(L, val);
    luaL_getmetatable(L, metatableName.c_str());
    lua_setmetatable(L, -2);
}

void LuaHelper::push(lua_State* L, lua_CFunction val)
{
    lua_pushcfunction(L, val);
}