#include <Modding/Exporters/ViewExporter.hpp>
#include <Modding/Exporters/FloatRectExporter.hpp>
#include <Modding/Exporters/TransformExporter.hpp>
#include <Modding/Exporters/Vector2Exporter.hpp>
#include <Modding/LuaExporter.hpp>
#include "Modding/LuaHelper.hpp"

void ViewExporter::createView(lua_State *L, const Lua_View& view)
{
    void* data = lua_newuserdata(L, sizeof(Lua_View));
    new (data) Lua_View(view);
    luaL_getmetatable(L, LUA_VIEW_METATABLENAME);
    lua_setmetatable(L, -2);
}

int ViewExporter::__new(lua_State *L)
{
    int arg_count = lua_gettop(L);
    if(arg_count == 0)
    {
        createView(L, Lua_View());
        return 1;
    }
    else if(arg_count == 1)
    {
        Exported_FloatRect* rectanglePtr = static_cast<Exported_FloatRect*>( LuaHelper::checkudata_WithError(L, 1, LUA_FLOATRECT_METATABLENAME) );
        createView(L, Lua_View(*rectanglePtr));
        return 1;
    }
    Exported_Vector2* centerPtr = static_cast<Exported_Vector2*>( LuaHelper::checkudata_WithError(L, 1, LUA_VECTOR2_METATABLENAME) );
    Exported_Vector2* sizePtr = static_cast<Exported_Vector2*>( LuaHelper::checkudata_WithError(L, 2, LUA_VECTOR2_METATABLENAME) );
    createView(L, Lua_View(*centerPtr, *sizePtr));

    return 1;
}

int ViewExporter::__destroy(lua_State *L)
{
    Lua_View* viewPtr = static_cast<Lua_View*>( LuaHelper::checkudata_WithError(L, 1, LUA_VIEW_METATABLENAME) );
    viewPtr->~Lua_View();
    return 0;
}

int ViewExporter::__index(lua_State *L)
{
    Lua_View* viewPtr = static_cast<Lua_View*>( LuaHelper::checkudata_WithError(L, 1, LUA_VIEW_METATABLENAME) );
    std::string indexStr = lua_tostring(L, 2);

    lua_getglobal(L, LUA_VIEW_CLASSNAME);
    lua_pushstring(L, indexStr.c_str());
    lua_rawget(L, -2);
    return 1;
}

int ViewExporter::setCenter(lua_State *L)
{
    int arg_count = lua_gettop(L);
    Lua_View* viewPtr = static_cast<Lua_View*>( LuaHelper::checkudata_WithError(L, 1, LUA_VIEW_METATABLENAME) );
    
    if(arg_count == 2)
    {
        Exported_Vector2* centerPtr = static_cast<Exported_Vector2*>( LuaHelper::checkudata_WithError(L, 2, LUA_VECTOR2_METATABLENAME) );
        viewPtr->setCenter(*centerPtr);
        return 0;
    }

    lua_Number x = luaL_checknumber(L, 2);
    lua_Number y = luaL_checknumber(L, 3);
    viewPtr->setCenter(x, y);

    return 0;
}

int ViewExporter::setSize(lua_State *L)
{
    int arg_count = lua_gettop(L);
    Lua_View* viewPtr = static_cast<Lua_View*>( LuaHelper::checkudata_WithError(L, 1, LUA_VIEW_METATABLENAME) );

    if(arg_count == 2)
    {
        Exported_Vector2* sizePtr = static_cast<Exported_Vector2*>( LuaHelper::checkudata_WithError(L, 2, LUA_VECTOR2_METATABLENAME) );
        viewPtr->setCenter(*sizePtr);
        return 0;
    }

    lua_Number width = luaL_checknumber(L, 2);
    lua_Number height = luaL_checknumber(L, 3);
    viewPtr->setSize(width, height);
    
    return 0;
}

int ViewExporter::setRotatin(lua_State *L)
{
    Lua_View* viewPtr = static_cast<Lua_View*>( LuaHelper::checkudata_WithError(L, 1, LUA_VIEW_METATABLENAME) );
    viewPtr->setRotation( luaL_checknumber(L, 2) );
    return 0;
}

int ViewExporter::setViewport(lua_State *L)
{
    Lua_View* viewPtr = static_cast<Lua_View*>( LuaHelper::checkudata_WithError(L, 1, LUA_VIEW_METATABLENAME) );
    Exported_FloatRect* viewportPtr = static_cast<Exported_FloatRect*>( LuaHelper::checkudata_WithError(L, 2, LUA_FLOATRECT_METATABLENAME) );
    viewPtr->setViewport(*viewportPtr);

    return 0;
}

