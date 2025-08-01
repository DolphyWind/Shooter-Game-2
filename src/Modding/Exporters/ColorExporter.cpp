#include <Modding/Exporters/ColorExporter.hpp>
#include <Modding/LuaExporter.hpp>
#include <cassert>
#include <sstream>
#include <iostream>
#include <string>
#include <Modding/LuaHelper.hpp>

void ColorExporter::createColor(lua_State* L, const sfex::Color& color)
{
    void* data = lua_newuserdata(L, sizeof(Exported_Color));
    new (data) Exported_Color(color);
    luaL_getmetatable(L, LUA_COLOR_METATABLENAME);
    lua_setmetatable(L, -2);
}

int ColorExporter::__new(lua_State *L)
{
    int arg_count = lua_gettop(L);
    if(arg_count == 1)
    {
        if(lua_isuserdata(L, 1))
        {
            Exported_Color* colorPtr = static_cast<Exported_Color*>( LuaHelper::checkudata_WithError(L, 1, LUA_COLOR_METATABLENAME) );
            createColor(L, *colorPtr);
            return 1;
        }
        else if(lua_isinteger(L, 1))
        {
            lua_Integer hex = luaL_checkinteger(L, 1);
            createColor(L, Exported_Color(hex));
            return 1;
        }
        luaL_error(L, "Given argument should have type userdata, not %d", lua_typename(L, lua_type(L, 1)));
        return 0;
    }
    else if(arg_count >= 3)
    {
        lua_Number r_num = luaL_checknumber(L, 1);
        lua_Number g_num = luaL_checknumber(L, 2);
        lua_Number b_num = luaL_checknumber(L, 3);
    
        r_num = std::clamp(r_num, lua_Number(0.0), lua_Number(255.0));
        g_num = std::clamp(g_num, lua_Number(0.0), lua_Number(255.0));
        b_num = std::clamp(b_num, lua_Number(0.0), lua_Number(255.0));

        sf::Uint8 r = static_cast<sf::Uint8>(r_num);
        sf::Uint8 g = static_cast<sf::Uint8>(g_num);
        sf::Uint8 b = static_cast<sf::Uint8>(b_num);
        sf::Uint8 a = 255;

        if(arg_count >= 4)
        {
            lua_Number a_num;
            a_num = luaL_checknumber(L, 4);
            a_num = std::clamp(a_num, lua_Number(0), lua_Number(255));
            a = static_cast<sf::Uint8>(a_num);
        }

        createColor(L, Exported_Color(r, g, b, a));
        return 1;
    }
    
    createColor(L, Exported_Color());
    return 1;
}

int ColorExporter::__destroy(lua_State* L)
{
    Exported_Color* colorPtr = static_cast<Exported_Color*>( LuaHelper::checkudata_WithError(L, 1, LUA_COLOR_METATABLENAME) );
    colorPtr->~Exported_Color();
    return 0;
}

int ColorExporter::__index(lua_State* L)
{
    Exported_Color* colorPtr = static_cast<Exported_Color*>( LuaHelper::checkudata_WithError(L, 1, LUA_COLOR_METATABLENAME) );
    std::string indexStr = luaL_checkstring(L, 2);

    if(indexStr == "r")
    {
        lua_pushnumber(L, colorPtr->r);
        return 1;
    }
    else if(indexStr == "g")
    {
        lua_pushnumber(L, colorPtr->g);
        return 1;
    }
    else if(indexStr == "b")
    {
        lua_pushnumber(L, colorPtr->b);
        return 1;
    }
    else if(indexStr == "a")
    {
        lua_pushnumber(L, colorPtr->a);
        return 1;
    }

    lua_getglobal(L, LUA_COLOR_CLASSNAME);
    lua_pushstring(L, indexStr.c_str());
    lua_rawget(L, -2);
    return 1;
}

int ColorExporter::__newindex(lua_State *L)
{
    Exported_Color* colorPtr = static_cast<Exported_Color*>( LuaHelper::checkudata_WithError(L, 1, LUA_COLOR_METATABLENAME) );
    std::string indexStr = luaL_checkstring(L, 2);

    if(indexStr == "r")
    {
        lua_Number num = luaL_checknumber(L, 3);
        num = std::clamp(num, lua_Number(0), lua_Number(255));
        colorPtr->r = static_cast<sf::Uint8>(num);
        return 0;
    }
    else if(indexStr == "g")
    {
        lua_Number num = luaL_checknumber(L, 3);
        num = std::clamp(num, lua_Number(0), lua_Number(255));
        colorPtr->g = static_cast<sf::Uint8>(num);
        return 0;
    }
    else if(indexStr == "b")
    {
        lua_Number num = luaL_checknumber(L, 3);
        num = std::clamp(num, lua_Number(0), lua_Number(255));
        colorPtr->b = static_cast<sf::Uint8>(num);
        return 0;
    }
    else if(indexStr == "a")
    {
        lua_Number num = luaL_checknumber(L, 3);
        num = std::clamp(num, lua_Number(0), lua_Number(255));
        colorPtr->a = static_cast<sf::Uint8>(num);
        return 0;
    }

    luaL_error(L, "Cannot set value for %s", indexStr.c_str());
    return 0;
}

int ColorExporter::__toString(lua_State *L)
{
    Exported_Color* colorPtr = static_cast<Exported_Color*>( LuaHelper::checkudata_WithError(L, 1, LUA_COLOR_METATABLENAME) );
    std::stringstream ss;
    ss << (*colorPtr);
    lua_pushstring(L, ss.str().c_str());
    return 1;
}

