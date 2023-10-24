#include <Modding/Exporters/CircleShapeExporter.hpp>
#include <Modding/Exporters/TextureExporter.hpp>
#include <Modding/Exporters/IntRectExporter.hpp>
#include <Modding/Exporters/FloatRectExporter.hpp>
#include <Modding/Exporters/ColorExporter.hpp>
#include <Modding/Exporters/Vector2Exporter.hpp>
#include <Modding/Exporters/TransformExporter.hpp>
#include <Modding/Exporters/EntityExporter.hpp>
#include <Modding/LuaHelper.hpp>
#include <Modding/LuaExporter.hpp>
#include <InGame/LuaEntity.hpp>

void CircleShapeExporter::createCircleShape(lua_State* L, float radius, std::size_t pointCount)
{
    void* data = lua_newuserdata(L, sizeof(Exported_CircleShape));
    new (data) Exported_CircleShape(nullptr, radius, pointCount);
    luaL_getmetatable(L, LUA_CIRCLESHAPE_METATABLENAME);
    lua_setmetatable(L, -2);
}

int CircleShapeExporter::__new(lua_State *L)
{
    int arg_count = lua_gettop(L);
    float radius = 0.0f;
    std::size_t pointCount = 30;

    if(arg_count >= 1)
    {
        radius = luaL_checknumber(L, 1);
    }
    if(arg_count >= 2)
    {
        lua_numbertointeger(luaL_checknumber(L, 2), &pointCount);
    }

    createCircleShape(L, radius, pointCount);
    return 1;
}

int CircleShapeExporter::__destroy(lua_State *L)
{
    Exported_CircleShape* circleShapePtr = static_cast<Exported_CircleShape*>( LuaHelper::checkudata_WithError(L, 1, LUA_CIRCLESHAPE_METATABLENAME) );
    circleShapePtr->~Exported_CircleShape();
    return 0;
}

int CircleShapeExporter::__index(lua_State* L)
{
    Exported_CircleShape* circleShapePtr = static_cast<Exported_CircleShape*>( LuaHelper::checkudata_WithError(L, 1, LUA_CIRCLESHAPE_METATABLENAME) );
    std::string indexStr = lua_tostring(L, 2);

    lua_getglobal(L, LUA_CIRCLESHAPE_CLASSNAME);
    lua_pushstring(L, indexStr.c_str());
    lua_rawget(L, -2);
    return 1;
}

int CircleShapeExporter::setRadius(lua_State* L)
{
    Exported_CircleShape* circleShapePtr = static_cast<Exported_CircleShape*>( LuaHelper::checkudata_WithError(L, 1, LUA_CIRCLESHAPE_METATABLENAME) );
    (*circleShapePtr)->setRadius(luaL_checknumber(L, 2) );

    return 0;
}

int CircleShapeExporter::getRadius(lua_State* L)
{
    Exported_CircleShape* circleShapePtr = static_cast<Exported_CircleShape*>( LuaHelper::checkudata_WithError(L, 1, LUA_CIRCLESHAPE_METATABLENAME) );
    lua_pushnumber(L, (*circleShapePtr)->getRadius());

    return 1;
}

int CircleShapeExporter::getPointCount(lua_State* L)
{
    Exported_CircleShape* circleShapePtr = static_cast<Exported_CircleShape*>( LuaHelper::checkudata_WithError(L, 1, LUA_CIRCLESHAPE_METATABLENAME) );
    lua_pushinteger(L, (*circleShapePtr)->getPointCount());

    return 1;
}

int CircleShapeExporter::getPoint(lua_State* L)
{
    Exported_CircleShape* circleShapePtr = static_cast<Exported_CircleShape*>( LuaHelper::checkudata_WithError(L, 1, LUA_CIRCLESHAPE_METATABLENAME) );
    lua_Integer index;
    lua_numbertointeger(luaL_checknumber(L, 2), &index);
    Vector2Exporter::createVector(L, (*circleShapePtr)->getPoint(index));

    return 1;
}

