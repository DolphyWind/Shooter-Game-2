#include <Modding/Exporters/VideoModeExporter.hpp>
#include <Modding/LuaExporter.hpp>

void VideoModeExporter::createVideoMode(lua_State *L, const Lua_VideoMode &videoMode)
{
    void* data = lua_newuserdata(L, sizeof(Lua_VideoMode));
    new (data) Lua_VideoMode(videoMode);
    luaL_getmetatable(L, LUA_VIDEOMODE_METATABLENAME);
    lua_setmetatable(L, -2);
}

int VideoModeExporter::__new(lua_State *L)
{
    int arg_count = lua_gettop(L);
    if(arg_count == 0)
    {
        createVideoMode(L, Lua_VideoMode());
        return 1;
    }
    else if(arg_count == 2)
    {
        lua_Integer modeWidth;
        lua_Integer modeHeight;
        lua_numbertointeger(luaL_checknumber(L, 1), &modeWidth);
        lua_numbertointeger(luaL_checknumber(L, 2), &modeHeight);

        createVideoMode(L, Lua_VideoMode(modeWidth, modeHeight));
        return 1;
    }
    else if(arg_count == 3)
    {
        lua_Integer modeWidth;
        lua_Integer modeHeight;
        lua_Integer modeBitsPerPixel;
        lua_numbertointeger(luaL_checknumber(L, 1), &modeWidth);
        lua_numbertointeger(luaL_checknumber(L, 2), &modeHeight);
        lua_numbertointeger(luaL_checknumber(L, 3), &modeBitsPerPixel);

        createVideoMode(L, Lua_VideoMode(modeWidth, modeHeight, modeBitsPerPixel));
        return 1;
    }

    luaL_error(L, "You cant create a videoMode with this amount of arguments!");
    return 0;
}

int VideoModeExporter::__destroy(lua_State *L)
{
    Lua_VideoMode* videoModePtr = static_cast<Lua_VideoMode*>( luaL_checkudata(L, 1, LUA_VIDEOMODE_METATABLENAME) );
    videoModePtr->~Lua_VideoMode();
    return 0;
}

int VideoModeExporter::__index(lua_State *L)
{
    Lua_VideoMode* videoModePtr = static_cast<Lua_VideoMode*>( luaL_checkudata(L, 1, LUA_VIDEOMODE_METATABLENAME) );
    std::string indexStr = luaL_checkstring(L, 2);

    if(indexStr == "width")
    {
        lua_pushinteger(L, videoModePtr->width);
        return 1;
    }
    else if(indexStr == "height")
    {
        lua_pushinteger(L, videoModePtr->height);
        return 1;
    }
    else if(indexStr == "bitsPerPixel")
    {
        lua_pushinteger(L, videoModePtr->bitsPerPixel);
        return 1;
    }

    lua_getglobal(L, LUA_VIDEOMODE_CLASSNAME);
    lua_pushstring(L, indexStr.c_str());
    lua_rawget(L, -2);
    return 1;
}

int VideoModeExporter::__newindex(lua_State *L)
{
    Lua_VideoMode* videoModePtr = static_cast<Lua_VideoMode*>( luaL_checkudata(L, 1, LUA_VIDEOMODE_METATABLENAME) );
    std::string indexStr = luaL_checkstring(L, 2);

    if(indexStr == "width")
    {
        lua_numbertointeger(luaL_checknumber(L, 3), &videoModePtr->width);
        return 0;
    }
    else if(indexStr == "height")
    {
        lua_numbertointeger(luaL_checknumber(L, 3), &videoModePtr->height);
        return 0;
    }
    else if(indexStr == "bitsPerPixel")
    {
        lua_numbertointeger(luaL_checknumber(L, 3), &videoModePtr->bitsPerPixel);
        return 0;
    }

    luaL_error(L, "Cannot set a value for %s", indexStr.c_str());
    return 0;
}

int VideoModeExporter::__eq(lua_State *L)
{
    Lua_VideoMode* firstVideoModePtr = static_cast<Lua_VideoMode*>( luaL_checkudata(L, 1, LUA_VIDEOMODE_METATABLENAME) );
    Lua_VideoMode* secondVideoModePtr = static_cast<Lua_VideoMode*>( luaL_checkudata(L, 2, LUA_VIDEOMODE_METATABLENAME) );
    lua_pushboolean(L, (*firstVideoModePtr) == (*secondVideoModePtr));
    return 1;
}

int VideoModeExporter::__lt(lua_State *L)
{
    Lua_VideoMode* firstVideoModePtr = static_cast<Lua_VideoMode*>( luaL_checkudata(L, 1, LUA_VIDEOMODE_METATABLENAME) );
    Lua_VideoMode* secondVideoModePtr = static_cast<Lua_VideoMode*>( luaL_checkudata(L, 2, LUA_VIDEOMODE_METATABLENAME) );
    lua_pushboolean(L, (*firstVideoModePtr) < (*secondVideoModePtr));
    return 1;
}

int VideoModeExporter::__le(lua_State *L)
{
    Lua_VideoMode* firstVideoModePtr = static_cast<Lua_VideoMode*>( luaL_checkudata(L, 1, LUA_VIDEOMODE_METATABLENAME) );
    Lua_VideoMode* secondVideoModePtr = static_cast<Lua_VideoMode*>( luaL_checkudata(L, 2, LUA_VIDEOMODE_METATABLENAME) );
    lua_pushboolean(L, (*firstVideoModePtr) <= (*secondVideoModePtr));
    return 1;
}

int VideoModeExporter::isValid(lua_State *L)
{
    Lua_VideoMode* videoModePtr = static_cast<Lua_VideoMode*>( luaL_checkudata(L, 1, LUA_VIDEOMODE_METATABLENAME) );
    lua_pushboolean(L, videoModePtr->isValid());
    return 1;
}

LuaExporter VideoModeExporter::toLuaExporter()
{
    LuaExporter exporter(
        LUA_VIDEOMODE_CLASSNAME,
        VideoModeExporter::__new,
        {
            {"isValid", VideoModeExporter::isValid},
        },
        {
            {"__gc", VideoModeExporter::__destroy},
            {"__index", VideoModeExporter::__index},
            {"__newindex", VideoModeExporter::__newindex},
            {"__eq", VideoModeExporter::__eq},
            {"__lt", VideoModeExporter::__lt},
            {"__le", VideoModeExporter::__le},
        }
    );

    return exporter;
}