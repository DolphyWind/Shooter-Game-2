#include <Modding/Exporters/TransformExporter.hpp>
#include <Modding/LuaExporter.hpp>
#include <Modding/Exporters/Vector2Exporter.hpp>
#include <Modding/Exporters/FloatRectExporter.hpp>
#include <array>
#include <iostream>
#include <Modding/LuaHelper.hpp>

void TransformExporter::createTransform(lua_State *L, const Lua_Transform &transform)
{
    void* data = lua_newuserdata(L, sizeof(Lua_Transform));
    new (data) Lua_Transform(transform);
    luaL_getmetatable(L, LUA_TRANSFORM_METATABLENAME);
    lua_setmetatable(L, -2);
}

int TransformExporter::__new(lua_State *L)
{
    int valCount = lua_gettop(L);

    if(valCount == 0)
    {
        createTransform(L, sf::Transform());
        return 1;
    }
    else if(valCount == 9)
    {
        std::array<float, 9> mat;
        for(std::size_t i = 0; i < 9; ++i)
        {
            mat[i] = luaL_checknumber(L, i);
        }
        createTransform(L, sf::Transform(
            mat[0], mat[1], mat[2],
            mat[3], mat[4], mat[5],
            mat[6], mat[7], mat[8]
        ));
        return 1;
    }

    luaL_error(L, "You can't create a transform with that amount of arguments!");
    
    return 0;
}

int TransformExporter::__destroy(lua_State *L)
{
    Lua_Transform* transformPtr = static_cast<Lua_Transform*>( luaL_checkudata(L, 1, LUA_TRANSFORM_METATABLENAME) );
    transformPtr->~Lua_Transform();
    return 0;
}

int TransformExporter::__index(lua_State *L)
{
    Lua_Transform* transformPtr = static_cast<Lua_Transform*>( luaL_checkudata(L, 1, LUA_TRANSFORM_METATABLENAME) );
    std::string indexStr = luaL_checkstring(L, 2);

    if(indexStr == "identity")
    {
        createTransform(L, sf::Transform::Identity);
        return 1;
    }

    lua_getglobal(L, LUA_TRANSFORM_CLASSNAME);
    lua_pushstring(L, indexStr.c_str());
    lua_rawget(L, -2);
    return 1;
}

int TransformExporter::__mul(lua_State *L)
{
    Lua_Transform* firstTransform = static_cast<Lua_Transform*>( luaL_checkudata(L, 1, LUA_TRANSFORM_METATABLENAME) );
    Lua_Transform* secondTransform = static_cast<Lua_Transform*>( luaL_checkudata(L, 2, LUA_TRANSFORM_METATABLENAME) );

    createTransform(L, (*firstTransform) * (*secondTransform));
    return 1;
}

int TransformExporter::__eq(lua_State *L)
{
    if(lua_type(L, 1) != lua_type(L, 2))
    {
        lua_pushboolean(L, false);
        return 1;
    }

    Lua_Transform* firstTransform = static_cast<Lua_Transform*>( luaL_checkudata(L, 1, LUA_TRANSFORM_METATABLENAME) );
    Lua_Transform* secondTransform = static_cast<Lua_Transform*>( luaL_checkudata(L, 2, LUA_TRANSFORM_METATABLENAME) );

    lua_pushboolean(L, (*firstTransform) == (*secondTransform));
    return 1;
}

int TransformExporter::getMatrix(lua_State *L)
{
    Lua_Transform* transformPtr = static_cast<Lua_Transform*>( luaL_checkudata(L, 1, LUA_TRANSFORM_METATABLENAME) );

    const float* mat = transformPtr->getMatrix();
    for(std::size_t i = 0; i < 16; ++i)
    {
        lua_pushnumber(L, *(mat + i));
    }

    return 16;
}

int TransformExporter::getInverse(lua_State *L)
{
    Lua_Transform* transformPtr = static_cast<Lua_Transform*>( luaL_checkudata(L, 1, LUA_TRANSFORM_METATABLENAME) );
    createTransform(L, transformPtr->getInverse());
    return 1;
}

int TransformExporter::transformPoint(lua_State *L)
{
    int arg_count = lua_gettop(L);
    Lua_Transform* transformPtr = static_cast<Lua_Transform*>( luaL_checkudata(L, 1, LUA_TRANSFORM_METATABLENAME) );
    Lua_Vector2 vecToTransform;

    if(arg_count == 2)
    {
        vecToTransform = *static_cast<Lua_Vector2*>( luaL_checkudata(L, 2, LUA_VECTOR2_METATABLENAME) );
    }
    else if(arg_count == 3)
    {
        lua_Number x = luaL_checknumber(L, 2);
        lua_Number y = luaL_checknumber(L, 3);
        vecToTransform.x = x;
        vecToTransform.y = y;
    }
    else
    {
        luaL_error(L, "You can't call %s with this amount of arguments", __func__);
        return 0;
    }
    
    Vector2Exporter::createVector(L, transformPtr->transformPoint(vecToTransform));
    return 1;
}

int TransformExporter::transformRect(lua_State *L)
{
    Lua_Transform* transformPtr = static_cast<Lua_Transform*>( luaL_checkudata(L, 1, LUA_TRANSFORM_METATABLENAME) );
    Lua_FloatRect* floatRectPtr = static_cast<Lua_FloatRect*>( luaL_checkudata(L, 2, LUA_FLOATRECT_METATABLENAME) );
    FloatRectExporter::createFloatRect(L, transformPtr->transformRect(*floatRectPtr));
    return 1;
}

