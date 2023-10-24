#include <Modding/LuaExporter.hpp>
#include <Modding/Exporters/GlyphExporter.hpp>
#include <Modding/Exporters/FloatRectExporter.hpp>
#include <Modding/Exporters/IntRectExporter.hpp>
#include "Modding/LuaHelper.hpp"

void GlyphExporter::createGlyph(lua_State *L, const Exported_Glyph &glyph)
{
    void* data = lua_newuserdata(L, sizeof(Exported_Glyph));
    new (data) Exported_Glyph(glyph);
    luaL_getmetatable(L, LUA_GLYPH_METATABLENAME);
    lua_setmetatable(L, -2);
}

int GlyphExporter::__new(lua_State *L)
{
    createGlyph(L, sf::Glyph());
    return 1;
}

int GlyphExporter::__destroy(lua_State *L)
{
    Exported_Glyph* glyphPtr = static_cast<Exported_Glyph*>( LuaHelper::checkudata_WithError(L, 1, LUA_GLYPH_METATABLENAME) );
    glyphPtr->~Exported_Glyph();
    return 0;
}

int GlyphExporter::__index(lua_State *L)
{
    Exported_Glyph* glyphPtr = static_cast<Exported_Glyph*>( LuaHelper::checkudata_WithError(L, 1, LUA_GLYPH_METATABLENAME) );
    std::string indexStr = luaL_checkstring(L, 2);

    if(indexStr == "advance")
    {
        lua_pushnumber(L, glyphPtr->advance);
        return 1;
    }
    else if(indexStr == "bounds")
    {
        FloatRectExporter::createFloatRect(L, glyphPtr->bounds);
        return 1;
    }
    else if(indexStr == "textureRect")
    {
        IntRectExporter::createIntRect(L, glyphPtr->textureRect);
        return 1;
    }

    lua_getglobal(L, LUA_GLYPH_CLASSNAME);
    lua_pushstring(L, indexStr.c_str());
    lua_rawget(L, -2);
    return 1;
}

int GlyphExporter::__newindex(lua_State *L)
{
    Exported_Glyph* glyphPtr = static_cast<Exported_Glyph*>( LuaHelper::checkudata_WithError(L, 1, LUA_GLYPH_METATABLENAME) );
    std::string indexStr = luaL_checkstring(L, 2);

    if(indexStr == "advance")
    {
        glyphPtr->advance = luaL_checknumber(L, 3);
        return 0;
    }
    else if(indexStr == "bounds")
    {
        glyphPtr->bounds = *static_cast<Exported_FloatRect*>( LuaHelper::checkudata_WithError(L, 3, LUA_FLOATRECT_METATABLENAME) );
        return 0;
    }
    else if(indexStr == "textureRect")
    {
        glyphPtr->textureRect = *static_cast<Exported_IntRect*>( LuaHelper::checkudata_WithError(L, 3, LUA_INTRECT_METATABLENAME) );
        return 0;
    }

    luaL_error(L, "Cannot set value for %s", indexStr.c_str());
    return 0;
}

int GlyphExporter::__eq(lua_State *L)
{
    if(!lua_isuserdata(L, 1) && !lua_isuserdata(L, 2))
    {
        lua_pushboolean(L, false);
        return 1;
    }
    Exported_Glyph* firstGlyphPtr = static_cast<Exported_Glyph*>( LuaHelper::checkudata_WithError(L, 1, LUA_GLYPH_METATABLENAME) );
    Exported_Glyph* secondGlyphPtr = static_cast<Exported_Glyph*>( LuaHelper::checkudata_WithError(L, 2, LUA_GLYPH_METATABLENAME) );
    lua_pushboolean(L,
        (firstGlyphPtr->advance == secondGlyphPtr->advance) &&
        (firstGlyphPtr->bounds == secondGlyphPtr->bounds) && 
        (firstGlyphPtr->textureRect == secondGlyphPtr->textureRect)
    );

    return 1;
}

LuaExporter GlyphExporter::toLuaExporter()
{
    LuaExporter exporter(
        LUA_GLYPH_CLASSNAME,
        GlyphExporter::__new,
        {},
        {
            {"__new", GlyphExporter::__new},
            {"__destroy", GlyphExporter::__destroy},
            {"__index", GlyphExporter::__index},
            {"__newindex", GlyphExporter::__newindex},
            {"__eq", GlyphExporter::__eq},
        }
    );

    return exporter;
}