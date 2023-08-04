#include <Modding/Exporters/MouseExporter.hpp>
#include <Modding/LuaExporter.hpp>
#include <Modding/Exporters/Vector2Exporter.hpp>
#include <SFEX/General/Mouse.hpp>

int MouseExporter::getButton(lua_State *L)
{
    lua_Integer button = luaL_checkinteger(L, 1);
    bool state = sfex::Mouse::getButton(static_cast<sfex::Mouse::Button>(button));
    lua_pushboolean(L, state);
    return 1;
}

int MouseExporter::getButtonDown(lua_State *L)
{
    lua_Integer button = luaL_checkinteger(L, 1);
    bool state = sfex::Mouse::getButtonDown(static_cast<sfex::Mouse::Button>(button));
    lua_pushboolean(L, state);
    return 1;
}

int MouseExporter::getButtonUp(lua_State *L)
{
    lua_Integer button = luaL_checkinteger(L, 1);
    bool state = sfex::Mouse::getButtonUp(static_cast<sfex::Mouse::Button>(button));
    lua_pushboolean(L, state);
    return 1;
}

int MouseExporter::getPosition(lua_State *L)
{
    // TODO: Add support for getting position relative to window
    Vector2Exporter::createVector(L, sfex::Mouse::getPosition());
    return 1;
}

int MouseExporter::setPosition(lua_State *L)
{
    // TODO: Add support for setting position relative to window
    if(lua_isuserdata(L, 1))
    {
        Lua_Vector2* newPos = static_cast<Lua_Vector2*>(lua_touserdata(L, 1));
        sfex::Mouse::setPosition(*newPos);
    }
    return 0;
}

LuaExporter MouseExporter::toLuaExporter()
{
    LuaExporter mouseExporter(
        LUA_MOUSE_CLASSNAME,
        nullptr,
        {
            {"getButton", MouseExporter::getButton},
            {"getButtonDown", MouseExporter::getButtonDown},
            {"getButtonUp", MouseExporter::getButtonUp},
            {"getPosition", MouseExporter::getPosition},
            {"setPosition", MouseExporter::setPosition},
        },
        {}
    );

    mouseExporter.addInteger("left", sfex::Mouse::Button::Left);
    mouseExporter.addInteger("middle", sfex::Mouse::Button::Middle);
    mouseExporter.addInteger("right", sfex::Mouse::Button::Right);
    mouseExporter.addInteger("xbutton1", sfex::Mouse::Button::XButton1);
    mouseExporter.addInteger("xbutton2", sfex::Mouse::Button::XButton2);

    return mouseExporter;
}