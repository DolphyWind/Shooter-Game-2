#include <Modding/Exporters/ColorExporter.hpp>
#include <Modding/LuaExporter.hpp>
#include <cassert>
#include <sstream>
#include <iostream>
#include <string>

void ColorExporter::createColor(lua_State* L, const sfex::Color& color)
{
    void* data = lua_newuserdata(L, sizeof(Lua_Color));
    new (data) Lua_Color(color);
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
            Lua_Color* colorPtr = static_cast<Lua_Color*>( luaL_checkudata(L, 1, LUA_COLOR_METATABLENAME) );
            createColor(L, *colorPtr);
            return 1;
        }
        else if(lua_isinteger(L, 1))
        {
            lua_Integer hex = luaL_checkinteger(L, 1);
            createColor(L, Lua_Color(hex));
            return 1;
        }
        luaL_error(L, "Given argument should have type userdata, not %d", lua_typename(L, lua_type(L, 1)));
        return 0;
    }
    else if(arg_count == 3 || arg_count == 4)
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

        lua_Number a_num;
        if(arg_count == 4)
        {
            a_num = luaL_checknumber(L, 4);
            a_num = std::clamp(a_num, lua_Number(0), lua_Number(255));
            a = static_cast<sf::Uint8>(a_num);
        }

        createColor(L, Lua_Color(r, g, b, a));
        return 1;
    }
    
    createColor(L, Lua_Color());
    return 1;
}

int ColorExporter::__destroy(lua_State* L)
{
    Lua_Color* colorPtr = static_cast<Lua_Color*>( luaL_checkudata(L, 1, LUA_COLOR_METATABLENAME) );
    colorPtr->~Lua_Color();
    return 0;
}

int ColorExporter::__index(lua_State* L)
{
    Lua_Color* colorPtr = static_cast<Lua_Color*>( luaL_checkudata(L, 1, LUA_COLOR_METATABLENAME) );
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
    else if(indexStr == "red")
    {
        createColor(L, Lua_Color::Red);
        return 1;
    }
    else if(indexStr == "green")
    {
        createColor(L, Lua_Color::Green);
        return 1;
    }
    else if(indexStr == "blue")
    {
        createColor(L, Lua_Color::Blue);
        return 1;
    }
    else if(indexStr == "yellow")
    {
        createColor(L, Lua_Color::Yellow);
        return 1;
    }
    else if(indexStr == "magenta")
    {
        createColor(L, Lua_Color::Magenta);
        return 1;
    }
    else if(indexStr == "cyan")
    {
        createColor(L, Lua_Color::Cyan);
        return 1;
    }
    else if(indexStr == "gray")
    {
        createColor(L, Lua_Color::Gray);
        return 1;
    }
    else if(indexStr == "white")
    {
        createColor(L, Lua_Color::White);
        return 1;
    }
    else if(indexStr == "black")
    {
        createColor(L, Lua_Color::Black);
        return 1;
    }
    else if(indexStr == "transparent")
    {
        createColor(L, Lua_Color::Transparent);
        return 1;
    }

    lua_getglobal(L, LUA_COLOR_CLASSNAME);
    lua_pushstring(L, indexStr.c_str());
    lua_rawget(L, -2);
    return 1;
}

int ColorExporter::__newindex(lua_State *L)
{
    Lua_Color* colorPtr = static_cast<Lua_Color*>( luaL_checkudata(L, 1, LUA_COLOR_METATABLENAME) );
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
    Lua_Color* colorPtr = static_cast<Lua_Color*>( luaL_checkudata(L, 1, LUA_COLOR_METATABLENAME) );
    std::stringstream ss;
    ss << (*colorPtr);
    lua_pushstring(L, ss.str().c_str());
    return 1;
}

int ColorExporter::__add(lua_State *L)
{
    if(!lua_isuserdata(L, 1) || !lua_isuserdata(L, 2))
    {
        luaL_error(L, "Unsupported binary operation between types %s and %s", lua_typename(L, lua_type(L, 1)), lua_typename(L, lua_type(L, 1)));
        return 0;
    }

    Lua_Color* firstItem = static_cast<Lua_Color*>( luaL_checkudata(L, 1, LUA_COLOR_METATABLENAME) );
    Lua_Color* secondItem = static_cast<Lua_Color*>( luaL_checkudata(L, 2, LUA_COLOR_METATABLENAME) );
    
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

    Lua_Color* firstItem = static_cast<Lua_Color*>( luaL_checkudata(L, 1, LUA_COLOR_METATABLENAME) );
    Lua_Color* secondItem = static_cast<Lua_Color*>( luaL_checkudata(L, 2, LUA_COLOR_METATABLENAME) );
    
    createColor(L, (*firstItem) - (*secondItem));
    return 1;
}