int TransformExporter::combine(lua_State *L)
{
    Lua_Transform* firstTransform = static_cast<Lua_Transform*>( luaL_checkudata(L, 1, LUA_TRANSFORM_METATABLENAME) );
    Lua_Transform* secondTransform = static_cast<Lua_Transform*>( luaL_checkudata(L, 2, LUA_TRANSFORM_METATABLENAME) );
    firstTransform->combine(*secondTransform);

    LuaHelper::push(L, (void*)firstTransform, LUA_TRANSFORM_CLASSNAME"_metatable");
    return 1;
}

int TransformExporter::translate(lua_State *L)
{
    int arg_count = lua_gettop(L);
    Lua_Transform* transformPtr = static_cast<Lua_Transform*>( luaL_checkudata(L, 1, LUA_TRANSFORM_METATABLENAME) );
    Lua_Vector2 vecToTranslate;

    if(arg_count == 2)
    {
        vecToTranslate = *static_cast<Lua_Vector2*>( luaL_checkudata(L, 2, LUA_VECTOR2_METATABLENAME) );
    }
    else if(arg_count == 3)
    {
        vecToTranslate.x = luaL_checknumber(L, 2);
        vecToTranslate.y = luaL_checknumber(L, 3);
    }
    else
    {
        luaL_error(L, "You can't call %s with this amount of arguments", __func__);
        return 0;
    }
    transformPtr->translate(vecToTranslate);
    LuaHelper::push(L, (void*)transformPtr, LUA_TRANSFORM_METATABLENAME);

    return 1;
}

int TransformExporter::rotate(lua_State *L)
{
    int arg_count = lua_gettop(L);
    Lua_Transform* transformPtr = static_cast<Lua_Transform*>( luaL_checkudata(L, 1, LUA_TRANSFORM_METATABLENAME) );
    lua_Number angle;
    Lua_Vector2 center;

    if(arg_count == 2)
    {
        angle = luaL_checknumber(L, 2);
        transformPtr->rotate(angle);
    }
    else if(arg_count == 3)
    {
        angle = luaL_checknumber(L, 2);
        center = *static_cast<Lua_Vector2*>( luaL_checkudata(L, 3, LUA_VECTOR2_METATABLENAME) );
        transformPtr->rotate(angle, center);
    }
    else if(arg_count == 4)
    {
        angle = luaL_checknumber(L, 2);
        center.x = luaL_checknumber(L, 3);
        center.y = luaL_checknumber(L, 4);
        transformPtr->rotate(angle, center);
    }
    else
    {
        luaL_error(L, "You can't call %s with this amount of arguments", __func__);
        return 0;
    }
    LuaHelper::push(L, (void*)transformPtr, LUA_TRANSFORM_METATABLENAME);
    
    return 1;
}

int TransformExporter::scale(lua_State *L)
{
    int arg_count = lua_gettop(L);
    Lua_Transform* transformPtr = static_cast<Lua_Transform*>( luaL_checkudata(L, 1, LUA_TRANSFORM_METATABLENAME) );
    Lua_Vector2 factors;
    Lua_Vector2 center;

    if(arg_count == 2)
    {
        factors = *static_cast<Lua_Vector2*>( luaL_checkudata(L, 1, LUA_VECTOR2_METATABLENAME) );
        transformPtr->scale(factors);
    }
    else if(arg_count == 3)
    {
        if(lua_isuserdata(L, 2) && lua_isuserdata(L, 3))
        {
            factors = *static_cast<Lua_Vector2*>( luaL_checkudata(L, 2, LUA_VECTOR2_METATABLENAME) );
            center = *static_cast<Lua_Vector2*>( luaL_checkudata(L, 3, LUA_VECTOR2_METATABLENAME) );
            transformPtr->scale(factors, center);
        }
        else
        {
            factors.x = luaL_checknumber(L, 2);
            factors.y = luaL_checknumber(L, 3);
            transformPtr->scale(factors);
        }
    }
    else if(arg_count == 5)
    {
        factors.x = luaL_checknumber(L, 2);
        factors.y = luaL_checknumber(L, 3);
        center.x = luaL_checknumber(L, 4);
        center.y = luaL_checknumber(L, 5);
        transformPtr->scale(factors, center);
    }
    else
    {
        luaL_error(L, "You can't call %s with this amount of arguments", __func__);
        return 0;
    }
    LuaHelper::push(L, (void*)transformPtr, LUA_TRANSFORM_CLASSNAME"_metatable");
    
    return 1;
}

int TransformExporter::identity(lua_State* L)
{
    createTransform(L, Lua_Transform::Identity);
    return 1;
}

LuaExporter TransformExporter::toLuaExporter()
{
    LuaExporter exporter(
        LUA_TRANSFORM_CLASSNAME,
        TransformExporter::__new,
        {
            {"getMatrix", TransformExporter::getMatrix},
            {"getInverse", TransformExporter::getInverse},
            {"transformPoint", TransformExporter::transformPoint},
            {"transformRect", TransformExporter::transformRect},
            {"combine", TransformExporter::combine},
            {"translate", TransformExporter::translate},
            {"rotate", TransformExporter::rotate},
            {"scale", TransformExporter::scale},
            {"identity", TransformExporter::identity},
        },
        {
            {"__gc", TransformExporter::__destroy},
            {"__index", TransformExporter::__index},
            {"__mul", TransformExporter::__mul},
            {"__eq", TransformExporter::__eq},
        }
    );

    return exporter;
}