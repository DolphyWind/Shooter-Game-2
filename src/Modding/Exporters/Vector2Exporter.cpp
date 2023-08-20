#include <sstream>
#include <cassert>

#include <SFEX/Numeric/Vector2.hpp>
#include <Modding/Exporters/Vector2Exporter.hpp>
#include <Modding/LuaExporter.hpp>
#include <Modding/LuaHelper.hpp>

#include <lua.hpp>

void Vector2Exporter::createVector(lua_State* L, const Lua_Vector2& vec)
{
    void* data = lua_newuserdata(L, sizeof(Lua_Vector2));
    new (data) Lua_Vector2(vec);
    luaL_getmetatable(L, LUA_VECTOR2_METATABLENAME);
    lua_setmetatable(L, -2);
}

int Vector2Exporter::__new(lua_State* L)
{
    int arg_count = lua_gettop(L);
    if(arg_count > 2) luaL_error(L, "Cannot create a Vector2 with that amount of arguments!", arg_count);

    lua_Number x, y;
    x = y = 0;

    if(arg_count == 1)
    {
        // Treat it as userdata
        Lua_Vector2* v = static_cast<Lua_Vector2*>( luaL_checkudata(L, 1, LUA_VECTOR2_METATABLENAME) );
        x = v->x;
        y = v->y;
    }
    else if(arg_count == 2)
    {
        x = luaL_checknumber(L, 1);
        y = luaL_checknumber(L, 2);
    }


    createVector(L, {x, y});

    return 1;
}

int Vector2Exporter::__destroy(lua_State* L)
{
    Lua_Vector2* vecPtr = static_cast<Lua_Vector2*>( luaL_checkudata(L, 1, LUA_VECTOR2_METATABLENAME) );
    vecPtr->~Lua_Vector2();
    return 0;
}

int Vector2Exporter::__index(lua_State* L)
{
    Lua_Vector2* vecPtr = static_cast<Lua_Vector2*>( luaL_checkudata(L, 1, LUA_VECTOR2_METATABLENAME) );
    std::string indexStr = luaL_checkstring(L, 2);

    lua_getglobal(L, LUA_VECTOR2_CLASSNAME);
    lua_pushstring(L, indexStr.c_str());
    lua_rawget(L, -2);
    return 1;
}

int Vector2Exporter::__newindex(lua_State* L)
{
    Lua_Vector2* vecPtr = static_cast<Lua_Vector2*>( luaL_checkudata(L, 1, LUA_VECTOR2_METATABLENAME) );
    std::string indexStr = luaL_checkstring(L, 2);

    if(indexStr == "x")
    {
        lua_Number new_x = luaL_checknumber(L, 3);
        vecPtr->x = new_x;
        return 0;
    }
    else if(indexStr == "y")
    {
        lua_Number new_y = luaL_checknumber(L, 3);
        vecPtr->y = new_y;
        return 0;
    }

    luaL_error(L, "Cannot set value for %s", indexStr.c_str());
    return 0;
}

int Vector2Exporter::__toString(lua_State* L)
{
    Lua_Vector2* vecPtr = static_cast<Lua_Vector2*>( luaL_checkudata(L, 1, LUA_VECTOR2_METATABLENAME) );
    std::stringstream ss;
    ss << (*vecPtr);
    lua_pushstring(L, ss.str().c_str());
    return 1;
}

int Vector2Exporter::__unm(lua_State* L)
{
    Lua_Vector2* vecPtr = static_cast<Lua_Vector2*>( luaL_checkudata(L, 1, LUA_VECTOR2_METATABLENAME) );
    createVector(L, -(*vecPtr));
    return 1;
}

int Vector2Exporter::__add(lua_State* L)
{
    Lua_Vector2* firstVec = static_cast<Lua_Vector2*>( luaL_checkudata(L, 1, LUA_VECTOR2_METATABLENAME) );
    Lua_Vector2* secondVec = static_cast<Lua_Vector2*>( luaL_checkudata(L, 2, LUA_VECTOR2_METATABLENAME) );

    createVector(L, (*firstVec) + (*secondVec));
    return 1;
}