int ColorExporter::__mul(lua_State* L)
{
    Lua_Color* colorPtr;
    lua_Number scalar;

    if(lua_isuserdata(L, 1) && lua_isnumber(L, 2))
    {
        colorPtr = static_cast<Lua_Color*>( luaL_checkudata(L, 1, LUA_COLOR_METATABLENAME) );
        scalar = luaL_checknumber(L, 2);
    }
    else if(lua_isnumber(L, 1) && lua_isuserdata(L, 2))
    {
        scalar = luaL_checknumber(L, 1);
        colorPtr = static_cast<Lua_Color*>( luaL_checkudata(L, 2, LUA_COLOR_METATABLENAME) );
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

    Lua_Color* colorPtr;
    lua_Number divider;

    colorPtr = static_cast<Lua_Color*>( luaL_checkudata(L, 1, LUA_COLOR_METATABLENAME) );
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

    Lua_Color* firstItem = static_cast<Lua_Color*>( luaL_checkudata(L, 1, LUA_COLOR_METATABLENAME) );
    Lua_Color* secondItem = static_cast<Lua_Color*>( luaL_checkudata(L, 2, LUA_COLOR_METATABLENAME) );

    lua_pushboolean(L, ((*firstItem) == (*secondItem)) );
    return 1;
}

int ColorExporter::toHex(lua_State *L)
{
    if(!lua_isuserdata(L, 1))
    {
        luaL_error(L, "First argument should be a userdata not %s", lua_typename(L, lua_type(L, 1)) );
        return 0;
    }

    Lua_Color* colorPtr = static_cast<Lua_Color*>( luaL_checkudata(L, 1, LUA_COLOR_METATABLENAME) );
    lua_Integer result = colorPtr->toHex();
    lua_pushinteger(L, result);
    return 1;
}

int ColorExporter::toGrayscale(lua_State *L)
{
    if(!lua_isuserdata(L, 1))
    {
        luaL_error(L, "First argument should be a userdata not %s", lua_typename(L, lua_type(L, 1)) );
        return 0;
    }

    Lua_Color* colorPtr = static_cast<Lua_Color*>( luaL_checkudata(L, 1, LUA_COLOR_METATABLENAME) );
    createColor(L, colorPtr->toGrayscale());
    return 1;
}

int ColorExporter::mixColors(lua_State *L)
{
    if(!lua_isuserdata(L, 1) || !lua_isuserdata(L, 2))
    {
        luaL_error(L, "Unsupported binary operation between types %s and %s", lua_typename(L, lua_type(L, 1)), lua_typename(L, lua_type(L, 1)));
        return 0;
    }

    Lua_Color* firstPtr = static_cast<Lua_Color*>( luaL_checkudata(L, 1, LUA_COLOR_METATABLENAME) );
    Lua_Color* secondPtr = static_cast<Lua_Color*>( luaL_checkudata(L, 2, LUA_COLOR_METATABLENAME) );

    createColor(L, sfex::Color::mixColors(*firstPtr, *secondPtr));
    return 1;
}

LuaExporter ColorExporter::toLuaExporter()
{
    LuaExporter exporter(
        LUA_COLOR_CLASSNAME, 
        ColorExporter::__new,
        {
            { "toHex", ColorExporter::toHex},
            { "toGrayscale", ColorExporter::toGrayscale},
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

    // For some reaseon in this function all static colors are set to (0, 0, 0, 0).
    // It only happens in this function and nowhere else which makes it really suspicious
    // I am guessing there is an undefined behaviour somewhere in the code
    std::vector<Lua_Color*> public_lua_colors = {
        new Lua_Color(sf::Color::Red),
        new Lua_Color(sf::Color::Green),
        new Lua_Color(sf::Color::Blue),
        new Lua_Color(sf::Color::Yellow),
        new Lua_Color(sf::Color::Magenta),
        new Lua_Color(sf::Color::Cyan),
        new Lua_Color(sf::Color(128, 128, 128, 255)),
        new Lua_Color(sf::Color::White),
        new Lua_Color(sf::Color::Black),
        new Lua_Color(sf::Color::Transparent),
    };


    exporter.addUserdata("red", public_lua_colors[0], sizeof(Lua_Color), LUA_COLOR_CLASSNAME"_metatable");
    exporter.addUserdata("green", public_lua_colors[1], sizeof(Lua_Color), LUA_COLOR_CLASSNAME"_metatable");
    exporter.addUserdata("blue", public_lua_colors[2], sizeof(Lua_Color), LUA_COLOR_CLASSNAME"_metatable");
    exporter.addUserdata("yellow", public_lua_colors[3], sizeof(Lua_Color), LUA_COLOR_CLASSNAME"_metatable");
    exporter.addUserdata("magenta", public_lua_colors[4], sizeof(Lua_Color), LUA_COLOR_CLASSNAME"_metatable");
    exporter.addUserdata("cyan", public_lua_colors[5], sizeof(Lua_Color), LUA_COLOR_CLASSNAME"_metatable");
    exporter.addUserdata("gray", public_lua_colors[6], sizeof(Lua_Color), LUA_COLOR_CLASSNAME"_metatable");
    exporter.addUserdata("white", public_lua_colors[7], sizeof(Lua_Color), LUA_COLOR_CLASSNAME"_metatable");
    exporter.addUserdata("black", public_lua_colors[8], sizeof(Lua_Color), LUA_COLOR_CLASSNAME"_metatable");
    exporter.addUserdata("transparent", public_lua_colors[9], sizeof(Lua_Color), LUA_COLOR_CLASSNAME"_metatable");

    // It is ok to delete them because addUserdata copies the data it got
    for(auto& v : public_lua_colors)
    {
        delete v;
    }

    return exporter;
}
