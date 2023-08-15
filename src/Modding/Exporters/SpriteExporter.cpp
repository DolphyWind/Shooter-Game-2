#include <Modding/Exporters/SpriteExporter.hpp>
#include <Modding/Exporters/TextureExporter.hpp>
#include <Modding/Exporters/IntRectExporter.hpp>
#include <Modding/Exporters/FloatRectExporter.hpp>
#include <Modding/Exporters/ColorExporter.hpp>
#include <Modding/Exporters/Vector2Exporter.hpp>
#include <Modding/Exporters/TransformExporter.hpp>
#include <Modding/LuaHelper.hpp>
#include <Modding/LuaExporter.hpp>

void SpriteExporter::createSprite(lua_State* L, const sf::Texture* texture, const sf::IntRect* rectangle)
{
    void* data = lua_newuserdata(L, sizeof(Lua_Sprite));
    if(!texture)
    {
        new (data) Lua_Sprite();
    }
    else
    {
        if(!rectangle)
        {
            new (data) Lua_Sprite(*texture);
        }
        else
        {
            new (data) Lua_Sprite(*texture, *rectangle);
        }
    }
    luaL_getmetatable(L, LUA_SPRITE_METATABLENAME);
    lua_setmetatable(L, -2);
}

int SpriteExporter::__new(lua_State *L)
{
    int arg_count = lua_gettop(L);
    if(arg_count == 0)
    {
        createSprite(L);
        return 1;
    }

    Lua_Texture* texturePtr = static_cast<Lua_Texture*>( luaL_checkudata(L, 1, LUA_TEXTURE_METATABLENAME) );
    Lua_IntRect* rectanglePtr = nullptr;
    if(arg_count >= 2)
    {
        rectanglePtr = static_cast<Lua_IntRect*>( luaL_checkudata(L, 2, LUA_TEXTURE_METATABLENAME) );
    }

    createSprite(L, texturePtr, rectanglePtr);
    return 1;
}

int SpriteExporter::__destroy(lua_State *L)
{
    Lua_Sprite* spritePtr = static_cast<Lua_Sprite*>( luaL_checkudata(L, 1, LUA_SPRITE_METATABLENAME) );
    spritePtr->~Lua_Sprite();
    return 0;
}

int SpriteExporter::__index(lua_State* L)
{
    Lua_Sprite* spritePtr = static_cast<Lua_Sprite*>( luaL_checkudata(L, 1, LUA_SPRITE_METATABLENAME) );
    std::string indexStr = lua_tostring(L, 2);

    lua_getglobal(L, LUA_SPRITE_CLASSNAME);
    lua_pushstring(L, indexStr.c_str());
    lua_rawget(L, -2);
    return 1;
}

int SpriteExporter::setTexture(lua_State* L)
{
    int arg_count = lua_gettop(L);
    Lua_Sprite* spritePtr = static_cast<Lua_Sprite*>( luaL_checkudata(L, 1, LUA_SPRITE_METATABLENAME) );
    Lua_Texture* texturePtr = static_cast<Lua_Texture*>( luaL_checkudata(L, 2, LUA_TEXTURE_METATABLENAME) );
    bool resetRect = false;

    if(arg_count >= 3)
    {
        resetRect = lua_toboolean(L, 3);
    }
    spritePtr->setTexture(*texturePtr, resetRect);

    return 0;
}

int SpriteExporter::setTextureRect(lua_State* L)
{
    Lua_Sprite* spritePtr = static_cast<Lua_Sprite*>( luaL_checkudata(L, 1, LUA_SPRITE_METATABLENAME) );
    Lua_IntRect* rectPtr = static_cast<Lua_IntRect*>( luaL_checkudata(L, 2, LUA_INTRECT_METATABLENAME) );
    spritePtr->setTextureRect(*rectPtr);

    return 0;
}

int SpriteExporter::setColor(lua_State* L)
{
    Lua_Sprite* spritePtr = static_cast<Lua_Sprite*>( luaL_checkudata(L, 1, LUA_SPRITE_METATABLENAME) );
    Lua_Color* colorPtr = static_cast<Lua_Color*>( luaL_checkudata(L, 2, LUA_COLOR_METATABLENAME) );
    spritePtr->setColor(*colorPtr);

    return 0;
}

