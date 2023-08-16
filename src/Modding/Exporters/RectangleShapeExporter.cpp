#include <Modding/Exporters/RectangleShapeExporter.hpp>
#include <Modding/Exporters/TextureExporter.hpp>
#include <Modding/Exporters/IntRectExporter.hpp>
#include <Modding/Exporters/FloatRectExporter.hpp>
#include <Modding/Exporters/ColorExporter.hpp>
#include <Modding/Exporters/Vector2Exporter.hpp>
#include <Modding/Exporters/TransformExporter.hpp>
#include <Modding/LuaHelper.hpp>
#include <Modding/LuaExporter.hpp>

void RectangleShapeExporter::createRectangleShape(lua_State* L, const sf::Vector2f& size)
{
    void* data = lua_newuserdata(L, sizeof(Lua_RectangleShape));
    new (data) Lua_RectangleShape(size);
    luaL_getmetatable(L, LUA_RECTANGLESHAPE_METATABLENAME);
    lua_setmetatable(L, -2);
}

int RectangleShapeExporter::__new(lua_State *L)
{
    int arg_count = lua_gettop(L);
    Lua_Vector2 size{0, 0};

    if(arg_count >= 1)
    {
        size = *static_cast<Lua_Vector2*>( luaL_checkudata(L, 1, LUA_VECTOR2_METATABLENAME) );
    }

    createRectangleShape(L, size);
    return 1;
}

int RectangleShapeExporter::__destroy(lua_State *L)
{
    Lua_RectangleShape* rectangleShapePtr = static_cast<Lua_RectangleShape*>( luaL_checkudata(L, 1, LUA_RECTANGLESHAPE_METATABLENAME) );
    rectangleShapePtr->~Lua_RectangleShape();
    return 0;
}

int RectangleShapeExporter::__index(lua_State* L)
{
    Lua_RectangleShape* rectangleShapePtr = static_cast<Lua_RectangleShape*>( luaL_checkudata(L, 1, LUA_RECTANGLESHAPE_METATABLENAME) );
    std::string indexStr = lua_tostring(L, 2);

    lua_getglobal(L, LUA_RECTANGLESHAPE_CLASSNAME);
    lua_pushstring(L, indexStr.c_str());
    lua_rawget(L, -2);
    return 1;
}

int RectangleShapeExporter::setSize(lua_State* L)
{
    Lua_RectangleShape* rectangleShapePtr = static_cast<Lua_RectangleShape*>( luaL_checkudata(L, 1, LUA_RECTANGLESHAPE_METATABLENAME) );
    Lua_Vector2* vecPtr = static_cast<Lua_Vector2*>( luaL_checkudata(L, 2, LUA_VECTOR2_METATABLENAME) );
    rectangleShapePtr->setSize(*vecPtr);

    return 0;
}

int RectangleShapeExporter::getSize(lua_State* L)
{
    Lua_RectangleShape* rectangleShapePtr = static_cast<Lua_RectangleShape*>( luaL_checkudata(L, 1, LUA_RECTANGLESHAPE_METATABLENAME) );
    Vector2Exporter::createVector(L, rectangleShapePtr->getSize());

    return 1;
}

int RectangleShapeExporter::getPointCount(lua_State* L)
{
    Lua_RectangleShape* rectangleShapePtr = static_cast<Lua_RectangleShape*>( luaL_checkudata(L, 1, LUA_RECTANGLESHAPE_METATABLENAME) );
    lua_pushinteger(L, rectangleShapePtr->getPointCount());

    return 1;
}

int RectangleShapeExporter::getPoint(lua_State* L)
{
    Lua_RectangleShape* rectangleShapePtr = static_cast<Lua_RectangleShape*>( luaL_checkudata(L, 1, LUA_RECTANGLESHAPE_METATABLENAME) );
    lua_Integer index;
    lua_numbertointeger(luaL_checknumber(L, 2), &index);
    Vector2Exporter::createVector(L, rectangleShapePtr->getPoint(index));

    return 1;
}

int RectangleShapeExporter::setTexture(lua_State* L)
{
    int arg_count = lua_gettop(L);
    Lua_RectangleShape* rectangleShapePtr = static_cast<Lua_RectangleShape*>( luaL_checkudata(L, 1, LUA_RECTANGLESHAPE_METATABLENAME) );
    Lua_Texture* texturePtr = static_cast<Lua_Texture*>( luaL_checkudata(L, 2, LUA_TEXTURE_METATABLENAME) );
    bool resetRect = false;

    if(arg_count >= 3)
    {
        resetRect = lua_toboolean(L, 3);
    }
    rectangleShapePtr->setTexture(texturePtr, resetRect);

    return 0;
}

