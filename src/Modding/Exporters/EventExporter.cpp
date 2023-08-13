#include <Modding/Exporters/EventExporter.hpp>
#include <Modding/LuaExporter.hpp>

void EventExporter::createEvent(lua_State *L, const Lua_Event& event)
{
    void* data = lua_newuserdata(L, sizeof(Lua_Event));
    new (data) Lua_Event(event);
    luaL_getmetatable(L, LUA_EVENT_METATABLENAME);
    lua_setmetatable(L, -2);
}

int EventExporter::__new(lua_State *L)
{
    createEvent(L, Lua_Event());
    return 1;
}

int EventExporter::__destroy(lua_State *L)
{
    Lua_Event* eventPtr = static_cast<Lua_Event*>( luaL_checkudata(L, 1, LUA_EVENT_CLASSNAME) );
    eventPtr->~Lua_Event();
    return 0;
}

int EventExporter::__index(lua_State *L)
{
    Lua_Event* eventPtr = static_cast<Lua_Event*>( luaL_checkudata(L, 1, LUA_EVENT_METATABLENAME) );
    std::string indexStr = luaL_checkstring(L, 2);

    if(indexStr == "type")
    {
        lua_pushinteger(L, eventPtr->type);
        return 1;
    }
    else if(indexStr == "size_width")
    {
        lua_pushinteger(L, eventPtr->size.width);
        return 1;
    }
    else if(indexStr == "size_height")
    {
        lua_pushinteger(L, eventPtr->size.height);
        return 1;
    }
    else if(indexStr == "key_code")
    {
        lua_pushinteger(L, eventPtr->key.code);
        return 1;
    }
    else if(indexStr == "key_alt")
    {
        lua_pushboolean(L, eventPtr->key.alt);
        return 1;
    }
    else if(indexStr == "key_control")
    {
        lua_pushboolean(L, eventPtr->key.control);
        return 1;
    }
    else if(indexStr == "key_shift")
    {
        lua_pushboolean(L, eventPtr->key.shift);
        return 1;
    }
    else if(indexStr == "key_system")
    {
        lua_pushboolean(L, eventPtr->key.system);
        return 1;
    }
    else if(indexStr == "text_unicode")
    {
        lua_pushinteger(L, eventPtr->text.unicode);
        return 1;
    }
    else if(indexStr == "mouseMove_x")
    {
        lua_pushinteger(L, eventPtr->mouseMove.x);
        return 1;
    }
    else if(indexStr == "mouseMove_y")
    {
        lua_pushinteger(L, eventPtr->mouseMove.y);
        return 1;
    }
    else if(indexStr == "mouseButton_button")
    {
        lua_pushinteger(L, eventPtr->mouseButton.button);
        return 1;
    }
    else if(indexStr == "mouseButton_x")
    {
        lua_pushinteger(L, eventPtr->mouseButton.x);
        return 1;
    }
    else if(indexStr == "mouseButton_y")
    {
        lua_pushinteger(L, eventPtr->mouseButton.y);
        return 1;
    }
    else if(indexStr == "mouseWheel_delta")
    {
        lua_pushnumber(L, eventPtr->mouseWheel.delta);
        return 1;
    }
    else if(indexStr == "mouseWheel_x")
    {
        lua_pushnumber(L, eventPtr->mouseWheel.x);
        return 1;
    }
    else if(indexStr == "mouseWheel_y")
    {
        lua_pushnumber(L, eventPtr->mouseWheel.y);
        return 1;
    }
    else if(indexStr == "mouseWheelScroll_wheel")
    {
        lua_pushnumber(L, eventPtr->mouseWheelScroll.wheel);
        return 1;
    }
    else if(indexStr == "mouseWheel_delta")
    {
        lua_pushnumber(L, eventPtr->mouseWheelScroll.delta);
        return 1;
    }
    else if(indexStr == "mouseWheel_x")
    {
        lua_pushnumber(L, eventPtr->mouseWheelScroll.x);
        return 1;
    }
    else if(indexStr == "mouseWheel_y")
    {
        lua_pushnumber(L, eventPtr->mouseWheelScroll.y);
        return 1;
    }
    else if(indexStr == "joystickMove_joystickId")
    {
        lua_pushinteger(L, eventPtr->joystickMove.joystickId);
        return 1;
    }
    else if(indexStr == "joystickMove_axis")
    {
        lua_pushinteger(L, eventPtr->joystickMove.axis);
        return 1;
    }
    else if(indexStr == "joystickMove_position")
    {
        lua_pushnumber(L, eventPtr->joystickMove.position);
        return 1;
    }
    else if(indexStr == "joystickButton_joystickId")
    {
        lua_pushinteger(L, eventPtr->joystickButton.joystickId);
        return 1;
    }
    else if(indexStr == "joystickButton_button")
    {
        lua_pushinteger(L, eventPtr->joystickButton.button);
        return 1;
    }
    else if(indexStr == "joystickConnect_joystickId")
    {
        lua_pushinteger(L, eventPtr->joystickConnect.joystickId);
        return 1;
    }
    else if(indexStr == "touch_finger")
    {
        lua_pushinteger(L, eventPtr->touch.finger);
        return 1;
    }
    else if(indexStr == "touch_x")
    {
        lua_pushinteger(L, eventPtr->touch.x);
        return 1;
    }
    else if(indexStr == "touch_y")
    {
        lua_pushinteger(L, eventPtr->touch.y);
        return 1;
    }

    lua_getglobal(L, LUA_EVENT_CLASSNAME);
    lua_pushstring(L, indexStr.c_str());
    lua_rawget(L, -2);
    return 1;
}

