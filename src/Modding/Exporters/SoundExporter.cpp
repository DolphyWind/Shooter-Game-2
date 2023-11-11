#include <Modding/Exporters/SoundExporter.hpp>
#include <Modding/Exporters/SoundBufferExporter.hpp>
#include <Modding/Exporters/Vector2Exporter.hpp>
#include <Modding/LuaExporter.hpp>
#include <Modding/LuaHelper.hpp>

void SoundExporter::createSound(lua_State* L, const Lua_Sound& sound)
{
    void* data = lua_newuserdata(L, sizeof(Lua_Sound));
    new (data) Lua_Sound(sound);
    luaL_getmetatable(L, LUA_SOUND_METATABLENAME);
    lua_setmetatable(L, -2);
}

int SoundExporter::__new(lua_State *L)
{
    int arg_count = lua_gettop(L);
    if(arg_count == 1)
    {
        if(LuaHelper::checkudata_orNull(L, 1, LUA_SOUND_METATABLENAME))
        {
            Lua_Sound* soundPtr = static_cast<Lua_Sound*>( LuaHelper::checkudata_WithError(L, 1, LUA_SOUND_METATABLENAME) );
            createSound(L, *soundPtr);
            return 1;
        }
        else if(LuaHelper::checkudata_orNull(L, 1, LUA_SOUNDBUFFER_METATABLENAME))
        {
            Exported_SoundBuffer* soundBufferPtr = static_cast<Exported_SoundBuffer*>( LuaHelper::checkudata_WithError(L, 1, LUA_SOUNDBUFFER_METATABLENAME) );
            createSound(L, Lua_Sound(*soundBufferPtr));
            return 1;
        }
    }
    createSound(L, Lua_Sound());

    return 1;
}

int SoundExporter::__destroy(lua_State *L)
{
    Lua_Sound* soundPtr = static_cast<Lua_Sound*>( LuaHelper::checkudata_WithError(L, 1, LUA_SOUND_METATABLENAME) );
    soundPtr->~Lua_Sound();
    return 0;
}

int SoundExporter::__index(lua_State* L)
{
    Lua_Sound* soundPtr = static_cast<Lua_Sound*>( LuaHelper::checkudata_WithError(L, 1, LUA_SOUND_METATABLENAME) );
    std::string indexStr = lua_tostring(L, 2);

    if(indexStr == "Status_Stopped")
    {
        lua_pushinteger(L, Lua_Sound::Status::Stopped);
        return 1;
    }
    else if(indexStr == "Status_Paused")
    {
        lua_pushinteger(L, Lua_Sound::Status::Paused);
        return 1;
    }
    else if(indexStr == "Status_Playing")
    {
        lua_pushinteger(L, Lua_Sound::Status::Playing);
        return 1;
    }

    lua_getglobal(L, LUA_SOUND_CLASSNAME);
    lua_pushstring(L, indexStr.c_str());
    lua_rawget(L, -2);
    return 1;
}

int SoundExporter::play(lua_State* L)
{
    Lua_Sound* soundPtr = static_cast<Lua_Sound*>( LuaHelper::checkudata_WithError(L, 1, LUA_SOUND_METATABLENAME) );
    soundPtr->play();
    return 0;
}

int SoundExporter::pause(lua_State* L)
{
    Lua_Sound* soundPtr = static_cast<Lua_Sound*>( LuaHelper::checkudata_WithError(L, 1, LUA_SOUND_METATABLENAME) );
    soundPtr->pause();
    return 0;
}

int SoundExporter::stop(lua_State* L)
{
    Lua_Sound* soundPtr = static_cast<Lua_Sound*>( LuaHelper::checkudata_WithError(L, 1, LUA_SOUND_METATABLENAME) );
    soundPtr->stop();
    return 0;
}

int SoundExporter::setBuffer(lua_State* L)
{
    Lua_Sound* soundPtr = static_cast<Lua_Sound*>( LuaHelper::checkudata_WithError(L, 1, LUA_SOUND_METATABLENAME) );
    Exported_SoundBuffer* soundBufferPtr = static_cast<Exported_SoundBuffer*>( LuaHelper::checkudata_WithError(L, 1, LUA_SOUNDBUFFER_METATABLENAME) );
    soundPtr->setBuffer(*soundBufferPtr);
    return 0;
}

