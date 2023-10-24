#include <Modding/LuaExporter.hpp>
#include <Modding/Exporters/ImageExporter.hpp>
#include <Modding/Exporters/ColorExporter.hpp>
#include <Modding/Exporters/IntRectExporter.hpp>
#include <Modding/Exporters/Vector2Exporter.hpp>
#include <iostream>
#include "Modding/LuaHelper.hpp"

void ImageExporter::createImage(lua_State *L, const Lua_Image &image)
{
    void* data = lua_newuserdata(L, sizeof(Lua_Image));
    new (data) Lua_Image(image);
    luaL_getmetatable(L, LUA_IMAGE_METATABLENAME);
    lua_setmetatable(L, -2);
}

int ImageExporter::__new(lua_State *L)
{
    createImage(L, sf::Image());
    return 1;
}

int ImageExporter::__index(lua_State *L)
{
    Lua_Image* imagePtr = static_cast<Lua_Image*>( LuaHelper::checkudata_WithError(L, 1, LUA_IMAGE_METATABLENAME) );
    std::string indexStr = luaL_checkstring(L, 2);

    lua_getglobal(L, LUA_IMAGE_CLASSNAME);
    lua_pushstring(L, indexStr.c_str());
    lua_rawget(L, -2);
    return 1;
}

int ImageExporter::__destroy(lua_State *L)
{
    Lua_Image* imagePtr = static_cast<Lua_Image*>( LuaHelper::checkudata_WithError(L, 1, LUA_IMAGE_METATABLENAME) );
    imagePtr->~Lua_Image();
    return 0;
}

int ImageExporter::create(lua_State *L)
{
    int arg_count = lua_gettop(L);
    Lua_Image* imagePtr = static_cast<Lua_Image*>( LuaHelper::checkudata_WithError(L, 1, LUA_IMAGE_METATABLENAME) );
    lua_Integer width;
    lua_Integer height;
    lua_numbertointeger(luaL_checknumber(L, 2), &width);
    lua_numbertointeger(luaL_checknumber(L, 3), &height);
    Exported_Color color(0, 0, 0);

    if(arg_count > 3)
    {
        color = *static_cast<Exported_Color*>( LuaHelper::checkudata_WithError(L, 4, LUA_COLOR_METATABLENAME) );
    }
    imagePtr->create(width, height, color);

    return 0;
}

int ImageExporter::loadFromFile(lua_State *L)
{
    Lua_Image* imagePtr = static_cast<Lua_Image*>( LuaHelper::checkudata_WithError(L, 1, LUA_IMAGE_METATABLENAME) );
    lua_getglobal(L, ASSETSPATH_VARNAME);
    std::filesystem::path total_path( luaL_checkstring(L, -1) );
    lua_pop(L, 1);
    total_path /= luaL_checkstring(L, 2);
    bool result = imagePtr->loadFromFile(total_path.string());
    lua_pushboolean(L, result);

    return 1;
}

int ImageExporter::saveToFile(lua_State *L)
{
    Lua_Image* imagePtr = static_cast<Lua_Image*>( LuaHelper::checkudata_WithError(L, 1, LUA_IMAGE_METATABLENAME) );
    lua_getglobal(L, ASSETSPATH_VARNAME);
    std::filesystem::path total_path( luaL_checkstring(L, -1) );
    lua_pop(L, 1);
    total_path /= luaL_checkstring(L, 2);
    bool result = imagePtr->saveToFile(total_path.string());
    lua_pushboolean(L, result);

    return 1;
}

int ImageExporter::getSize(lua_State *L)
{
    Lua_Image* imagePtr = static_cast<Lua_Image*>( LuaHelper::checkudata_WithError(L, 1, LUA_IMAGE_METATABLENAME) );
    Exported_Vector2 size = imagePtr->getSize();
    Vector2Exporter::createVector(L, size);
    return 1;
}

