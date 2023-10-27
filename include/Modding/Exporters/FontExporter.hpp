#pragma once
#include <SFML/Graphics/Font.hpp>
#include <lua.hpp>
#include <filesystem>
namespace fs = std::filesystem;

#define LUA_FONT_CLASSNAME "Font"
#define LUA_FONT_METATABLENAME LUA_FONT_CLASSNAME"_metatable"
typedef sf::Font Exported_Font;

class LuaExporter;
struct FontExporter
{
    static void createFont(lua_State* L, const Exported_Font& font);
    static int __new(lua_State* L);
    static int __destroy(lua_State* L);
    static int __index(lua_State* L);

    static int loadFromFile(lua_State* L);
    static int getFontFamily(lua_State* L);
    static int getGlyph(lua_State* L);
    static int getKenning(lua_State* L);
    static int getLineSpacing(lua_State* L);
    static int getUnderlinePosition(lua_State* L);
    static int getUnderlineThickness(lua_State* L);

    static LuaExporter toLuaExporter();
};