int RectangleShapeExporter::setTextureRect(lua_State* L)
{
    Lua_RectangleShape* rectangleShapePtr = static_cast<Lua_RectangleShape*>( luaL_checkudata(L, 1, LUA_RECTANGLESHAPE_METATABLENAME) );
    Lua_IntRect* rectPtr = static_cast<Lua_IntRect*>( luaL_checkudata(L, 2, LUA_INTRECT_METATABLENAME) );
    rectangleShapePtr->setTextureRect(*rectPtr);

    return 0;
}

int RectangleShapeExporter::setFillColor(lua_State* L)
{
    Lua_RectangleShape* rectangleShapePtr = static_cast<Lua_RectangleShape*>( luaL_checkudata(L, 1, LUA_RECTANGLESHAPE_METATABLENAME) );
    Lua_Color* colorPtr = static_cast<Lua_Color*>( luaL_checkudata(L, 2, LUA_COLOR_METATABLENAME) );
    rectangleShapePtr->setFillColor(*colorPtr);

    return 0;
}

int RectangleShapeExporter::setOutlineColor(lua_State* L)
{
    Lua_RectangleShape* rectangleShapePtr = static_cast<Lua_RectangleShape*>( luaL_checkudata(L, 1, LUA_RECTANGLESHAPE_METATABLENAME) );
    Lua_Color* colorPtr = static_cast<Lua_Color*>( luaL_checkudata(L, 2, LUA_COLOR_METATABLENAME) );
    rectangleShapePtr->setOutlineColor(*colorPtr);

    return 0;
}

int RectangleShapeExporter::setOutlineThickness(lua_State* L)
{
    Lua_RectangleShape* rectangleShapePtr = static_cast<Lua_RectangleShape*>( luaL_checkudata(L, 1, LUA_RECTANGLESHAPE_METATABLENAME) );
    rectangleShapePtr->setOutlineThickness(luaL_checknumber(L, 2));

    return 0;
}

int RectangleShapeExporter::getTexture(lua_State* L)
{
    Lua_RectangleShape* rectangleShapePtr = static_cast<Lua_RectangleShape*>( luaL_checkudata(L, 1, LUA_RECTANGLESHAPE_METATABLENAME) );
    LuaHelper::push(L, {(void*)rectangleShapePtr->getTexture(), LUA_TEXTURE_METATABLENAME});

    return 1;
}

int RectangleShapeExporter::getTextureRect(lua_State* L)
{
    Lua_RectangleShape* rectangleShapePtr = static_cast<Lua_RectangleShape*>( luaL_checkudata(L, 1, LUA_RECTANGLESHAPE_METATABLENAME) );
    IntRectExporter::createIntRect(L, rectangleShapePtr->getTextureRect());

    return 1;
}

int RectangleShapeExporter::getFillColor(lua_State* L)
{
    Lua_RectangleShape* rectangleShapePtr = static_cast<Lua_RectangleShape*>( luaL_checkudata(L, 1, LUA_RECTANGLESHAPE_METATABLENAME) );
    ColorExporter::createColor(L, rectangleShapePtr->getFillColor());

    return 1;
}

int RectangleShapeExporter::getOutlineColor(lua_State* L)
{
    Lua_RectangleShape* rectangleShapePtr = static_cast<Lua_RectangleShape*>( luaL_checkudata(L, 1, LUA_RECTANGLESHAPE_METATABLENAME) );
    ColorExporter::createColor(L, rectangleShapePtr->getOutlineColor());

    return 1;
}

int RectangleShapeExporter::getOutlineThickness(lua_State* L)
{
    Lua_RectangleShape* rectangleShapePtr = static_cast<Lua_RectangleShape*>( luaL_checkudata(L, 1, LUA_RECTANGLESHAPE_METATABLENAME) );
    lua_pushnumber(L, rectangleShapePtr->getOutlineThickness());

    return 1;
}

int RectangleShapeExporter::getLocalBounds(lua_State* L)
{
    Lua_RectangleShape* rectangleShapePtr = static_cast<Lua_RectangleShape*>( luaL_checkudata(L, 1, LUA_RECTANGLESHAPE_METATABLENAME) );
    FloatRectExporter::createFloatRect(L, rectangleShapePtr->getLocalBounds());

    return 1;
}