int SpriteExporter::getTexture(lua_State* L)
{
    Lua_Sprite* spritePtr = static_cast<Lua_Sprite*>( luaL_checkudata(L, 1, LUA_SPRITE_METATABLENAME) );
    LuaHelper::push(L, {(void*)spritePtr->getTexture(), LUA_TEXTURE_METATABLENAME});

    return 1;
}

int SpriteExporter::getTextureRect(lua_State* L)
{
    Lua_Sprite* spritePtr = static_cast<Lua_Sprite*>( luaL_checkudata(L, 1, LUA_SPRITE_METATABLENAME) );
    IntRectExporter::createIntRect(L, spritePtr->getTextureRect());

    return 1;
}

int SpriteExporter::getColor(lua_State* L)
{
    Lua_Sprite* spritePtr = static_cast<Lua_Sprite*>( luaL_checkudata(L, 1, LUA_SPRITE_METATABLENAME) );
    ColorExporter::createColor(L, spritePtr->getColor());

    return 1;
}

int SpriteExporter::getLocalBounds(lua_State* L)
{
    Lua_Sprite* spritePtr = static_cast<Lua_Sprite*>( luaL_checkudata(L, 1, LUA_SPRITE_METATABLENAME) );
    FloatRectExporter::createFloatRect(L, spritePtr->getLocalBounds());

    return 1;
}

int SpriteExporter::getGlobalBounds(lua_State* L)
{
    Lua_Sprite* spritePtr = static_cast<Lua_Sprite*>( luaL_checkudata(L, 1, LUA_SPRITE_METATABLENAME) );
    FloatRectExporter::createFloatRect(L, spritePtr->getGlobalBounds());

    return 1;
}

int SpriteExporter::setPosition(lua_State* L)
{
    int arg_count = lua_gettop(L);
    Lua_Sprite* spritePtr = static_cast<Lua_Sprite*>( luaL_checkudata(L, 1, LUA_SPRITE_METATABLENAME) );
    Lua_Vector2* vecPtr;

    vecPtr = (Lua_Vector2*)LuaHelper::checkudata(L, 2, LUA_VECTOR2_METATABLENAME);
    if(vecPtr)
    {
        spritePtr->setPosition(*vecPtr);
        return 0;
    }
    spritePtr->setPosition(
        luaL_checknumber(L, 2),
        luaL_checknumber(L, 3)
    );

    return 0;
}

int SpriteExporter::setRotation(lua_State* L)
{
    Lua_Sprite* spritePtr = static_cast<Lua_Sprite*>( luaL_checkudata(L, 1, LUA_SPRITE_METATABLENAME) );
    spritePtr->setRotation(luaL_checknumber(L, 2) );

    return 0;
}

int SpriteExporter::setScale(lua_State* L)
{
    Lua_Sprite* spritePtr = static_cast<Lua_Sprite*>( luaL_checkudata(L, 1, LUA_SPRITE_METATABLENAME) );
    Lua_Vector2* vecPtr;

    vecPtr = (Lua_Vector2*) LuaHelper::checkudata(L, 2, LUA_VECTOR2_METATABLENAME);
    if(vecPtr)
    {
        spritePtr->setScale(*vecPtr);
        return 0;
    }
    spritePtr->setScale(
        luaL_checknumber(L, 2),
        luaL_checknumber(L, 3)
    );

    return 0;
}

int SpriteExporter::setOrigin(lua_State* L)
{
    Lua_Sprite* spritePtr = static_cast<Lua_Sprite*>( luaL_checkudata(L, 1, LUA_SPRITE_METATABLENAME) );
    Lua_Vector2* vecPtr;

    vecPtr = (Lua_Vector2*) LuaHelper::checkudata(L, 2, LUA_VECTOR2_METATABLENAME);
    if(vecPtr)
    {
        spritePtr->setOrigin(*vecPtr);
        return 0;
    }
    spritePtr->setOrigin(
        luaL_checknumber(L, 2),
        luaL_checknumber(L, 3)
    );

    return 0;
}

int SpriteExporter::getPosition(lua_State* L)
{
    Lua_Sprite* spritePtr = static_cast<Lua_Sprite*>( luaL_checkudata(L, 1, LUA_SPRITE_METATABLENAME) );
    Vector2Exporter::createVector(L, spritePtr->getPosition());

    return 1;
}

int SpriteExporter::getRotation(lua_State* L)
{
    Lua_Sprite* spritePtr = static_cast<Lua_Sprite*>( luaL_checkudata(L, 1, LUA_SPRITE_METATABLENAME) );
    lua_pushnumber(L, spritePtr->getRotation());

    return 1;
}