int CircleShapeExporter::setTexture(lua_State* L)
{
    int arg_count = lua_gettop(L);
    Exported_CircleShape* circleShapePtr = static_cast<Exported_CircleShape*>( LuaHelper::checkudata_WithError(L, 1, LUA_CIRCLESHAPE_METATABLENAME) );
    Lua_Texture* texturePtr = static_cast<Lua_Texture*>( LuaHelper::checkudata_WithError(L, 2, LUA_TEXTURE_METATABLENAME) );
    bool resetRect = false;

    if(arg_count >= 3)
    {
        resetRect = lua_toboolean(L, 3);
    }
    (*circleShapePtr)->setTexture(texturePtr, resetRect);

    return 0;
}

int CircleShapeExporter::setTextureRect(lua_State* L)
{
    Exported_CircleShape* circleShapePtr = static_cast<Exported_CircleShape*>( LuaHelper::checkudata_WithError(L, 1, LUA_CIRCLESHAPE_METATABLENAME) );
    Exported_IntRect* rectPtr = static_cast<Exported_IntRect*>( LuaHelper::checkudata_WithError(L, 2, LUA_INTRECT_METATABLENAME) );
    (*circleShapePtr)->setTextureRect(*rectPtr);

    return 0;
}

int CircleShapeExporter::setFillColor(lua_State* L)
{
    Exported_CircleShape* circleShapePtr = static_cast<Exported_CircleShape*>( LuaHelper::checkudata_WithError(L, 1, LUA_CIRCLESHAPE_METATABLENAME) );
    Exported_Color* colorPtr = static_cast<Exported_Color*>( LuaHelper::checkudata_WithError(L, 2, LUA_COLOR_METATABLENAME) );
    (*circleShapePtr)->setFillColor(*colorPtr);

    return 0;
}

int CircleShapeExporter::setOutlineColor(lua_State* L)
{
    Exported_CircleShape* circleShapePtr = static_cast<Exported_CircleShape*>( LuaHelper::checkudata_WithError(L, 1, LUA_CIRCLESHAPE_METATABLENAME) );
    Exported_Color* colorPtr = static_cast<Exported_Color*>( LuaHelper::checkudata_WithError(L, 2, LUA_COLOR_METATABLENAME) );
    (*circleShapePtr)->setOutlineColor(*colorPtr);

    return 0;
}

int CircleShapeExporter::setOutlineThickness(lua_State* L)
{
    Exported_CircleShape* circleShapePtr = static_cast<Exported_CircleShape*>( LuaHelper::checkudata_WithError(L, 1, LUA_CIRCLESHAPE_METATABLENAME) );
    (*circleShapePtr)->setOutlineThickness(luaL_checknumber(L, 2));

    return 0;
}

int CircleShapeExporter::getTexture(lua_State* L)
{
    Exported_CircleShape* circleShapePtr = static_cast<Exported_CircleShape*>( LuaHelper::checkudata_WithError(L, 1, LUA_CIRCLESHAPE_METATABLENAME) );
    LuaHelper::push(L, (void*)(*circleShapePtr)->getTexture());

    return 1;
}

int CircleShapeExporter::getTextureRect(lua_State* L)
{
    Exported_CircleShape* circleShapePtr = static_cast<Exported_CircleShape*>( LuaHelper::checkudata_WithError(L, 1, LUA_CIRCLESHAPE_METATABLENAME) );
    IntRectExporter::createIntRect(L, (*circleShapePtr)->getTextureRect());

    return 1;
}

int CircleShapeExporter::getFillColor(lua_State* L)
{
    Exported_CircleShape* circleShapePtr = static_cast<Exported_CircleShape*>( LuaHelper::checkudata_WithError(L, 1, LUA_CIRCLESHAPE_METATABLENAME) );
    ColorExporter::createColor(L, (*circleShapePtr)->getFillColor());

    return 1;
}