int RectangleShapeExporter::getGlobalBounds(lua_State* L)
{
    Lua_RectangleShape* rectangleShapePtr = static_cast<Lua_RectangleShape*>( luaL_checkudata(L, 1, LUA_RECTANGLESHAPE_METATABLENAME) );
    FloatRectExporter::createFloatRect(L, rectangleShapePtr->getGlobalBounds());

    return 1;
}

int RectangleShapeExporter::setPosition(lua_State* L)
{
    int arg_count = lua_gettop(L);
    Lua_RectangleShape* rectangleShapePtr = static_cast<Lua_RectangleShape*>( luaL_checkudata(L, 1, LUA_RECTANGLESHAPE_METATABLENAME) );
    Lua_Vector2* vecPtr;

    vecPtr = (Lua_Vector2*)LuaHelper::checkudata(L, 2, LUA_VECTOR2_METATABLENAME);
    if(vecPtr)
    {
        rectangleShapePtr->setPosition(*vecPtr);
        return 0;
    }
    rectangleShapePtr->setPosition(
        luaL_checknumber(L, 2),
        luaL_checknumber(L, 3)
    );

    return 0;
}

int RectangleShapeExporter::setRotation(lua_State* L)
{
    Lua_RectangleShape* rectangleShapePtr = static_cast<Lua_RectangleShape*>( luaL_checkudata(L, 1, LUA_RECTANGLESHAPE_METATABLENAME) );
    rectangleShapePtr->setRotation(luaL_checknumber(L, 2) );

    return 0;
}

int RectangleShapeExporter::setScale(lua_State* L)
{
    Lua_RectangleShape* rectangleShapePtr = static_cast<Lua_RectangleShape*>( luaL_checkudata(L, 1, LUA_RECTANGLESHAPE_METATABLENAME) );
    Lua_Vector2* vecPtr;

    vecPtr = (Lua_Vector2*) LuaHelper::checkudata(L, 2, LUA_VECTOR2_METATABLENAME);
    if(vecPtr)
    {
        rectangleShapePtr->setScale(*vecPtr);
        return 0;
    }
    rectangleShapePtr->setScale(
        luaL_checknumber(L, 2),
        luaL_checknumber(L, 3)
    );

    return 0;
}

int RectangleShapeExporter::setOrigin(lua_State* L)
{
    Lua_RectangleShape* rectangleShapePtr = static_cast<Lua_RectangleShape*>( luaL_checkudata(L, 1, LUA_RECTANGLESHAPE_METATABLENAME) );
    Lua_Vector2* vecPtr;

    vecPtr = (Lua_Vector2*) LuaHelper::checkudata(L, 2, LUA_VECTOR2_METATABLENAME);
    if(vecPtr)
    {
        rectangleShapePtr->setOrigin(*vecPtr);
        return 0;
    }
    rectangleShapePtr->setOrigin(
        luaL_checknumber(L, 2),
        luaL_checknumber(L, 3)
    );

    return 0;
}

int RectangleShapeExporter::getPosition(lua_State* L)
{
    Lua_RectangleShape* rectangleShapePtr = static_cast<Lua_RectangleShape*>( luaL_checkudata(L, 1, LUA_RECTANGLESHAPE_METATABLENAME) );
    Vector2Exporter::createVector(L, rectangleShapePtr->getPosition());

    return 1;
}

int RectangleShapeExporter::getRotation(lua_State* L)
{
    Lua_RectangleShape* rectangleShapePtr = static_cast<Lua_RectangleShape*>( luaL_checkudata(L, 1, LUA_RECTANGLESHAPE_METATABLENAME) );
    lua_pushnumber(L, rectangleShapePtr->getRotation());

    return 1;
}

int RectangleShapeExporter::getScale(lua_State* L)
{
    Lua_RectangleShape* rectangleShapePtr = static_cast<Lua_RectangleShape*>( luaL_checkudata(L, 1, LUA_RECTANGLESHAPE_METATABLENAME) );
    Vector2Exporter::createVector(L, rectangleShapePtr->getScale());

    return 1;
}

int RectangleShapeExporter::getOrigin(lua_State* L)
{
    Lua_RectangleShape* rectangleShapePtr = static_cast<Lua_RectangleShape*>( luaL_checkudata(L, 1, LUA_RECTANGLESHAPE_METATABLENAME) );
    Vector2Exporter::createVector(L, rectangleShapePtr->getOrigin());

    return 1;
}

