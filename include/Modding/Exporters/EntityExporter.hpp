#pragma once
#include <lua.hpp>

class LuaEntity;
#define LUA_ENTITY_CLASSNAME "Entity"
#define LUA_ENTITY_METATABLENAME LUA_ENTITY_CLASSNAME"_metatable"
typedef Entity* Exported_Entity;

class LuaExporter;
struct EntityExporter
{
    static void createEntity(lua_State* L, const std::string& modName, const std::string& entityName, const sfex::Vec2& position=sfex::Vec2::zero);
    static void pushEntity(lua_State* L, Entity* entity);

    static int __new(lua_State* L);
    static int __destroy(lua_State* L);
    static int __index(lua_State* L);

    static int getHealth(lua_State* L);
    static int setHealth(lua_State* L);
    static int changeHealth(lua_State* L);
    static int getPosition(lua_State* L);
    static int setPosition(lua_State* L);
    static int move(lua_State* L);
    static int getName(lua_State* L);
    static int getModName(lua_State* L);
    static int getFullName(lua_State* L);
    static int getMetadata(lua_State* L);
    static int setMetadata(lua_State* L);
    static int getCollider(lua_State* L);
    static int setCollider(lua_State* L);
    static int destroy(lua_State* L);
    static int isPlayer(lua_State* L);
    static int getPlayerId(lua_State* L);

    static int findEntitiesWithName(lua_State* L);
    static int getGlobal(lua_State* L);
    static int setGlobal(lua_State* L);
    static int callFunction(lua_State* L);
    static int runCode(lua_State* L);

    static LuaExporter toLuaExporter();
};