int CircleShapeExporter::getOutlineColor(lua_State* L)
{
    Exported_CircleShape* circleShapePtr = static_cast<Exported_CircleShape*>( LuaHelper::checkudata_WithError(L, 1, LUA_CIRCLESHAPE_METATABLENAME) );
    ColorExporter::createColor(L, (*circleShapePtr)->getOutlineColor());

    return 1;
}

int CircleShapeExporter::getOutlineThickness(lua_State* L)
{
    Exported_CircleShape* circleShapePtr = static_cast<Exported_CircleShape*>( LuaHelper::checkudata_WithError(L, 1, LUA_CIRCLESHAPE_METATABLENAME) );
    lua_pushnumber(L, (*circleShapePtr)->getOutlineThickness());

    return 1;
}

int CircleShapeExporter::getLocalBounds(lua_State* L)
{
    Exported_CircleShape* circleShapePtr = static_cast<Exported_CircleShape*>( LuaHelper::checkudata_WithError(L, 1, LUA_CIRCLESHAPE_METATABLENAME) );
    FloatRectExporter::createFloatRect(L, (*circleShapePtr)->getLocalBounds());

    return 1;
}

int CircleShapeExporter::getGlobalBounds(lua_State* L)
{
    Exported_CircleShape* circleShapePtr = static_cast<Exported_CircleShape*>( LuaHelper::checkudata_WithError(L, 1, LUA_CIRCLESHAPE_METATABLENAME) );
    FloatRectExporter::createFloatRect(L, circleShapePtr->getGlobalBounds());

    return 1;
}

int CircleShapeExporter::setPosition(lua_State* L)
{
    int arg_count = lua_gettop(L);
    Exported_CircleShape* circleShapePtr = static_cast<Exported_CircleShape*>( LuaHelper::checkudata_WithError(L, 1, LUA_CIRCLESHAPE_METATABLENAME) );
    Exported_Vector2* vecPtr;

    vecPtr = (Exported_Vector2*)LuaHelper::checkudata_orNull(L, 2, LUA_VECTOR2_METATABLENAME);
    if(vecPtr)
    {
        (*circleShapePtr)->setPosition(*vecPtr);
        return 0;
    }
    (*circleShapePtr)->setPosition(
        luaL_checknumber(L, 2),
        luaL_checknumber(L, 3)
    );

    return 0;
}

int CircleShapeExporter::setRotation(lua_State* L)
{
    Exported_CircleShape* circleShapePtr = static_cast<Exported_CircleShape*>( LuaHelper::checkudata_WithError(L, 1, LUA_CIRCLESHAPE_METATABLENAME) );
    (*circleShapePtr)->setRotation(luaL_checknumber(L, 2) );

    return 0;
}

int CircleShapeExporter::setScale(lua_State* L)
{
    Exported_CircleShape* circleShapePtr = static_cast<Exported_CircleShape*>( LuaHelper::checkudata_WithError(L, 1, LUA_CIRCLESHAPE_METATABLENAME) );
    Exported_Vector2* vecPtr;

    vecPtr = (Exported_Vector2*)LuaHelper::checkudata_orNull(L, 2, LUA_VECTOR2_METATABLENAME);
    if(vecPtr)
    {
        (*circleShapePtr)->setScale(*vecPtr);
        return 0;
    }
    (*circleShapePtr)->setScale(
        luaL_checknumber(L, 2),
        luaL_checknumber(L, 3)
    );

    return 0;
}

