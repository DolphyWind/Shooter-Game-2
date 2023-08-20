#include <Modding/Exporters/MusicExporter.hpp>
#include <Modding/LuaExporter.hpp>
#include <Modding/LuaHelper.hpp>

void MusicExporter::createMusic(lua_State* L)
{
    void* data = lua_newuserdata(L, sizeof(Lua_Music));
    new (data) Lua_Music();
    luaL_getmetatable(L, LUA_MUSIC_METATABLENAME);
    lua_setmetatable(L, -2);
}

int MusicExporter::__new(lua_State *L)
{
    createMusic(L);

    return 1;
}

int MusicExporter::__destroy(lua_State *L)
{
    Lua_Music* musicPtr = static_cast<Lua_Music*>( luaL_checkudata(L, 1, LUA_MUSIC_METATABLENAME) );
    musicPtr->~Lua_Music();
    return 0;
}

int MusicExporter::__index(lua_State* L)
{
    Lua_Music* musicPtr = static_cast<Lua_Music*>( luaL_checkudata(L, 1, LUA_MUSIC_METATABLENAME) );
    std::string indexStr = lua_tostring(L, 2);

    if(indexStr == "Status_Stopped")
    {
        lua_pushinteger(L, Lua_Music::Status::Stopped);
        return 1;
    }
    else if(indexStr == "Status_Paused")
    {
        lua_pushinteger(L, Lua_Music::Status::Paused);
        return 1;
    }
    else if(indexStr == "Status_Playing")
    {
        lua_pushinteger(L, Lua_Music::Status::Playing);
        return 1;
    }

    lua_getglobal(L, LUA_MUSIC_CLASSNAME);
    lua_pushstring(L, indexStr.c_str());
    lua_rawget(L, -2);
    return 1;
}

int MusicExporter::openFromFile(lua_State* L)
{
    Lua_Music* musicPtr = static_cast<Lua_Music*>( luaL_checkudata(L, 1, LUA_MUSIC_METATABLENAME) );
    std::string filename = lua_tostring(L, 2);
    lua_getglobal(L, ASSETSPATH_VARNAME);
    std::filesystem::path fullPath = lua_tostring(L, -1);
    fullPath /= filename;
    bool result = musicPtr->openFromFile(fullPath.string());
    lua_pushboolean(L, result);

    return 1;
}

int MusicExporter::getDuration(lua_State* L)
{
    Lua_Music* musicPtr = static_cast<Lua_Music*>( luaL_checkudata(L, 1, LUA_MUSIC_METATABLENAME) );
    lua_pushnumber(L, musicPtr->getDuration().asSeconds());
    return 1;
}

int MusicExporter::getLoopPoints(lua_State* L)
{
    Lua_Music* musicPtr = static_cast<Lua_Music*>( luaL_checkudata(L, 1, LUA_MUSIC_METATABLENAME) );
    Lua_Music::TimeSpan loopPoints = musicPtr->getLoopPoints();
    lua_pushnumber(L, loopPoints.offset.asSeconds());
    lua_pushnumber(L, loopPoints.length.asSeconds());
    return 2;
}

int MusicExporter::setLoopPoints(lua_State* L)
{
    Lua_Music* musicPtr = static_cast<Lua_Music*>( luaL_checkudata(L, 1, LUA_MUSIC_METATABLENAME) );
    lua_Number offset = luaL_checknumber(L, 2);
    lua_Number len = luaL_checknumber(L, 3);
    Lua_Music::TimeSpan loopPoints(sf::seconds(offset), sf::seconds(len));
    musicPtr->setLoopPoints(loopPoints);
    return 0;
}

int MusicExporter::play(lua_State* L)
{
    Lua_Music* musicPtr = static_cast<Lua_Music*>( luaL_checkudata(L, 1, LUA_MUSIC_METATABLENAME) );
    musicPtr->play();
    return 0;
}

int MusicExporter::pause(lua_State* L)
{
    Lua_Music* musicPtr = static_cast<Lua_Music*>( luaL_checkudata(L, 1, LUA_MUSIC_METATABLENAME) );
    musicPtr->pause();
    return 0;
}

