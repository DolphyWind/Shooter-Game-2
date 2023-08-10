#pragma once
#include <SFML/Graphics/Transform.hpp>
#include <lua.hpp>

#define LUA_TRANSFORM_CLASSNAME "Transform"
#define LUA_TRANSFORM_METATABLENAME LUA_TRANSFORM_CLASSNAME"_metatable"
typedef sf::Transform Lua_Transform;

class LuaExporter;
struct TransformExporter
{
    static void createTransform(lua_State* L, const Lua_Transform& transform);
    static int __new(lua_State* L);
    static int __destroy(lua_State* L);
    static int __index(lua_State* L);
    static int __mul(lua_State* L);
    static int __eq(lua_State* L);

    static int getMatrix(lua_State* L);
    static int getInverse(lua_State* L);
    static int transformPoint(lua_State* L);
    static int transformRect(lua_State* L);
    static int combine(lua_State* L);
    static int translate(lua_State* L);
    static int rotate(lua_State* L);
    static int scale(lua_State* L);

    static LuaExporter toLuaExporter();
};