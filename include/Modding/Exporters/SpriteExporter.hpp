#pragma once

#include <SFML/Graphics.hpp>
#include <Modding/AttachableObject.hpp>
#include <lua.hpp>

#define LUA_SPRITE_CLASSNAME "Sprite"
#define LUA_SPRITE_METATABLENAME LUA_SPRITE_CLASSNAME"_metatable"
typedef AttachableObject<sf::Sprite> Lua_Sprite;

class LuaExporter;
struct SpriteExporter
{
    static void createSprite(lua_State* L, const sf::Texture* texture=nullptr, const sf::IntRect* rectangle=nullptr);
    static int __new(lua_State* L);
    static int __destroy(lua_State* L);
    static int __index(lua_State* L);

    static int setTexture(lua_State* L);
    static int setTextureRect(lua_State* L);
    static int setColor(lua_State* L);
    static int getTexture(lua_State* L);
    static int getTextureRect(lua_State* L);
    static int getColor(lua_State* L);
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