int Vector2Exporter::__sub(lua_State* L)
{
    Lua_Vector2* firstVec = static_cast<Lua_Vector2*>( luaL_checkudata(L, 1, LUA_VECTOR2_METATABLENAME) );
    Lua_Vector2* secondVec = static_cast<Lua_Vector2*>( luaL_checkudata(L, 2, LUA_VECTOR2_METATABLENAME) );

    createVector(L, (*firstVec) - (*secondVec));
    return 1;
}

int Vector2Exporter::__mul(lua_State* L)
{
    Lua_Vector2* vecPtr;
    lua_Number scalar;

    if(lua_isuserdata(L, 1) && lua_isnumber(L, 2))
    {
        vecPtr = static_cast<Lua_Vector2*>( luaL_checkudata(L, 1, LUA_VECTOR2_METATABLENAME) );
        scalar = luaL_checknumber(L, 2);
    }
    else if(lua_isnumber(L, 1) && lua_isuserdata(L, 2))
    {
        scalar = luaL_checknumber(L, 1);
        vecPtr = static_cast<Lua_Vector2*>( luaL_checkudata(L, 2, LUA_VECTOR2_METATABLENAME) );
    }
    else
    {
        luaL_error(L, "Unsupported binary operation between types %s and %s", lua_typename(L, lua_type(L, 1)), lua_typename(L, lua_type(L, 1)));
        return 0;
    }

    createVector(L, (*vecPtr) * scalar);
    return 1;
}

int Vector2Exporter::__div(lua_State* L)
{
    if(!lua_isuserdata(L, 1) || !lua_isnumber(L, 2))
    {
        luaL_error(L, "Unsupported binary operation between types %s and %s", lua_typename(L, lua_type(L, 1)), lua_typename(L, lua_type(L, 1)));
        return 0;
    }

    Lua_Vector2* vecPtr = static_cast<Lua_Vector2*>( luaL_checkudata(L, 1, LUA_VECTOR2_METATABLENAME) );
    lua_Number divider = luaL_checknumber(L, 2);

    createVector(L, (*vecPtr) / divider);
    return 1;
}

int Vector2Exporter::__idiv(lua_State* L)
{
    if(!lua_isuserdata(L, 1) || !lua_isnumber(L, 2))
    {
        luaL_error(L, "Unsupported binary operation between types %s and %s", lua_typename(L, lua_type(L, 1)), lua_typename(L, lua_type(L, 1)));
        return 0;
    }
    Lua_Vector2* vecPtr = static_cast<Lua_Vector2*>( luaL_checkudata(L, 1, LUA_VECTOR2_METATABLENAME) );
    lua_Number divider = luaL_checknumber(L, 2);
    lua_Integer x_int, y_int;
    
    lua_numbertointeger(vecPtr->x / divider, &x_int);
    lua_numbertointeger(vecPtr->y / divider, &y_int);

    createVector(L, {
    static_cast<lua_Number>(x_int),
    static_cast<lua_Number>(y_int)
    } );
    return 1;
}

int Vector2Exporter::__eq(lua_State* L)
{
    if(lua_type(L, 1) != lua_type(L, 2))
    {
        lua_pushboolean(L, false);
        return 1;
    }

    Lua_Vector2* firstVec = static_cast<Lua_Vector2*>( luaL_checkudata(L, 1, LUA_VECTOR2_METATABLENAME) );
    Lua_Vector2* secondVec = static_cast<Lua_Vector2*>( luaL_checkudata(L, 2, LUA_VECTOR2_METATABLENAME) );

    lua_pushboolean(L, ((*firstVec) == (*secondVec)) );
    return 1;
}

/// Regular Functions
int Vector2Exporter::magnitude(lua_State* L)
{
    Lua_Vector2* vecPtr = static_cast<Lua_Vector2*>( luaL_checkudata(L, 1, LUA_VECTOR2_METATABLENAME) );
    lua_pushnumber(L, vecPtr->magnitude());

    return 1;
}