int CircleShapeExporter::setOrigin(lua_State* L)
{
    Exported_CircleShape* circleShapePtr = static_cast<Exported_CircleShape*>( LuaHelper::checkudata_WithError(L, 1, LUA_CIRCLESHAPE_METATABLENAME) );
    Exported_Vector2* vecPtr;

    vecPtr = (Exported_Vector2*)LuaHelper::checkudata_orNull(L, 2, LUA_VECTOR2_METATABLENAME);
    if(vecPtr)
    {
        (*circleShapePtr)->setOrigin(*vecPtr);
        return 0;
    }
    (*circleShapePtr)->setOrigin(
        luaL_checknumber(L, 2),
        luaL_checknumber(L, 3)
    );

    return 0;
}

int CircleShapeExporter::getLocalPosition(lua_State* L)
{
    Exported_CircleShape* circleShapePtr = static_cast<Exported_CircleShape*>( LuaHelper::checkudata_WithError(L, 1, LUA_CIRCLESHAPE_METATABLENAME) );
    Vector2Exporter::createVector(L, (*circleShapePtr)->getPosition());

    return 1;
}

int CircleShapeExporter::getWorldPosition(lua_State* L)
{
    Exported_CircleShape* circleShapePtr = static_cast<Exported_CircleShape*>( LuaHelper::checkudata_WithError(L, 1, LUA_CIRCLESHAPE_METATABLENAME) );
    Vector2Exporter::createVector(L, circleShapePtr->getPosition());

    return 1;
}

int CircleShapeExporter::getRotation(lua_State* L)
{
    Exported_CircleShape* circleShapePtr = static_cast<Exported_CircleShape*>( LuaHelper::checkudata_WithError(L, 1, LUA_CIRCLESHAPE_METATABLENAME) );
    lua_pushnumber(L, (*circleShapePtr)->getRotation());

    return 1;
}

int CircleShapeExporter::getScale(lua_State* L)
{
    Exported_CircleShape* circleShapePtr = static_cast<Exported_CircleShape*>( LuaHelper::checkudata_WithError(L, 1, LUA_CIRCLESHAPE_METATABLENAME) );
    Vector2Exporter::createVector(L, (*circleShapePtr)->getScale());

    return 1;
}

int CircleShapeExporter::getOrigin(lua_State* L)
{
    Exported_CircleShape* circleShapePtr = static_cast<Exported_CircleShape*>( LuaHelper::checkudata_WithError(L, 1, LUA_CIRCLESHAPE_METATABLENAME) );
    Vector2Exporter::createVector(L, (*circleShapePtr)->getOrigin());

    return 1;
}

int CircleShapeExporter::move(lua_State* L)
{
    Exported_CircleShape* circleShapePtr = static_cast<Exported_CircleShape*>( LuaHelper::checkudata_WithError(L, 1, LUA_CIRCLESHAPE_METATABLENAME) );
    Exported_Vector2* vecPtr;

    vecPtr = (Exported_Vector2*)LuaHelper::checkudata_orNull(L, 2, LUA_VECTOR2_METATABLENAME);
    if(vecPtr)
    {
        (*circleShapePtr)->move(*vecPtr);
        return 0;
    }
    (*circleShapePtr)->move(
        luaL_checknumber(L, 2),
        luaL_checknumber(L, 3)
    );

    return 0;
}

int CircleShapeExporter::rotate(lua_State* L)
{
    Exported_CircleShape* circleShapePtr = static_cast<Exported_CircleShape*>( LuaHelper::checkudata_WithError(L, 1, LUA_CIRCLESHAPE_METATABLENAME) );
    (*circleShapePtr)->rotate(luaL_checknumber(L, 2));

    return 0;
}

int CircleShapeExporter::scale(lua_State* L)
{
    Exported_CircleShape* circleShapePtr = static_cast<Exported_CircleShape*>( LuaHelper::checkudata_WithError(L, 1, LUA_CIRCLESHAPE_METATABLENAME) );
    Exported_Vector2* vecPtr;

    vecPtr = (Exported_Vector2*)LuaHelper::checkudata_orNull(L, 2, LUA_VECTOR2_METATABLENAME);
    if(vecPtr)
    {
        (*circleShapePtr)->scale(*vecPtr);
        return 0;
    }
    (*circleShapePtr)->scale(
        luaL_checknumber(L, 2),
        luaL_checknumber(L, 3)
    );

    return 0;
}

