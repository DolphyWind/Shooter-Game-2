#include <Modding/Exporters/RenderWindowExporter.hpp>
#include <Modding/LuaExporter.hpp>

int RenderWindowExporter::__index(lua_State *L)
{
    Lua_RenderWindow* renderWindowPtr = static_cast<Lua_RenderWindow*>( luaL_checkudata(L, 1, LUA_RENDERWINDOW_METATABLENAME) );
    std::string indexStr = luaL_checkstring(L, 2);

    lua_getglobal(L, LUA_RENDERWINDOW_CLASSNAME);
    lua_pushstring(L, indexStr.c_str());
    lua_rawget(L, -2);
    return 1;
}

int RenderWindowExporter::draw(lua_State *L)
{
    Lua_RenderWindow* renderWindowPtr = static_cast<Lua_RenderWindow*>( luaL_checkudata(L, 1, LUA_RENDERWINDOW_METATABLENAME) );
    sf::Drawable* drawablePtr = static_cast<sf::Drawable*>( lua_touserdata(L, 2) );

    // I am not sure whether it will work or not. I'll fix it when I add textures sprites etc
    renderWindowPtr->draw(*drawablePtr);
    return 0;
}

LuaExporter RenderWindowExporter::toLuaExporter()
{
    LuaExporter exporter(
        LUA_RENDERWINDOW_CLASSNAME,
        nullptr,
        {
            {"draw", RenderWindowExporter::draw},
        },
        {
            {"__index", RenderWindowExporter::__index},
        }
    );

    return exporter;
}