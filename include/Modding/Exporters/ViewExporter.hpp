#pragma once
#include <SFML/Graphics.hpp>
#include <lua.hpp>

#define LUA_VIEW_CLASSNAME "View"
#define LUA_VIEW_METATABLENAME LUA_VIEW_CLASSNAME"_metatable"
typedef sf::View Exported_View;

class LuaExporter;
struct ViewExporter
{
    static void createView(lua_State* L, const Exported_View& view);
    static int __new(lua_State* L);
    static int __destroy(lua_State* L);
    static int __index(lua_State* L);

    static int setCenter(lua_State* L);
    static int setSize(lua_State* L);
    static int setRotation(lua_State* L);
    static int setViewport(lua_State* L);
    static int reset(lua_State* L);
    static int getCenter(lua_State* L);
    static int getSize(lua_State* L);
    static int getRotation(lua_State* L);
    static int getViewport(lua_State* L);
    static int move(lua_State* L);
    static int rotate(lua_State* L);
    static int zoom(lua_State* L);
    static int getTransform(lua_State* L);
    static int getInverseTransform(lua_State* L);

    static LuaExporter toLuaExporter();
};