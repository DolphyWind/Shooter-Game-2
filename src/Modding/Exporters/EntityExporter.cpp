#include <Modding/LuaExporter.hpp>
#include <InGame/LuaEntity.hpp>
#include <Modding/Exporters/EntityExporter.hpp>
#include <Modding/Exporters/Vector2Exporter.hpp>
#include <Modding/Exporters/ColliderExporter.hpp>

int EntityExporter::__index(lua_State* L)
{
    Lua_Entity* entityPtr = static_cast<Lua_Entity*>( LuaHelper::checkudata_WithError(L, 1, LUA_ENTITY_METATABLENAME) );
    std::string indexStr = luaL_checkstring(L, 2);

    lua_getglobal(L, LUA_ENTITY_CLASSNAME);
    lua_pushstring(L, indexStr.c_str());
    lua_rawget(L, -2);
    return 1;
}

int EntityExporter::setHealth(lua_State* L)
{
    Lua_Entity* entityPtr = static_cast<Lua_Entity*>( LuaHelper::checkudata_WithError(L, 1, LUA_ENTITY_METATABLENAME) );
    entityPtr->setHealth(luaL_checknumber(L, 2));

    return 0;
}

int EntityExporter::changeHealth(lua_State* L)
{
    Lua_Entity* entityPtr = static_cast<Lua_Entity*>( LuaHelper::checkudata_WithError(L, 1, LUA_ENTITY_METATABLENAME) );
    entityPtr->changeHealth(luaL_checknumber(L, 2));

    return 0;
}

int EntityExporter::getHealth(lua_State* L)
{
    Lua_Entity* entityPtr = static_cast<Lua_Entity*>( LuaHelper::checkudata_WithError(L, 1, LUA_ENTITY_METATABLENAME) );
    lua_pushnumber(L, entityPtr->getHealth());

    return 1;
}

int EntityExporter::setPosition(lua_State* L)
{
    Lua_Entity* entityPtr = static_cast<Lua_Entity*>( LuaHelper::checkudata_WithError(L, 1, LUA_ENTITY_METATABLENAME) );
    Lua_Vector2* vecPtr = static_cast<Lua_Vector2*>( LuaHelper::checkudata_WithError(L, 2, LUA_VECTOR2_METATABLENAME) );
    entityPtr->setPosition(*vecPtr);

    return 0;
}

int EntityExporter::getPosition(lua_State* L)
{
    Lua_Entity* entityPtr = static_cast<Lua_Entity*>( LuaHelper::checkudata_WithError(L, 1, LUA_ENTITY_METATABLENAME) );
    Vector2Exporter::createVector(L, entityPtr->getPosition());

    return 1;
}

int EntityExporter::move(lua_State* L)
{
    Lua_Entity* entityPtr = static_cast<Lua_Entity*>( LuaHelper::checkudata_WithError(L, 1, LUA_ENTITY_METATABLENAME) );
    Lua_Vector2* vecPtr = static_cast<Lua_Vector2*>( LuaHelper::checkudata_WithError(L, 2, LUA_VECTOR2_METATABLENAME) );
    entityPtr->move(*vecPtr);

    return 0;
}

int EntityExporter::getName(lua_State* L)
{
    Lua_Entity* entityPtr = static_cast<Lua_Entity*>( LuaHelper::checkudata_WithError(L, 1, LUA_ENTITY_METATABLENAME) );
    lua_pushstring(L, entityPtr->getName().c_str());

    return 1;
}

int EntityExporter::setMetadata(lua_State* L)
{
    Lua_Entity* entityPtr = static_cast<Lua_Entity*>( LuaHelper::checkudata_WithError(L, 1, LUA_ENTITY_METATABLENAME) );
    entityPtr->setMetadata(luaL_checkstring(L, 2));

    return 0;
}

int EntityExporter::getMetadata(lua_State* L)
{
    Lua_Entity* entityPtr = static_cast<Lua_Entity*>( LuaHelper::checkudata_WithError(L, 1, LUA_ENTITY_METATABLENAME) );
    lua_pushstring(L, entityPtr->getMetadata().c_str());

    return 1;
}

int EntityExporter::setCollider(lua_State* L)
{
    Lua_Entity* entityPtr = static_cast<Lua_Entity*>( LuaHelper::checkudata_WithError(L, 1, LUA_ENTITY_METATABLENAME) );
    Lua_Collider* colliderPtr = static_cast<Lua_Collider*>( LuaHelper::checkudata_WithError(L, 2, LUA_COLLIDER_METATABLENAME) );

    entityPtr->setCollider(*colliderPtr);

    return 0;
}

int EntityExporter::getGlobal(lua_State* L)
{
    Lua_Entity* entityPtr = static_cast<Lua_Entity*>( LuaHelper::checkudata_WithError(L, 1, LUA_ENTITY_METATABLENAME) );
    lua_State* sourceState = entityPtr->getLuaState();
    std::string varname = lua_tostring(L, 2);

    lua_getglobal(sourceState, varname.c_str());
    return LuaHelper::MoveData(sourceState, L, -1);
}

int EntityExporter::setGlobal(lua_State* L)
{
    Lua_Entity* entityPtr = static_cast<Lua_Entity*>( LuaHelper::checkudata_WithError(L, 1, LUA_ENTITY_METATABLENAME) );
    lua_State* targetState = entityPtr->getLuaState();
    std::string varname = lua_tostring(L, 2);
    int returnVal = LuaHelper::MoveData(L, targetState, 3);
    if(!returnVal) return 0;

    lua_setglobal(targetState, varname.c_str());
    return 0;
}

int EntityExporter::runCode(lua_State* L)
{
    Lua_Entity* entityPtr = static_cast<Lua_Entity*>( LuaHelper::checkudata_WithError(L, 1, LUA_ENTITY_METATABLENAME) );
    lua_State* entityState = entityPtr->getLuaState();
    std::string code = luaL_checkstring(L, 2);
    luaL_dostring(entityState, code.c_str());

    return 0;
}

LuaExporter EntityExporter::toLuaExporter()
{
    LuaExporter exporter(
        LUA_ENTITY_CLASSNAME,
        nullptr,
        {
            {"setHealth", EntityExporter::setHealth},
            {"changeHealth", EntityExporter::changeHealth},
            {"getHealth", EntityExporter::getHealth},
            {"setPosition", EntityExporter::setPosition},
            {"getPosition", EntityExporter::getPosition},
            {"move", EntityExporter::move},
            {"getName", EntityExporter::getName},
            {"setMetadata", EntityExporter::setMetadata},
            {"getMetadata", EntityExporter::getMetadata},
            {"setCollider", EntityExporter::setCollider},
            {"getGlobal", EntityExporter::getGlobal},
            {"setGlobal", EntityExporter::setGlobal},
            {"runCode", EntityExporter::runCode},
        },
        {
            {"__index", EntityExporter::__index},
        }
    );

    return exporter;
}
