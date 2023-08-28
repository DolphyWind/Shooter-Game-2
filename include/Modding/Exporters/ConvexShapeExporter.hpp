#pragma once

#include <SFML/Graphics.hpp>
#include <Modding/AttachableObject.hpp>
#include <lua.hpp>

#define LUA_CONVEXSHAPE_CLASSNAME "ConvexShape"
#define LUA_CONVEXSHAPE_METATABLENAME LUA_CONVEXSHAPE_CLASSNAME"_metatable"
typedef AttachableObject<sf::ConvexShape> Lua_ConvexShape;

class LuaExporter;
struct ConvexShapeExporter
{
    static void createConvexShape(lua_State* L, std::size_t pointCount=0);
    static int __new(lua_State* L);
    static int __destroy(lua_State* L);
    static int __index(lua_State* L);

    static int setPointCount(lua_State* L);
    static int getPointCount(lua_State* L);
    static int setPoint(lua_State* L);
    static int getPoint(lua_State* L);
    static int setTexture(lua_State* L);
    static int setTextureRect(lua_State* L);
    static int setFillColor(lua_State* L);
    static int setOutlineColor(lua_State* L);
    static int setOutlineThickness(lua_State* L);
    static int getTexture(lua_State* L);
    static int getTextureRect(lua_State* L);
    static int getFillColor(lua_State* L);
    static int getOutlineColor(lua_State* L);
    static int getOutlineThickness(lua_State* L);
    static int getLocalBounds(lua_State* L);
    static int getGlobalBounds(lua_State* L);
    static int setPosition(lua_State* L);
    static int setRotation(lua_State* L);
    static int setScale(lua_State* L);
    static int setOrigin(lua_State* L);
    static int getLocalPosition(lua_State* L);
    static int getWorldPosition(lua_State* L);
    static int getRotation(lua_State* L);
    static int getScale(lua_State* L);
    static int getOrigin(lua_State* L);
    static int move(lua_State* L);
    static int rotate(lua_State* L);
    static int scale(lua_State* L);
    static int getTransform(lua_State* L);
    static int getInverseTransform(lua_State* L);

    static int attachTo(lua_State* L);

    static LuaExporter toLuaExporter();
};