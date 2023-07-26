#pragma once
#include <SFEX/Numeric/Vector2.hpp>
#include <Modding/LuaExporter.hpp>
#include <lua.hpp>
#include <cassert>
#include <sstream>
#include <Modding/ShooterGameExporter.hpp>

typedef sfex::Vector2<lua_Number> Lua_Vector2;
struct Vector2Exporter
{
    static void Vector2_createVector(lua_State* L, int idx, const Lua_Vector2& vec)
    {
        lua_remove(L, idx);
        void* data = lua_newuserdata(L, sizeof(Lua_Vector2));
        Lua_Vector2* vecPtr = new (data) Lua_Vector2(vec);
        luaL_getmetatable(L, "Vector2_metatable");
        assert(lua_istable(L, -1));
        lua_setmetatable(L, -2);
        lua_insert(L, idx);
    }

    static int Vector2_new(lua_State* L)
    {
        int arg_count = lua_gettop(L);
        if(arg_count > 2) luaL_error(L, "Cannot create a Vector2 with that amount of arguments!", arg_count);

        lua_Number x, y;
        x = y = 0;

        if(arg_count == 1)
        {
            // Treat it as userdata
            Lua_Vector2* v = static_cast<Lua_Vector2*>( lua_touserdata(L, 1) );
            x = v->x;
            y = v->y;
        }
        else if(arg_count == 2)
        {
            x = luaL_checknumber(L, 1);
            y = luaL_checknumber(L, 2);
        }

        Vector2_createVector(L, -1, {x, y});

        return 1;
    }

    static int Vector2_destroy(lua_State* L)
    {
        Lua_Vector2* vecPtr = static_cast<Lua_Vector2*>( lua_touserdata(L, 1) );
        vecPtr->~Lua_Vector2();
        return 0;
    }

    static int Vector2_index(lua_State* L)
    {
        Lua_Vector2* vecPtr = static_cast<Lua_Vector2*>( lua_touserdata(L, 1) );
        std::string indexStr = lua_tostring(L, 2);

        if(indexStr == "x")
        {
            lua_pushnumber(L, vecPtr->x);
            return 1;
        }
        else if(indexStr == "y")
        {
            lua_pushnumber(L, vecPtr->y);
            return 1;
        }
        else if(indexStr == "left")
        {
            Vector2_createVector(L, -1, Lua_Vector2::left);
            return 1;
        }
        else if(indexStr == "right")
        {
            Vector2_createVector(L, -1, Lua_Vector2::right);
            return 1;
        }
        else if(indexStr == "up")
        {
            Vector2_createVector(L, -1, Lua_Vector2::up);
            return 1;
        }
        else if(indexStr == "down")
        {
            Vector2_createVector(L, -1, Lua_Vector2::down);
            return 1;
        }

        luaL_error(L, "Cannot retrieve %s", indexStr.c_str());
        return 0;
    }
    
    static int Vector2_newindex(lua_State* L)
    {
        Lua_Vector2* vecPtr = static_cast<Lua_Vector2*>( lua_touserdata(L, 1) );
        std::string indexStr = lua_tostring(L, 2);

        if(indexStr == "x")
        {
            lua_Number new_x = luaL_checknumber(L, 3);
            vecPtr->x = new_x;
            return 1;
        }
        else if(indexStr == "y")
        {
            lua_Number new_y = luaL_checknumber(L, 3);
            vecPtr->y = new_y;
            return 1;
        }

        luaL_error(L, "Cannot set value for %s", indexStr.c_str());
        return 0;
    }

    static int Vector2_toString(lua_State* L)
    {
        Lua_Vector2* vecPtr = static_cast<Lua_Vector2*>( lua_touserdata(L, 1) );
        std::stringstream ss;
        ss << (*vecPtr);
        lua_pushstring(L, ss.str().c_str());
        return 1;
    }

    static int Vector2_unm(lua_State* L)
    {
        Lua_Vector2* vecPtr = static_cast<Lua_Vector2*>( lua_touserdata(L, 1) );
        Vector2_createVector(L, -1, -(*vecPtr));
        return 1;
    }
    
    static int Vector2_add(lua_State* L)
    {
        if(!lua_isuserdata(L, 1) || !lua_isuserdata(L, 2))
        {
            luaL_error(L, "Unsupported binary operation between types %s and %s", lua_typename(L, lua_type(L, 1)), lua_typename(L, lua_type(L, 1)));
            return 0;
        }

        Lua_Vector2* firstVec = static_cast<Lua_Vector2*>( lua_touserdata(L, 1) );
        Lua_Vector2* secondVec = static_cast<Lua_Vector2*>( lua_touserdata(L, 2) );

        Vector2_createVector(L, -1, (*firstVec) + (*secondVec));
        return 1;
    }

