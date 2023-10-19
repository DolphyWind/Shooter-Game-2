#include <Modding/Exporters/TextExporter.hpp>
#include <Modding/Exporters/Vector2Exporter.hpp>
#include <Modding/Exporters/ColorExporter.hpp>
#include <Modding/Exporters/FloatRectExporter.hpp>
#include <Modding/Exporters/TransformExporter.hpp>
#include <Modding/Exporters/FontExporter.hpp>
#include <Modding/Exporters/EntityExporter.hpp>
#include <Modding/LuaExporter.hpp>
#include <Modding/LuaHelper.hpp>
#include <InGame/LuaEntity.hpp>

void TextExporter::createText(lua_State* L)
{
    void* data = lua_newuserdata(L, sizeof(Lua_Text));
    new (data) Lua_Text(nullptr);
    luaL_getmetatable(L, LUA_TEXT_METATABLENAME);
    lua_setmetatable(L, -2);
}

void TextExporter::createText(lua_State* L, const sf::String& string, sf::Font* font, unsigned int charSize)
{
    void* data = lua_newuserdata(L, sizeof(Lua_Text));
    new (data) Lua_Text(nullptr, string, *font, charSize);
    luaL_getmetatable(L, LUA_TEXT_METATABLENAME);
    lua_setmetatable(L, -2);
}

int TextExporter::__new(lua_State *L)
{
    int arg_count = lua_gettop(L);
    if(arg_count == 0)
    {
        createText(L);
        return 1;
    }
    sf::String string = lua_tostring(L, 1);
    Lua_Font* font = static_cast<Lua_Font*>( LuaHelper::checkudata_WithError(L, 2, LUA_FONT_METATABLENAME) );
    lua_Integer charSize = 30;
    if(arg_count >= 3)
    {
        lua_numbertointeger(luaL_checknumber(L, 3), &charSize);
    }
    createText(L, string, font, charSize);

    return 1;
}

int TextExporter::__destroy(lua_State *L)
{
    Lua_Text* textPtr = static_cast<Lua_Text*>( LuaHelper::checkudata_WithError(L, 1, LUA_TEXT_METATABLENAME) );
    textPtr->~Lua_Text();
    return 0;
}

int TextExporter::__index(lua_State* L)
{
    Lua_Text* textPtr = static_cast<Lua_Text*>( LuaHelper::checkudata_WithError(L, 1, LUA_TEXT_METATABLENAME) );
    std::string indexStr = luaL_checkstring(L, 2);

    if(indexStr == "Style_Regular")
    {
        lua_pushinteger(L, sf::Text::Style::Regular);
        return 1;
    }
    else if(indexStr == "Style_Bold")
    {
        lua_pushinteger(L, sf::Text::Style::Bold);
        return 1;
    }
    else if(indexStr == "Style_Italic")
    {
        lua_pushinteger(L, sf::Text::Style::Italic);
        return 1;
    }
    else if(indexStr == "Style_Underlined")
    {
        lua_pushinteger(L, sf::Text::Style::Underlined);
        return 1;
    }
    else if(indexStr == "Style_StrikeThrough")
    {
        lua_pushinteger(L, sf::Text::Style::StrikeThrough);
        return 1;
    }

    lua_getglobal(L, LUA_TEXT_CLASSNAME);
    lua_pushstring(L, indexStr.c_str());
    lua_rawget(L, -2);
    return 1;
}

int TextExporter::setString(lua_State* L)
{
    Lua_Text* textPtr = static_cast<Lua_Text*>( LuaHelper::checkudata_WithError(L, 1, LUA_TEXT_METATABLENAME) );
    std::string string = luaL_checkstring(L, 2);
    (*textPtr)->setString(string);

    return 0;
}

int TextExporter::setFont(lua_State* L)
{
    Lua_Text* textPtr = static_cast<Lua_Text*>( LuaHelper::checkudata_WithError(L, 1, LUA_TEXT_METATABLENAME) );
    Lua_Font* fontPtr = static_cast<Lua_Font*>( LuaHelper::checkudata_WithError(L, 2, LUA_FONT_METATABLENAME) );
    (*textPtr)->setFont(*fontPtr);

    return 0;
}