int ImageExporter::createMaskFromColor(lua_State *L)
{
    int arg_count = lua_gettop(L);
    Lua_Image* imagePtr = static_cast<Lua_Image*>( LuaHelper::checkudata_WithError(L, 1, LUA_IMAGE_METATABLENAME) );
    Exported_Color* colorPtr = static_cast<Exported_Color*>( LuaHelper::checkudata_WithError(L, 2, LUA_COLOR_METATABLENAME) );
    lua_Integer alpha = 0;
    
    if(arg_count > 2)
    {
        lua_numbertointeger(luaL_checknumber(L, 3), &alpha);
    }
    imagePtr->createMaskFromColor(*colorPtr, alpha);

    return 0;
}

int ImageExporter::copy(lua_State *L)
{
    int arg_count = lua_gettop(L);
    Lua_Image* imagePtr = static_cast<Lua_Image*>( LuaHelper::checkudata_WithError(L, 1, LUA_IMAGE_METATABLENAME) );
    Lua_Image* sourcePtr = static_cast<Lua_Image*>( LuaHelper::checkudata_WithError(L, 2, LUA_IMAGE_METATABLENAME) );
    lua_Integer destX;
    lua_Integer destY;
    sf::IntRect sourceRect(0, 0, 0, 0);
    bool applyAlpha = false;

    lua_numbertointeger(luaL_checknumber(L, 3), &destX);
    lua_numbertointeger(luaL_checknumber(L, 4), &destY);
    if(arg_count > 4)
    {
        sourceRect = *static_cast<Exported_IntRect*>( LuaHelper::checkudata_WithError(L, 5, LUA_INTRECT_METATABLENAME) );
        if(arg_count > 5)
        {
            applyAlpha = lua_toboolean(L, 2);
        }
    }
    imagePtr->copy(*sourcePtr, destX, destY, sourceRect, applyAlpha);

    return 0;
}

int ImageExporter::setPixel(lua_State *L)
{
    Lua_Image* imagePtr = static_cast<Lua_Image*>( LuaHelper::checkudata_WithError(L, 1, LUA_IMAGE_METATABLENAME) );
    lua_Integer x;
    lua_Integer y;
    Exported_Color color;
    
    lua_numbertointeger(luaL_checknumber(L, 2), &x);
    lua_numbertointeger(luaL_checknumber(L, 3), &y);
    color = *static_cast<Exported_Color*>( LuaHelper::checkudata_WithError(L, 4, LUA_COLOR_METATABLENAME) );
    imagePtr->setPixel(x, y, color);

    return 0;
}

int ImageExporter::getPixel(lua_State *L)
{
    Lua_Image* imagePtr = static_cast<Lua_Image*>( LuaHelper::checkudata_WithError(L, 1, LUA_IMAGE_METATABLENAME) );
    lua_Integer x;
    lua_Integer y;
    
    lua_numbertointeger(luaL_checknumber(L, 2), &x);
    lua_numbertointeger(luaL_checknumber(L, 3), &y);
    ColorExporter::createColor(L, imagePtr->getPixel(x, y));

    return 1;
}

int ImageExporter::flipHorizontally(lua_State *L)
{
    Lua_Image* imagePtr = static_cast<Lua_Image*>( LuaHelper::checkudata_WithError(L, 1, LUA_IMAGE_METATABLENAME) );
    imagePtr->flipHorizontally();
    return 0;
}

int ImageExporter::flipVertically(lua_State *L)
{
    Lua_Image* imagePtr = static_cast<Lua_Image*>( LuaHelper::checkudata_WithError(L, 1, LUA_IMAGE_METATABLENAME) );
    imagePtr->flipVertically();
    return 0;
}

LuaExporter ImageExporter::toLuaExporter()
{
    LuaExporter exporter(
        LUA_IMAGE_CLASSNAME,
        __new, 
        {
            {"create", ImageExporter::create},
            {"loadFromFile", ImageExporter::loadFromFile},
            {"saveToFile", ImageExporter::saveToFile},
            {"getSize", ImageExporter::getSize},
            {"createMaskFromColor", ImageExporter::createMaskFromColor},
            {"copy", ImageExporter::copy},
            {"setPixel", ImageExporter::setPixel},
            {"getPixel", ImageExporter::getPixel},
            {"flipHorizontally", ImageExporter::flipHorizontally},
            {"flipVertically", ImageExporter::flipVertically},
        },
        {
            {"__gc", ImageExporter::__destroy},
            {"__index", ImageExporter::__index},
        }
    );

    return exporter;
}
