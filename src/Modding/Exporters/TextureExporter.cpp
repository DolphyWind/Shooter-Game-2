#include <Modding/Exporters/TextureExporter.hpp>
#include <Modding/Exporters/ImageExporter.hpp>
#include <Modding/Exporters/IntRectExporter.hpp>
#include <Modding/Exporters/Vector2Exporter.hpp>
#include <Modding/Exporters/RenderWindowExporter.hpp>
#include <Modding/LuaExporter.hpp>

void TextureExporter::createTexture(lua_State* L, const Lua_Texture& texture)
{
    void* userdata = lua_newuserdata(L, sizeof(Lua_Texture));
    new (userdata) Lua_Texture(texture);
    luaL_getmetatable(L, LUA_TEXTURE_METATABLENAME);
    lua_setmetatable(L, -2);
}

int TextureExporter::__new(lua_State* L)
{
    int arg_count = lua_gettop(L);
    if(arg_count >= 1)
    {
        Lua_Texture* texturePtr = static_cast<Lua_Texture*>( luaL_checkudata(L, 1, LUA_TEXTURE_METATABLENAME) );
        createTexture(L, *texturePtr);
        return 1;
    }

    createTexture(L, Lua_Texture());
    return 1;
}

int TextureExporter::__destroy(lua_State* L)
{
    Lua_Texture* texturePtr = static_cast<Lua_Texture*>( luaL_checkudata(L, 1, LUA_TEXTURE_METATABLENAME) );
    texturePtr->~Lua_Texture();
    return 0;
}

int TextureExporter::__index(lua_State* L)
{
    Lua_Texture* texturePtr = static_cast<Lua_Texture*>( luaL_checkudata(L, 1, LUA_TEXTURE_METATABLENAME) );
    std::string indexStr = luaL_checkstring(L, 2);

    lua_getglobal(L, LUA_TEXTURE_CLASSNAME);
    lua_pushstring(L, indexStr.c_str());
    lua_rawget(L, -2);
    return 1;
}

int TextureExporter::create(lua_State* L)
{
    Lua_Texture* texturePtr = static_cast<Lua_Texture*>( luaL_checkudata(L, 1, LUA_TEXTURE_METATABLENAME) );
    lua_Integer width;
    lua_Integer height;
    lua_numbertointeger(luaL_checknumber(L, 2), &width);
    lua_numbertointeger(luaL_checknumber(L, 3), &height);
    bool result = texturePtr->create(width, height);
    lua_pushboolean(L, result);

    return 1;
}

int TextureExporter::loadFromFile(lua_State* L)
{
    Lua_Texture* texturePtr = static_cast<Lua_Texture*>( luaL_checkudata(L, 1, LUA_TEXTURE_METATABLENAME) );
    std::string filename = luaL_checkstring(L, 2);
    lua_getglobal(L, ASSETSPATH_VARNAME);
    std::filesystem::path totalPath(luaL_checkstring(L, -1));
    totalPath /= filename;
    bool result = texturePtr->loadFromFile(totalPath.string());
    lua_pushboolean(L, result);
    return 1;
}

int TextureExporter::loadFromImage(lua_State* L)
{
    int arg_count = lua_gettop(L);
    Lua_Texture* texturePtr = static_cast<Lua_Texture*>( luaL_checkudata(L, 1, LUA_TEXTURE_METATABLENAME) );
    Lua_Image* imagePtr = static_cast<Lua_Image*>( luaL_checkudata(L, 2, LUA_IMAGE_METATABLENAME) );
    Lua_IntRect rect;

    if(arg_count >= 3)
    {
        rect = *static_cast<Lua_IntRect*>( luaL_checkudata(L, 3, LUA_INTRECT_METATABLENAME) );
    }

    bool result = texturePtr->loadFromImage(*imagePtr, rect);
    lua_pushboolean(L, result);

    return 1;
}

int TextureExporter::getSize(lua_State* L)
{
    Lua_Texture* texturePtr = static_cast<Lua_Texture*>( luaL_checkudata(L, 1, LUA_TEXTURE_METATABLENAME) );
    Vector2Exporter::createVector(L, texturePtr->getSize());

    return 1;
}

int TextureExporter::copyToImage(lua_State* L)
{
    Lua_Texture* texturePtr = static_cast<Lua_Texture*>( luaL_checkudata(L, 1, LUA_TEXTURE_METATABLENAME) );
    ImageExporter::createImage(L, texturePtr->copyToImage());

    return 1;
}