int TextExporter::setCharacterSize(lua_State* L)
{
    Lua_Text* textPtr = static_cast<Lua_Text*>( LuaHelper::checkudata_WithError(L, 1, LUA_TEXT_METATABLENAME) );
    lua_Integer size;
    lua_numbertointeger(luaL_checknumber(L, 2), &size);
    (*textPtr)->setCharacterSize(size);

    return 0;
}

int TextExporter::setLineSpacing(lua_State* L)
{
    Lua_Text* textPtr = static_cast<Lua_Text*>( LuaHelper::checkudata_WithError(L, 1, LUA_TEXT_METATABLENAME) );
    lua_Number spacingFactor = luaL_checknumber(L, 2);
    (*textPtr)->setLineSpacing(spacingFactor);

    return 0;
}

int TextExporter::setLetterSpacing(lua_State* L)
{
    Lua_Text* textPtr = static_cast<Lua_Text*>( LuaHelper::checkudata_WithError(L, 1, LUA_TEXT_METATABLENAME) );
    lua_Number spacingFactor = luaL_checknumber(L, 2);
    (*textPtr)->setLetterSpacing(spacingFactor);

    return 0;
}

int TextExporter::setStyle(lua_State* L)
{
    Lua_Text* textPtr = static_cast<Lua_Text*>( LuaHelper::checkudata_WithError(L, 1, LUA_TEXT_METATABLENAME) );
    lua_Integer style;
    lua_numbertointeger(luaL_checknumber(L, 2), &style);
    (*textPtr)->setStyle(style);

    return 0;
}

int TextExporter::setFillColor(lua_State* L)
{
    Lua_Text* textPtr = static_cast<Lua_Text*>( LuaHelper::checkudata_WithError(L, 1, LUA_TEXT_METATABLENAME) );
    Lua_Color* colorPtr = static_cast<Lua_Color*>( LuaHelper::checkudata_WithError(L, 2, LUA_COLOR_METATABLENAME) );
    (*textPtr)->setFillColor(*colorPtr);

    return 0;
}

int TextExporter::setOutlineColor(lua_State* L)
{
    Lua_Text* textPtr = static_cast<Lua_Text*>( LuaHelper::checkudata_WithError(L, 1, LUA_TEXT_METATABLENAME) );
    Lua_Color* colorPtr = static_cast<Lua_Color*>( LuaHelper::checkudata_WithError(L, 2, LUA_COLOR_METATABLENAME) );
    (*textPtr)->setOutlineColor(*colorPtr);

    return 0;
}

int TextExporter::setOutlineThickness(lua_State* L)
{
    Lua_Text* textPtr = static_cast<Lua_Text*>( LuaHelper::checkudata_WithError(L, 1, LUA_TEXT_METATABLENAME) );
    lua_Number thickness = luaL_checknumber(L, 2);
    (*textPtr)->setOutlineThickness(thickness);

    return 0;
}

int TextExporter::getString(lua_State* L)
{
    Lua_Text* textPtr = static_cast<Lua_Text*>( LuaHelper::checkudata_WithError(L, 1, LUA_TEXT_METATABLENAME) );
    lua_pushstring(L, (*textPtr)->getString().toAnsiString().c_str());

    return 1;
}

int TextExporter::getFont(lua_State* L)
{
    Lua_Text* textPtr = static_cast<Lua_Text*>( LuaHelper::checkudata_WithError(L, 1, LUA_TEXT_METATABLENAME) );
    const Lua_Font* fontPtr = (*textPtr)->getFont();
    LuaHelper::push(L, (void*)fontPtr);

    return 1;
}

int TextExporter::getCharacterSize(lua_State* L)
{
    Lua_Text* textPtr = static_cast<Lua_Text*>( LuaHelper::checkudata_WithError(L, 1, LUA_TEXT_METATABLENAME) );
    lua_pushinteger(L, (*textPtr)->getCharacterSize());

    return 1;
}

