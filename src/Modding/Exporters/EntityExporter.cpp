#include <Modding/LuaExporter.hpp>
#include <InGame/LuaEntity.hpp>
#include <InGame/GameManager.hpp>
#include <Modding/Exporters/EntityExporter.hpp>
#include <Modding/Exporters/Vector2Exporter.hpp>
#include <Modding/Exporters/ColliderExporter.hpp>

void EntityExporter::createEntity(lua_State* L, const std::string& modName, const std::string& entityName, const sfex::Vec2& position)
{
    void* data = lua_newuserdata(L, sizeof(Exported_Entity));
    luaL_getmetatable(L, LUA_ENTITY_METATABLENAME);
    lua_setmetatable(L, -2);

    Entity* spawnedPtr = Global::defaultModManager.spawnEntity(modName, entityName);
    spawnedPtr->setPosition(position);
    auto* luaEntityPtr = dynamic_cast<LuaEntity*>(spawnedPtr);
    if(!luaEntityPtr) return;
    new (data) Exported_Entity(luaEntityPtr);
}

void EntityExporter::pushEntity(lua_State* L, Entity* entity)
{
    if(!entity)
    {
        lua_pushnil(L);
        return;
    }

    void* data = lua_newuserdata(L, sizeof(Entity*));
    new (data) Entity*(entity);
    luaL_getmetatable(L, LUA_ENTITY_METATABLENAME);
    lua_setmetatable(L, -2);
}

int EntityExporter::__new(lua_State* L)
{
    int arg_count = lua_gettop(L);
    if(arg_count < 2)
    {
        return 0;
    }

    std::string modName = luaL_checkstring(L, 1);
    std::string entityName = luaL_checkstring(L, 2);
    sfex::Vec2 position = sfex::Vec2::zero;
    if(arg_count >= 3)
    {
        position = *static_cast<Lua_Vector2*>( LuaHelper::checkudata_WithError(L, 3, LUA_VECTOR2_METATABLENAME) );
    }

    createEntity(L, modName, entityName, position);

    return 1;
}

int EntityExporter::__destroy(lua_State* L)
{
    return 0;
}

int EntityExporter::__index(lua_State* L)
{
    Exported_Entity* entityPtr = static_cast<Exported_Entity*>( LuaHelper::checkudata_WithError(L, 1, LUA_ENTITY_METATABLENAME) );
    std::string indexStr = luaL_checkstring(L, 2);

    lua_getglobal(L, LUA_ENTITY_CLASSNAME);
    lua_pushstring(L, indexStr.c_str());
    lua_rawget(L, -2);
    return 1;
}

int EntityExporter::getHealth(lua_State* L)
{
    Exported_Entity* entityPtr = static_cast<Exported_Entity*>( LuaHelper::checkudata_WithError(L, 1, LUA_ENTITY_METATABLENAME) );
    lua_pushnumber(L, (*entityPtr)->getHealth());

    return 1;
}

int EntityExporter::setHealth(lua_State* L)
{
    Exported_Entity* entityPtr = static_cast<Exported_Entity*>( LuaHelper::checkudata_WithError(L, 1, LUA_ENTITY_METATABLENAME) );
    (*entityPtr)->setHealth(luaL_checknumber(L, 2));

    return 0;
}

int EntityExporter::changeHealth(lua_State* L)
{
    Exported_Entity* entityPtr = static_cast<Exported_Entity*>( LuaHelper::checkudata_WithError(L, 1, LUA_ENTITY_METATABLENAME) );
    (*entityPtr)->changeHealth(luaL_checknumber(L, 2));

    return 0;
}

int EntityExporter::getPosition(lua_State* L)
{
    Exported_Entity* entityPtr = static_cast<Exported_Entity*>( LuaHelper::checkudata_WithError(L, 1, LUA_ENTITY_METATABLENAME) );
    Vector2Exporter::createVector(L, (*entityPtr)->getPosition());

    return 1;
}

int EntityExporter::setPosition(lua_State* L)
{
    Exported_Entity* entityPtr = static_cast<Exported_Entity*>( LuaHelper::checkudata_WithError(L, 1, LUA_ENTITY_METATABLENAME) );
    Lua_Vector2* vecPtr = static_cast<Lua_Vector2*>( LuaHelper::checkudata_WithError(L, 2, LUA_VECTOR2_METATABLENAME) );
    (*entityPtr)->setPosition(*vecPtr);

    return 0;
}

