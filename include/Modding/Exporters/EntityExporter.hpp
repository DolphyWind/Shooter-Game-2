#pragma once
#include <lua.hpp>

class LuaEntity;
#define LUA_ENTITY_CLASSNAME "Entity"
#define LUA_ENTITY_METATABLENAME LUA_ENTITY_CLASSNAME"_metatable"
typedef LuaEntity* Lua_Entity;

class LuaExporter;
struct EntityExporter
{
    // These will be implemented later when I create the mod manager.
//    static void createEntity(lua_State* L, const Lua_ContextSettings& settings);
//    static int __new(lua_State* L);
//    static int __destroy(lua_State* L);
    static int __index(lua_State* L);
//    static int __newindex(lua_State* L);

    static int setHealth(lua_State* L);
    static int changeHealth(lua_State* L);
    static int getHealth(lua_State* L);
    static int setPosition(lua_State* L);
    static int getPosition(lua_State* L);
    static int move(lua_State* L);
//    static int isPlayer(lua_State* L);
//    static int setName(lua_State* L);
    static int getName(lua_State* L);
//    static int getFullName(lua_State* L); This will be implemented after I create the ModManager. Equals to {modname}::{name}
    static int setMetadata(lua_State* L);
    static int getMetadata(lua_State* L);
    static int setCollider(lua_State* L);
    // static int getColliderInnerLines(lua_State* L);
    // static int getColliderOuterLines(lua_State* L);

    static int findEntitiesWithName(lua_State* L);
    static int getGlobal(lua_State* L);
    static int setGlobal(lua_State* L);
    static int callFunction(lua_State* L);
    static int runCode(lua_State* L);

    static LuaExporter toLuaExporter();
};