int TextExporter::getLetterSpacing(lua_State* L)
{
    Lua_Text* textPtr = static_cast<Lua_Text*>( LuaHelper::checkudata_WithError(L, 1, LUA_TEXT_METATABLENAME) );
    lua_pushnumber(L, (*textPtr)->getLetterSpacing());

    return 1;
}

int TextExporter::getLineSpacing(lua_State* L)
{
    Lua_Text* textPtr = static_cast<Lua_Text*>( LuaHelper::checkudata_WithError(L, 1, LUA_TEXT_METATABLENAME) );
    lua_pushnumber(L, (*textPtr)->getLineSpacing());

    return 1;
}

int TextExporter::getStyle(lua_State* L)
{
    Lua_Text* textPtr = static_cast<Lua_Text*>( LuaHelper::checkudata_WithError(L, 1, LUA_TEXT_METATABLENAME) );
    lua_pushinteger(L, (*textPtr)->getStyle());

    return 1;
}

int TextExporter::getFillColor(lua_State* L)
{
    Lua_Text* textPtr = static_cast<Lua_Text*>( LuaHelper::checkudata_WithError(L, 1, LUA_TEXT_METATABLENAME) );
    ColorExporter::createColor(L, (*textPtr)->getFillColor());

    return 1;
}

int TextExporter::getOutlineColor(lua_State* L)
{
    Lua_Text* textPtr = static_cast<Lua_Text*>( LuaHelper::checkudata_WithError(L, 1, LUA_TEXT_METATABLENAME) );
    ColorExporter::createColor(L, (*textPtr)->getOutlineColor());

    return 1;
}

int TextExporter::getOutlineThickness(lua_State* L)
{
    Lua_Text* textPtr = static_cast<Lua_Text*>( LuaHelper::checkudata_WithError(L, 1, LUA_TEXT_METATABLENAME) );
    lua_pushnumber(L, (*textPtr)->getOutlineThickness());

    return 1;
}

int TextExporter::findCharacterPos(lua_State* L)
{
    Lua_Text* textPtr = static_cast<Lua_Text*>( LuaHelper::checkudata_WithError(L, 1, LUA_TEXT_METATABLENAME) );
    lua_Integer index;
    lua_numbertointeger(luaL_checknumber(L, 2), &index);
    Vector2Exporter::createVector(L, (*textPtr)->findCharacterPos(index));

    return 1;
}

int TextExporter::getLocalBounds(lua_State* L)
{
    Lua_Text* textPtr = static_cast<Lua_Text*>( LuaHelper::checkudata_WithError(L, 1, LUA_TEXT_METATABLENAME) );
    FloatRectExporter::createFloatRect(L, (*textPtr)->getLocalBounds());

    return 1;
}

int TextExporter::getGlobalBounds(lua_State* L)
{
    Lua_Text* textPtr = static_cast<Lua_Text*>( LuaHelper::checkudata_WithError(L, 1, LUA_TEXT_METATABLENAME) );
    FloatRectExporter::createFloatRect(L, textPtr->getGlobalBounds());

    return 1;
}

int TextExporter::setPosition(lua_State* L)
{
    int arg_count = lua_gettop(L);
    Lua_Text* textPtr = static_cast<Lua_Text*>( LuaHelper::checkudata_WithError(L, 1, LUA_TEXT_METATABLENAME) );
    Lua_Vector2* vecPtr;

    vecPtr = (Lua_Vector2*)LuaHelper::checkudata_orNull(L, 2, LUA_VECTOR2_METATABLENAME);
    if(vecPtr)
    {
        (*textPtr)->setPosition(*vecPtr);
        return 0;
    }
    (*textPtr)->setPosition(
        luaL_checknumber(L, 2),
        luaL_checknumber(L, 3)
    );

    return 0;
}

int TextExporter::setRotation(lua_State* L)
{
    Lua_Text* textPtr = static_cast<Lua_Text*>( LuaHelper::checkudata_WithError(L, 1, LUA_TEXT_METATABLENAME) );
    (*textPtr)->setRotation(luaL_checknumber(L, 2) );

    return 0;
}