int CircleShapeExporter::getTransform(lua_State* L)
{
    Exported_CircleShape* circleShapePtr = static_cast<Exported_CircleShape*>( LuaHelper::checkudata_WithError(L, 1, LUA_CIRCLESHAPE_METATABLENAME) );
    TransformExporter::createTransform(L, (*circleShapePtr)->getTransform());

    return 1;
}

int CircleShapeExporter::getInverseTransform(lua_State* L)
{
    Exported_CircleShape* circleShapePtr = static_cast<Exported_CircleShape*>( LuaHelper::checkudata_WithError(L, 1, LUA_CIRCLESHAPE_METATABLENAME) );
    TransformExporter::createTransform(L, (*circleShapePtr)->getInverseTransform());

    return 1;
}

int CircleShapeExporter::attachTo(lua_State* L)
{
    Exported_CircleShape* circleShapePtr = static_cast<Exported_CircleShape*>( LuaHelper::checkudata_WithError(L, 1, LUA_CIRCLESHAPE_METATABLENAME) );
    Exported_Entity* entityPtr = static_cast<Exported_Entity*>( LuaHelper::checkudata_WithError(L, 2, LUA_ENTITY_METATABLENAME) );

    circleShapePtr->attachTo(dynamic_cast<Entity*>(*entityPtr));
    return 0;
}

LuaExporter CircleShapeExporter::toLuaExporter()
{
    LuaExporter exporter(
        LUA_CIRCLESHAPE_CLASSNAME,
        __new,
        {
            {"setRadius", CircleShapeExporter::setRadius},
            {"getRadius", CircleShapeExporter::getRadius},
            {"getPointCount", CircleShapeExporter::getPointCount},
            {"getPoint", CircleShapeExporter::getPoint},
            {"setTexture", CircleShapeExporter::setTexture},
            {"setTextureRect", CircleShapeExporter::setTextureRect},
            {"setFillColor", CircleShapeExporter::setFillColor},
            {"setOutlineColor", CircleShapeExporter::setOutlineColor},
            {"setOutlineThickness", CircleShapeExporter::setOutlineThickness},
            {"getTexture", CircleShapeExporter::getTexture},
            {"getTextureRect", CircleShapeExporter::getTextureRect},
            {"getFillColor", CircleShapeExporter::getFillColor},
            {"getOutlineColor", CircleShapeExporter::getOutlineColor},
            {"getOutlineThickness", CircleShapeExporter::getOutlineThickness},
            {"getLocalBounds", CircleShapeExporter::getLocalBounds},
            {"getGlobalBounds", CircleShapeExporter::getGlobalBounds},
            {"setPosition", CircleShapeExporter::setPosition},
            {"setRotation", CircleShapeExporter::setRotation},
            {"setScale", CircleShapeExporter::setScale},
            {"setOrigin", CircleShapeExporter::setOrigin},
            {"getLocalPosition", CircleShapeExporter::getLocalPosition},
            {"getWorldPosition", CircleShapeExporter::getWorldPosition},
            {"getRotation", CircleShapeExporter::getRotation},
            {"getScale", CircleShapeExporter::getScale},
            {"getOrigin", CircleShapeExporter::getOrigin},
            {"move", CircleShapeExporter::move},
            {"rotate", CircleShapeExporter::rotate},
            {"scale", CircleShapeExporter::scale},
            {"getTransform", CircleShapeExporter::getTransform},
            {"getInverseTransform", CircleShapeExporter::getInverseTransform},
            {"attachTo", CircleShapeExporter::attachTo},
        },
        {
            {"__gc", CircleShapeExporter::__destroy},
            {"__index", CircleShapeExporter::__index},
        }
    );

    return exporter;
}