int TextureExporter::update(lua_State* L)
{
    int arg_count = lua_gettop(L);
    Lua_Texture* texturePtr = static_cast<Lua_Texture*>( luaL_checkudata(L, 1, LUA_TEXTURE_METATABLENAME) );
    lua_Integer x = 0;
    lua_Integer y = 0;
    if(arg_count >= 4)
    {
        lua_numbertointeger(luaL_checknumber(L, 3), &x);
        lua_numbertointeger(luaL_checknumber(L, 4), &y);
    }

    if(LuaHelper::checkudata_orNull(L, 2, LUA_TEXTURE_METATABLENAME))
    {
        Lua_Texture* textureToCopyPtr = static_cast<Lua_Texture*>(lua_touserdata(L, 2));
        texturePtr->update(*textureToCopyPtr, x, y);
    }
    else if(LuaHelper::checkudata_orNull(L, 2, LUA_IMAGE_METATABLENAME))
    {
        Lua_Image* imageToCopyPtr = static_cast<Lua_Image*>(lua_touserdata(L, 2));
        texturePtr->update(*imageToCopyPtr, x, y);
    }
    else if(LuaHelper::checkudata_orNull(L, 2, LUA_RENDERWINDOW_METATABLENAME))
    {
        Lua_RenderWindow* windowToCopyPtr = static_cast<Lua_RenderWindow*>(lua_touserdata(L, 2));
        texturePtr->update(*windowToCopyPtr, x, y);
    }

    return 0;
}

int TextureExporter::setSmooth(lua_State* L)
{
    Lua_Texture* texturePtr = static_cast<Lua_Texture*>( luaL_checkudata(L, 1, LUA_TEXTURE_METATABLENAME) );
    bool smooth = lua_toboolean(L, 2);
    texturePtr->setSmooth(smooth);

    return 0;
}

int TextureExporter::isSmooth(lua_State* L)
{
    Lua_Texture* texturePtr = static_cast<Lua_Texture*>( luaL_checkudata(L, 1, LUA_TEXTURE_METATABLENAME) );
    lua_pushboolean(L, texturePtr->isSmooth());
    return 1;
}

int TextureExporter::setSrgb(lua_State* L)
{
    Lua_Texture* texturePtr = static_cast<Lua_Texture*>( luaL_checkudata(L, 1, LUA_TEXTURE_METATABLENAME) );
    bool srgb = lua_toboolean(L, 2);
    texturePtr->setSmooth(srgb);

    return 0;
}

int TextureExporter::isSrgb(lua_State* L)
{
    Lua_Texture* texturePtr = static_cast<Lua_Texture*>( luaL_checkudata(L, 1, LUA_TEXTURE_METATABLENAME) );
    lua_pushboolean(L, texturePtr->isSrgb());
    return 1;
}

int TextureExporter::setRepeated(lua_State* L)
{
    Lua_Texture* texturePtr = static_cast<Lua_Texture*>( luaL_checkudata(L, 1, LUA_TEXTURE_METATABLENAME) );
    bool repeated = lua_toboolean(L, 2);
    texturePtr->setRepeated(repeated);

    return 0;
}

int TextureExporter::isRepeated(lua_State* L)
{
    Lua_Texture* texturePtr = static_cast<Lua_Texture*>( luaL_checkudata(L, 1, LUA_TEXTURE_METATABLENAME) );
    lua_pushboolean(L, texturePtr->isRepeated());
    return 1;
}

int TextureExporter::generateMipmap(lua_State* L)
{
    Lua_Texture* texturePtr = static_cast<Lua_Texture*>( luaL_checkudata(L, 1, LUA_TEXTURE_METATABLENAME) );
    lua_pushboolean(L, texturePtr->generateMipmap());
    return 1;
}

int TextureExporter::swap(lua_State* L)
{
    Lua_Texture* firstTexturePtr = static_cast<Lua_Texture*>( luaL_checkudata(L, 1, LUA_TEXTURE_METATABLENAME) );
    Lua_Texture* secondTexturePtr = static_cast<Lua_Texture*>( luaL_checkudata(L, 2, LUA_TEXTURE_METATABLENAME) );

    firstTexturePtr->swap(*secondTexturePtr);
    return 0;
}

int TextureExporter::getNativeHandle(lua_State* L)
{
    Lua_Texture* texturePtr = static_cast<Lua_Texture*>( luaL_checkudata(L, 1, LUA_TEXTURE_METATABLENAME) );
    lua_pushinteger(L, texturePtr->getNativeHandle());
    return 1;
}

int TextureExporter::getMaximumSize(lua_State* L)
{
    lua_pushinteger(L, Lua_Texture::getMaximumSize());
    return 1;
}

LuaExporter TextureExporter::toLuaExporter()
{
    LuaExporter exporter(
        LUA_TEXTURE_CLASSNAME,
        __new,
        {
            {"create", TextureExporter::create},
            {"loadFromFile", TextureExporter::loadFromFile},
            {"loadFromImage", TextureExporter::loadFromImage},
            {"getSize", TextureExporter::getSize},
            {"copyToImage", TextureExporter::copyToImage},
            {"update", TextureExporter::update},
            {"setSmooth", TextureExporter::setSmooth},
            {"isSmooth", TextureExporter::isSmooth},
            {"setSrgb", TextureExporter::setSrgb},
            {"isSrgb", TextureExporter::isSrgb},
            {"setRepeated", TextureExporter::setRepeated},
            {"isRepeated", TextureExporter::isRepeated},
            {"generateMipmap", TextureExporter::generateMipmap},
            {"swap", TextureExporter::swap},
            {"getNativeHandle", TextureExporter::getNativeHandle},
            {"getMaximumSize", TextureExporter::getMaximumSize},
        },
        {
            {"__gc", TextureExporter::__destroy},
            {"__index", TextureExporter::__index},
        }
    );

    return exporter;
}
