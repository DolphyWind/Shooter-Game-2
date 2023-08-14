#include <Modding/LuaHelper.hpp>
#include <Global.hpp>
#include <Modding/Exporters/RenderWindowExporter.hpp>

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

void LuaHelper::push(lua_State* L, const std::pair<void*, std::string>& dataWithMetatable)
{
    LuaHelper::push(L, dataWithMetatable.first, dataWithMetatable.second);
}

void LuaHelper::push(lua_State* L, lua_CFunction val)
{
    lua_pushcfunction(L, val);
}

int LuaHelper::LuaGetMainWindow(lua_State* L)
{
    LuaHelper::push(L, {(void*)Global::mainWindow, LUA_RENDERWINDOW_METATABLENAME});
    return 1;
}

void* LuaHelper::checkudata(lua_State* L, int index, const std::string& metatableName)
{
    void* ud = lua_touserdata(L, index);
    if(ud != nullptr)
    {
        if(lua_getmetatable(L, index))
        {
            luaL_getmetatable(L, metatableName.c_str());

            if(lua_rawequal(L, -1, -2))
            {
                lua_pop(L, 2);
                return ud;
            }
        }
    }

    return nullptr;
}
