#pragma once
#include <InGame/Collider.hpp>
#include <lua.hpp>

#define LUA_COLLIDER_CLASSNAME "Collider"
#define LUA_COLLIDER_METATABLENAME LUA_COLLIDER_CLASSNAME"_metatable"
typedef Collider Exported_Collider;

class LuaExporter;
struct ColliderExporter
{
    static void createCollider(lua_State* L, const Exported_Collider& collider);
    static int __new(lua_State* L);
    static int __destroy(lua_State* L);
    static int __index(lua_State* L);

    static int setPoints(lua_State* L);
    static int setStatic(lua_State* L);
    static int setImmovable(lua_State* L);
    static int setEntity(lua_State* L);
    static int getColliderCenter(lua_State* L);
    static int getPoints(lua_State* L);
    static int getInnerLines(lua_State* L);
    static int getOuterLines(lua_State* L);
    static int isStatic(lua_State* L);
    static int isImmovable(lua_State* L);
    static int getEntity(lua_State* L);
    static int checkCollisions(lua_State* L);

    static LuaExporter toLuaExporter();
};