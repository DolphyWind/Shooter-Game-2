#pragma once
#include <SFEX/Numeric/Vector2.hpp>
#include <Modding/LuaExporter.hpp>
#include <lua.hpp>
#include <cassert>
#include <sstream>
#include <Modding/ShooterGameExporter.hpp>

#define LUA_VECTOR2_CLASSNAME "Vector2"
typedef sfex::Vector2<lua_Number> Lua_Vector2;
struct Vector2Exporter
{
    static void Vector2_createVector(lua_State* L, int idx, const Lua_Vector2& vec)
    {
        lua_remove(L, idx);
        void* data = lua_newuserdata(L, sizeof(Lua_Vector2));
        Lua_Vector2* vecPtr = new (data) Lua_Vector2(vec);
        luaL_getmetatable(L, LUA_VECTOR2_CLASSNAME"_metatable");
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
        else if(indexStr == "one")
        {
            Vector2_createVector(L, -1, Lua_Vector2::one);
            return 1;
        }
        else if(indexStr == "zero")
        {
            Vector2_createVector(L, -1, Lua_Vector2::zero);
            return 1;
        }

        lua_getglobal(L, LUA_VECTOR2_CLASSNAME);
        lua_pushstring(L, indexStr.c_str());
        lua_rawget(L, -2);
        return 1;
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

    /// Regular Functions
    static int Vector2_magnitude(lua_State* L)
    {
        if(!lua_isuserdata(L, 1))
        {
            luaL_error(L, "The first parameter has be a userdata, not %s", lua_typename(L, lua_type(L, 1)) );
            return 0;
        }

        Lua_Vector2* vecPtr = static_cast<Lua_Vector2*>( lua_touserdata(L, 1) );
        lua_pushnumber(L, vecPtr->magnitude());

        return 1;
    }

    static int Vector2_magnitude2(lua_State* L)
    {
        if(!lua_isuserdata(L, 1))
        {
            luaL_error(L, "The first parameter has be a userdata, not %s", lua_typename(L, lua_type(L, 1)) );
            return 0;
        }

        Lua_Vector2* vecPtr = static_cast<Lua_Vector2*>( lua_touserdata(L, 1) );
        lua_pushnumber(L, vecPtr->magnitude2());

        return 1;
    }

    static int Vector2_setmagnitude(lua_State* L)
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

        Lua_Vector2* vecPtr = static_cast<Lua_Vector2*>( lua_touserdata(L, 1) );
        vecPtr->setMagnitude( lua_tonumber(L, 2) );

        return 0;
    }

    static int Vector2_normalize(lua_State* L)
    {
        if(!lua_isuserdata(L, 1))
        {
            luaL_error(L, "The operand has be an user data, not %s", lua_typename(L, lua_type(L, 1)) );
            return 0;
        }

        Lua_Vector2* vecPtr = static_cast<Lua_Vector2*>( lua_touserdata(L, 1) );
        vecPtr->normalize();
        return 0;
    }

    static int Vector2_normalized(lua_State* L)
    {
        if(!lua_isuserdata(L, 1))
        {
            luaL_error(L, "The operand has be an user data, not %s", lua_typename(L, lua_type(L, 1)) );
            return 0;
        }

        Lua_Vector2* vecPtr = static_cast<Lua_Vector2*>( lua_touserdata(L, 1) );
        Vector2_createVector(L, -1, vecPtr->normalized());

        return 1;
    }

    static int Vector2_dot(lua_State* L)
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

        Lua_Vector2* firstVec = static_cast<Lua_Vector2*>( lua_touserdata(L, 1) );
        Lua_Vector2* secondVec = static_cast<Lua_Vector2*>( lua_touserdata(L, 2) );
        lua_pushnumber(L, firstVec->dot(*secondVec));

