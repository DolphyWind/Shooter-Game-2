#include <Modding/Exporters/JoystickExporter.hpp>
#include <Modding/LuaExporter.hpp>
#include <SFEX/General/Joystick.hpp>

int JoystickExporter::isConnected(lua_State *L)
{
    unsigned int id = luaL_checkinteger(L, 1);
    lua_pushboolean(L, sfex::Joystick::isConnected(id));
    return 1;
}

int JoystickExporter::getButtonCount(lua_State *L)
{
    unsigned int id = luaL_checkinteger(L, 1);
    lua_pushinteger(L, sfex::Joystick::getButtonCount(id));
    return 1;
}

int JoystickExporter::hasAxis(lua_State *L)
{
    unsigned int id = luaL_checkinteger(L, 1);
    sfex::Joystick::Axis axis = static_cast<sfex::Joystick::Axis>( luaL_checkinteger(L, 2) );
    lua_pushboolean(L, sfex::Joystick::hasAxis(id, axis));
    return 1;
}

int JoystickExporter::getButton(lua_State *L)
{
    unsigned int id = luaL_checkinteger(L, 1);
    unsigned int buttonId = luaL_checkinteger(L, 2);
    lua_pushboolean(L, sfex::Joystick::getButton(id, buttonId));
    return 1;
}

int JoystickExporter::getButtonDown(lua_State *L)
{
    unsigned int id = luaL_checkinteger(L, 1);
    unsigned int buttonId = luaL_checkinteger(L, 2);
    lua_pushboolean(L, sfex::Joystick::getButtonDown(id, buttonId));
    return 1;
}

int JoystickExporter::getButtonUp(lua_State *L)
{
    unsigned int id = luaL_checkinteger(L, 1);
    unsigned int buttonId = luaL_checkinteger(L, 2);
    lua_pushboolean(L, sfex::Joystick::getButtonUp(id, buttonId));
    return 1;
}

int JoystickExporter::getAxisPosition(lua_State *L)
{
    int arg_count = lua_gettop(L);
    unsigned int id = luaL_checkinteger(L, 1);
    sfex::Joystick::Axis axis = static_cast<sfex::Joystick::Axis>( luaL_checkinteger(L, 2) );
    float minSensitivity = 0.0f;
    
    if(arg_count > 2)
    {
        minSensitivity = luaL_checknumber(L, 3);
    }

    lua_pushnumber(L, sfex::Joystick::getAxisPosition(id, axis, minSensitivity));
    return 1;
}

LuaExporter JoystickExporter::toLuaExporter()
{
    LuaExporter exporter(
        LUA_JOYSTICK_CLASSNAME,
        nullptr,
        {
            {"isConnected", JoystickExporter::isConnected},
            {"getButtonCount", JoystickExporter::getButtonCount},
            {"hasAxis", JoystickExporter::hasAxis},
            {"getButton", JoystickExporter::getButton},
            {"getButtonDown", JoystickExporter::getButtonDown},
            {"getButtonUp", JoystickExporter::getButtonUp},
            {"getAxisPosition", JoystickExporter::getAxisPosition},
        },
        {
            
        }
    );

    exporter.addInteger("Axis_X", sfex::Joystick::Axis::X);
    exporter.addInteger("Axis_Y", sfex::Joystick::Axis::Y);
    exporter.addInteger("Axis_Z", sfex::Joystick::Axis::Z);
    exporter.addInteger("Axis_R", sfex::Joystick::Axis::R);
    exporter.addInteger("Axis_U", sfex::Joystick::Axis::U);
    exporter.addInteger("Axis_V", sfex::Joystick::Axis::V);
    exporter.addInteger("AxisPov_X", sfex::Joystick::Axis::PovX);
    exporter.addInteger("AxisPov_Y", sfex::Joystick::Axis::PovY);

    exporter.addInteger("Count", sfex::Joystick::Count);
    exporter.addInteger("AxisCount", sfex::Joystick::AxisCount);
    exporter.addInteger("ButtonCount", sfex::Joystick::ButtonCount);

    return exporter;
}