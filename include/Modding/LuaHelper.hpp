#pragma once
#include <lua.hpp>
#include <string>

class Entity;
class LuaHelper
{
public:

    static void push(lua_State* L, int val);
    static void push(lua_State* L, double val);
    static void push(lua_State* L, float val);
    static void push(lua_State* L, bool val);
    static void push(lua_State* L, const std::string& val);
    static void push(lua_State* L, const char* val);
    static void push(lua_State* L, void* val);
    static void push(lua_State* L, void* val, const std::string& metatableName);
    static void push(lua_State* L, const std::pair<void*, std::string>& dataWithMetatable);
    static void push(lua_State* L, lua_CFunction val);
    static void push(lua_State* L, void* val, std::size_t size, const std::string& metatableName);
    static void push(lua_State* L, const std::tuple<void*, std::size_t, std::string>& udataTuple);
    static void push(lua_State* L, Entity* e);

    static int GetMainWindow(lua_State* L);
    static int InterpretLUdataAs(lua_State* L);

    /// @brief Returns the usertada if it has the said metatable or has no metatable. Otherwise it returns null
    /// @param L Lua state to check
    /// @param index Index of the userdata
    /// @param metatableName Metatable name of the userdata
    /// @return The userdata if the metatables match or has no metatable. Otherwise it returns null
    static void* checkudata_orNull(lua_State* L, int index, const std::string& metatableName);

    /// \brief
    /// \param L
    /// \param index
    /// \param metatableName
    /// \return
    static void* checkudata_WithError(lua_State* L, int index, const std::string& metatableName);

    static int MoveData(lua_State* sourceState, lua_State* targetState, int dataIndex);

    union LuaVariable
    {
        lua_Integer integer;
        lua_Number number;
        lua_CFunction cfunction;
        bool boolean;
        const char* string;
        void* userdata;
    };

};