int TextExporter::setScale(lua_State* L)
{
    Lua_Text* textPtr = static_cast<Lua_Text*>( LuaHelper::checkudata_WithError(L, 1, LUA_TEXT_METATABLENAME) );
    Lua_Vector2* vecPtr;

    vecPtr = (Lua_Vector2*) LuaHelper::checkudata_orNull(L, 2, LUA_VECTOR2_METATABLENAME);
    if(vecPtr)
    {
        (*textPtr)->setScale(*vecPtr);
        return 0;
    }
    (*textPtr)->setScale(
        luaL_checknumber(L, 2),
        luaL_checknumber(L, 3)
    );

    return 0;
}

int TextExporter::setOrigin(lua_State* L)
{
    Lua_Text* textPtr = static_cast<Lua_Text*>( LuaHelper::checkudata_WithError(L, 1, LUA_TEXT_METATABLENAME) );
    Lua_Vector2* vecPtr;

    vecPtr = (Lua_Vector2*) LuaHelper::checkudata_orNull(L, 2, LUA_VECTOR2_METATABLENAME);
    if(vecPtr)
    {
        (*textPtr)->setOrigin(*vecPtr);
        return 0;
    }
    (*textPtr)->setOrigin(
        luaL_checknumber(L, 2),
        luaL_checknumber(L, 3)
    );

    return 0;
}

int TextExporter::getLocalPosition(lua_State* L)
{
    Lua_Text* textPtr = static_cast<Lua_Text*>( LuaHelper::checkudata_WithError(L, 1, LUA_TEXT_METATABLENAME) );
    Vector2Exporter::createVector(L, (*textPtr)->getPosition());

    return 1;
}

int TextExporter::getWorldPosition(lua_State* L)
{
    Lua_Text* textPtr = static_cast<Lua_Text*>( LuaHelper::checkudata_WithError(L, 1, LUA_TEXT_METATABLENAME) );
    Vector2Exporter::createVector(L, textPtr->getPosition());

    return 1;
}

int TextExporter::getRotation(lua_State* L)
{
    Lua_Text* textPtr = static_cast<Lua_Text*>( LuaHelper::checkudata_WithError(L, 1, LUA_TEXT_METATABLENAME) );
    lua_pushnumber(L, (*textPtr)->getRotation());

    return 1;
}

int TextExporter::getScale(lua_State* L)
{
    Lua_Text* textPtr = static_cast<Lua_Text*>( LuaHelper::checkudata_WithError(L, 1, LUA_TEXT_METATABLENAME) );
    Vector2Exporter::createVector(L, (*textPtr)->getScale());

    return 1;
}

int TextExporter::getOrigin(lua_State* L)
{
    Lua_Text* textPtr = static_cast<Lua_Text*>( LuaHelper::checkudata_WithError(L, 1, LUA_TEXT_METATABLENAME) );
    Vector2Exporter::createVector(L, (*textPtr)->getOrigin());

    return 1;
}

int TextExporter::move(lua_State* L)
{
    Lua_Text* textPtr = static_cast<Lua_Text*>( LuaHelper::checkudata_WithError(L, 1, LUA_TEXT_METATABLENAME) );
    Lua_Vector2* vecPtr;

    vecPtr = (Lua_Vector2*) LuaHelper::checkudata_orNull(L, 2, LUA_VECTOR2_METATABLENAME);
    if(vecPtr)
    {
        (*textPtr)->move(*vecPtr);
        return 0;
    }
    (*textPtr)->move(
        luaL_checknumber(L, 2),
        luaL_checknumber(L, 3)
    );

    return 0;
}

int TextExporter::rotate(lua_State* L)
{
    Lua_Text* textPtr = static_cast<Lua_Text*>( LuaHelper::checkudata_WithError(L, 1, LUA_TEXT_METATABLENAME) );
    (*textPtr)->rotate(luaL_checknumber(L, 2));

    return 0;
}

int TextExporter::scale(lua_State* L)
{
    Lua_Text* textPtr = static_cast<Lua_Text*>( LuaHelper::checkudata_WithError(L, 1, LUA_TEXT_METATABLENAME) );
    Lua_Vector2* vecPtr;

    vecPtr = (Lua_Vector2*) LuaHelper::checkudata_orNull(L, 2, LUA_VECTOR2_METATABLENAME);
    if(vecPtr)
    {
        (*textPtr)->scale(*vecPtr);
        return 0;
    }
    (*textPtr)->scale(
        luaL_checknumber(L, 2),
        luaL_checknumber(L, 3)
    );

    return 0;
}

