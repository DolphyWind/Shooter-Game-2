#include <Modding/Exporters/ConvexShapeExporter.hpp>
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

void ConvexShapeExporter::createConvexShape(lua_State* L, std::size_t pointCount)
{
    void* data = lua_newuserdata(L, sizeof(Lua_ConvexShape));
    new (data) Lua_ConvexShape(nullptr, pointCount);
    luaL_getmetatable(L, LUA_CONVEXSHAPE_METATABLENAME);
    lua_setmetatable(L, -2);
}

int ConvexShapeExporter::__new(lua_State *L)
{
    int arg_count = lua_gettop(L);
    std::size_t pointCount = 0;

    if(arg_count >= 1)
    {
        lua_numbertointeger(luaL_checknumber(L, 1), &pointCount);
    }
    
    createConvexShape(L, pointCount);
    return 1;
}

int ConvexShapeExporter::__destroy(lua_State *L)
{
    Lua_ConvexShape* convexShapePtr = static_cast<Lua_ConvexShape*>( LuaHelper::checkudata_WithError(L, 1, LUA_CONVEXSHAPE_METATABLENAME) );
    convexShapePtr->~Lua_ConvexShape();
    return 0;
}

int ConvexShapeExporter::__index(lua_State* L)
{
    Lua_ConvexShape* convexShapePtr = static_cast<Lua_ConvexShape*>( LuaHelper::checkudata_WithError(L, 1, LUA_CONVEXSHAPE_METATABLENAME) );
    std::string indexStr = lua_tostring(L, 2);

    lua_getglobal(L, LUA_CONVEXSHAPE_CLASSNAME);
    lua_pushstring(L, indexStr.c_str());
    lua_rawget(L, -2);
    return 1;
}

int ConvexShapeExporter::setPointCount(lua_State* L)
{
    Lua_ConvexShape* convexShapePtr = static_cast<Lua_ConvexShape*>( LuaHelper::checkudata_WithError(L, 1, LUA_CONVEXSHAPE_METATABLENAME) );
    std::size_t pointCount = 0;
    lua_numbertointeger(luaL_checknumber(L, 2), &pointCount);
    (*convexShapePtr)->setPointCount(pointCount);

    return 0;
}

int ConvexShapeExporter::getPointCount(lua_State* L)
{
    Lua_ConvexShape* convexShapePtr = static_cast<Lua_ConvexShape*>( LuaHelper::checkudata_WithError(L, 1, LUA_CONVEXSHAPE_METATABLENAME) );
    lua_pushinteger(L, (*convexShapePtr)->getPointCount());

    return 1;
}

int ConvexShapeExporter::setPoint(lua_State* L)
{
    Lua_ConvexShape* convexShapePtr = static_cast<Lua_ConvexShape*>( LuaHelper::checkudata_WithError(L, 1, LUA_CONVEXSHAPE_METATABLENAME) );
    std::size_t index;
    Lua_Vector2 point;
    lua_numbertointeger(luaL_checknumber(L, 2), &index);
    point = *static_cast<Lua_Vector2*>( LuaHelper::checkudata_WithError(L, 3, LUA_VECTOR2_METATABLENAME) );

    (*convexShapePtr)->setPoint(index, point);

    return 0;
}

int ConvexShapeExporter::getPoint(lua_State* L)
{
    Lua_ConvexShape* convexShapePtr = static_cast<Lua_ConvexShape*>( LuaHelper::checkudata_WithError(L, 1, LUA_CONVEXSHAPE_METATABLENAME) );
    lua_Integer index;
    lua_numbertointeger(luaL_checknumber(L, 2), &index);
    Vector2Exporter::createVector(L, (*convexShapePtr)->getPoint(index));

    return 1;
}