int SoundExporter::setLoop(lua_State* L)
{
    Lua_Sound* soundPtr = static_cast<Lua_Sound*>( LuaHelper::checkudata_WithError(L, 1, LUA_SOUND_METATABLENAME) );
    bool loop = lua_toboolean(L, 2);
    soundPtr->setLoop(loop);
    return 0;
}

int SoundExporter::setPlayingOffset(lua_State* L)
{
    Lua_Sound* soundPtr = static_cast<Lua_Sound*>( LuaHelper::checkudata_WithError(L, 1, LUA_SOUND_METATABLENAME) );
    lua_Number timeOffset = luaL_checknumber(L, 2);
    soundPtr->setPlayingOffset(sf::seconds(timeOffset));
    return 0;
}

int SoundExporter::getBuffer(lua_State* L)
{
    Lua_Sound* soundPtr = static_cast<Lua_Sound*>( LuaHelper::checkudata_WithError(L, 1, LUA_SOUND_METATABLENAME) );
    LuaHelper::push(L, soundPtr->getBuffer());
    return 1;
}

int SoundExporter::getLoop(lua_State* L)
{
    Lua_Sound* soundPtr = static_cast<Lua_Sound*>( LuaHelper::checkudata_WithError(L, 1, LUA_SOUND_METATABLENAME) );
    lua_pushboolean(L, soundPtr->getLoop());
    return 1;
}

int SoundExporter::getPlayingOffset(lua_State* L)
{
    Lua_Sound* soundPtr = static_cast<Lua_Sound*>( LuaHelper::checkudata_WithError(L, 1, LUA_SOUND_METATABLENAME) );
    lua_pushnumber(L, soundPtr->getPlayingOffset().asSeconds());
    return 1;
}

int SoundExporter::getStatus(lua_State* L)
{
    Lua_Sound* soundPtr = static_cast<Lua_Sound*>( LuaHelper::checkudata_WithError(L, 1, LUA_SOUND_METATABLENAME) );
    lua_pushinteger(L, (lua_Integer)soundPtr->getStatus());
    return 1;
}

int SoundExporter::resetBuffer(lua_State* L)
{
    Lua_Sound* soundPtr = static_cast<Lua_Sound*>( LuaHelper::checkudata_WithError(L, 1, LUA_SOUND_METATABLENAME) );
    soundPtr->resetBuffer();
    return 0;
}

int SoundExporter::setPitch(lua_State* L)
{
    Lua_Sound* soundPtr = static_cast<Lua_Sound*>( LuaHelper::checkudata_WithError(L, 1, LUA_SOUND_METATABLENAME) );
    lua_Number pitch = luaL_checknumber(L, 2);
    soundPtr->setPitch(pitch);
    return 0;
}

int SoundExporter::setVolume(lua_State* L)
{
    Lua_Sound* soundPtr = static_cast<Lua_Sound*>( LuaHelper::checkudata_WithError(L, 1, LUA_SOUND_METATABLENAME) );
    lua_Number volume = luaL_checknumber(L, 2);
    soundPtr->setVolume(volume);
    return 0;
}

int SoundExporter::setPosition(lua_State* L)
{
    Lua_Sound* soundPtr = static_cast<Lua_Sound*>( LuaHelper::checkudata_WithError(L, 1, LUA_SOUND_METATABLENAME) );
    soundPtr->setPosition(
        luaL_checknumber(L, 2),
        luaL_checknumber(L, 3),
        luaL_checknumber(L, 4)
    );
    return 0;
}

int SoundExporter::setRelativeToListener(lua_State* L)
{
    Lua_Sound* soundPtr = static_cast<Lua_Sound*>( LuaHelper::checkudata_WithError(L, 1, LUA_SOUND_METATABLENAME) );
    bool relative = lua_toboolean(L, 2);
    soundPtr->setRelativeToListener(relative);
    return 0;
}

int SoundExporter::setMinDistance(lua_State* L)
{
    Lua_Sound* soundPtr = static_cast<Lua_Sound*>( LuaHelper::checkudata_WithError(L, 1, LUA_SOUND_METATABLENAME) );
    lua_Number minDistance = luaL_checknumber(L, 2);
    soundPtr->setMinDistance(minDistance);
    return 0;
}

