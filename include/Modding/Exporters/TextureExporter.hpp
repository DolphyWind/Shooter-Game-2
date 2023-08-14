#pragma

#include <filesystem>
#include <iostream>

#include <SFML/Graphics.hpp>
#include <lua.hpp>
#include <Modding/LuaHelper.hpp>

#define LUA_TEXTURE_CLASSNAME "Texture"
#define LUA_TEXTURE_METATABLENAME LUA_TEXTURE_CLASSNAME"_metatable"
typedef sf::Texture Lua_Texture;

class LuaExporter;
struct TextureExporter
{
    static void createTexture(lua_State* L, const Lua_Texture& texture);
    static int __new(lua_State* L);
    static int __destroy(lua_State* L);
    static int __index(lua_State* L);

    static int create(lua_State* L);
    static int loadFromFile(lua_State* L);
    static int loadFromImage(lua_State* L);
    static int getSize(lua_State* L);
    static int copyToImage(lua_State* L);
    static int update(lua_State* L);
    static int setSmooth(lua_State* L);
    static int isSmooth(lua_State* L);
    static int setSrgb(lua_State* L);
    static int isSrgb(lua_State* L);
    static int setRepeated(lua_State* L);
    static int isRepeated(lua_State* L);
    static int generateMipmap(lua_State* L);
    static int swap(lua_State* L);
    static int getNativeHandle(lua_State* L);
    static int getMaximumSize(lua_State* L);

    static LuaExporter toLuaExporter();
};