LuaExporter EventExporter::toLuaExporter()
{
    LuaExporter exporter(
        LUA_EVENT_CLASSNAME,
        __new,
        {

        },
        {
            {"__gc", EventExporter::__destroy},
            {"__index", EventExporter::__index},
        }
    );

    exporter.addInteger("EventType_Closed", sf::Event::Closed);
    exporter.addInteger("EventType_Resized", sf::Event::Resized);
    exporter.addInteger("EventType_LostFocus", sf::Event::LostFocus);
    exporter.addInteger("EventType_GainedFocus", sf::Event::GainedFocus);
    exporter.addInteger("EventType_TextEntered", sf::Event::TextEntered);
    exporter.addInteger("EventType_KeyPressed", sf::Event::KeyPressed);
    exporter.addInteger("EventType_KeyReleased", sf::Event::KeyReleased);
    exporter.addInteger("EventType_MouseWheelMoved", sf::Event::MouseWheelMoved);
    exporter.addInteger("EventType_MouseWheelScrolled", sf::Event::MouseWheelScrolled);
    exporter.addInteger("EventType_MouseButtonPressed", sf::Event::MouseButtonPressed);
    exporter.addInteger("EventType_MouseButtonReleased", sf::Event::MouseButtonReleased);
    exporter.addInteger("EventType_MouseMoved", sf::Event::MouseMoved);
    exporter.addInteger("EventType_MouseEntered", sf::Event::MouseEntered);
    exporter.addInteger("EventType_MouseLeft", sf::Event::MouseLeft);
    exporter.addInteger("EventType_JoystickButtonPressed", sf::Event::JoystickButtonPressed);
    exporter.addInteger("EventType_JoystickButtonReleased", sf::Event::JoystickButtonReleased);
    exporter.addInteger("EventType_JoystickMoved", sf::Event::JoystickMoved);
    exporter.addInteger("EventType_JoystickConnected", sf::Event::JoystickConnected);
    exporter.addInteger("EventType_JoystickDisconnected", sf::Event::JoystickDisconnected);
    exporter.addInteger("EventType_TouchBegan", sf::Event::TouchBegan);
    exporter.addInteger("EventType_TouchMoved", sf::Event::TouchMoved);
    exporter.addInteger("EventType_TouchEnded", sf::Event::TouchEnded);
    exporter.addInteger("EventType_SensorChanged", sf::Event::SensorChanged);
    exporter.addInteger("EventType_Count", sf::Event::Count);

    return exporter;
}