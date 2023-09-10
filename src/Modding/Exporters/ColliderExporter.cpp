#include <Modding/Exporters/ColliderExporter.hpp>
#include <Modding/Exporters/EntityExporter.hpp>
#include <Modding/Exporters/Vector2Exporter.hpp>
#include <Modding/LuaExporter.hpp>
#include <Modding/LuaHelper.hpp>
#include <InGame/Entity.hpp>
#include <InGame/LuaEntity.hpp>

void ColliderExporter::createCollider(lua_State* L, const Lua_Collider& collider)
{
    void* data = lua_newuserdata(L, sizeof(Lua_Collider));
    new (data) Lua_Collider(collider);
    luaL_getmetatable(L, LUA_COLLIDER_METATABLENAME);
    lua_setmetatable(L, -2);
}

int ColliderExporter::__new(lua_State* L)
{
    int arg_count = lua_gettop(L);
    Lua_Entity* entityPtr = nullptr;
    if(arg_count == 0)
    {
        createCollider(L, Lua_Collider());
        return 1;
    }
    if(arg_count == 1 && lua_isuserdata(L, 1))
    {
        entityPtr = static_cast<Lua_Entity*>(LuaHelper::checkudata_WithError(L, 1, LUA_COLLIDER_METATABLENAME));
        createCollider(L, Lua_Collider( dynamic_cast<Entity*>(entityPtr) ));
        return 1;
    }

    std::vector<sfex::Vec2> points;
    if(!lua_istable(L, 1))
    {
        luaL_error(L, "The Points should be an array containing vectors");
        return 0;
    }
    int arrLen = luaL_len(L, 1);
    points.reserve(arrLen);
    for(int i = 1; i <= arrLen; ++i)
    {
        lua_rawgeti(L, 1, i);
        Lua_Vector2* currentPoint = static_cast<Lua_Vector2*>( LuaHelper::checkudata_WithError(L, -1, LUA_VECTOR2_METATABLENAME) );
        points.push_back(
            {
                static_cast<float>(currentPoint->x),
                static_cast<float>(currentPoint->y)
            }
        );
    }

    bool isStatic = false;
    if(arg_count >= 2)
    {
        isStatic = lua_toboolean(L, 2);
    }

    if(arg_count >= 3)
    {
        entityPtr = static_cast<Lua_Entity*>(LuaHelper::checkudata_WithError(L, 1, LUA_COLLIDER_METATABLENAME));
    }

    createCollider(L, Lua_Collider(points, isStatic, dynamic_cast<Entity*>(entityPtr)));
    return 1;
}

int ColliderExporter::__destroy(lua_State* L)
{
    Lua_Collider* colliderPtr = static_cast<Lua_Collider*>( LuaHelper::checkudata_WithError(L, 1, LUA_COLLIDER_METATABLENAME) );
    colliderPtr->~Lua_Collider();
    return 0;
}

int ColliderExporter::__index(lua_State* L)
{
    Lua_Collider* fontPtr = static_cast<Lua_Collider*>( LuaHelper::checkudata_WithError(L, 1, LUA_COLLIDER_METATABLENAME) );
    std::string indexStr = luaL_checkstring(L, 2);

    lua_getglobal(L, LUA_COLLIDER_CLASSNAME);
    lua_pushstring(L, indexStr.c_str());
    lua_rawget(L, -2);
    return 1;
}

int ColliderExporter::setPoints(lua_State* L)
{
    Lua_Collider* colliderPtr = static_cast<Lua_Collider*>(LuaHelper::checkudata_WithError(L, 1, LUA_COLLIDER_METATABLENAME));
    std::vector<sfex::Vec2> points;
    if(!lua_istable(L, 2))
    {
        luaL_error(L, "The Points should be an array containing vectors");
        return 0;
    }
    int arrLen = luaL_len(L, 2);
    points.reserve(arrLen);
    for(int i = 1; i <= arrLen; ++i)
    {
        lua_rawgeti(L, 2, i);
        Lua_Vector2* currentPoint = static_cast<Lua_Vector2*>( LuaHelper::checkudata_WithError(L, -1, LUA_VECTOR2_METATABLENAME) );
        points.push_back(
            {
                static_cast<float>(currentPoint->x),
                static_cast<float>(currentPoint->y)
            }
        );
    }
    colliderPtr->setPoints(points);

    return 0;
}

int ColliderExporter::setStatic(lua_State* L)
{
    Lua_Collider* colliderPtr = static_cast<Lua_Collider*>(LuaHelper::checkudata_WithError(L, 1, LUA_COLLIDER_METATABLENAME));
    colliderPtr->setStatic(lua_toboolean(L, 2) );

    return 0;
}

int ColliderExporter::setImmovable(lua_State* L)
{
    Lua_Collider* colliderPtr = static_cast<Lua_Collider*>(LuaHelper::checkudata_WithError(L, 1, LUA_COLLIDER_METATABLENAME));
    colliderPtr->setImmovable(lua_toboolean(L, 2) );

    return 0;
}

int ColliderExporter::setEntity(lua_State* L)
{
    Lua_Collider* colliderPtr = static_cast<Lua_Collider*>(LuaHelper::checkudata_WithError(L, 1, LUA_COLLIDER_METATABLENAME));
    Lua_Entity* entityPtr = static_cast<Lua_Entity*>(LuaHelper::checkudata_WithError(L, 2, LUA_ENTITY_METATABLENAME));
    colliderPtr->setEntity(entityPtr);

    return 0;
}

