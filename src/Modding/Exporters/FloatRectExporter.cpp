#include <Modding/LuaExporter.hpp>
#include <Modding/Exporters/FloatRectExporter.hpp>
#include <Modding/Exporters/Vector2Exporter.hpp>

void FloatRectExporter::createFloatRect(lua_State *L, const Lua_FloatRect& floatRect)
{
    void* data = lua_newuserdata(L, sizeof(Lua_FloatRect));
    Lua_FloatRect* floatRectPtr = new (data) Lua_FloatRect(floatRect);
    luaL_getmetatable(L, LUA_FLOATRECT_CLASSNAME"_metatable");
    lua_setmetatable(L, -2);
}

int FloatRectExporter::__new(lua_State *L)
{
    int arg_count = lua_gettop(L);

    if(arg_count == 0)
    {
        createFloatRect(L, Lua_FloatRect());
        return 1;
    }
    else if(arg_count == 1)
    {
        Lua_FloatRect* floatRectPtr = static_cast<Lua_FloatRect*>( lua_touserdata(L, 1) );
        createFloatRect(L, Lua_FloatRect(*floatRectPtr));
        return 1;
    }
    else if(arg_count == 2)
    {
        Lua_Vector2* positionVec = static_cast<Lua_Vector2*>( lua_touserdata(L, 1) );
        Lua_Vector2* sizeVec = static_cast<Lua_Vector2*>( lua_touserdata(L, 2) );
        createFloatRect(L, Lua_FloatRect(*positionVec, *sizeVec));
        return 1;
    }
    else if(arg_count == 4)
    {
        lua_Number rectLeft = luaL_checknumber(L, 1);
        lua_Number rectTop = luaL_checknumber(L, 2);
        lua_Number rectWidth = luaL_checknumber(L, 3);
        lua_Number rectHeight = luaL_checknumber(L, 4);

        createFloatRect(L, Lua_FloatRect(rectLeft, rectTop, rectWidth, rectHeight));
        return 1;
    }

    luaL_error(L, "Cannot create new FloatRect with that amount of arguments!");
    return 0;
}

int FloatRectExporter::__destroy(lua_State *L)
{
    Lua_FloatRect* floatRectPtr = static_cast<Lua_FloatRect*>( lua_touserdata(L, 1) );
    floatRectPtr->~Lua_FloatRect();
    return 0;
}

int FloatRectExporter::__index(lua_State *L)
{
    Lua_FloatRect* floatRectPtr = static_cast<Lua_FloatRect*>( lua_touserdata(L, 1) );
    std::string indexStr = lua_tostring(L, 2);

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
    Lua_FloatRect* floatRectPtr = static_cast<Lua_FloatRect*>( lua_touserdata(L, 1) );
    std::string indexStr = lua_tostring(L, 2);

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

    Lua_FloatRect* firstFloatRect = static_cast<Lua_FloatRect*>( lua_touserdata(L, 1) );
    Lua_FloatRect* secondFloatRect = static_cast<Lua_FloatRect*>( lua_touserdata(L, 2) );
    lua_pushboolean(L, (*firstFloatRect) == (*secondFloatRect));
    return 1;
}

int FloatRectExporter::contains(lua_State *L)
{
    int arg_count = lua_gettop(L);
    Lua_FloatRect* floatRectPtr = static_cast<Lua_FloatRect*>( lua_touserdata(L, 1) );

    if(arg_count == 2)
    {
        Lua_Vector2* vecPtr = static_cast<Lua_Vector2*>( lua_touserdata(L, 2) );
        lua_pushboolean(L, floatRectPtr->contains(*vecPtr));
        return 1;
    }
    else if(arg_count == 3)
    {
        lua_Number x = luaL_checknumber(L, 2);
        lua_Number y = luaL_checknumber(L, 3);
        lua_pushboolean(L, floatRectPtr->contains(x, y));
        return 1;
    }

    luaL_error(L, "You can't call %s with this amount of arguments", __func__);
    return 0;
}

int FloatRectExporter::intersects(lua_State *L)
{
    int arg_count = lua_gettop(L);
    Lua_FloatRect* floatRectPtr = static_cast<Lua_FloatRect*>( lua_touserdata(L, 1) );
    Lua_FloatRect* rectanglePtr = static_cast<Lua_FloatRect*>( lua_touserdata(L, 2) );

    if(arg_count == 2)
    {
        lua_pushboolean(L, floatRectPtr->intersects(*rectanglePtr));
        return 1;
    }
    else if(arg_count == 3)
    {
        Lua_FloatRect* intersectionPtr = static_cast<Lua_FloatRect*>( lua_touserdata(L, 3) );
        lua_pushboolean(L, floatRectPtr->intersects(*rectanglePtr, *intersectionPtr));
        return 1;
    }

    luaL_error(L, "You can't call %s with this amount of arguments", __func__);
    return 0;
}

int FloatRectExporter::getPosition(lua_State *L)
{
    Lua_FloatRect* floatRectPtr = static_cast<Lua_FloatRect*>( lua_touserdata(L, 1) );
    Vector2Exporter::createVector(L, Lua_Vector2(floatRectPtr->left, floatRectPtr->top));
    return 1;
}

int FloatRectExporter::getSize(lua_State *L)
{
    Lua_FloatRect* floatRectPtr = static_cast<Lua_FloatRect*>( lua_touserdata(L, 1) );
    Vector2Exporter::createVector(L, Lua_Vector2(floatRectPtr->width, floatRectPtr->height));
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