#include <Modding/LuaExporter.hpp>
#include <Modding/Exporters/FloatRectExporter.hpp>
#include <Modding/Exporters/Vector2Exporter.hpp>
#include "Modding/LuaHelper.hpp"

void FloatRectExporter::createFloatRect(lua_State *L, const Exported_FloatRect& floatRect)
{
    void* data = lua_newuserdata(L, sizeof(Exported_FloatRect));
    new (data) Exported_FloatRect(floatRect);
    luaL_getmetatable(L, LUA_FLOATRECT_METATABLENAME);
    lua_setmetatable(L, -2);
}

int FloatRectExporter::__new(lua_State *L)
{
    int arg_count = lua_gettop(L);

    if(arg_count == 0)
    {
        createFloatRect(L, Exported_FloatRect());
        return 1;
    }
    else if(arg_count == 1)
    {
        Exported_FloatRect* floatRectPtr = static_cast<Exported_FloatRect*>( LuaHelper::checkudata_WithError(L, 1, LUA_FLOATRECT_METATABLENAME) );
        createFloatRect(L, Exported_FloatRect(*floatRectPtr));
        return 1;
    }
    else if(arg_count == 2)
    {
        Exported_Vector2* positionVec = static_cast<Exported_Vector2*>( LuaHelper::checkudata_WithError(L, 1, LUA_VECTOR2_METATABLENAME) );
        Exported_Vector2* sizeVec = static_cast<Exported_Vector2*>( LuaHelper::checkudata_WithError(L, 2, LUA_VECTOR2_METATABLENAME) );
        createFloatRect(L, Exported_FloatRect(*positionVec, *sizeVec));
        return 1;
    }
    else if(arg_count == 3)
    {
        luaL_error(L, "Cannot create new FloatRect with that amount of arguments!");
    }

    lua_Number rectLeft = luaL_checknumber(L, 1);
    lua_Number rectTop = luaL_checknumber(L, 2);
    lua_Number rectWidth = luaL_checknumber(L, 3);
    lua_Number rectHeight = luaL_checknumber(L, 4);

    createFloatRect(L, Exported_FloatRect(rectLeft, rectTop, rectWidth, rectHeight));
    return 1;
}

int FloatRectExporter::__destroy(lua_State *L)
{
    Exported_FloatRect* floatRectPtr = static_cast<Exported_FloatRect*>( LuaHelper::checkudata_WithError(L, 1, LUA_FLOATRECT_METATABLENAME) );
    floatRectPtr->~Exported_FloatRect();
    return 0;
}

int FloatRectExporter::__index(lua_State *L)
{
    Exported_FloatRect* floatRectPtr = static_cast<Exported_FloatRect*>( LuaHelper::checkudata_WithError(L, 1, LUA_FLOATRECT_METATABLENAME) );
    std::string indexStr = luaL_checkstring(L, 2);

    if(indexStr == "left")
    {
        lua_pushnumber(L, floatRectPtr->left);
        return 1;
    }
    else if(indexStr == "top")
    {
        lua_pushnumber(L, floatRectPtr->top);
        return 1;
    }
    else if(indexStr == "width")
    {
        lua_pushnumber(L, floatRectPtr->width);
        return 1;
    }
    else if(indexStr == "height")
    {
        lua_pushnumber(L, floatRectPtr->height);
        return 1;
    }

    lua_getglobal(L, LUA_FLOATRECT_CLASSNAME);
    lua_pushstring(L, indexStr.c_str());
    lua_rawget(L, -2);
    return 1;
}

int FloatRectExporter::__newindex(lua_State *L)
{
    Exported_FloatRect* floatRectPtr = static_cast<Exported_FloatRect*>( LuaHelper::checkudata_WithError(L, 1, LUA_FLOATRECT_METATABLENAME) );
    std::string indexStr = luaL_checkstring(L, 2);

    if(indexStr == "left")
    {
        floatRectPtr->left = luaL_checknumber(L, 3);
        return 0;
    }
    else if(indexStr == "top")
    {
        floatRectPtr->top = luaL_checknumber(L, 3);
        return 0;
    }
    else if(indexStr == "width")
    {
        floatRectPtr->width = luaL_checknumber(L, 3);
        return 0;
    }
    else if(indexStr == "height")
    {
        floatRectPtr->height = luaL_checknumber(L, 3);
        return 0;
    }

    luaL_error(L, "Cannot set value for %s", indexStr.c_str());
    return 0;
}