int ColliderExporter::getColliderCenter(lua_State* L)
{
    Lua_Collider* colliderPtr = static_cast<Lua_Collider*>(LuaHelper::checkudata_WithError(L, 1, LUA_COLLIDER_METATABLENAME));
    Vector2Exporter::createVector(L, colliderPtr->getColliderCenter());

    return 1;
}

int ColliderExporter::getPoints(lua_State* L)
{
    Lua_Collider* colliderPtr = static_cast<Lua_Collider*>(LuaHelper::checkudata_WithError(L, 1, LUA_COLLIDER_METATABLENAME));
    auto points = colliderPtr->getPoints();
    lua_newtable(L);
    int arrLen = points.size();
    for(int i = 1; i <= arrLen; ++i)
    {
        Vector2Exporter::createVector(L, points[i-1]);
        lua_rawseti(L, -2, i);
    }

    return 1;
}

int ColliderExporter::getInnerLines(lua_State* L)
{
    Lua_Collider* colliderPtr = static_cast<Lua_Collider*>(LuaHelper::checkudata_WithError(L, 1, LUA_COLLIDER_METATABLENAME));
    auto innerLines = colliderPtr->getInnerLines();
    int arrLen = innerLines.size();
    lua_newtable(L);
    for(int i = 1; i < arrLen; ++i)
    {
        auto currentItem = innerLines[i - 1];
        lua_newtable(L);
        Vector2Exporter::createVector(L, currentItem[0].position);
        lua_rawseti(L, -2, -1);
        Vector2Exporter::createVector(L, currentItem[1].position);
        lua_rawseti(L, -2, -1);
        lua_rawseti(L, -2, -1);
    }

    return 1;
}

int ColliderExporter::getOuterLines(lua_State* L)
{
    Lua_Collider* colliderPtr = static_cast<Lua_Collider*>(LuaHelper::checkudata_WithError(L, 1, LUA_COLLIDER_METATABLENAME));
    auto outerLines = colliderPtr->getOuterLines();
    int arrLen = outerLines.size();
    lua_newtable(L);
    for(int i = 1; i < arrLen; ++i)
    {
        auto currentItem = outerLines[i - 1];
        lua_newtable(L);
        Vector2Exporter::createVector(L, currentItem[0].position);
        lua_rawseti(L, -2, -1);
        Vector2Exporter::createVector(L, currentItem[1].position);
        lua_rawseti(L, -2, -1);
        lua_rawseti(L, -2, -1);
    }

    return 1;
}

int ColliderExporter::isStatic(lua_State* L)
{
    Lua_Collider* colliderPtr = static_cast<Lua_Collider*>(LuaHelper::checkudata_WithError(L, 1, LUA_COLLIDER_METATABLENAME));
    lua_pushboolean(L, colliderPtr->isStatic());

    return 1;
}

int ColliderExporter::isImmovable(lua_State* L)
{
    Lua_Collider* colliderPtr = static_cast<Lua_Collider*>(LuaHelper::checkudata_WithError(L, 1, LUA_COLLIDER_METATABLENAME));
    lua_pushboolean(L, colliderPtr->isImmovable());

    return 1;
}

int ColliderExporter::getEntity(lua_State* L)
{
    Lua_Collider* colliderPtr = static_cast<Lua_Collider*>(LuaHelper::checkudata_WithError(L, 1, LUA_COLLIDER_METATABLENAME));
    LuaHelper::push(L, (void*)colliderPtr->getEntity());

    return 1;
}

int ColliderExporter::checkCollisions(lua_State* L)
{
    Lua_Collider* firstColliderPtr = static_cast<Lua_Collider*>(LuaHelper::checkudata_WithError(L, 1, LUA_COLLIDER_METATABLENAME));
    Lua_Collider* secondColliderPtr = static_cast<Lua_Collider*>(LuaHelper::checkudata_WithError(L, 2, LUA_COLLIDER_METATABLENAME));
    lua_pushboolean(L, firstColliderPtr->checkCollisions(*secondColliderPtr));

    return 1;
}

LuaExporter ColliderExporter::toLuaExporter()
{
    LuaExporter exporter(
        LUA_COLLIDER_CLASSNAME,
        __new,
        {
            {"setPoints", ColliderExporter::setPoints},
            {"setStatic", ColliderExporter::setStatic},
            {"setImmovable", ColliderExporter::setImmovable},
            {"setEntity", ColliderExporter::setEntity},
            {"getColliderCenter", ColliderExporter::getColliderCenter},
            {"getPoints", ColliderExporter::getPoints},
            {"getInnerLines", ColliderExporter::getInnerLines},
            {"getOuterLines", ColliderExporter::getOuterLines},
            {"isStatic", ColliderExporter::isStatic},
            {"isImmovable", ColliderExporter::isImmovable},
            {"getEntity", ColliderExporter::getEntity},
            {"checkCollisions", ColliderExporter::checkCollisions},
        },
        {
            {"__new", ColliderExporter::__new},
            {"__gc", ColliderExporter::__destroy},
            {"__index", ColliderExporter::__index},
        }
    );

    return exporter;
}