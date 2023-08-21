#include <Modding/Exporters/FontExporter.hpp>
#include <Modding/Exporters/GlyphExporter.hpp>
#include <Modding/LuaExporter.hpp>

void FontExporter::createFont(lua_State *L, const Lua_Font &font)
{
    void* data = lua_newuserdata(L, sizeof(Lua_Font));
    new (data) Lua_Font(font);
    luaL_getmetatable(L, LUA_FONT_METATABLENAME);
    lua_setmetatable(L, -2);
}

int FontExporter::__new(lua_State *L)
{
    int arg_count = lua_gettop(L);
    if(arg_count == 1)
    {
        Lua_Font* fontPtr = static_cast<Lua_Font*>( luaL_checkudata(L, 1, LUA_FONT_METATABLENAME) );
        createFont(L, *fontPtr);
        return 1;
    }

    createFont(L, Lua_Font());    
    return 1;
}

int FontExporter::__destroy(lua_State *L)
{
    Lua_Font* fontPtr = static_cast<Lua_Font*>( luaL_checkudata(L, 1, LUA_FONT_METATABLENAME) );
    fontPtr->~Lua_Font();
    return 0;
}

int FontExporter::__index(lua_State *L)
{
    Lua_Font* fontPtr = static_cast<Lua_Font*>( luaL_checkudata(L, 1, LUA_FONT_METATABLENAME) );
    std::string indexStr = luaL_checkstring(L, 2);

    lua_getglobal(L, LUA_FONT_CLASSNAME);
    lua_pushstring(L, indexStr.c_str());
    lua_rawget(L, -2);
    return 1;
}

int FontExporter::loadFromFile(lua_State *L)
{
    Lua_Font* fontPtr = static_cast<Lua_Font*>( luaL_checkudata(L, 1, LUA_FONT_METATABLENAME) );
    lua_getglobal(L, ASSETSPATH_VARNAME);
    fs::path total_path( luaL_checkstring(L, -1) );
    lua_pop(L, 1);
    total_path /= luaL_checkstring(L, 2);
    bool result = fontPtr->loadFromFile(total_path.string());
    lua_pushboolean(L, result);
    return 1;
}

int FontExporter::getFontFamily(lua_State *L)
{
    Lua_Font* fontPtr = static_cast<Lua_Font*>( luaL_checkudata(L, 1, LUA_FONT_METATABLENAME) );
    lua_pushstring(L, fontPtr->getInfo().family.c_str());
    return 1;
}

int FontExporter::getGlyph(lua_State *L)
{
    int arg_count = lua_gettop(L);
    Lua_Font* fontPtr = static_cast<Lua_Font*>( luaL_checkudata(L, 1, LUA_FONT_METATABLENAME) );
    lua_Integer codePoint;
    lua_Integer characterSize;
    bool bold;
    float outlineThickness = 0;

    lua_numbertointeger(luaL_checknumber(L, 2), &codePoint);
    lua_numbertointeger(luaL_checknumber(L, 3), &characterSize);
    bold = lua_toboolean(L, 4);
    if(arg_count > 4)
    {
        outlineThickness = luaL_checknumber(L, 5);
    }

    GlyphExporter::createGlyph(L, fontPtr->getGlyph(codePoint, characterSize, bold, outlineThickness));
    return 1;
}

int FontExporter::getKenning(lua_State *L)
{
    Lua_Font* fontPtr = static_cast<Lua_Font*>( luaL_checkudata(L, 1, LUA_FONT_METATABLENAME) );
    lua_Integer first;
    lua_Integer second;
    lua_Integer characterSize;

    lua_numbertointeger(luaL_checknumber(L, 2), &first);
    lua_numbertointeger(luaL_checknumber(L, 3), &second);
    lua_numbertointeger(luaL_checknumber(L, 4), &characterSize);

    lua_pushnumber(L, fontPtr->getKerning(first, second, characterSize));
    return 1;
}

int FontExporter::getLineSpacing(lua_State *L)
{
    Lua_Font* fontPtr = static_cast<Lua_Font*>( luaL_checkudata(L, 1, LUA_FONT_METATABLENAME) );
    lua_Integer characterSize;
    lua_numbertointeger(luaL_checknumber(L, 2), &characterSize);
    lua_pushnumber(L, fontPtr->getLineSpacing(characterSize));
    return 1;
}

int FontExporter::getUnderlinePosition(lua_State *L)
{
    Lua_Font* fontPtr = static_cast<Lua_Font*>( luaL_checkudata(L, 1, LUA_FONT_METATABLENAME) );
    lua_Integer characterSize;
    lua_numbertointeger(luaL_checknumber(L, 2), &characterSize);
    lua_pushnumber(L, fontPtr->getUnderlinePosition(characterSize));
    return 1;
}

int FontExporter::getUnderlineThickness(lua_State *L)
{
    Lua_Font* fontPtr = static_cast<Lua_Font*>( luaL_checkudata(L, 1, LUA_FONT_METATABLENAME) );
    lua_Integer characterSize;
    lua_numbertointeger(luaL_checknumber(L, 2), &characterSize);
    lua_pushnumber(L, fontPtr->getUnderlineThickness(characterSize));
    return 1;
}

LuaExporter FontExporter::toLuaExporter()
{
    LuaExporter exporter(
        LUA_FONT_CLASSNAME,
        __new,
        {
            {"loadFromFile", FontExporter::loadFromFile},
            {"getFontFamily", FontExporter::getFontFamily},
            {"getGlyph", FontExporter::getGlyph},
            {"getKenning", FontExporter::getKenning},
            {"getLineSpacing", FontExporter::getLineSpacing},
            {"getUnderlinePosition", FontExporter::getUnderlinePosition},
            {"getUnderlineThickness", FontExporter::getUnderlineThickness},
        },
        {
            {"__new", FontExporter::__new},
            {"__gc", FontExporter::__destroy},
            {"__index", FontExporter::__index},
        }
    );

    return exporter;
}
