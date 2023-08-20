#include <Modding/Exporters/SoundBufferExporter.hpp>
#include <Modding/LuaExporter.hpp>

void SoundBufferExporter::createSoundBuffer(lua_State* L, const Lua_SoundBuffer& soundBuffer)
{
    void* data = lua_newuserdata(L, sizeof(Lua_SoundBuffer));
    new (data) Lua_SoundBuffer(soundBuffer);
    luaL_getmetatable(L, LUA_SOUNDBUFFER_METATABLENAME);
    lua_setmetatable(L, -2);
}

int SoundBufferExporter::__new(lua_State *L)
{
    int arg_count = lua_gettop(L);
    if(arg_count == 1)
    {
        Lua_SoundBuffer* soundBufferPtr = static_cast<Lua_SoundBuffer*>( luaL_checkudata(L, 1, LUA_SOUNDBUFFER_METATABLENAME) );
        createSoundBuffer(L, *soundBufferPtr);
        return 1;
    }
    createSoundBuffer(L, Lua_SoundBuffer());

    return 1;
}

int SoundBufferExporter::__destroy(lua_State *L)
{
    Lua_SoundBuffer* soundBufferPtr = static_cast<Lua_SoundBuffer*>( luaL_checkudata(L, 1, LUA_SOUNDBUFFER_METATABLENAME) );
    soundBufferPtr->~Lua_SoundBuffer();
    return 0;
}

int SoundBufferExporter::__index(lua_State* L)
{
    Lua_SoundBuffer* soundBufferPtr = static_cast<Lua_SoundBuffer*>( luaL_checkudata(L, 1, LUA_SOUNDBUFFER_METATABLENAME) );
    std::string indexStr = lua_tostring(L, 2);

    lua_getglobal(L, LUA_SOUNDBUFFER_CLASSNAME);
    lua_pushstring(L, indexStr.c_str());
    lua_rawget(L, -2);
    return 1;
}

int SoundBufferExporter::loadFromFile(lua_State* L)
{
    Lua_SoundBuffer* soundBufferPtr = static_cast<Lua_SoundBuffer*>( luaL_checkudata(L, 1, LUA_SOUNDBUFFER_METATABLENAME) );
    std::string filename = lua_tostring(L, 2);
    lua_getglobal(L, ASSETSPATH_VARNAME);
    std::filesystem::path totalPath = lua_tostring(L, -1);
    totalPath /= filename;
    bool result = soundBufferPtr->loadFromFile(totalPath.string());
    lua_pushboolean(L, result);

    return 1;
}

int SoundBufferExporter::saveToFile(lua_State* L)
{
    Lua_SoundBuffer* soundBufferPtr = static_cast<Lua_SoundBuffer*>( luaL_checkudata(L, 1, LUA_SOUNDBUFFER_METATABLENAME) );
    std::string filename = lua_tostring(L, 2);
    lua_getglobal(L, ASSETSPATH_VARNAME);
    std::filesystem::path totalPath = lua_tostring(L, -1);
    totalPath /= filename;
    bool result = soundBufferPtr->saveToFile(totalPath.string());
    lua_pushboolean(L, result);

    return 1;
}

int SoundBufferExporter::getSamples(lua_State* L)
{
    Lua_SoundBuffer* soundBufferPtr = static_cast<Lua_SoundBuffer*>( luaL_checkudata(L, 1, LUA_SOUNDBUFFER_METATABLENAME) );
    int arr_len = soundBufferPtr->getSampleCount();
    lua_newtable(L);
    for(int i = 0; i < arr_len; ++i)
    {
        lua_pushinteger(L, soundBufferPtr->getSamples()[i]);
        lua_rawseti(L, -2, i + 1);
    }

    return 1;
}

int SoundBufferExporter::getSampleCount(lua_State* L)
{
    Lua_SoundBuffer* soundBufferPtr = static_cast<Lua_SoundBuffer*>( luaL_checkudata(L, 1, LUA_SOUNDBUFFER_METATABLENAME) );
    lua_pushinteger(L, soundBufferPtr->getSampleCount());
    return 1;
}

int SoundBufferExporter::getSampleRate(lua_State* L)
{
    Lua_SoundBuffer* soundBufferPtr = static_cast<Lua_SoundBuffer*>( luaL_checkudata(L, 1, LUA_SOUNDBUFFER_METATABLENAME) );
    lua_pushinteger(L, soundBufferPtr->getSampleRate());
    return 1;
}

int SoundBufferExporter::getChannelCount(lua_State* L)
{
    Lua_SoundBuffer* soundBufferPtr = static_cast<Lua_SoundBuffer*>( luaL_checkudata(L, 1, LUA_SOUNDBUFFER_METATABLENAME) );
    lua_pushinteger(L, soundBufferPtr->getChannelCount());
    return 1;
}

int SoundBufferExporter::getDuration(lua_State* L)
{
    Lua_SoundBuffer* soundBufferPtr = static_cast<Lua_SoundBuffer*>( luaL_checkudata(L, 1, LUA_SOUNDBUFFER_METATABLENAME) );
    lua_pushnumber(L, soundBufferPtr->getDuration().asSeconds());
    return 1;
}

LuaExporter SoundBufferExporter::toLuaExporter()
{
    LuaExporter exporter(
        LUA_SOUNDBUFFER_CLASSNAME,
        __new,
        {
            {"loadFromFile", SoundBufferExporter::loadFromFile},
            {"saveToFile", SoundBufferExporter::saveToFile},
            {"getSamples", SoundBufferExporter::getSamples},
            {"getSampleCount", SoundBufferExporter::getSampleCount},
            {"getSampleRate", SoundBufferExporter::getSampleRate},
            {"getChannelCount", SoundBufferExporter::getChannelCount},
            {"getDuration", SoundBufferExporter::getDuration},
        },
        {
            {"__gc", SoundBufferExporter::__destroy},
            {"__index", SoundBufferExporter::__index},
        }
    );

    return exporter;
}
