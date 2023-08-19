#pragma once

#include <SFML/Graphics.hpp>
#include <lua.hpp>

#define LUA_TEXT_CLASSNAME "Text"
#define LUA_TEXT_METATABLENAME LUA_TEXT_CLASSNAME"_metatable"
typedef sf::Text Lua_Text;

class LuaExporter;
struct TextExporter
{
    static void createText(lua_State* L);
    static void createText(lua_State* L, const sf::String& string, sf::Font* font, unsigned int charSize);
    static int __new(lua_State* L);
    static int __destroy(lua_State* L);
    static int __index(lua_State* L);

    static int setString(lua_State* L);
    static int setFont(lua_State* L);
    static int setCharacterSize(lua_State* L);
    static int setLineSpacing(lua_State* L);
    static int setLetterSpacing(lua_State* L);
    static int setStyle(lua_State* L);
    static int setFillColor(lua_State* L);
    static int setOutlineColor(lua_State* L);
    static int setOutlineThickness(lua_State* L);
    static int getString(lua_State* L);
    static int getFont(lua_State* L);
    static int getCharacterSize(lua_State* L);
    static int getLetterSpacing(lua_State* L);
    static int getLineSpacing(lua_State* L);
    static int getStyle(lua_State* L);
    static int getFillColor(lua_State* L);
    static int getOutlineColor(lua_State* L);
    static int getOutlineThickness(lua_State* L);
    static int findCharacterPos(lua_State* L);
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