int MusicExporter::stop(lua_State* L)
{
    Lua_Music* musicPtr = static_cast<Lua_Music*>( luaL_checkudata(L, 1, LUA_MUSIC_METATABLENAME) );
    musicPtr->stop();
    return 0;
}

int MusicExporter::getChannelCount(lua_State* L)
{
    Lua_Music* musicPtr = static_cast<Lua_Music*>( luaL_checkudata(L, 1, LUA_MUSIC_METATABLENAME) );
    lua_pushinteger(L, musicPtr->getChannelCount());
    return 1;
}

int MusicExporter::getSampleRate(lua_State* L)
{
    Lua_Music* musicPtr = static_cast<Lua_Music*>( luaL_checkudata(L, 1, LUA_MUSIC_METATABLENAME) );
    lua_pushinteger(L, musicPtr->getSampleRate());
    return 1;
}

int MusicExporter::getStatus(lua_State* L)
{
    Lua_Music* musicPtr = static_cast<Lua_Music*>( luaL_checkudata(L, 1, LUA_MUSIC_METATABLENAME) );
    lua_pushinteger(L, (int)musicPtr->getStatus());
    return 1;
}

int MusicExporter::setPlayingOffset(lua_State* L)
{
    Lua_Music* musicPtr = static_cast<Lua_Music*>( luaL_checkudata(L, 1, LUA_MUSIC_METATABLENAME) );
    lua_Number offset = luaL_checknumber(L, 2);
    musicPtr->setPlayingOffset(sf::seconds(offset));
    return 0;
}

int MusicExporter::getPlayingOffset(lua_State* L)
{
    Lua_Music* musicPtr = static_cast<Lua_Music*>( luaL_checkudata(L, 1, LUA_MUSIC_METATABLENAME) );
    lua_pushnumber(L, musicPtr->getPlayingOffset().asSeconds());
    return 1;
}

int MusicExporter::setLoop(lua_State* L)
{
    Lua_Music* musicPtr = static_cast<Lua_Music*>( luaL_checkudata(L, 1, LUA_MUSIC_METATABLENAME) );
    bool loop = lua_toboolean(L, 2);
    musicPtr->setLoop(loop);
    return 0;
}

int MusicExporter::getLoop(lua_State* L)
{
    Lua_Music* musicPtr = static_cast<Lua_Music*>( luaL_checkudata(L, 1, LUA_MUSIC_METATABLENAME) );
    lua_pushboolean(L, musicPtr->getLoop());
    return 1;
}

int MusicExporter::setPitch(lua_State* L)
{
    Lua_Music* musicPtr = static_cast<Lua_Music*>( luaL_checkudata(L, 1, LUA_MUSIC_METATABLENAME) );
    lua_Number pitch = luaL_checknumber(L, 2);
    musicPtr->setPitch(pitch);
    return 0;
}

int MusicExporter::setVolume(lua_State* L)
{
    Lua_Music* musicPtr = static_cast<Lua_Music*>( luaL_checkudata(L, 1, LUA_MUSIC_METATABLENAME) );
    lua_Number volume = luaL_checknumber(L, 2);
    musicPtr->setVolume(volume);
    return 0;
}

int MusicExporter::setPosition(lua_State* L)
{
    Lua_Music* musicPtr = static_cast<Lua_Music*>( luaL_checkudata(L, 1, LUA_MUSIC_METATABLENAME) );
    musicPtr->setPosition(
        luaL_checknumber(L, 2),
        luaL_checknumber(L, 3),
        luaL_checknumber(L, 4)
    );
    return 0;
}

int MusicExporter::setRelativeToListener(lua_State* L)
{
    Lua_Music* musicPtr = static_cast<Lua_Music*>( luaL_checkudata(L, 1, LUA_MUSIC_METATABLENAME) );
    bool relative = lua_toboolean(L, 2);
    musicPtr->setRelativeToListener(relative);
    return 0;
}

int MusicExporter::setMinDistance(lua_State* L)
{
    Lua_Music* musicPtr = static_cast<Lua_Music*>( luaL_checkudata(L, 1, LUA_MUSIC_METATABLENAME) );
    lua_Number minDistance = luaL_checknumber(L, 2);
    musicPtr->setMinDistance(minDistance);
    return 0;
}

