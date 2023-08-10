#pragma once
#include <SFML/Graphics/Image.hpp>
#include <filesystem>
#include <lua.hpp>

#define LUA_IMAGE_CLASSNAME "Image"
#define LUA_IMAGE_METATABLENAME LUA_IMAGE_CLASSNAME"_metatable"
typedef sf::Image Lua_Image;

class LuaExporter;
struct ImageExporter
{
    static void createImage(lua_State* L, const Lua_Image& image);
    static int __new(lua_State* L);
    static int __index(lua_State* L);
    static int __destroy(lua_State* L);
    
    static int create(lua_State* L);
    static int loadFromFile(lua_State* L);
    static int saveToFile(lua_State* L);
    static int getSize(lua_State* L);
    static int createMaskFromColor(lua_State* L);
    static int copy(lua_State* L);
    static int setPixel(lua_State* L);
    static int getPixel(lua_State* L);
    static int flipHorizontally(lua_State* L);
    static int flipVertically(lua_State* L);

    static LuaExporter toLuaExporter();
};