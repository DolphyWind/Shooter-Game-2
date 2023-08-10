#pragma once
#include <SFML/Graphics/Font.hpp>
#include <lua.hpp>

#define LUA_GLYPH_CLASSNAME "Glyph"
#define LUA_GLYPH_METATABLENAME LUA_GLYPH_CLASSNAME"_metatable"
typedef sf::Glyph Lua_Glyph;

class LuaExporter;
struct GlyphExporter
{
    static void createGlyph(lua_State* L, const Lua_Glyph& glyph);
    static int __new(lua_State* L);
    static int __destroy(lua_State* L);
    static int __index(lua_State* L);
    static int __newindex(lua_State* L);
    static int __eq(lua_State* L);

    static LuaExporter toLuaExporter();
};