int FloatRectExporter::__eq(lua_State *L)
{
    if(lua_type(L, 1) != lua_type(L, 2))
    {
        lua_pushboolean(L, false);
        return 1;
    }

    Exported_FloatRect* firstFloatRect = static_cast<Exported_FloatRect*>( LuaHelper::checkudata_WithError(L, 1, LUA_FLOATRECT_METATABLENAME) );
    Exported_FloatRect* secondFloatRect = static_cast<Exported_FloatRect*>( LuaHelper::checkudata_WithError(L, 2, LUA_FLOATRECT_METATABLENAME) );
    lua_pushboolean(L, (*firstFloatRect) == (*secondFloatRect));
    return 1;
}

int FloatRectExporter::contains(lua_State *L)
{
    int arg_count = lua_gettop(L);
    Exported_FloatRect* floatRectPtr = static_cast<Exported_FloatRect*>( LuaHelper::checkudata_WithError(L, 1, LUA_FLOATRECT_METATABLENAME) );

    if(arg_count == 2)
    {
        Exported_Vector2* vecPtr = static_cast<Exported_Vector2*>( LuaHelper::checkudata_WithError(L, 2, LUA_VECTOR2_METATABLENAME) );
        lua_pushboolean(L, floatRectPtr->contains(*vecPtr));
        return 1;
    }

    lua_Number x = luaL_checknumber(L, 2);
    lua_Number y = luaL_checknumber(L, 3);
    lua_pushboolean(L, floatRectPtr->contains(x, y));
    return 1;
}

int FloatRectExporter::intersects(lua_State *L)
{
    int arg_count = lua_gettop(L);
    Exported_FloatRect* floatRectPtr = static_cast<Exported_FloatRect*>( LuaHelper::checkudata_WithError(L, 1, LUA_FLOATRECT_METATABLENAME) );
    Exported_FloatRect* rectanglePtr = static_cast<Exported_FloatRect*>( LuaHelper::checkudata_WithError(L, 2, LUA_FLOATRECT_METATABLENAME) );

    if(arg_count == 2)
    {
        lua_pushboolean(L, floatRectPtr->intersects(*rectanglePtr));
        return 1;
    }

    Exported_FloatRect* intersectionPtr = static_cast<Exported_FloatRect*>( LuaHelper::checkudata_WithError(L, 3, LUA_FLOATRECT_METATABLENAME) );
    lua_pushboolean(L, floatRectPtr->intersects(*rectanglePtr, *intersectionPtr));
    return 1;
}

int FloatRectExporter::getPosition(lua_State *L)
{
    Exported_FloatRect* floatRectPtr = static_cast<Exported_FloatRect*>( LuaHelper::checkudata_WithError(L, 1, LUA_FLOATRECT_METATABLENAME) );
    Vector2Exporter::createVector(L, Exported_Vector2(floatRectPtr->left, floatRectPtr->top));
    return 1;
}

int FloatRectExporter::getSize(lua_State *L)
{
    Exported_FloatRect* floatRectPtr = static_cast<Exported_FloatRect*>( LuaHelper::checkudata_WithError(L, 1, LUA_FLOATRECT_METATABLENAME) );
    Vector2Exporter::createVector(L, Exported_Vector2(floatRectPtr->width, floatRectPtr->height));
    return 1;
}

LuaExporter FloatRectExporter::toLuaExporter()
{
    LuaExporter exporter(
        LUA_FLOATRECT_CLASSNAME,
        __new,
        {
            {"contains", FloatRectExporter::contains},
            {"intersects", FloatRectExporter::intersects},
            {"getPosition", FloatRectExporter::getPosition},
            {"getSize", FloatRectExporter::getSize},
        },
        {
            {"__gc", FloatRectExporter::__destroy},
            {"__index", FloatRectExporter::__index},
            {"__newindex", FloatRectExporter::__newindex},
            {"__eq", FloatRectExporter::__eq},
        }
    );

    return exporter;
}