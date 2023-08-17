#pragma once

#include <filesystem>
#include <SFML/Audio.hpp>
#include <lua.hpp>

#define LUA_SOUND_CLASSNAME "Sound"
#define LUA_SOUND_METATABLENAME LUA_SOUND_CLASSNAME"_metatable"
typedef sf::Sound Lua_Sound;

class LuaExporter;
struct SoundExporter
{
    static void createSound(lua_State* L, const Lua_Sound& sound);
    static int __new(lua_State* L);
    static int __destroy(lua_State* L);
    static int __index(lua_State* L);

    static int play(lua_State* L);
    static int pause(lua_State* L);
    static int stop(lua_State* L);
    static int setBuffer(lua_State* L);
    static int setLoop(lua_State* L);
    static int setPlayingOffset(lua_State* L);
    static int getBuffer(lua_State* L);
    static int getLoop(lua_State* L);
    static int getPlayingOffset(lua_State* L);
    static int getStatus(lua_State* L);
    static int resetBuffer(lua_State* L);
    static int setPitch(lua_State* L);
    static int setVolume(lua_State* L);
    static int setPosition(lua_State* L);
    static int setRelativeToListener(lua_State* L);
    static int setMinDistance(lua_State* L);
    static int setAttenuation(lua_State* L);
    static int getPitch(lua_State* L);
    static int getVolume(lua_State* L);
    static int getPosition(lua_State* L);
    static int isRelativeToListener(lua_State* L);
    static int getMinDistance(lua_State* L);
    static int getAttenuation(lua_State* L);

    static LuaExporter toLuaExporter();
};