int ConvexShapeExporter::setTexture(lua_State* L)
{
    int arg_count = lua_gettop(L);
    Lua_ConvexShape* convexShapePtr = static_cast<Lua_ConvexShape*>( LuaHelper::checkudata_WithError(L, 1, LUA_CONVEXSHAPE_METATABLENAME) );
    Lua_Texture* texturePtr = static_cast<Lua_Texture*>( LuaHelper::checkudata_WithError(L, 2, LUA_TEXTURE_METATABLENAME) );
    bool resetRect = false;

    if(arg_count >= 3)
    {
        resetRect = lua_toboolean(L, 3);
    }
    (*convexShapePtr)->setTexture(texturePtr, resetRect);

    return 0;
}

int ConvexShapeExporter::setTextureRect(lua_State* L)
{
    Lua_ConvexShape* convexShapePtr = static_cast<Lua_ConvexShape*>( LuaHelper::checkudata_WithError(L, 1, LUA_CONVEXSHAPE_METATABLENAME) );
    Lua_IntRect* rectPtr = static_cast<Lua_IntRect*>( LuaHelper::checkudata_WithError(L, 2, LUA_INTRECT_METATABLENAME) );
    (*convexShapePtr)->setTextureRect(*rectPtr);

    return 0;
}

int ConvexShapeExporter::setFillColor(lua_State* L)
{
    Lua_ConvexShape* convexShapePtr = static_cast<Lua_ConvexShape*>( LuaHelper::checkudata_WithError(L, 1, LUA_CONVEXSHAPE_METATABLENAME) );
    Lua_Color* colorPtr = static_cast<Lua_Color*>( LuaHelper::checkudata_WithError(L, 2, LUA_COLOR_METATABLENAME) );
    (*convexShapePtr)->setFillColor(*colorPtr);

    return 0;
}

int ConvexShapeExporter::setOutlineColor(lua_State* L)
{
    Lua_ConvexShape* convexShapePtr = static_cast<Lua_ConvexShape*>( LuaHelper::checkudata_WithError(L, 1, LUA_CONVEXSHAPE_METATABLENAME) );
    Lua_Color* colorPtr = static_cast<Lua_Color*>( LuaHelper::checkudata_WithError(L, 2, LUA_COLOR_METATABLENAME) );
    (*convexShapePtr)->setOutlineColor(*colorPtr);

    return 0;
}

int ConvexShapeExporter::setOutlineThickness(lua_State* L)
{
    Lua_ConvexShape* convexShapePtr = static_cast<Lua_ConvexShape*>( LuaHelper::checkudata_WithError(L, 1, LUA_CONVEXSHAPE_METATABLENAME) );
    (*convexShapePtr)->setOutlineThickness(luaL_checknumber(L, 2));

    return 0;
}

int ConvexShapeExporter::getTexture(lua_State* L)
{
    Lua_ConvexShape* convexShapePtr = static_cast<Lua_ConvexShape*>( LuaHelper::checkudata_WithError(L, 1, LUA_CONVEXSHAPE_METATABLENAME) );
    LuaHelper::push(L, (void*)(*convexShapePtr)->getTexture());

    return 1;
}

int ConvexShapeExporter::getTextureRect(lua_State* L)
{
    Lua_ConvexShape* convexShapePtr = static_cast<Lua_ConvexShape*>( LuaHelper::checkudata_WithError(L, 1, LUA_CONVEXSHAPE_METATABLENAME) );
    IntRectExporter::createIntRect(L, (*convexShapePtr)->getTextureRect());

    return 1;
}

int ConvexShapeExporter::getFillColor(lua_State* L)
{
    Lua_ConvexShape* convexShapePtr = static_cast<Lua_ConvexShape*>( LuaHelper::checkudata_WithError(L, 1, LUA_CONVEXSHAPE_METATABLENAME) );
    ColorExporter::createColor(L, (*convexShapePtr)->getFillColor());

    return 1;
}

