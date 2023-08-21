#include <Modding/LuaExporter.hpp>
#include <Modding/Exporters/IntRectExporter.hpp>
#include <Modding/Exporters/Vector2Exporter.hpp>
#include "Modding/LuaHelper.hpp"

void IntRectExporter::createIntRect(lua_State *L, const Lua_IntRect& intRect)
{
    void* data = lua_newuserdata(L, sizeof(Lua_IntRect));
    new (data) Lua_IntRect(intRect);
    luaL_getmetatable(L, LUA_INTRECT_METATABLENAME);
    lua_setmetatable(L, -2);
}

int IntRectExporter::__new(lua_State *L)
{
    int arg_count = lua_gettop(L);

    if(arg_count == 0)
    {
        createIntRect(L, Lua_IntRect());
        return 1;
    }
    else if(arg_count == 1)
    {
        Lua_IntRect* intRectPtr = static_cast<Lua_IntRect*>( LuaHelper::checkudata_WithError(L, 1, LUA_INTRECT_METATABLENAME) );
        createIntRect(L, Lua_IntRect(*intRectPtr));
        return 1;
    }
    else if(arg_count == 2)
    {
        Lua_Vector2* positionVec = static_cast<Lua_Vector2*>( LuaHelper::checkudata_WithError(L, 1, LUA_VECTOR2_METATABLENAME) );
        Lua_Vector2* sizeVec = static_cast<Lua_Vector2*>( LuaHelper::checkudata_WithError(L, 2, LUA_VECTOR2_METATABLENAME) );
        createIntRect(L, Lua_IntRect(*positionVec, *sizeVec));
        return 1;
    }
    else if(arg_count == 4)
    {
        lua_Integer rectLeft;
        lua_Integer rectTop;
        lua_Integer rectWidth;
        lua_Integer rectHeight;
        lua_numbertointeger(luaL_checknumber(L, 1), &rectLeft);
        lua_numbertointeger(luaL_checknumber(L, 2), &rectTop);
        lua_numbertointeger(luaL_checknumber(L, 3), &rectWidth);
        lua_numbertointeger(luaL_checknumber(L, 4), &rectHeight);

        createIntRect(L, Lua_IntRect(rectLeft, rectTop, rectWidth, rectHeight));
        return 1;
    }

    luaL_error(L, "Cannot create new IntRect with that amount of arguments!");
    return 0;
}

int IntRectExporter::__destroy(lua_State *L)
{
    Lua_IntRect* intRectPtr = static_cast<Lua_IntRect*>( LuaHelper::checkudata_WithError(L, 1, LUA_INTRECT_METATABLENAME) );
    intRectPtr->~Lua_IntRect();
    return 0;
}

int IntRectExporter::__index(lua_State *L)
{
    Lua_IntRect* intRectPtr = static_cast<Lua_IntRect*>( LuaHelper::checkudata_WithError(L, 1, LUA_INTRECT_METATABLENAME) );
    std::string indexStr = luaL_checkstring(L, 2);

    if(indexStr == "left")
    {
        lua_pushinteger(L, intRectPtr->left);
        return 1;
    }
    else if(indexStr == "top")
    {
        lua_pushinteger(L, intRectPtr->top);
        return 1;
    }
    else if(indexStr == "width")
    {
        lua_pushinteger(L, intRectPtr->width);
        return 1;
    }
    else if(indexStr == "height")
    {
        lua_pushinteger(L, intRectPtr->height);
        return 1;
    }

    lua_getglobal(L, LUA_INTRECT_CLASSNAME);
    lua_pushstring(L, indexStr.c_str());
    lua_rawget(L, -2);
    return 1;
}

int IntRectExporter::__newindex(lua_State *L)
{
    Lua_IntRect* intRectPtr = static_cast<Lua_IntRect*>( LuaHelper::checkudata_WithError(L, 1, LUA_INTRECT_METATABLENAME) );
    std::string indexStr = luaL_checkstring(L, 2);

    if(indexStr == "left")
    {
        lua_numbertointeger(luaL_checknumber(L, 3), &intRectPtr->left);
        return 0;
    }
    else if(indexStr == "top")
    {
        lua_numbertointeger(luaL_checknumber(L, 3), &intRectPtr->top);
        return 0;
    }
    else if(indexStr == "width")
    {
        lua_numbertointeger(luaL_checknumber(L, 3), &intRectPtr->width);
        return 0;
    }
    else if(indexStr == "height")
    {
        lua_numbertointeger(luaL_checknumber(L, 3), &intRectPtr->height);
        return 0;
    }

    luaL_error(L, "Cannot set value for %s", indexStr.c_str());
    return 0;
}