int SpriteExporter::getScale(lua_State* L)
{
    Lua_Sprite* spritePtr = static_cast<Lua_Sprite*>( luaL_checkudata(L, 1, LUA_SPRITE_METATABLENAME) );
    Vector2Exporter::createVector(L, spritePtr->getScale());

    return 1;
}

int SpriteExporter::getOrigin(lua_State* L)
{
    Lua_Sprite* spritePtr = static_cast<Lua_Sprite*>( luaL_checkudata(L, 1, LUA_SPRITE_METATABLENAME) );
    Vector2Exporter::createVector(L, spritePtr->getOrigin());

    return 1;
}

int SpriteExporter::move(lua_State* L)
{
    Lua_Sprite* spritePtr = static_cast<Lua_Sprite*>( luaL_checkudata(L, 1, LUA_SPRITE_METATABLENAME) );
    Lua_Vector2* vecPtr;

    vecPtr = (Lua_Vector2*) LuaHelper::checkudata(L, 2, LUA_VECTOR2_METATABLENAME);
    if(vecPtr)
    {
        spritePtr->move(*vecPtr);
        return 0;
    }
    spritePtr->move(
        luaL_checknumber(L, 2),
        luaL_checknumber(L, 3)
    );

    return 0;
}

int SpriteExporter::rotate(lua_State* L)
{
    Lua_Sprite* spritePtr = static_cast<Lua_Sprite*>( luaL_checkudata(L, 1, LUA_SPRITE_METATABLENAME) );
    spritePtr->rotate(luaL_checknumber(L, 2));

    return 0;
}

int SpriteExporter::scale(lua_State* L)
{
    Lua_Sprite* spritePtr = static_cast<Lua_Sprite*>( luaL_checkudata(L, 1, LUA_SPRITE_METATABLENAME) );
    Lua_Vector2* vecPtr;

    vecPtr = (Lua_Vector2*) LuaHelper::checkudata(L, 2, LUA_VECTOR2_METATABLENAME);
    if(vecPtr)
    {
        spritePtr->scale(*vecPtr);
        return 0;
    }
    spritePtr->scale(
        luaL_checknumber(L, 2),
        luaL_checknumber(L, 3)
    );

    return 0;
}

int SpriteExporter::getTransform(lua_State* L)
{
    Lua_Sprite* spritePtr = static_cast<Lua_Sprite*>( luaL_checkudata(L, 1, LUA_SPRITE_METATABLENAME) );
    TransformExporter::createTransform(L, spritePtr->getTransform());

    return 1;
}

int SpriteExporter::getInverseTransform(lua_State* L)
{
    Lua_Sprite* spritePtr = static_cast<Lua_Sprite*>( luaL_checkudata(L, 1, LUA_SPRITE_METATABLENAME) );
    TransformExporter::createTransform(L, spritePtr->getInverseTransform());

    return 1;
}

LuaExporter SpriteExporter::toLuaExporter()
{
    LuaExporter exporter(
        LUA_SPRITE_CLASSNAME,
        __new,
        {
            {"setTexture", SpriteExporter::setTexture},
            {"setTextureRect", SpriteExporter::setTextureRect},
            {"setColor", SpriteExporter::setColor},
            {"getTexture", SpriteExporter::getTexture},
            {"getTextureRect", SpriteExporter::getTextureRect},
            {"getColor", SpriteExporter::getColor},
            {"getLocalBounds", SpriteExporter::getLocalBounds},
            {"getGlobalBounds", SpriteExporter::getGlobalBounds},
            {"setPosition", SpriteExporter::setPosition},
            {"setRotation", SpriteExporter::setRotation},
            {"setScale", SpriteExporter::setScale},
            {"setOrigin", SpriteExporter::setOrigin},
            {"getPosition", SpriteExporter::getPosition},
            {"getRotation", SpriteExporter::getRotation},
            {"getScale", SpriteExporter::getScale},
            {"getOrigin", SpriteExporter::getOrigin},
            {"move", SpriteExporter::move},
            {"rotate", SpriteExporter::rotate},
            {"scale", SpriteExporter::scale},
            {"getTransform", SpriteExporter::getTransform},
            {"getInverseTransform", SpriteExporter::getInverseTransform},
        },
        {
            {"__gc", SpriteExporter::__destroy},
            {"__index", SpriteExporter::__index},
        }
    );

    return exporter;
}