int ConvexShapeExporter::getOutlineColor(lua_State* L)
{
    Lua_ConvexShape* convexShapePtr = static_cast<Lua_ConvexShape*>( LuaHelper::checkudata_WithError(L, 1, LUA_CONVEXSHAPE_METATABLENAME) );
    ColorExporter::createColor(L, (*convexShapePtr)->getOutlineColor());

    return 1;
}

int ConvexShapeExporter::getOutlineThickness(lua_State* L)
{
    Lua_ConvexShape* convexShapePtr = static_cast<Lua_ConvexShape*>( LuaHelper::checkudata_WithError(L, 1, LUA_CONVEXSHAPE_METATABLENAME) );
    lua_pushnumber(L, (*convexShapePtr)->getOutlineThickness());

    return 1;
}

int ConvexShapeExporter::getLocalBounds(lua_State* L)
{
    Lua_ConvexShape* convexShapePtr = static_cast<Lua_ConvexShape*>( LuaHelper::checkudata_WithError(L, 1, LUA_CONVEXSHAPE_METATABLENAME) );
    FloatRectExporter::createFloatRect(L, (*convexShapePtr)->getLocalBounds());

    return 1;
}

int ConvexShapeExporter::getGlobalBounds(lua_State* L)
{
    Lua_ConvexShape* convexShapePtr = static_cast<Lua_ConvexShape*>( LuaHelper::checkudata_WithError(L, 1, LUA_CONVEXSHAPE_METATABLENAME) );
    FloatRectExporter::createFloatRect(L, convexShapePtr->getGlobalBounds());

    return 1;
}

int ConvexShapeExporter::setPosition(lua_State* L)
{
    int arg_count = lua_gettop(L);
    Lua_ConvexShape* convexShapePtr = static_cast<Lua_ConvexShape*>( LuaHelper::checkudata_WithError(L, 1, LUA_CONVEXSHAPE_METATABLENAME) );
    Lua_Vector2* vecPtr;

    vecPtr = (Lua_Vector2*)LuaHelper::checkudata_orNull(L, 2, LUA_VECTOR2_METATABLENAME);
    if(vecPtr)
    {
        (*convexShapePtr)->setPosition(*vecPtr);
        return 0;
    }
    (*convexShapePtr)->setPosition(
        luaL_checknumber(L, 2),
        luaL_checknumber(L, 3)
    );

    return 0;
}

int ConvexShapeExporter::setRotation(lua_State* L)
{
    Lua_ConvexShape* convexShapePtr = static_cast<Lua_ConvexShape*>( LuaHelper::checkudata_WithError(L, 1, LUA_CONVEXSHAPE_METATABLENAME) );
    (*convexShapePtr)->setRotation(luaL_checknumber(L, 2) );

    return 0;
}

int ConvexShapeExporter::setScale(lua_State* L)
{
    Lua_ConvexShape* convexShapePtr = static_cast<Lua_ConvexShape*>( LuaHelper::checkudata_WithError(L, 1, LUA_CONVEXSHAPE_METATABLENAME) );
    Lua_Vector2* vecPtr;

    vecPtr = (Lua_Vector2*)LuaHelper::checkudata_orNull(L, 2, LUA_VECTOR2_METATABLENAME);
    if(vecPtr)
    {
        (*convexShapePtr)->setScale(*vecPtr);
        return 0;
    }
    (*convexShapePtr)->setScale(
        luaL_checknumber(L, 2),
        luaL_checknumber(L, 3)
    );

    return 0;
}

int ConvexShapeExporter::setOrigin(lua_State* L)
{
    Lua_ConvexShape* convexShapePtr = static_cast<Lua_ConvexShape*>( LuaHelper::checkudata_WithError(L, 1, LUA_CONVEXSHAPE_METATABLENAME) );
    Lua_Vector2* vecPtr;

    vecPtr = (Lua_Vector2*)LuaHelper::checkudata_orNull(L, 2, LUA_VECTOR2_METATABLENAME);
    if(vecPtr)
    {
        (*convexShapePtr)->setOrigin(*vecPtr);
        return 0;
    }
    (*convexShapePtr)->setOrigin(
        luaL_checknumber(L, 2),
        luaL_checknumber(L, 3)
    );

    return 0;
}

