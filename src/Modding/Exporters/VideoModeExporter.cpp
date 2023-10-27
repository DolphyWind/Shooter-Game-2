#include <Modding/Exporters/VideoModeExporter.hpp>
#include <Modding/LuaExporter.hpp>
#include "Modding/LuaHelper.hpp"

void VideoModeExporter::createVideoMode(lua_State *L, const Exported_VideoMode &videoMode)
{
    void* data = lua_newuserdata(L, sizeof(Exported_VideoMode));
    new (data) Exported_VideoMode(videoMode);
    luaL_getmetatable(L, LUA_VIDEOMODE_METATABLENAME);
    lua_setmetatable(L, -2);
}

int VideoModeExporter::__new(lua_State *L)
{
    int arg_count = lua_gettop(L);
    if(arg_count == 0)
    {
        createVideoMode(L, Exported_VideoMode());
        return 1;
    }
    else if(arg_count == 2)
    {
        lua_Integer modeWidth;
        lua_Integer modeHeight;
        lua_numbertointeger(luaL_checknumber(L, 1), &modeWidth);
        lua_numbertointeger(luaL_checknumber(L, 2), &modeHeight);

        createVideoMode(L, Exported_VideoMode(modeWidth, modeHeight));
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

        createVideoMode(L, Exported_VideoMode(modeWidth, modeHeight, modeBitsPerPixel));
        return 1;
    }

    luaL_error(L, "You cant create a videoMode with this amount of arguments!");
    return 0;
}

int VideoModeExporter::__destroy(lua_State *L)
{
    Exported_VideoMode* videoModePtr = static_cast<Exported_VideoMode*>( LuaHelper::checkudata_WithError(L, 1, LUA_VIDEOMODE_METATABLENAME) );
    videoModePtr->~Exported_VideoMode();
    return 0;
}

int VideoModeExporter::__index(lua_State *L)
{
    Exported_VideoMode* videoModePtr = static_cast<Exported_VideoMode*>( LuaHelper::checkudata_WithError(L, 1, LUA_VIDEOMODE_METATABLENAME) );
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
    Exported_VideoMode* videoModePtr = static_cast<Exported_VideoMode*>( LuaHelper::checkudata_WithError(L, 1, LUA_VIDEOMODE_METATABLENAME) );
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
    Exported_VideoMode* firstVideoModePtr = static_cast<Exported_VideoMode*>( LuaHelper::checkudata_WithError(L, 1, LUA_VIDEOMODE_METATABLENAME) );
    Exported_VideoMode* secondVideoModePtr = static_cast<Exported_VideoMode*>( LuaHelper::checkudata_WithError(L, 2, LUA_VIDEOMODE_METATABLENAME) );
    lua_pushboolean(L, (*firstVideoModePtr) == (*secondVideoModePtr));
    return 1;
}

int VideoModeExporter::__lt(lua_State *L)
{
    Exported_VideoMode* firstVideoModePtr = static_cast<Exported_VideoMode*>( LuaHelper::checkudata_WithError(L, 1, LUA_VIDEOMODE_METATABLENAME) );
    Exported_VideoMode* secondVideoModePtr = static_cast<Exported_VideoMode*>( LuaHelper::checkudata_WithError(L, 2, LUA_VIDEOMODE_METATABLENAME) );
    lua_pushboolean(L, (*firstVideoModePtr) < (*secondVideoModePtr));
    return 1;
}

int VideoModeExporter::__le(lua_State *L)
{
    Exported_VideoMode* firstVideoModePtr = static_cast<Exported_VideoMode*>( LuaHelper::checkudata_WithError(L, 1, LUA_VIDEOMODE_METATABLENAME) );
    Exported_VideoMode* secondVideoModePtr = static_cast<Exported_VideoMode*>( LuaHelper::checkudata_WithError(L, 2, LUA_VIDEOMODE_METATABLENAME) );
    lua_pushboolean(L, (*firstVideoModePtr) <= (*secondVideoModePtr));
    return 1;
}

int VideoModeExporter::isValid(lua_State *L)
{
    Exported_VideoMode* videoModePtr = static_cast<Exported_VideoMode*>( LuaHelper::checkudata_WithError(L, 1, LUA_VIDEOMODE_METATABLENAME) );
    lua_pushboolean(L, videoModePtr->isValid());
    return 1;
}

int VideoModeExporter::getDesktopMode(lua_State* L)
{
    createVideoMode(L, Exported_VideoMode::getDesktopMode());
    return 1;
}

int VideoModeExporter::getFullscreenModes(lua_State* L)
{
    const std::vector<Exported_VideoMode>& fullscreenModes = Exported_VideoMode::getFullscreenModes();
    for (auto& mode : fullscreenModes)
    {
        createVideoMode(L, mode);
    }

    return static_cast<int>(fullscreenModes.size());
}

LuaExporter VideoModeExporter::toLuaExporter()
{
    LuaExporter exporter(
        LUA_VIDEOMODE_CLASSNAME,
        VideoModeExporter::__new,
        {
            {"isValid", VideoModeExporter::isValid},
            {"getDesktopMode", VideoModeExporter::getDesktopMode},
            {"getFullscreenModes", VideoModeExporter::getFullscreenModes},
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