#include <Modding/Exporters/CursorExporter.hpp>
#include <Modding/Exporters/ImageExporter.hpp>
#include <Modding/Exporters/Vector2Exporter.hpp>
#include <Modding/LuaExporter.hpp>

void CursorExporter::createCursor(lua_State* L) {
    void* data = lua_newuserdata(L, sizeof(Lua_Cursor));
    new (data) Lua_Cursor();
    luaL_getmetatable(L, LUA_CURSOR_METATABLENAME);
    lua_setmetatable(L, -2);
}

int CursorExporter::__new(lua_State *L)
{
    createCursor(L);
    return 1;
}

int CursorExporter::__destroy(lua_State *L)
{
    Lua_Cursor* cursorPtr = static_cast<Lua_Cursor*>( luaL_checkudata(L, 1, LUA_CURSOR_METATABLENAME) );
    cursorPtr->~Lua_Cursor();
    return 0;
}

int CursorExporter::__index(lua_State *L)
{
    Lua_Cursor* cursorPtr = static_cast<Lua_Cursor*>( luaL_checkudata(L, 1, LUA_CURSOR_METATABLENAME) );
    std::string indexStr = luaL_checkstring(L, 2);

    if(indexStr == "Type_Arrow")
    {
        lua_pushinteger(L, sf::Cursor::Type::Arrow);
        return 1;
    }
    else if(indexStr == "Type_ArrowWait")
    {
        lua_pushinteger(L, sf::Cursor::Type::ArrowWait);
        return 1;
    }
    else if(indexStr == "Type_Wait")
    {
        lua_pushinteger(L, sf::Cursor::Type::Wait);
        return 1;
    }
    else if(indexStr == "Type_Text")
    {
        lua_pushinteger(L, sf::Cursor::Type::Text);
        return 1;
    }
    else if(indexStr == "Type_Hand")
    {
        lua_pushinteger(L, sf::Cursor::Type::Hand);
        return 1;
    }
    else if(indexStr == "Type_SizeHorizontal")
    {
        lua_pushinteger(L, sf::Cursor::Type::SizeHorizontal);
        return 1;
    }
    else if(indexStr == "Type_SizeVertical")
    {
        lua_pushinteger(L, sf::Cursor::Type::SizeVertical);
        return 1;
    }
    else if(indexStr == "Type_SizeTopLeftBottomRight")
    {
        lua_pushinteger(L, sf::Cursor::Type::SizeTopLeftBottomRight);
        return 1;
    }
    else if(indexStr == "Type_SizeBottomLeftTopRight")
    {
        lua_pushinteger(L, sf::Cursor::Type::SizeBottomLeftTopRight);
        return 1;
    }
    else if(indexStr == "Type_SizeAll")
    {
        lua_pushinteger(L, sf::Cursor::Type::SizeAll);
        return 1;
    }
    else if(indexStr == "Type_Cross")
    {
        lua_pushinteger(L, sf::Cursor::Type::Cross);
        return 1;
    }
    else if(indexStr == "Type_Help")
    {
        lua_pushinteger(L, sf::Cursor::Type::Help);
        return 1;
    }
    else if(indexStr == "Type_NotAllowed")
    {
        lua_pushinteger(L, sf::Cursor::Type::NotAllowed);
        return 1;
    }

    lua_getglobal(L, LUA_CURSOR_CLASSNAME);
    lua_pushstring(L, indexStr.c_str());
    lua_rawget(L, -2);
    return 1;
}

int CursorExporter::loadFromImage(lua_State* L)
{
    Lua_Cursor* cursorPtr = static_cast<Lua_Cursor*>( luaL_checkudata(L, 1, LUA_CURSOR_METATABLENAME) );
    Lua_Image* imagePtr = static_cast<Lua_Image*>( luaL_checkudata(L, 2, LUA_IMAGE_METATABLENAME) );
    Lua_Vector2* hotspotPtr = static_cast<Lua_Vector2*>( luaL_checkudata(L, 3, LUA_VECTOR2_METATABLENAME) );

    bool result = cursorPtr->loadFromPixels(imagePtr->getPixelsPtr(), imagePtr->getSize(), *hotspotPtr);
    lua_pushboolean(L, result);
    return 1;
}

int CursorExporter::loadFromSystem(lua_State* L)
{
    Lua_Cursor* cursorPtr = static_cast<Lua_Cursor*>( luaL_checkudata(L, 1, LUA_CURSOR_METATABLENAME) );
    lua_Integer typeAsInteger;
    lua_numbertointeger(luaL_checknumber(L, 2), &typeAsInteger);

    bool result = cursorPtr->loadFromSystem(static_cast<Lua_Cursor::Type>(typeAsInteger));
    lua_pushboolean(L, result);
    return 1;
}

LuaExporter CursorExporter::toLuaExporter()
{
    LuaExporter exporter(
        LUA_CURSOR_CLASSNAME,
        __new,
        {
            {"loadFromImage", CursorExporter::loadFromImage},
            {"loadFromSystem", CursorExporter::loadFromSystem},
        },
        {
            {"__gc", CursorExporter::__destroy},
            {"__index", CursorExporter::__index},
        }
    );

    exporter.addInteger("Type_Arrow", sf::Cursor::Type::Arrow);
    exporter.addInteger("Type_ArrowWait", sf::Cursor::Type::ArrowWait);
    exporter.addInteger("Type_Wait", sf::Cursor::Type::Wait);
    exporter.addInteger("Type_Text", sf::Cursor::Type::Text);
    exporter.addInteger("Type_Hand", sf::Cursor::Type::Hand);
    exporter.addInteger("Type_SizeHorizontal", sf::Cursor::Type::SizeHorizontal);
    exporter.addInteger("Type_SizeVertical", sf::Cursor::Type::SizeVertical);
    exporter.addInteger("Type_SizeTopLeftBottomRight", sf::Cursor::Type::SizeTopLeftBottomRight);
    exporter.addInteger("Type_SizeBottomLeftTopRight", sf::Cursor::Type::SizeBottomLeftTopRight);
    exporter.addInteger("Type_SizeAll", sf::Cursor::Type::SizeAll);
    exporter.addInteger("Type_Cross", sf::Cursor::Type::Cross);
    exporter.addInteger("Type_Help", sf::Cursor::Type::Help);
    exporter.addInteger("Type_NotAllowed", sf::Cursor::Type::NotAllowed);

    return exporter;
}