int TextExporter::getTransform(lua_State* L)
{
    Lua_Text* textPtr = static_cast<Lua_Text*>( LuaHelper::checkudata_WithError(L, 1, LUA_TEXT_METATABLENAME) );
    TransformExporter::createTransform(L, (*textPtr)->getTransform());

    return 1;
}

int TextExporter::getInverseTransform(lua_State* L)
{
    Lua_Text* textPtr = static_cast<Lua_Text*>( LuaHelper::checkudata_WithError(L, 1, LUA_TEXT_METATABLENAME) );
    TransformExporter::createTransform(L, (*textPtr)->getInverseTransform());

    return 1;
}

int TextExporter::attachTo(lua_State* L)
{
    Lua_Text* textPtr = static_cast<Lua_Text*>( LuaHelper::checkudata_WithError(L, 1, LUA_TEXT_METATABLENAME) );
    Exported_Entity* entityPtr = static_cast<Exported_Entity*>( LuaHelper::checkudata_WithError(L, 2, LUA_ENTITY_METATABLENAME) );

    textPtr->attachTo(dynamic_cast<Entity*>(*entityPtr));
    return 0;
}

LuaExporter TextExporter::toLuaExporter()
{
    LuaExporter exporter(
        LUA_TEXT_CLASSNAME,
        __new,
        {
            {"setString", TextExporter::setString},
            {"setFont", TextExporter::setFont},
            {"setCharacterSize", TextExporter::setCharacterSize},
            {"setLineSpacing", TextExporter::setLineSpacing},
            {"setLetterSpacing", TextExporter::setLetterSpacing},
            {"setStyle", TextExporter::setStyle},
            {"setFillColor", TextExporter::setFillColor},
            {"setOutlineColor", TextExporter::setOutlineColor},
            {"setOutlineThickness", TextExporter::setOutlineThickness},
            {"getString", TextExporter::getString},
            {"getFont", TextExporter::getFont},
            {"getCharacterSize", TextExporter::getCharacterSize},
            {"getLetterSpacing", TextExporter::getLetterSpacing},
            {"getLineSpacing", TextExporter::getLineSpacing},
            {"getStyle", TextExporter::getStyle},
            {"getFillColor", TextExporter::getFillColor},
            {"getOutlineColor", TextExporter::getOutlineColor},
            {"getOutlineThickness", TextExporter::getOutlineThickness},
            {"findCharacterPos", TextExporter::findCharacterPos},
            {"getLocalBounds", TextExporter::getLocalBounds},
            {"getGlobalBounds", TextExporter::getGlobalBounds},
            {"setPosition", TextExporter::setPosition},
            {"setRotation", TextExporter::setRotation},
            {"setScale", TextExporter::setScale},
            {"setOrigin", TextExporter::setOrigin},
            {"getLocalPosition", TextExporter::getLocalPosition},
            {"getWorldPosition", TextExporter::getWorldPosition},
            {"getRotation", TextExporter::getRotation},
            {"getScale", TextExporter::getScale},
            {"getOrigin", TextExporter::getOrigin},
            {"move", TextExporter::move},
            {"rotate", TextExporter::rotate},
            {"scale", TextExporter::scale},
            {"getTransform", TextExporter::getTransform},
            {"getInverseTransform", TextExporter::getInverseTransform},
        },
        {
            {"__gc", TextExporter::__destroy},
            {"__index", TextExporter::__index},
        }
    );

    exporter.addInteger("Style_Regular", sf::Text::Style::Regular);
    exporter.addInteger("Style_Bold", sf::Text::Style::Bold);
    exporter.addInteger("Style_Italic", sf::Text::Style::Italic);
    exporter.addInteger("Style_Underlined", sf::Text::Style::Underlined);
    exporter.addInteger("Style_StrikeThrough", sf::Text::Style::StrikeThrough);

    return exporter;
}