int ConvexShapeExporter::getLocalPosition(lua_State* L)
{
    Lua_ConvexShape* convexShapePtr = static_cast<Lua_ConvexShape*>( LuaHelper::checkudata_WithError(L, 1, LUA_CONVEXSHAPE_METATABLENAME) );
    Vector2Exporter::createVector(L, (*convexShapePtr)->getPosition());

    return 1;
}

int ConvexShapeExporter::getWorldPosition(lua_State* L)
{
    Lua_ConvexShape* convexShapePtr = static_cast<Lua_ConvexShape*>( LuaHelper::checkudata_WithError(L, 1, LUA_CONVEXSHAPE_METATABLENAME) );
    Vector2Exporter::createVector(L, convexShapePtr->getPosition());

    return 1;
}

int ConvexShapeExporter::getRotation(lua_State* L)
{
    Lua_ConvexShape* convexShapePtr = static_cast<Lua_ConvexShape*>( LuaHelper::checkudata_WithError(L, 1, LUA_CONVEXSHAPE_METATABLENAME) );
    lua_pushnumber(L, (*convexShapePtr)->getRotation());

    return 1;
}

int ConvexShapeExporter::getScale(lua_State* L)
{
    Lua_ConvexShape* convexShapePtr = static_cast<Lua_ConvexShape*>( LuaHelper::checkudata_WithError(L, 1, LUA_CONVEXSHAPE_METATABLENAME) );
    Vector2Exporter::createVector(L, (*convexShapePtr)->getScale());

    return 1;
}

int ConvexShapeExporter::getOrigin(lua_State* L)
{
    Lua_ConvexShape* convexShapePtr = static_cast<Lua_ConvexShape*>( LuaHelper::checkudata_WithError(L, 1, LUA_CONVEXSHAPE_METATABLENAME) );
    Vector2Exporter::createVector(L, (*convexShapePtr)->getOrigin());

    return 1;
}

int ConvexShapeExporter::move(lua_State* L)
{
    Lua_ConvexShape* convexShapePtr = static_cast<Lua_ConvexShape*>( LuaHelper::checkudata_WithError(L, 1, LUA_CONVEXSHAPE_METATABLENAME) );
    Lua_Vector2* vecPtr;

    vecPtr = (Lua_Vector2*)LuaHelper::checkudata_orNull(L, 2, LUA_VECTOR2_METATABLENAME);
    if(vecPtr)
    {
        (*convexShapePtr)->move(*vecPtr);
        return 0;
    }
    (*convexShapePtr)->move(
        luaL_checknumber(L, 2),
        luaL_checknumber(L, 3)
    );

    return 0;
}

int ConvexShapeExporter::rotate(lua_State* L)
{
    Lua_ConvexShape* convexShapePtr = static_cast<Lua_ConvexShape*>( LuaHelper::checkudata_WithError(L, 1, LUA_CONVEXSHAPE_METATABLENAME) );
    (*convexShapePtr)->rotate(luaL_checknumber(L, 2));

    return 0;
}

int ConvexShapeExporter::scale(lua_State* L)
{
    Lua_ConvexShape* convexShapePtr = static_cast<Lua_ConvexShape*>( LuaHelper::checkudata_WithError(L, 1, LUA_CONVEXSHAPE_METATABLENAME) );
    Lua_Vector2* vecPtr;

    vecPtr = (Lua_Vector2*)LuaHelper::checkudata_orNull(L, 2, LUA_VECTOR2_METATABLENAME);
    if(vecPtr)
    {
        (*convexShapePtr)->scale(*vecPtr);
        return 0;
    }
    (*convexShapePtr)->scale(
        luaL_checknumber(L, 2),
        luaL_checknumber(L, 3)
    );

    return 0;
}