int MusicExporter::setAttenuation(lua_State* L)
{
    Lua_Music* musicPtr = static_cast<Lua_Music*>( luaL_checkudata(L, 1, LUA_MUSIC_METATABLENAME) );
    lua_Number attenuation = luaL_checknumber(L, 2);
    musicPtr->setAttenuation(attenuation);
    return 0;
}

int MusicExporter::getPitch(lua_State* L)
{
    Lua_Music* musicPtr = static_cast<Lua_Music*>( luaL_checkudata(L, 1, LUA_MUSIC_METATABLENAME) );
    lua_pushnumber(L, musicPtr->getPitch());
    return 1;
}

int MusicExporter::getVolume(lua_State* L)
{
    Lua_Music* musicPtr = static_cast<Lua_Music*>( luaL_checkudata(L, 1, LUA_MUSIC_METATABLENAME) );
    lua_pushnumber(L, musicPtr->getVolume());
    return 1;
}

int MusicExporter::getPosition(lua_State* L)
{
    Lua_Music* musicPtr = static_cast<Lua_Music*>( luaL_checkudata(L, 1, LUA_MUSIC_METATABLENAME) );
    lua_pushnumber(L, musicPtr->getPosition().x);
    lua_pushnumber(L, musicPtr->getPosition().y);
    lua_pushnumber(L, musicPtr->getPosition().z);
    return 3;
}

int MusicExporter::isRelativeToListener(lua_State* L)
{
    Lua_Music* musicPtr = static_cast<Lua_Music*>( luaL_checkudata(L, 1, LUA_MUSIC_METATABLENAME) );
    lua_pushboolean(L, musicPtr->isRelativeToListener());
    return 1;
}

int MusicExporter::getMinDistance(lua_State* L)
{
    Lua_Music* musicPtr = static_cast<Lua_Music*>( luaL_checkudata(L, 1, LUA_MUSIC_METATABLENAME) );
    lua_pushnumber(L, musicPtr->getMinDistance());
    return 1;
}

int MusicExporter::getAttenuation(lua_State* L)
{
    Lua_Music* musicPtr = static_cast<Lua_Music*>( luaL_checkudata(L, 1, LUA_MUSIC_METATABLENAME) );
    lua_pushnumber(L, musicPtr->getAttenuation());
    return 1;
}

LuaExporter MusicExporter::toLuaExporter()
{
    LuaExporter exporter(
        LUA_MUSIC_CLASSNAME,
        __new,
        {
            {"openFromFile", MusicExporter::openFromFile},
            {"getDuration", MusicExporter::getDuration},
            {"getLoopPoints", MusicExporter::getLoopPoints},
            {"setLoopPoints", MusicExporter::setLoopPoints},
            {"play", MusicExporter::play},
            {"pause", MusicExporter::pause},
            {"stop", MusicExporter::stop},
            {"getChannelCount", MusicExporter::getChannelCount},
            {"getSampleRate", MusicExporter::getSampleRate},
            {"getStatus", MusicExporter::getStatus},
            {"setPlayingOffset", MusicExporter::setPlayingOffset},
            {"getPlayingOffset", MusicExporter::getPlayingOffset},
            {"setLoop", MusicExporter::setLoop},
            {"getLoop", MusicExporter::getLoop},
            {"setPitch", MusicExporter::setPitch},
            {"setVolume", MusicExporter::setVolume},
            {"setPosition", MusicExporter::setPosition},
            {"setRelativeToListener", MusicExporter::setRelativeToListener},
            {"setMinDistance", MusicExporter::setMinDistance},
            {"setAttenuation", MusicExporter::setAttenuation},
            {"getPitch", MusicExporter::getPitch},
            {"getVolume", MusicExporter::getVolume},
            {"getPosition", MusicExporter::getPosition},
            {"isRelativeToListener", MusicExporter::isRelativeToListener},
            {"getMinDistance", MusicExporter::getMinDistance},
            {"getAttenuation", MusicExporter::getAttenuation},
        },
        {
            {"__gc", MusicExporter::__destroy},
            {"__index", MusicExporter::__index},
        }
    );

    exporter.addInteger("Status_Stopped", Lua_Music::Status::Stopped);
    exporter.addInteger("Status_Paused", Lua_Music::Status::Paused);
    exporter.addInteger("Status_Playing", Lua_Music::Status::Playing);

    return exporter;
}
