#pragma once
#include <SFEX/Numeric/Vector2.hpp>
#include <lua.hpp>

#define LUA_VECTOR2_CLASSNAME "Vector2"
#define LUA_VECTOR2_METATABLENAME LUA_VECTOR2_CLASSNAME"_metatable"
typedef sfex::Vector2<lua_Number> Lua_Vector2;

class LuaExporter;
struct Vector2Exporter
{
    /// Lua Functions
    static void createVector(lua_State* L, const Lua_Vector2& vec);
    static int __new(lua_State* L);
    static int __destroy(lua_State* L);
    static int __index(lua_State* L);
    static int __newindex(lua_State* L);
    static int __toString(lua_State* L);
    static int __unm(lua_State* L);
    static int __add(lua_State* L);
    static int __sub(lua_State* L);
    static int __mul(lua_State* L);
    static int __div(lua_State* L);
    static int __idiv(lua_State* L);
    static int __eq(lua_State* L);
    
    /// Regular Functions
    static int magnitude(lua_State* L);
    static int magnitude2(lua_State* L);
    static int setmagnitude(lua_State* L);
    static int normalize(lua_State* L);
    static int normalized(lua_State* L);
    static int dot(lua_State* L);
    static int cross(lua_State* L);
    static int cwiseMul(lua_State* L);
    static int cwiseDiv(lua_State* L);
    static int scale(lua_State* L);
    static int scaled(lua_State* L);
    static int rotate(lua_State* L);
    static int rotated(lua_State* L);
    static int angle(lua_State* L);
    static int projectOnto(lua_State* L);
    static int projectedOnto(lua_State* L);

    /// Lua Exporter
    static LuaExporter toLuaExporter();
};

