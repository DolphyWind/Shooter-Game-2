#pragma once

#include <SFML/Graphics.hpp>
#include <lua.hpp>

#define LUA_CIRCLESHAPE_CLASSNAME "CircleShape"
#define LUA_CIRCLESHAPE_METATABLENAME LUA_CIRCLESHAPE_CLASSNAME"_metatable"
typedef sf::CircleShape Lua_CircleShape;

class LuaExporter;
struct CircleShapeExporter
{
    static void createCircleShape(lua_State* L, float radius=0.0f, std::size_t pointCount=30);
    static int __new(lua_State* L);
    static int __destroy(lua_State* L);
    static int __index(lua_State* L);

    static int setRadius(lua_State* L);
    static int getRadius(lua_State* L);
    static int getPointCount(lua_State* L);
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
    static int getPosition(lua_State* L);
    static int getRotation(lua_State* L);
    static int getScale(lua_State* L);
    static int getOrigin(lua_State* L);
    static int move(lua_State* L);
    static int rotate(lua_State* L);
    static int scale(lua_State* L);
    static int getTransform(lua_State* L);
    static int getInverseTransform(lua_State* L);

    static LuaExporter toLuaExporter();
};