int ViewExporter::reset(lua_State *L)
{
    Lua_View* viewPtr = static_cast<Lua_View*>( LuaHelper::checkudata_WithError(L, 1, LUA_VIEW_METATABLENAME) );
    Exported_FloatRect* rectanglePtr = static_cast<Exported_FloatRect*>( LuaHelper::checkudata_WithError(L, 2, LUA_FLOATRECT_METATABLENAME) );
    viewPtr->reset(*rectanglePtr);
    
    return 0;
}

int ViewExporter::getCenter(lua_State *L)
{
    Lua_View* viewPtr = static_cast<Lua_View*>( LuaHelper::checkudata_WithError(L, 1, LUA_VIEW_METATABLENAME) );
    Vector2Exporter::createVector(L, viewPtr->getCenter());
    return 1;
}

int ViewExporter::getSize(lua_State *L)
{
    Lua_View* viewPtr = static_cast<Lua_View*>( LuaHelper::checkudata_WithError(L, 1, LUA_VIEW_METATABLENAME) );
    Vector2Exporter::createVector(L, viewPtr->getSize());
    return 1;
}

int ViewExporter::getRotation(lua_State *L)
{
    Lua_View* viewPtr = static_cast<Lua_View*>( LuaHelper::checkudata_WithError(L, 1, LUA_VIEW_METATABLENAME) );
    lua_pushnumber(L, viewPtr->getRotation());
    return 1;
}

int ViewExporter::getViewport(lua_State *L)
{
    Lua_View* viewPtr = static_cast<Lua_View*>( LuaHelper::checkudata_WithError(L, 1, LUA_VIEW_METATABLENAME) );
    FloatRectExporter::createFloatRect(L, viewPtr->getViewport());
    return 1;
}

int ViewExporter::move(lua_State *L)
{
    int arg_count = lua_gettop(L);
    Lua_View* viewPtr = static_cast<Lua_View*>( LuaHelper::checkudata_WithError(L, 1, LUA_VIEW_METATABLENAME) );
    
    if(arg_count == 2)
    {
        Exported_Vector2* offsetPtr = static_cast<Exported_Vector2*>( LuaHelper::checkudata_WithError(L, 2, LUA_VECTOR2_METATABLENAME) );
        viewPtr->move(*offsetPtr);
        return 1;
    }
    viewPtr->move(
        luaL_checknumber(L, 2),
        luaL_checknumber(L, 3)
    );

    return 1;
}

int ViewExporter::rotate(lua_State *L)
{
    Lua_View* viewPtr = static_cast<Lua_View*>( LuaHelper::checkudata_WithError(L, 1, LUA_VIEW_METATABLENAME) );
    viewPtr->rotate( luaL_checknumber(L, 2) );
    return 1;
}

int ViewExporter::zoom(lua_State *L)
{
    Lua_View* viewPtr = static_cast<Lua_View*>( LuaHelper::checkudata_WithError(L, 1, LUA_VIEW_METATABLENAME) );
    viewPtr->zoom( luaL_checknumber(L, 2) );
    return 1;
}

int ViewExporter::getTransform(lua_State *L)
{
    Lua_View* viewPtr = static_cast<Lua_View*>( LuaHelper::checkudata_WithError(L, 1, LUA_VIEW_METATABLENAME) );
    TransformExporter::createTransform(L, viewPtr->getTransform());
    return 1;
}

int ViewExporter::getInverseTransform(lua_State *L)
{
    Lua_View* viewPtr = static_cast<Lua_View*>( LuaHelper::checkudata_WithError(L, 1, LUA_VIEW_METATABLENAME) );
    TransformExporter::createTransform(L, viewPtr->getInverseTransform());
    return 1;
}

LuaExporter ViewExporter::toLuaExporter()
{
    LuaExporter exporter(
        LUA_VIEW_CLASSNAME,
        __new,
        {
            {"setCenter", ViewExporter::setCenter},
            {"setSize", ViewExporter::setSize},
            {"setRotatin", ViewExporter::setRotatin},
            {"setViewport", ViewExporter::setViewport},
            {"reset", ViewExporter::reset},
            {"getCenter", ViewExporter::getCenter},
            {"getSize", ViewExporter::getSize},
            {"getRotation", ViewExporter::getRotation},
            {"getViewport", ViewExporter::getViewport},
            {"move", ViewExporter::move},
            {"rotate", ViewExporter::rotate},
            {"zoom", ViewExporter::zoom},
            {"getTransform", ViewExporter::getTransform},
            {"getInverseTransform", ViewExporter::getInverseTransform},
        },
        {
            {"__gc", ViewExporter::__destroy},
            {"__index", ViewExporter::__index},
        }
    );

    return exporter;
}