int ColorExporter::__add(lua_State *L)
{
    Exported_Color* firstItem = static_cast<Exported_Color*>( LuaHelper::checkudata_WithError(L, 1, LUA_COLOR_METATABLENAME) );
    Exported_Color* secondItem = static_cast<Exported_Color*>( LuaHelper::checkudata_WithError(L, 2, LUA_COLOR_METATABLENAME) );
    
    createColor(L, (*firstItem) + (*secondItem));
    return 1;
}


int ColorExporter::__sub(lua_State *L)
{
    if(!lua_isuserdata(L, 1) || !lua_isuserdata(L, 2))
    {
        luaL_error(L, "Unsupported binary operation between types %s and %s", lua_typename(L, lua_type(L, 1)), lua_typename(L, lua_type(L, 1)));
        return 0;
    }

    Exported_Color* firstItem = static_cast<Exported_Color*>( LuaHelper::checkudata_WithError(L, 1, LUA_COLOR_METATABLENAME) );
    Exported_Color* secondItem = static_cast<Exported_Color*>( LuaHelper::checkudata_WithError(L, 2, LUA_COLOR_METATABLENAME) );
    
    createColor(L, (*firstItem) - (*secondItem));
    return 1;
}

int ColorExporter::__mul(lua_State* L)
{
    Exported_Color* colorPtr;
    lua_Number scalar;

    if(lua_isuserdata(L, 1) && lua_isnumber(L, 2))
    {
        colorPtr = static_cast<Exported_Color*>( LuaHelper::checkudata_WithError(L, 1, LUA_COLOR_METATABLENAME) );
        scalar = luaL_checknumber(L, 2);
    }
    else if(lua_isnumber(L, 1) && lua_isuserdata(L, 2))
    {
        scalar = luaL_checknumber(L, 1);
        colorPtr = static_cast<Exported_Color*>( LuaHelper::checkudata_WithError(L, 2, LUA_COLOR_METATABLENAME) );
    }
    else
    {
        luaL_error(L, "Unsupported binary operation between types %s and %s", lua_typename(L, lua_type(L, 1)), lua_typename(L, lua_type(L, 1)));
        return 0;
    }

    createColor(L, (*colorPtr) * float(scalar) );
    return 1;
}

int ColorExporter::__div(lua_State* L)
{
    if(!lua_isuserdata(L, 1) || !lua_isnumber(L, 2))
    {
        luaL_error(L, "Unsupported binary operation between types %s and %s", lua_typename(L, lua_type(L, 1)), lua_typename(L, lua_type(L, 1)));
        return 0;
    }

    Exported_Color* colorPtr;
    lua_Number divider;

    colorPtr = static_cast<Exported_Color*>( LuaHelper::checkudata_WithError(L, 1, LUA_COLOR_METATABLENAME) );
    divider = luaL_checknumber(L, 2);

    createColor(L, (*colorPtr) / float(divider));
    return 1;
}

int ColorExporter::__eq(lua_State* L)
{
    if(lua_type(L, 1) != lua_type(L, 2))
    {
        lua_pushboolean(L, false);
        return 1;
    }

    Exported_Color* firstItem = static_cast<Exported_Color*>( LuaHelper::checkudata_WithError(L, 1, LUA_COLOR_METATABLENAME) );
    Exported_Color* secondItem = static_cast<Exported_Color*>( LuaHelper::checkudata_WithError(L, 2, LUA_COLOR_METATABLENAME) );

    lua_pushboolean(L, ((*firstItem) == (*secondItem)) );
    return 1;
}

int ColorExporter::toHex(lua_State *L)
{
    Exported_Color* colorPtr = static_cast<Exported_Color*>( LuaHelper::checkudata_WithError(L, 1, LUA_COLOR_METATABLENAME) );
    lua_Integer result = colorPtr->toHex();
    lua_pushinteger(L, result);
    return 1;
}

int ColorExporter::toGrayscale(lua_State *L)
{
    Exported_Color* colorPtr = static_cast<Exported_Color*>( LuaHelper::checkudata_WithError(L, 1, LUA_COLOR_METATABLENAME) );
    createColor(L, colorPtr->toGrayscale());
    return 1;
}

int ColorExporter::mixColors(lua_State *L)
{
    Exported_Color* firstPtr = static_cast<Exported_Color*>( LuaHelper::checkudata_WithError(L, 1, LUA_COLOR_METATABLENAME) );
    Exported_Color* secondPtr = static_cast<Exported_Color*>( LuaHelper::checkudata_WithError(L, 2, LUA_COLOR_METATABLENAME) );

    createColor(L, sfex::Color::mixColors(*firstPtr, *secondPtr));
    return 1;
}

LuaExporter ColorExporter::toLuaExporter()
{
    LuaExporter exporter(
        LUA_COLOR_CLASSNAME, 
        ColorExporter::__new,
        {
            {"toHex", ColorExporter::toHex},
            {"toGrayscale", ColorExporter::toGrayscale},
            {"mixColors", ColorExporter::mixColors},
        },
        {
            {"__gc", ColorExporter::__destroy},
            {"__index", ColorExporter::__index},
            {"__newindex", ColorExporter::__newindex},
            {"__tostring", ColorExporter::__toString},
            {"__add", ColorExporter::__add},
            {"__sub", ColorExporter::__sub},
            {"__mul", ColorExporter::__mul},
            {"__div", ColorExporter::__div},
            {"__eq", ColorExporter::__eq},
        }
    );

    return exporter;
}