        return 1;
    }

    static int Vector2_cross(lua_State* L)
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

        Lua_Vector2* firstVec = static_cast<Lua_Vector2*>( lua_touserdata(L, 1) );
        Lua_Vector2* secondVec = static_cast<Lua_Vector2*>( lua_touserdata(L, 2) );
        lua_pushnumber(L, firstVec->cross(*secondVec));
        
        return 1;
    }

    static int Vector2_cwiseMul(lua_State* L)
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

        Lua_Vector2* firstVec = static_cast<Lua_Vector2*>( lua_touserdata(L, 1) );
        Lua_Vector2* secondVec = static_cast<Lua_Vector2*>( lua_touserdata(L, 2) );
        Vector2_createVector(L, -1, firstVec->cwiseMul(*secondVec));
        
        return 1;
    }

    static int Vector2_cwiseDiv(lua_State* L)
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

        Lua_Vector2* firstVec = static_cast<Lua_Vector2*>( lua_touserdata(L, 1) );
        Lua_Vector2* secondVec = static_cast<Lua_Vector2*>( lua_touserdata(L, 2) );
        Vector2_createVector(L, -1, firstVec->cwiseDiv(*secondVec));
        
        return 1;
    }

    static int Vector2_scale(lua_State* L)
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

        Lua_Vector2* vecPtr = static_cast<Lua_Vector2*>( lua_touserdata(L, 1) );
        vecPtr->scale( lua_tonumber(L, 2) );
        
        return 0;
    }

    static int Vector2_scaled(lua_State* L)
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

        Lua_Vector2* vecPtr = static_cast<Lua_Vector2*>( lua_touserdata(L, 1) );
        Vector2_createVector(L, -1, vecPtr->scaled( lua_tonumber(L, 2) ));
        
        return 1;
    }

    static int Vector2_rotate(lua_State* L)
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
            rotateAround = *static_cast<Lua_Vector2*>( lua_touserdata(L, 3) );
        }

        Lua_Vector2* vecPtr = static_cast<Lua_Vector2*>( lua_touserdata(L, 1) );
        vecPtr->rotate( lua_tonumber(L, 2), rotateAround);
        
        return 0;
    }

    static int Vector2_rotated(lua_State* L)
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
            rotateAround = *static_cast<Lua_Vector2*>( lua_touserdata(L, 3) );
        }

        Lua_Vector2* vecPtr = static_cast<Lua_Vector2*>( lua_touserdata(L, 1) );
        Vector2_createVector(L, -1, vecPtr->rotated( lua_tonumber(L, 2), rotateAround));

        return 1;
    }

    static int Vector2_angle(lua_State* L)
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
            otherVector = *static_cast<Lua_Vector2*>( lua_touserdata(L, 2) );
        }

        Lua_Vector2* vecPtr = static_cast<Lua_Vector2*>( lua_touserdata(L, 1) );
        lua_pushnumber(L, vecPtr->angle(otherVector) );

        return 1;
    }

    static int Vector2_projectOnto(lua_State* L)
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

        Lua_Vector2* firstVec = static_cast<Lua_Vector2*>( lua_touserdata(L, 1) );
        Lua_Vector2* secondVec = static_cast<Lua_Vector2*>( lua_touserdata(L, 2) );
        firstVec->projectOnto(*secondVec);

        return 0;
    }

    static int Vector2_projectedOnto(lua_State* L)
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

        Lua_Vector2* firstVec = static_cast<Lua_Vector2*>( lua_touserdata(L, 1) );
        Lua_Vector2* secondVec = static_cast<Lua_Vector2*>( lua_touserdata(L, 2) );
        Vector2_createVector(L, -1, firstVec->projectedOnto(*secondVec));

        return 1;
    }


    static LuaExporter toLuaExporter()
    {
        LuaExporter exporter(
            LUA_VECTOR2_CLASSNAME, 
            Vector2Exporter::Vector2_new,
            {
                {"magnitude", Vector2Exporter::Vector2_magnitude},
                {"magnitude2", Vector2Exporter::Vector2_magnitude2},
                {"setMagnitude", Vector2Exporter::Vector2_setmagnitude},
                {"normalize", Vector2Exporter::Vector2_normalize},
                {"normalized", Vector2Exporter::Vector2_normalized},
                {"dot", Vector2Exporter::Vector2_dot},
                {"cross", Vector2Exporter::Vector2_cross},
                {"cwiseMul", Vector2Exporter::Vector2_cwiseMul},
                {"cwiseDiv", Vector2Exporter::Vector2_cwiseDiv},
                {"scale", Vector2Exporter::Vector2_scale},
                {"scaled", Vector2Exporter::Vector2_scaled},
                {"rotate", Vector2Exporter::Vector2_rotate},
                {"rotated", Vector2Exporter::Vector2_rotated},
                {"angle", Vector2Exporter::Vector2_angle},
                {"projectOnto", Vector2Exporter::Vector2_projectOnto},
                {"projectedOnto", Vector2Exporter::Vector2_projectedOnto},
            },
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

        std::vector<Lua_Vector2*> public_lua_vectors;
        public_lua_vectors.push_back(new Lua_Vector2(Lua_Vector2::left));
        public_lua_vectors.push_back(new Lua_Vector2(Lua_Vector2::right));
        public_lua_vectors.push_back(new Lua_Vector2(Lua_Vector2::up));
        public_lua_vectors.push_back(new Lua_Vector2(Lua_Vector2::down));
        public_lua_vectors.push_back(new Lua_Vector2(Lua_Vector2::zero));
        public_lua_vectors.push_back(new Lua_Vector2(Lua_Vector2::one));

        exporter.addUserdata("left", public_lua_vectors[0], sizeof(Lua_Vector2), LUA_VECTOR2_CLASSNAME"_metatable");
        exporter.addUserdata("right", public_lua_vectors[1], sizeof(Lua_Vector2), LUA_VECTOR2_CLASSNAME"_metatable");
        exporter.addUserdata("up", public_lua_vectors[2], sizeof(Lua_Vector2), LUA_VECTOR2_CLASSNAME"_metatable");
        exporter.addUserdata("down", public_lua_vectors[3], sizeof(Lua_Vector2), LUA_VECTOR2_CLASSNAME"_metatable");
        exporter.addUserdata("zero", public_lua_vectors[4], sizeof(Lua_Vector2), LUA_VECTOR2_CLASSNAME"_metatable");
        exporter.addUserdata("one", public_lua_vectors[5], sizeof(Lua_Vector2), LUA_VECTOR2_CLASSNAME"_metatable");

        for(auto& v : public_lua_vectors)
        {
            delete v;
        }

        return exporter;
    }
};

