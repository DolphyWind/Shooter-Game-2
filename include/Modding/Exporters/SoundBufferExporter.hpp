#pragma once

#include <filesystem>
#include <SFML/Audio.hpp>
#include <lua.hpp>

#define LUA_SOUNDBUFFER_CLASSNAME "SoundBuffer"
#define LUA_SOUNDBUFFER_METATABLENAME LUA_SOUNDBUFFER_CLASSNAME"_metatable"
typedef sf::SoundBuffer Lua_SoundBuffer;

class LuaExporter;
struct SoundBufferExporter
{
    static void createSoundBuffer(lua_State* L, const Lua_SoundBuffer& soundBuffer);
    static int __new(lua_State* L);
    static int __destroy(lua_State* L);
    static int __index(lua_State* L);

    static int loadFromFile(lua_State* L);
    static int saveToFile(lua_State* L);
    static int getSamples(lua_State* L);
    static int getSampleCount(lua_State* L);
    static int getSampleRate(lua_State* L);
    static int getChannelCount(lua_State* L);
    static int getDuration(lua_State* L);

    static LuaExporter toLuaExporter();
};