int Vector2Exporter::magnitude2(lua_State* L)
{
    Lua_Vector2* vecPtr = static_cast<Lua_Vector2*>( luaL_checkudata(L, 1, LUA_VECTOR2_METATABLENAME) );
    lua_pushnumber(L, vecPtr->magnitude2());

    return 1;
}

int Vector2Exporter::setmagnitude(lua_State* L)
{
    Lua_Vector2* vecPtr = static_cast<Lua_Vector2*>( luaL_checkudata(L, 1, LUA_VECTOR2_METATABLENAME) );
    vecPtr->setMagnitude( luaL_checknumber(L, 2) );

    return 0;
}

int Vector2Exporter::normalize(lua_State* L)
{
    Lua_Vector2* vecPtr = static_cast<Lua_Vector2*>( luaL_checkudata(L, 1, LUA_VECTOR2_METATABLENAME) );
    vecPtr->normalize();
    return 0;
}

int Vector2Exporter::normalized(lua_State* L)
{
    Lua_Vector2* vecPtr = static_cast<Lua_Vector2*>( luaL_checkudata(L, 1, LUA_VECTOR2_METATABLENAME) );
    createVector(L, vecPtr->normalized());

    return 1;
}

int Vector2Exporter::dot(lua_State* L)
{
    Lua_Vector2* firstVec = static_cast<Lua_Vector2*>( luaL_checkudata(L, 1, LUA_VECTOR2_METATABLENAME) );
    Lua_Vector2* secondVec = static_cast<Lua_Vector2*>( luaL_checkudata(L, 2, LUA_VECTOR2_METATABLENAME) );
    lua_pushnumber(L, firstVec->dot(*secondVec));

    return 1;
}

int Vector2Exporter::cross(lua_State* L)
{
    Lua_Vector2* firstVec = static_cast<Lua_Vector2*>( luaL_checkudata(L, 1, LUA_VECTOR2_METATABLENAME) );
    Lua_Vector2* secondVec = static_cast<Lua_Vector2*>( luaL_checkudata(L, 2, LUA_VECTOR2_METATABLENAME) );
    lua_pushnumber(L, firstVec->cross(*secondVec));
    
    return 1;
}

int Vector2Exporter::cwiseMul(lua_State* L)
{
    if(!lua_isuserdata(L, 1))
    {
        luaL_error(L, "The first parameter has be a userdata, not %s", lua_typename(L, lua_type(L, 1)) );
        return 0;
    }
    if(!lua_isuserdata(L, 2))
    {
        luaL_error(L, "The second parameter has be a userdata, not %s", lua_typename(L, lua_type(L, 2)) );
        return 0;
    }

    Lua_Vector2* firstVec = static_cast<Lua_Vector2*>( luaL_checkudata(L, 1, LUA_VECTOR2_METATABLENAME) );
    Lua_Vector2* secondVec = static_cast<Lua_Vector2*>( luaL_checkudata(L, 2, LUA_VECTOR2_METATABLENAME) );
    createVector(L, firstVec->cwiseMul(*secondVec));
    
    return 1;
}

int Vector2Exporter::cwiseDiv(lua_State* L)
{
    if(!lua_isuserdata(L, 1))
    {
        luaL_error(L, "The first parameter has be a userdata, not %s", lua_typename(L, lua_type(L, 1)) );
        return 0;
    }
    if(!lua_isuserdata(L, 2))
    {
        luaL_error(L, "The second parameter has be a userdata, not %s", lua_typename(L, lua_type(L, 2)) );
        return 0;
    }

    Lua_Vector2* firstVec = static_cast<Lua_Vector2*>( luaL_checkudata(L, 1, LUA_VECTOR2_METATABLENAME) );
    Lua_Vector2* secondVec = static_cast<Lua_Vector2*>( luaL_checkudata(L, 2, LUA_VECTOR2_METATABLENAME) );
    createVector(L, firstVec->cwiseDiv(*secondVec));
    
    return 1;
}