int EntityExporter::move(lua_State* L)
{
    Exported_Entity* entityPtr = static_cast<Exported_Entity*>( LuaHelper::checkudata_WithError(L, 1, LUA_ENTITY_METATABLENAME) );
    Lua_Vector2* vecPtr = static_cast<Lua_Vector2*>( LuaHelper::checkudata_WithError(L, 2, LUA_VECTOR2_METATABLENAME) );
    (*entityPtr)->move(*vecPtr);
    return 0;
}

int EntityExporter::getName(lua_State* L)
{
    Exported_Entity* entityPtr = static_cast<Exported_Entity*>( LuaHelper::checkudata_WithError(L, 1, LUA_ENTITY_METATABLENAME) );
    lua_pushstring(L, (*entityPtr)->getName().c_str());

    return 1;
}

int EntityExporter::getModName(lua_State* L)
{
    Exported_Entity* entityPtr = static_cast<Exported_Entity*>( LuaHelper::checkudata_WithError(L, 1, LUA_ENTITY_METATABLENAME) );
    lua_pushstring(L, (*entityPtr)->getModName().c_str());

    return 1;
}

int EntityExporter::getFullName(lua_State* L)
{
    Exported_Entity* entityPtr = static_cast<Exported_Entity*>( LuaHelper::checkudata_WithError(L, 1, LUA_ENTITY_METATABLENAME) );
    lua_pushstring(L, (*entityPtr)->getFullName().c_str());

    return 1;
}

int EntityExporter::getMetadata(lua_State* L)
{
    Exported_Entity* entityPtr = static_cast<Exported_Entity*>( LuaHelper::checkudata_WithError(L, 1, LUA_ENTITY_METATABLENAME) );
    lua_pushstring(L, (*entityPtr)->getMetadata().c_str());

    return 1;
}

int EntityExporter::setMetadata(lua_State* L)
{
    Exported_Entity* entityPtr = static_cast<Exported_Entity*>( LuaHelper::checkudata_WithError(L, 1, LUA_ENTITY_METATABLENAME) );
    (*entityPtr)->setMetadata(luaL_checkstring(L, 2));

    return 0;
}

int EntityExporter::getCollider(lua_State* L)
{
    Exported_Entity* entityPtr = static_cast<Exported_Entity*>( LuaHelper::checkudata_WithError(L, 1, LUA_ENTITY_METATABLENAME) );
    ColliderExporter::createCollider(L, (*entityPtr)->getCollider());
    return 1;
}

int EntityExporter::setCollider(lua_State* L)
{
    Exported_Entity* entityPtr = static_cast<Exported_Entity*>( LuaHelper::checkudata_WithError(L, 1, LUA_ENTITY_METATABLENAME) );
    Lua_Collider* colliderPtr = static_cast<Lua_Collider*>( LuaHelper::checkudata_WithError(L, 2, LUA_COLLIDER_METATABLENAME) );

    (*entityPtr)->setCollider(*colliderPtr);

    return 0;
}

int EntityExporter::destroy(lua_State* L)
{
    Exported_Entity* entityPtr = static_cast<Exported_Entity*>( LuaHelper::checkudata_WithError(L, 1, LUA_ENTITY_METATABLENAME) );
    Global::defaultGameManager.destroyEntity(*entityPtr);
    return 0;
}

int EntityExporter::isPlayer(lua_State* L)
{
    Exported_Entity* entityPtr = static_cast<Exported_Entity*>( LuaHelper::checkudata_WithError(L, 1, LUA_ENTITY_METATABLENAME) );
    lua_pushboolean(L, (*entityPtr)->isPlayer());
    return 1;
}

int EntityExporter::getPlayerId(lua_State* L)
{
    Exported_Entity* entityPtr = static_cast<Exported_Entity*>( LuaHelper::checkudata_WithError(L, 1, LUA_ENTITY_METATABLENAME) );
    if((*entityPtr)->isPlayer())
    {
        Player* player = dynamic_cast<Player*>( *entityPtr );
        lua_pushinteger(L, player->getPlayerId());
        return 1;
    }

    lua_pushinteger(L, -1);
    return 1;
}


int EntityExporter::findEntitiesWithName(lua_State* L)
{
    auto& entities = Global::defaultGameManager.getEntities();
    std::string entityName = luaL_checkstring(L, 1);
    lua_newtable(L);
    lua_Integer currentIndex = 1;
    for (auto& entity : entities)
    {
        if(entity->getName() == entityName)
        {
            lua_pushinteger(L, currentIndex);
            Entity* underlyingPointer = entity.get();
            LuaHelper::push(L, underlyingPointer);
            lua_settable(L, -3);
            ++currentIndex;
        }
    }

    return 1;
}

