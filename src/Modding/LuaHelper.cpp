#include <Modding/LuaHelper.hpp>
#include <Global.hpp>
#include <Modding/Exporters/EntityExporter.hpp>

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

void LuaHelper::push(lua_State* L, void* val, std::size_t size, const std::string& metatableName)
{
    void* newData = lua_newuserdata(L, size);
    std::memcpy(newData, val, size);
    luaL_getmetatable(L, metatableName.c_str());
    lua_setmetatable(L, -2);
}

void LuaHelper::push(lua_State* L, const std::tuple<void*, std::size_t, std::string>& udataTuple)
{
    auto [newData, size, metatableName] = udataTuple;
    LuaHelper::push(L, newData, size, metatableName);
}

void LuaHelper::push(lua_State* L, Entity* e)
{
    EntityExporter::pushEntity(L, e);
}

int LuaHelper::GetMainWindow(lua_State* L)
{
    LuaHelper::push(L, (void*)Global::mainWindow);
    return 1;
}

int LuaHelper::InterpretLUdataAs(lua_State* L)
{
    lua_pushlightuserdata(L, nullptr);
    std::string dataType = luaL_checkstring(L, 1);
    luaL_setmetatable(L, (dataType + std::string("_metatable")).c_str());
    lua_pop(L, lua_gettop(L));

    return 0;
}

void* LuaHelper::checkudata_orNull(lua_State* L, int index, const std::string& metatableName)
{
    if(lua_islightuserdata(L, index))
    {
        return lua_touserdata(L, index);
    }

    void* ud = lua_touserdata(L, index);
    if(ud != nullptr)
    {
        if(!lua_getmetatable(L, index)) return ud;

        luaL_getmetatable(L, metatableName.c_str());

        if(lua_rawequal(L, -1, -2))
        {
            lua_pop(L, 2);
            return ud;
        }
    }

    return nullptr;
}

void* LuaHelper::checkudata_WithError(lua_State* L, int index, const std::string& metatableName)
{
    if(lua_islightuserdata(L, index))
    {
        return lua_touserdata(L, index);
    }

    void* ud = lua_touserdata(L, index);
    if(ud != nullptr)
    {
        if(!lua_getmetatable(L, index)) return ud;

        luaL_getmetatable(L, metatableName.c_str());
        if(lua_rawequal(L, -1, -2))
        {
            lua_pop(L, 2);
            return ud;
        }
    }

    luaL_error(L, "Expected a userdata with metatable %s got %s", metatableName.c_str(), lua_typename(L, lua_type(L, index)));
    return nullptr;
}

int LuaHelper::MoveData(lua_State* sourceState, lua_State* targetState, int dataIndex)
{
    if(lua_isnil(sourceState, dataIndex))
    {
        lua_pushnil(targetState);
        return 1;
    }
    else if(lua_isboolean(sourceState, dataIndex))
    {
        lua_pushboolean(targetState, lua_toboolean(sourceState, dataIndex));
        return 1;
    }
    else if(lua_isinteger(sourceState, dataIndex))
    {
        lua_pushinteger(targetState, lua_tointeger(sourceState, dataIndex));
        return 1;
    }
    else if(lua_isnumber(sourceState, dataIndex))
    {
        lua_pushnumber(targetState, lua_tonumber(sourceState, dataIndex));
        return 1;
    }
    else if(lua_isstring(sourceState, dataIndex))
    {
        lua_pushstring(targetState, lua_tostring(sourceState, dataIndex));
        return 1;
    }
    else if (lua_islightuserdata(sourceState, dataIndex))
    {
        void* srcPtr = lua_touserdata(sourceState, dataIndex);
        lua_pushlightuserdata(targetState, srcPtr);
        return 1;
    }
    else if(lua_isuserdata(sourceState, dataIndex))
    {
        void* srcPtr = lua_touserdata(sourceState, dataIndex);
        std::string metatableName;
        if(lua_getmetatable(sourceState, dataIndex))
        {
            lua_pushstring(sourceState, "__name");
            lua_rawget(sourceState, -2);
            metatableName = luaL_checkstring(sourceState, -1);

            lua_pop(sourceState, 2);
        }
        std::size_t pointerSize = lua_rawlen(sourceState, dataIndex);
        void* destPtr = lua_newuserdata(targetState, pointerSize);
        std::memcpy(destPtr, srcPtr, pointerSize);

        if(!metatableName.empty())
        {
            luaL_setmetatable(targetState, metatableName.c_str());
        }

        return 1;
    }

    luaL_error(sourceState, "This global value type is not supported! (type=%s)", lua_typename(sourceState, lua_type(sourceState, -1)));
    return 0;
}