#pragma once
#include <lua.hpp>
#include <string>

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
    static void push(lua_State* L, lua_CFunction val);

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