int EntityExporter::getGlobal(lua_State* L)
{
    Exported_Entity* entityPtr = static_cast<Exported_Entity*>( LuaHelper::checkudata_WithError(L, 1, LUA_ENTITY_METATABLENAME) );
    LuaEntity* luaEntityPtr = dynamic_cast<LuaEntity*>(*entityPtr);
    if(!luaEntityPtr) return 0;

    lua_State* sourceState = luaEntityPtr->getLuaState();
    std::string varname = lua_tostring(L, 2);

    lua_getglobal(sourceState, varname.c_str());
    return LuaHelper::CopyData(sourceState, L, -1);
}

int EntityExporter::setGlobal(lua_State* L)
{
    Exported_Entity* entityPtr = static_cast<Exported_Entity*>( LuaHelper::checkudata_WithError(L, 1, LUA_ENTITY_METATABLENAME) );
    LuaEntity* luaEntityPtr = dynamic_cast<LuaEntity*>(*entityPtr);
    if(!luaEntityPtr) return 0;

    lua_State* targetState = luaEntityPtr->getLuaState();
    std::string varname = lua_tostring(L, 2);
    int returnVal = LuaHelper::CopyData(L, targetState, 3);
    if(!returnVal) return 0;

    lua_setglobal(targetState, varname.c_str());
    return 0;
}

int EntityExporter::callFunction(lua_State* L)
{
    Exported_Entity* entityPtr = static_cast<Exported_Entity*>( LuaHelper::checkudata_WithError(L, 1, LUA_ENTITY_METATABLENAME) );
    auto* luaEntityPtr = dynamic_cast<LuaEntity*>(*entityPtr);
    if(!luaEntityPtr) return 0;

    std::string functionName = luaL_checkstring(L, 2);
    lua_Integer returnValCount = luaL_checkinteger(L, 3);
    lua_Integer argCount = lua_gettop(L) - 3;

    lua_State* entityState = luaEntityPtr->getLuaState();

    lua_getglobal(entityState, functionName.c_str());
    for(int i = 1; i <= argCount; ++i)
    {
        LuaHelper::CopyData(L, entityState, 4);
        lua_remove(L, 4);
    }
    lua_pcall(entityState, argCount, returnValCount, 0);

    for(int i = 1; i <= returnValCount; ++i)
    {
        LuaHelper::CopyData(entityState, L, 1);
        lua_remove(entityState, 1);
    }

    return static_cast<int>(returnValCount);
}

int EntityExporter::runCode(lua_State* L)
{
    Exported_Entity* entityPtr = static_cast<Exported_Entity*>( LuaHelper::checkudata_WithError(L, 1, LUA_ENTITY_METATABLENAME) );
    LuaEntity* luaEntityPtr = dynamic_cast<LuaEntity*>(*entityPtr);
    if(!luaEntityPtr) return 0;

    lua_State* entityState = luaEntityPtr->getLuaState();
    std::string code = luaL_checkstring(L, 2);
    luaL_dostring(entityState, code.c_str());

    return 0;
}

LuaExporter EntityExporter::toLuaExporter()
{
    LuaExporter exporter(
        LUA_ENTITY_CLASSNAME,
        __new,
        {
            {"getHealth", EntityExporter::getHealth},
            {"setHealth", EntityExporter::setHealth},
            {"changeHealth", EntityExporter::changeHealth},
            {"getPosition", EntityExporter::getPosition},
            {"setPosition", EntityExporter::setPosition},
            {"move", EntityExporter::move},
            {"getName", EntityExporter::getName},
            {"getModName", EntityExporter::getModName},
            {"getFullName", EntityExporter::getFullName},
            {"setMetadata", EntityExporter::setMetadata},
            {"getMetadata", EntityExporter::getMetadata},
            {"getCollider", EntityExporter::getCollider},
            {"setCollider", EntityExporter::setCollider},
            {"destroy", EntityExporter::destroy},
            {"isPlayer", EntityExporter::isPlayer},
            {"getPlayerId", EntityExporter::getPlayerId},
            {"findEntitiesWithName", EntityExporter::findEntitiesWithName},
            {"getGlobal", EntityExporter::getGlobal},
            {"setGlobal", EntityExporter::setGlobal},
            {"callFunction", EntityExporter::callFunction},
            {"runCode", EntityExporter::runCode},
        },
        {
            {"__index", EntityExporter::__index},
            {"__gc", EntityExporter::__destroy},
        }
    );

    return exporter;
}