int SoundExporter::setAttenuation(lua_State* L)
{
    Lua_Sound* soundPtr = static_cast<Lua_Sound*>( LuaHelper::checkudata_WithError(L, 1, LUA_SOUND_METATABLENAME) );
    lua_Number attenuation = luaL_checknumber(L, 2);
    soundPtr->setAttenuation(attenuation);
    return 0;
}

int SoundExporter::getPitch(lua_State* L)
{
    Lua_Sound* soundPtr = static_cast<Lua_Sound*>( LuaHelper::checkudata_WithError(L, 1, LUA_SOUND_METATABLENAME) );
    lua_pushnumber(L, soundPtr->getPitch());
    return 1;
}

int SoundExporter::getVolume(lua_State* L)
{
    Lua_Sound* soundPtr = static_cast<Lua_Sound*>( LuaHelper::checkudata_WithError(L, 1, LUA_SOUND_METATABLENAME) );
    lua_pushnumber(L, soundPtr->getVolume());
    return 1;
}

int SoundExporter::getPosition(lua_State* L)
{
    Lua_Sound* soundPtr = static_cast<Lua_Sound*>( LuaHelper::checkudata_WithError(L, 1, LUA_SOUND_METATABLENAME) );
    lua_pushnumber(L, soundPtr->getPosition().x);
    lua_pushnumber(L, soundPtr->getPosition().y);
    lua_pushnumber(L, soundPtr->getPosition().z);
    return 3;
}

int SoundExporter::isRelativeToListener(lua_State* L)
{
    Lua_Sound* soundPtr = static_cast<Lua_Sound*>( LuaHelper::checkudata_WithError(L, 1, LUA_SOUND_METATABLENAME) );
    lua_pushboolean(L, soundPtr->isRelativeToListener());
    return 1;
}

int SoundExporter::getMinDistance(lua_State* L)
{
    Lua_Sound* soundPtr = static_cast<Lua_Sound*>( LuaHelper::checkudata_WithError(L, 1, LUA_SOUND_METATABLENAME) );
    lua_pushnumber(L, soundPtr->getMinDistance());
    return 1;
}

int SoundExporter::getAttenuation(lua_State* L)
{
    Lua_Sound* soundPtr = static_cast<Lua_Sound*>( LuaHelper::checkudata_WithError(L, 1, LUA_SOUND_METATABLENAME) );
    lua_pushnumber(L, soundPtr->getAttenuation());
    return 1;
}

LuaExporter SoundExporter::toLuaExporter()
{
    LuaExporter exporter(
        LUA_SOUND_CLASSNAME,
        __new,
        {
            {"play", SoundExporter::play},
            {"pause", SoundExporter::pause},
            {"stop", SoundExporter::stop},
            {"setBuffer", SoundExporter::setBuffer},
            {"setLoop", SoundExporter::setLoop},
            {"setPlayingOffset", SoundExporter::setPlayingOffset},
            {"getBuffer", SoundExporter::getBuffer},
            {"getLoop", SoundExporter::getLoop},
            {"getPlayingOffset", SoundExporter::getPlayingOffset},
            {"getStatus", SoundExporter::getStatus},
            {"resetBuffer", SoundExporter::resetBuffer},
            {"setPitch", SoundExporter::setPitch},
            {"setVolume", SoundExporter::setVolume},
            {"setPosition", SoundExporter::setPosition},
            {"setRelativeToListener", SoundExporter::setRelativeToListener},
            {"setMinDistance", SoundExporter::setMinDistance},
            {"setAttenuation", SoundExporter::setAttenuation},
            {"getPitch", SoundExporter::getPitch},
            {"getVolume", SoundExporter::getVolume},
            {"getPosition", SoundExporter::getPosition},
            {"isRelativeToListener", SoundExporter::isRelativeToListener},
            {"getMinDistance", SoundExporter::getMinDistance},
            {"getAttenuation", SoundExporter::getAttenuation},
        },
        {
            {"__gc", SoundExporter::__destroy},
            {"__index", SoundExporter::__index},
        }
    );

    exporter.addInteger("Status_Stopped", Lua_Sound::Status::Stopped);
    exporter.addInteger("Status_Paused", Lua_Sound::Status::Paused);
    exporter.addInteger("Status_Playing", Lua_Sound::Status::Playing);

    return exporter;
}