int RectangleShapeExporter::move(lua_State* L)
{
    Lua_RectangleShape* rectangleShapePtr = static_cast<Lua_RectangleShape*>( luaL_checkudata(L, 1, LUA_RECTANGLESHAPE_METATABLENAME) );
    Lua_Vector2* vecPtr;

    vecPtr = (Lua_Vector2*) LuaHelper::checkudata(L, 2, LUA_VECTOR2_METATABLENAME);
    if(vecPtr)
    {
        rectangleShapePtr->move(*vecPtr);
        return 0;
    }
    rectangleShapePtr->move(
        luaL_checknumber(L, 2),
        luaL_checknumber(L, 3)
    );

    return 0;
}

int RectangleShapeExporter::rotate(lua_State* L)
{
    Lua_RectangleShape* rectangleShapePtr = static_cast<Lua_RectangleShape*>( luaL_checkudata(L, 1, LUA_RECTANGLESHAPE_METATABLENAME) );
    rectangleShapePtr->rotate(luaL_checknumber(L, 2));

    return 0;
}

int RectangleShapeExporter::scale(lua_State* L)
{
    Lua_RectangleShape* rectangleShapePtr = static_cast<Lua_RectangleShape*>( luaL_checkudata(L, 1, LUA_RECTANGLESHAPE_METATABLENAME) );
    Lua_Vector2* vecPtr;

    vecPtr = (Lua_Vector2*) LuaHelper::checkudata(L, 2, LUA_VECTOR2_METATABLENAME);
    if(vecPtr)
    {
        rectangleShapePtr->scale(*vecPtr);
        return 0;
    }
    rectangleShapePtr->scale(
        luaL_checknumber(L, 2),
        luaL_checknumber(L, 3)
    );

    return 0;
}

int RectangleShapeExporter::getTransform(lua_State* L)
{
    Lua_RectangleShape* rectangleShapePtr = static_cast<Lua_RectangleShape*>( luaL_checkudata(L, 1, LUA_RECTANGLESHAPE_METATABLENAME) );
    TransformExporter::createTransform(L, rectangleShapePtr->getTransform());

    return 1;
}

int RectangleShapeExporter::getInverseTransform(lua_State* L)
{
    Lua_RectangleShape* rectangleShapePtr = static_cast<Lua_RectangleShape*>( luaL_checkudata(L, 1, LUA_RECTANGLESHAPE_METATABLENAME) );
    TransformExporter::createTransform(L, rectangleShapePtr->getInverseTransform());

    return 1;
}

LuaExporter RectangleShapeExporter::toLuaExporter()
{
    LuaExporter exporter(
        LUA_RECTANGLESHAPE_CLASSNAME,
        __new,
        {
            {"setSize", RectangleShapeExporter::setSize},
            {"getSize", RectangleShapeExporter::getSize},
            {"getPointCount", RectangleShapeExporter::getPointCount},
            {"getPoint", RectangleShapeExporter::getPoint},
            {"setTexture", RectangleShapeExporter::setTexture},
            {"setTextureRect", RectangleShapeExporter::setTextureRect},
            {"setFillColor", RectangleShapeExporter::setFillColor},
            {"setOutlineColor", RectangleShapeExporter::setOutlineColor},
            {"setOutlineThickness", RectangleShapeExporter::setOutlineThickness},
            {"getTexture", RectangleShapeExporter::getTexture},
            {"getTextureRect", RectangleShapeExporter::getTextureRect},
            {"getFillColor", RectangleShapeExporter::getFillColor},
            {"getOutlineColor", RectangleShapeExporter::getOutlineColor},
            {"getOutlineThickness", RectangleShapeExporter::getOutlineThickness},
            {"getLocalBounds", RectangleShapeExporter::getLocalBounds},
            {"getGlobalBounds", RectangleShapeExporter::getGlobalBounds},
            {"setPosition", RectangleShapeExporter::setPosition},
            {"setRotation", RectangleShapeExporter::setRotation},
            {"setScale", RectangleShapeExporter::setScale},
            {"setOrigin", RectangleShapeExporter::setOrigin},
            {"getPosition", RectangleShapeExporter::getPosition},
            {"getRotation", RectangleShapeExporter::getRotation},
            {"getScale", RectangleShapeExporter::getScale},
            {"getOrigin", RectangleShapeExporter::getOrigin},
            {"move", RectangleShapeExporter::move},
            {"rotate", RectangleShapeExporter::rotate},
            {"scale", RectangleShapeExporter::scale},
            {"getTransform", RectangleShapeExporter::getTransform},
            {"getInverseTransform", RectangleShapeExporter::getInverseTransform},
        },
        {
            {"__gc", RectangleShapeExporter::__destroy},
            {"__index", RectangleShapeExporter::__index},
        }
    );

    return exporter;
}