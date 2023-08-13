#include <Modding/Exporters/ContextSettingsExporter.hpp>
#include <Modding/LuaExporter.hpp>

void ContextSettingsExporter::createContextSetting(lua_State *L, const Lua_ContextSettings& settings)
{
    void* data = lua_newuserdata(L, sizeof(Lua_ContextSettings));
    new (data) Lua_ContextSettings(settings);
    luaL_getmetatable(L, LUA_CONTEXTSETTINGS_METATABLENAME);
    lua_setmetatable(L, -2);
}

int ContextSettingsExporter::__new(lua_State *L)
{
    int arg_count = lua_gettop(L);

    lua_Integer depthBits = 0;
    lua_Integer stencilBits = 0;
    lua_Integer antialiasingLevel = 0;
    lua_Integer majorVersion = 1;
    lua_Integer minorVersion = 1;
    lua_Integer attributeFlags = sf::ContextSettings::Attribute::Default;
    bool sRgbCapable = false;

    if(arg_count >= 1) lua_numbertointeger(luaL_checkinteger(L, 1), &depthBits);
    if(arg_count >= 2) lua_numbertointeger(luaL_checkinteger(L, 2), &stencilBits);
    if(arg_count >= 3) lua_numbertointeger(luaL_checkinteger(L, 3), &antialiasingLevel);
    if(arg_count >= 4) lua_numbertointeger(luaL_checkinteger(L, 4), &majorVersion);
    if(arg_count >= 5) lua_numbertointeger(luaL_checkinteger(L, 5), &minorVersion);
    if(arg_count >= 6) lua_numbertointeger(luaL_checkinteger(L, 6), &attributeFlags);
    if(arg_count >= 7) lua_toboolean(L, 7);

    createContextSetting(L, sf::ContextSettings(depthBits, stencilBits, antialiasingLevel, majorVersion, minorVersion, attributeFlags, sRgbCapable));
    return 1;
}

int ContextSettingsExporter::__destroy(lua_State *L)
{
    Lua_ContextSettings* contextSettingsPtr = static_cast<Lua_ContextSettings*>( luaL_checkudata(L, 1, LUA_CONTEXTSETTINGS_METATABLENAME) );
    contextSettingsPtr->~Lua_ContextSettings();
    return 0;
}

int ContextSettingsExporter::__index(lua_State *L)
{
    Lua_ContextSettings* contextSettingsPtr = static_cast<Lua_ContextSettings*>( luaL_checkudata(L, 1, LUA_CONTEXTSETTINGS_METATABLENAME) );
    std::string indexStr = luaL_checkstring(L, 2);

    if(indexStr == "depthBits")
    {
        lua_pushinteger(L, contextSettingsPtr->depthBits);
        return 1;
    }
    else if(indexStr == "stencilBits")
    {
        lua_pushinteger(L, contextSettingsPtr->stencilBits);
        return 1;
    }
    else if(indexStr == "antialiasingLevel")
    {
        lua_pushinteger(L, contextSettingsPtr->antialiasingLevel);
        return 1;
    }
    else if(indexStr == "majorVersion")
    {
        lua_pushinteger(L, contextSettingsPtr->majorVersion);
        return 1;
    }
    else if(indexStr == "minorVersion")
    {
        lua_pushinteger(L, contextSettingsPtr->minorVersion);
        return 1;
    }
    else if(indexStr == "attributeFlags")
    {
        lua_pushinteger(L, contextSettingsPtr->attributeFlags);
        return 1;
    }
    else if(indexStr == "sRgbCapable")
    {
        lua_pushboolean(L, contextSettingsPtr->sRgbCapable);
        return 1;
    }
    else if(indexStr == "Attribute_Default")
    {
        lua_pushinteger(L, Lua_ContextSettings::Attribute::Default);
        return 1;
    }
    else if(indexStr == "Attribute_Core")
    {
        lua_pushinteger(L, Lua_ContextSettings::Attribute::Core);
        return 1;
    }
    else if(indexStr == "Attribute_Debug")
    {
        lua_pushinteger(L, Lua_ContextSettings::Attribute::Debug);
        return 1;
    }

    lua_getglobal(L, LUA_CONTEXTSETTINGS_CLASSNAME);
    lua_pushstring(L, indexStr.c_str());
    lua_rawget(L, -2);
    return 1;
}

int ContextSettingsExporter::__newindex(lua_State *L)
{
    Lua_ContextSettings* contextSettingsPtr = static_cast<Lua_ContextSettings*>( luaL_checkudata(L, 1, LUA_CONTEXTSETTINGS_METATABLENAME) );
    std::string indexStr = luaL_checkstring(L, 2);

    if(indexStr == "depthBits")
    {
        lua_numbertointeger(luaL_checknumber(L, 3), &contextSettingsPtr->depthBits);
        return 0;
    }
    else if(indexStr == "stencilBits")
    {
        lua_numbertointeger(luaL_checknumber(L, 3), &contextSettingsPtr->stencilBits);
        return 0;
    }
    else if(indexStr == "antialiasingLevel")
    {
        lua_numbertointeger(luaL_checknumber(L, 3), &contextSettingsPtr->antialiasingLevel);
        return 0;
    }
    else if(indexStr == "majorVersion")
    {
        lua_numbertointeger(luaL_checknumber(L, 3), &contextSettingsPtr->majorVersion);
        return 0;
    }
    else if(indexStr == "minorVersion")
    {
        lua_numbertointeger(luaL_checknumber(L, 3), &contextSettingsPtr->minorVersion);
        return 0;
    }
    else if(indexStr == "attributeFlags")
    {
        lua_numbertointeger(luaL_checknumber(L, 3), &contextSettingsPtr->attributeFlags);
        return 0;
    }
    else if(indexStr == "sRgbCapable")
    {
        contextSettingsPtr->sRgbCapable = lua_toboolean(L, 3);
        return 0;
    }

    luaL_error(L, "Cannot set value for %s", indexStr.c_str());
    return 0;
}

LuaExporter ContextSettingsExporter::toLuaExporter()
{
    LuaExporter exporter(
        LUA_CONTEXTSETTINGS_CLASSNAME,
        __new,
        {},
        {
            {"__new", ContextSettingsExporter::__new},
            {"__destroy", ContextSettingsExporter::__destroy},
            {"__index", ContextSettingsExporter::__index},
            {"__newindex", ContextSettingsExporter::__newindex},
        }
    );

    exporter.addInteger("Attribute_Default", Lua_ContextSettings::Attribute::Default);
    exporter.addInteger("Attribute_Core", Lua_ContextSettings::Attribute::Core);
    exporter.addInteger("Attribute_Debug", Lua_ContextSettings::Attribute::Debug);

    return exporter;
}