    static int Vector2_sub(lua_State* L)
    {
        if(!lua_isuserdata(L, 1) || !lua_isuserdata(L, 2))
        {
            luaL_error(L, "Unsupported binary operation between types %s and %s", lua_typename(L, lua_type(L, 1)), lua_typename(L, lua_type(L, 1)));
            return 0;
        }

        Lua_Vector2* firstVec = static_cast<Lua_Vector2*>( lua_touserdata(L, 1) );
        Lua_Vector2* secondVec = static_cast<Lua_Vector2*>( lua_touserdata(L, 2) );

        Vector2_createVector(L, -1, (*firstVec) - (*secondVec));
        return 1;
    }

    static int Vector2_mul(lua_State* L)
    {
        Lua_Vector2* vecPtr;
        lua_Number scalar;

        if(lua_isuserdata(L, 1) && lua_isnumber(L, 2))
        {
            vecPtr = static_cast<Lua_Vector2*>( lua_touserdata(L, 1) );
            scalar = lua_tonumber(L, 2);
        }
        else if(lua_isnumber(L, 1) && lua_isuserdata(L, 2))
        {
            scalar = lua_tonumber(L, 1);
            vecPtr = static_cast<Lua_Vector2*>( lua_touserdata(L, 2) );
        }
        else
        {
            luaL_error(L, "Unsupported binary operation between types %s and %s", lua_typename(L, lua_type(L, 1)), lua_typename(L, lua_type(L, 1)));
            return 0;
        }

        Vector2_createVector(L, -1, (*vecPtr) * scalar);
        return 1;
    }

    static int Vector2_div(lua_State* L)
    {
        if(!lua_isuserdata(L, 1) || !lua_isnumber(L, 2))
        {
            luaL_error(L, "Unsupported binary operation between types %s and %s", lua_typename(L, lua_type(L, 1)), lua_typename(L, lua_type(L, 1)));
            return 0;
        }

        Lua_Vector2* vecPtr;
        lua_Number divider;

        vecPtr = static_cast<Lua_Vector2*>( lua_touserdata(L, 1) );
        divider = lua_tonumber(L, 2);

        Vector2_createVector(L, -1, (*vecPtr) / divider);
        return 1;
    }

    static int Vector2_idiv(lua_State* L)
    {
        if(!lua_isuserdata(L, 1) || !lua_isnumber(L, 2))
        {
            luaL_error(L, "Unsupported binary operation between types %s and %s", lua_typename(L, lua_type(L, 1)), lua_typename(L, lua_type(L, 1)));
            return 0;
        }
        Lua_Vector2* vecPtr;
        lua_Number divider;

        vecPtr = static_cast<Lua_Vector2*>( lua_touserdata(L, 1) );
        divider = lua_tonumber(L, 2);


        Vector2_createVector(L, -1, {
            static_cast<lua_Integer>(vecPtr->x / divider),
            static_cast<lua_Integer>(vecPtr->y / divider)
        } );
        return 1;
    }

    static int Vector2_eq(lua_State* L)
    {
        if(!lua_isuserdata(L, 1) || !lua_isuserdata(L, 2))
        {
            luaL_error(L, "Unsupported binary operation between types %s and %s", lua_typename(L, lua_type(L, 1)), lua_typename(L, lua_type(L, 1)));
            return 0;
        }

        Lua_Vector2* firstVec = static_cast<Lua_Vector2*>( lua_touserdata(L, 1) );
        Lua_Vector2* secondVec = static_cast<Lua_Vector2*>( lua_touserdata(L, 2) );

        lua_pushboolean(L, ((*firstVec) == (*secondVec)) );
        return 1;
    }

    static LuaExporter toLuaExporter()
    {
        return LuaExporter(
            "Vector2", 
            Vector2Exporter::Vector2_new,
            {},
            {
                {"__gc", Vector2Exporter::Vector2_destroy},
                {"__index", Vector2Exporter::Vector2_index},
                {"__newindex", Vector2Exporter::Vector2_newindex},
                {"__tostring", Vector2Exporter::Vector2_toString},
                {"__unm", Vector2Exporter::Vector2_unm},
                {"__add", Vector2Exporter::Vector2_add},
                {"__sub", Vector2Exporter::Vector2_sub},
                {"__mul", Vector2Exporter::Vector2_mul},
                {"__div", Vector2Exporter::Vector2_div},
                {"__idiv", Vector2Exporter::Vector2_idiv},
                {"__eq", Vector2Exporter::Vector2_eq},
            }
        );
    }
};