int IntRectExporter::__eq(lua_State *L)
{
    if(lua_type(L, 1) != lua_type(L, 2))
    {
        lua_pushboolean(L, false);
        return 1;
    }

    Lua_IntRect* firstIntRect = static_cast<Lua_IntRect*>( LuaHelper::checkudata_WithError(L, 1, LUA_INTRECT_METATABLENAME) );
    Lua_IntRect* secondIntRect = static_cast<Lua_IntRect*>( LuaHelper::checkudata_WithError(L, 2, LUA_INTRECT_METATABLENAME) );
    lua_pushboolean(L, (*firstIntRect) == (*secondIntRect));
    return 1;
}

int IntRectExporter::contains(lua_State *L)
{
    int arg_count = lua_gettop(L);
    Lua_IntRect* intRectPtr = static_cast<Lua_IntRect*>( LuaHelper::checkudata_WithError(L, 1, LUA_INTRECT_METATABLENAME) );

    if(arg_count == 2)
    {
        Lua_Vector2* vecPtr = static_cast<Lua_Vector2*>( LuaHelper::checkudata_WithError(L, 2, LUA_VECTOR2_METATABLENAME) );
        lua_pushboolean(L, intRectPtr->contains(*vecPtr));
        return 1;
    }
    else if(arg_count == 3)
    {
        lua_Integer x;
        lua_Integer y;
        lua_numbertointeger(luaL_checknumber(L, 2), &x);
        lua_numbertointeger(luaL_checknumber(L, 3), &y);
        lua_pushboolean(L, intRectPtr->contains(x, y));
        return 1;
    }

    luaL_error(L, "You can't call %s with this amount of arguments", __func__);
    return 0;
}

int IntRectExporter::intersects(lua_State *L)
{
    int arg_count = lua_gettop(L);
    Lua_IntRect* intRectPtr = static_cast<Lua_IntRect*>( LuaHelper::checkudata_WithError(L, 1, LUA_INTRECT_METATABLENAME) );
    Lua_IntRect* rectanglePtr = static_cast<Lua_IntRect*>( LuaHelper::checkudata_WithError(L, 2, LUA_INTRECT_METATABLENAME) );

    if(arg_count == 2)
    {
        lua_pushboolean(L, intRectPtr->intersects(*rectanglePtr));
        return 1;
    }
    else if(arg_count == 3)
    {
        Lua_IntRect* intersectionPtr = static_cast<Lua_IntRect*>( LuaHelper::checkudata_WithError(L, 3, LUA_INTRECT_METATABLENAME) );
        lua_pushboolean(L, intRectPtr->intersects(*rectanglePtr, *intersectionPtr));
        return 1;
    }

    luaL_error(L, "You can't call %s with this amount of arguments", __func__);
    return 0;
}

int IntRectExporter::getPosition(lua_State *L)
{
    Lua_IntRect* intRectPtr = static_cast<Lua_IntRect*>( LuaHelper::checkudata_WithError(L, 1, LUA_INTRECT_METATABLENAME) );
    Vector2Exporter::createVector(L, Lua_Vector2(intRectPtr->left, intRectPtr->top));
    return 1;
}

int IntRectExporter::getSize(lua_State *L)
{
    Lua_IntRect* intRectPtr = static_cast<Lua_IntRect*>( LuaHelper::checkudata_WithError(L, 1, LUA_INTRECT_METATABLENAME) );
    Vector2Exporter::createVector(L, Lua_Vector2(intRectPtr->width, intRectPtr->height));
    return 1;
}

LuaExporter IntRectExporter::toLuaExporter()
{
    LuaExporter exporter(
        LUA_INTRECT_CLASSNAME,
        __new,
        {
            {"contains", IntRectExporter::contains},
            {"intersects", IntRectExporter::intersects},
            {"getPosition", IntRectExporter::getPosition},
            {"getSize", IntRectExporter::getSize},
        },
        {
            {"__gc", IntRectExporter::__destroy},
            {"__index", IntRectExporter::__index},
            {"__newindex", IntRectExporter::__newindex},
            {"__eq", IntRectExporter::__eq},
        }
    );

    return exporter;
}