int ConvexShapeExporter::getTransform(lua_State* L)
{
    Lua_ConvexShape* convexShapePtr = static_cast<Lua_ConvexShape*>( LuaHelper::checkudata_WithError(L, 1, LUA_CONVEXSHAPE_METATABLENAME) );
    TransformExporter::createTransform(L, (*convexShapePtr)->getTransform());

    return 1;
}

int ConvexShapeExporter::getInverseTransform(lua_State* L)
{
    Lua_ConvexShape* convexShapePtr = static_cast<Lua_ConvexShape*>( LuaHelper::checkudata_WithError(L, 1, LUA_CONVEXSHAPE_METATABLENAME) );
    TransformExporter::createTransform(L, (*convexShapePtr)->getInverseTransform());

    return 1;
}

int ConvexShapeExporter::attachTo(lua_State* L)
{
    Lua_ConvexShape* convexShapePtr = static_cast<Lua_ConvexShape*>( LuaHelper::checkudata_WithError(L, 1, LUA_CONVEXSHAPE_METATABLENAME) );
    LuaEntity* entityPtr = static_cast<LuaEntity*>( LuaHelper::checkudata_WithError(L, 2, LUA_ENTITY_METATABLENAME) );

    convexShapePtr->attachTo(dynamic_cast<Entity*>(entityPtr));
    return 0;
}

LuaExporter ConvexShapeExporter::toLuaExporter()
{
    LuaExporter exporter(
        LUA_CONVEXSHAPE_CLASSNAME,
        __new,
        {
            {"setPointCount", ConvexShapeExporter::setPointCount},
            {"getPointCount", ConvexShapeExporter::getPointCount},
            {"setPoint", ConvexShapeExporter::setPoint},
            {"getPoint", ConvexShapeExporter::getPoint},
            {"setTexture", ConvexShapeExporter::setTexture},
            {"setTextureRect", ConvexShapeExporter::setTextureRect},
            {"setFillColor", ConvexShapeExporter::setFillColor},
            {"setOutlineColor", ConvexShapeExporter::setOutlineColor},
            {"setOutlineThickness", ConvexShapeExporter::setOutlineThickness},
            {"getTexture", ConvexShapeExporter::getTexture},
            {"getTextureRect", ConvexShapeExporter::getTextureRect},
            {"getFillColor", ConvexShapeExporter::getFillColor},
            {"getOutlineColor", ConvexShapeExporter::getOutlineColor},
            {"getOutlineThickness", ConvexShapeExporter::getOutlineThickness},
            {"getLocalBounds", ConvexShapeExporter::getLocalBounds},
            {"getGlobalBounds", ConvexShapeExporter::getGlobalBounds},
            {"setPosition", ConvexShapeExporter::setPosition},
            {"setRotation", ConvexShapeExporter::setRotation},
            {"setScale", ConvexShapeExporter::setScale},
            {"setOrigin", ConvexShapeExporter::setOrigin},
            {"getLocalPosition", ConvexShapeExporter::getLocalPosition},
            {"getWorldPosition", ConvexShapeExporter::getWorldPosition},
            {"getRotation", ConvexShapeExporter::getRotation},
            {"getScale", ConvexShapeExporter::getScale},
            {"getOrigin", ConvexShapeExporter::getOrigin},
            {"move", ConvexShapeExporter::move},
            {"rotate", ConvexShapeExporter::rotate},
            {"scale", ConvexShapeExporter::scale},
            {"getTransform", ConvexShapeExporter::getTransform},
            {"getInverseTransform", ConvexShapeExporter::getInverseTransform},
            {"attachTo", ConvexShapeExporter::attachTo},
        },
        {
            {"__gc", ConvexShapeExporter::__destroy},
            {"__index", ConvexShapeExporter::__index},
        }
    );

    return exporter;
}