int Vector2Exporter::scale(lua_State* L)
{
    if(!lua_isuserdata(L, 1))
    {
        luaL_error(L, "The first parameter has be a userdata, not %s", lua_typename(L, lua_type(L, 1)) );
        return 0;
    }
    if(!lua_isnumber(L, 2))
    {
        luaL_error(L, "The second parameter has be a number, not %s", lua_typename(L, lua_type(L, 2)) );
        return 0;
    }

    Lua_Vector2* vecPtr = static_cast<Lua_Vector2*>( luaL_checkudata(L, 1, LUA_VECTOR2_METATABLENAME) );
    vecPtr->scale( luaL_checknumber(L, 2) );
    
    return 0;
}

int Vector2Exporter::scaled(lua_State* L)
{
    if(!lua_isuserdata(L, 1))
    {
        luaL_error(L, "The first parameter has be a userdata, not %s", lua_typename(L, lua_type(L, 1)) );
        return 0;
    }
    if(!lua_isnumber(L, 2))
    {
        luaL_error(L, "The second parameter has be a number, not %s", lua_typename(L, lua_type(L, 2)) );
        return 0;
    }

    Lua_Vector2* vecPtr = static_cast<Lua_Vector2*>( luaL_checkudata(L, 1, LUA_VECTOR2_METATABLENAME) );
    createVector(L, vecPtr->scaled( luaL_checknumber(L, 2) ));
    
    return 1;
}

int Vector2Exporter::rotate(lua_State* L)
{
    if(!lua_isuserdata(L, 1))
    {
        luaL_error(L, "The first parameter has be a userdata, not %s", lua_typename(L, lua_type(L, 1)) );
        return 0;
    }
    if(!lua_isnumber(L, 2))
    {
        luaL_error(L, "The second parameter has be a number, not %s", lua_typename(L, lua_type(L, 2)) );
        return 0;
    }

    Lua_Vector2 rotateAround = Lua_Vector2::zero;
    if(lua_gettop(L) == 3)
    {
        if(!lua_isuserdata(L, 1))
        {
            luaL_error(L, "The third parameter has be a userdata, not %s", lua_typename(L, lua_type(L, 3)) );
            return 0;
        }
        rotateAround = *static_cast<Lua_Vector2*>( luaL_checkudata(L, 3, LUA_VECTOR2_METATABLENAME) );
    }

    Lua_Vector2* vecPtr = static_cast<Lua_Vector2*>( luaL_checkudata(L, 1, LUA_VECTOR2_METATABLENAME) );
    vecPtr->rotate( luaL_checknumber(L, 2), rotateAround);
    
    return 0;
}

int Vector2Exporter::rotated(lua_State* L)
{
    if(!lua_isuserdata(L, 1))
    {
        luaL_error(L, "The first parameter has be a userdata, not %s", lua_typename(L, lua_type(L, 1)) );
        return 0;
    }
    if(!lua_isnumber(L, 2))
    {
        luaL_error(L, "The second parameter has be a number, not %s", lua_typename(L, lua_type(L, 2)) );
        return 0;
    }

    Lua_Vector2 rotateAround = Lua_Vector2::zero;
    if(lua_gettop(L) == 3)
    {
        if(!lua_isuserdata(L, 1))
        {
            luaL_error(L, "The third parameter has be a userdata, not %s", lua_typename(L, lua_type(L, 3)) );
            return 0;
        }
        rotateAround = *static_cast<Lua_Vector2*>( luaL_checkudata(L, 3, LUA_VECTOR2_METATABLENAME) );
    }

    Lua_Vector2* vecPtr = static_cast<Lua_Vector2*>( luaL_checkudata(L, 1, LUA_VECTOR2_METATABLENAME) );
    createVector(L, vecPtr->rotated( luaL_checknumber(L, 2), rotateAround));

    return 1;
}

int Vector2Exporter::angle(lua_State* L)
{
    if(!lua_isuserdata(L, 1))
    {
        luaL_error(L, "The first parameter has be a userdata, not %s", lua_typename(L, lua_type(L, 1)) );
        return 0;
    }

    Lua_Vector2 otherVector = Lua_Vector2::right;
    if(lua_gettop(L) == 2)
    {
        if(!lua_isuserdata(L, 2))
        {
            luaL_error(L, "The second parameter has be a userdata, not %s", lua_typename(L, lua_type(L, 2)) );
            return 0;
        }
        otherVector = *static_cast<Lua_Vector2*>( luaL_checkudata(L, 2, LUA_VECTOR2_METATABLENAME) );
    }

    Lua_Vector2* vecPtr = static_cast<Lua_Vector2*>( luaL_checkudata(L, 1, LUA_VECTOR2_METATABLENAME) );
    lua_pushnumber(L, vecPtr->angle(otherVector) );

    return 1;
}

int Vector2Exporter::projectOnto(lua_State* L)
{
    if(!lua_isuserdata(L, 1))
    {
        luaL_error(L, "The first parameter has be a userdata, not %s", lua_typename(L, lua_type(L, 1)) );
        return 0;
    }
    if(!lua_isuserdata(L, 2))
    {
        luaL_error(L, "The second parameter has be a userdata, not %s", lua_typename(L, lua_type(L, 2)) );
        return 0;
    }

    Lua_Vector2* firstVec = static_cast<Lua_Vector2*>( luaL_checkudata(L, 1, LUA_VECTOR2_METATABLENAME) );
    Lua_Vector2* secondVec = static_cast<Lua_Vector2*>( luaL_checkudata(L, 2, LUA_VECTOR2_METATABLENAME) );
    firstVec->projectOnto(*secondVec);

    return 0;
}

int Vector2Exporter::projectedOnto(lua_State* L)
{
    if(!lua_isuserdata(L, 1))
    {
        luaL_error(L, "The first parameter has be a userdata, not %s", lua_typename(L, lua_type(L, 1)) );
        return 0;
    }
    if(!lua_isuserdata(L, 2))
    {
        luaL_error(L, "The second parameter has be a userdata, not %s", lua_typename(L, lua_type(L, 2)) );
        return 0;
    }

    Lua_Vector2* firstVec = static_cast<Lua_Vector2*>( luaL_checkudata(L, 1, LUA_VECTOR2_METATABLENAME) );
    Lua_Vector2* secondVec = static_cast<Lua_Vector2*>( luaL_checkudata(L, 2, LUA_VECTOR2_METATABLENAME) );
    createVector(L, firstVec->projectedOnto(*secondVec));

    return 1;
}

LuaExporter Vector2Exporter::toLuaExporter()
{
    LuaExporter exporter(
        LUA_VECTOR2_CLASSNAME, 
        Vector2Exporter::__new,
        {
            {"magnitude", Vector2Exporter::magnitude},
            {"magnitude2", Vector2Exporter::magnitude2},
            {"setMagnitude", Vector2Exporter::setmagnitude},
            {"normalize", Vector2Exporter::normalize},
            {"normalized", Vector2Exporter::normalized},
            {"dot", Vector2Exporter::dot},
            {"cross", Vector2Exporter::cross},
            {"cwiseMul", Vector2Exporter::cwiseMul},
            {"cwiseDiv", Vector2Exporter::cwiseDiv},
            {"scale", Vector2Exporter::scale},
            {"scaled", Vector2Exporter::scaled},
            {"rotate", Vector2Exporter::rotate},
            {"rotated", Vector2Exporter::rotated},
            {"angle", Vector2Exporter::angle},
            {"projectOnto", Vector2Exporter::projectOnto},
            {"projectedOnto", Vector2Exporter::projectedOnto},
        },
        {
            {"__gc", Vector2Exporter::__destroy},
            {"__index", Vector2Exporter::__index},
            {"__newindex", Vector2Exporter::__newindex},
            {"__tostring", Vector2Exporter::__toString},
            {"__unm", Vector2Exporter::__unm},
            {"__add", Vector2Exporter::__add},
            {"__sub", Vector2Exporter::__sub},
            {"__mul", Vector2Exporter::__mul},
            {"__div", Vector2Exporter::__div},
            {"__idiv", Vector2Exporter::__idiv},
            {"__eq", Vector2Exporter::__eq},
        }
    );

    return exporter;
}
