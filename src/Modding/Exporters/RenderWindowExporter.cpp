#include <Modding/Exporters/RenderWindowExporter.hpp>
#include <Modding/Exporters/Vector2Exporter.hpp>
#include <Modding/Exporters/ImageExporter.hpp>
#include <Modding/Exporters/ColorExporter.hpp>
#include <Modding/Exporters/ViewExporter.hpp>
#include <Modding/Exporters/IntRectExporter.hpp>
#include <Modding/LuaExporter.hpp>

int RenderWindowExporter::__index(lua_State *L)
{
    Lua_RenderWindow* renderWindowPtr = static_cast<Lua_RenderWindow*>( luaL_checkudata(L, 1, LUA_RENDERWINDOW_METATABLENAME) );
    std::string indexStr = luaL_checkstring(L, 2);

    if(indexStr == "StyleNone")
    {
        lua_pushinteger(L, sf::Style::None);
        return 1;
    }
    else if(indexStr == "Titlebar")
    {
        lua_pushinteger(L, sf::Style::Titlebar);
        return 1;
    }
    else if(indexStr == "Resize")
    {
        lua_pushinteger(L, sf::Style::Resize);
        return 1;
    }
    else if(indexStr == "Close")
    {
        lua_pushinteger(L, sf::Style::Close);
        return 1;
    }
    else if(indexStr == "Fullscreen")
    {
        lua_pushinteger(L, sf::Style::Fullscreen);
        return 1;
    }
    else if(indexStr == "Default")
    {
        lua_pushinteger(L, sf::Style::Default);
        return 1;
    }

    lua_getglobal(L, LUA_RENDERWINDOW_CLASSNAME);
    lua_pushstring(L, indexStr.c_str());
    lua_rawget(L, -2);
    return 1;
}

int RenderWindowExporter::__destroy(lua_State *L)
{
    Lua_RenderWindow* renderWindowPtr = static_cast<Lua_RenderWindow*>( luaL_checkudata(L, 1, LUA_RENDERWINDOW_METATABLENAME) );
    renderWindowPtr->~Lua_RenderWindow();
    return 0;
}

int RenderWindowExporter::getSize(lua_State *L)
{
    Lua_RenderWindow* renderWindowPtr = static_cast<Lua_RenderWindow*>( luaL_checkudata(L, 1, LUA_RENDERWINDOW_METATABLENAME) );
    Vector2Exporter::createVector(L, renderWindowPtr->getSize());
    return 1;
}

int RenderWindowExporter::setActive(lua_State *L)
{
    int arg_count = lua_gettop(L);
    Lua_RenderWindow* renderWindowPtr = static_cast<Lua_RenderWindow*>( luaL_checkudata(L, 1, LUA_RENDERWINDOW_METATABLENAME) );
    bool active = true;
    
    if(arg_count == 2)
    {
        active = lua_toboolean(L, 2);
    }

    renderWindowPtr->setActive(active);
    return 0;
}

int RenderWindowExporter::close(lua_State *L)
{
    Lua_RenderWindow* renderWindowPtr = static_cast<Lua_RenderWindow*>( luaL_checkudata(L, 1, LUA_RENDERWINDOW_METATABLENAME) );
    renderWindowPtr->close();
    return 0;
}

int RenderWindowExporter::isOpen(lua_State *L)
{
    Lua_RenderWindow* renderWindowPtr = static_cast<Lua_RenderWindow*>( luaL_checkudata(L, 1, LUA_RENDERWINDOW_METATABLENAME) );
    lua_pushboolean(L, renderWindowPtr->isOpen());
    return 1;
}

int RenderWindowExporter::getPosition(lua_State *L)
{
    Lua_RenderWindow* renderWindowPtr = static_cast<Lua_RenderWindow*>( luaL_checkudata(L, 1, LUA_RENDERWINDOW_METATABLENAME) );
    Vector2Exporter::createVector(L, renderWindowPtr->getPosition());
    return 1;
}

int RenderWindowExporter::setPosition(lua_State *L)
{
    Lua_RenderWindow* renderWindowPtr = static_cast<Lua_RenderWindow*>( luaL_checkudata(L, 1, LUA_RENDERWINDOW_METATABLENAME) );
    Lua_Vector2* positionPtr = static_cast<Lua_Vector2*>( luaL_checkudata(L, 2, LUA_VECTOR2_METATABLENAME) );
    renderWindowPtr->setPosition( *positionPtr );
    return 0;
}

int RenderWindowExporter::setSize(lua_State *L)
{
    Lua_RenderWindow* renderWindowPtr = static_cast<Lua_RenderWindow*>( luaL_checkudata(L, 1, LUA_RENDERWINDOW_METATABLENAME) );
    Lua_Vector2* sizePtr = static_cast<Lua_Vector2*>( luaL_checkudata(L, 2, LUA_VECTOR2_METATABLENAME) );
    renderWindowPtr->setSize( *sizePtr );

    return 0;
}

int RenderWindowExporter::setTitle(lua_State *L)
{
    Lua_RenderWindow* renderWindowPtr = static_cast<Lua_RenderWindow*>( luaL_checkudata(L, 1, LUA_RENDERWINDOW_METATABLENAME) );
    std::string titleStr = luaL_checkstring(L, 2);
    renderWindowPtr->setTitle(titleStr);

    return 0;
}

int RenderWindowExporter::setIcon(lua_State *L)
{
    Lua_RenderWindow* renderWindowPtr = static_cast<Lua_RenderWindow*>( luaL_checkudata(L, 1, LUA_RENDERWINDOW_METATABLENAME) );
    Lua_Image* iconPtr = static_cast<Lua_Image*>( luaL_checkudata(L, 2, LUA_IMAGE_METATABLENAME) );
    renderWindowPtr->setIcon(iconPtr->getSize().x, iconPtr->getSize().y, iconPtr->getPixelsPtr());

    return 0;
}

int RenderWindowExporter::setVisible(lua_State *L)
{
    Lua_RenderWindow* renderWindowPtr = static_cast<Lua_RenderWindow*>( luaL_checkudata(L, 1, LUA_RENDERWINDOW_METATABLENAME) );
    renderWindowPtr->setVisible( lua_toboolean(L, 2) );

    return 0;
}

int RenderWindowExporter::setVerticalSyncEnabled(lua_State *L)
{
    Lua_RenderWindow* renderWindowPtr = static_cast<Lua_RenderWindow*>( luaL_checkudata(L, 1, LUA_RENDERWINDOW_METATABLENAME) );
    renderWindowPtr->setVerticalSyncEnabled( lua_toboolean(L, 2) );
    
    return 0;
}

int RenderWindowExporter::setMouseCursorVisible(lua_State *L)
{
    Lua_RenderWindow* renderWindowPtr = static_cast<Lua_RenderWindow*>( luaL_checkudata(L, 1, LUA_RENDERWINDOW_METATABLENAME) );
    renderWindowPtr->setMouseCursorVisible( lua_toboolean(L, 2) );
    
    return 0;
}

int RenderWindowExporter::setMouseCursorGrabbed(lua_State *L)
{
    Lua_RenderWindow* renderWindowPtr = static_cast<Lua_RenderWindow*>( luaL_checkudata(L, 1, LUA_RENDERWINDOW_METATABLENAME) );
    renderWindowPtr->setMouseCursorGrabbed( lua_toboolean(L, 2) );
    
    return 0;
}

int RenderWindowExporter::setMouseCursor(lua_State *L)
{
    luaL_error(L, "Not yet implemented!");
    return 0;
}

int RenderWindowExporter::setKeyRepeatEnabled(lua_State *L)
{
    Lua_RenderWindow* renderWindowPtr = static_cast<Lua_RenderWindow*>( luaL_checkudata(L, 1, LUA_RENDERWINDOW_METATABLENAME) );
    renderWindowPtr->setKeyRepeatEnabled( lua_toboolean(L, 2) );
    
    return 0;
}

int RenderWindowExporter::setFramerateLimit(lua_State *L)
{
    Lua_RenderWindow* renderWindowPtr = static_cast<Lua_RenderWindow*>( luaL_checkudata(L, 1, LUA_RENDERWINDOW_METATABLENAME) );
    lua_Integer framerateLimit;
    lua_numbertointeger(luaL_checknumber(L, 2), &framerateLimit);
    renderWindowPtr->setFramerateLimit(framerateLimit);

    return 0;
}

int RenderWindowExporter::setJoystickTreshold(lua_State *L)
{
    Lua_RenderWindow* renderWindowPtr = static_cast<Lua_RenderWindow*>( luaL_checkudata(L, 1, LUA_RENDERWINDOW_METATABLENAME) );
    renderWindowPtr->setJoystickThreshold( luaL_checknumber(L, 2) );
    return 0;
}

int RenderWindowExporter::requestFocus(lua_State *L)
{
    Lua_RenderWindow* renderWindowPtr = static_cast<Lua_RenderWindow*>( luaL_checkudata(L, 1, LUA_RENDERWINDOW_METATABLENAME) );
    renderWindowPtr->requestFocus();
    return 0;
}

int RenderWindowExporter::hasFocus(lua_State *L)
{
    Lua_RenderWindow* renderWindowPtr = static_cast<Lua_RenderWindow*>( luaL_checkudata(L, 1, LUA_RENDERWINDOW_METATABLENAME) );
    lua_pushboolean(L, renderWindowPtr->hasFocus());
    return 1;
}

int RenderWindowExporter::display(lua_State *L)
{
    Lua_RenderWindow* renderWindowPtr = static_cast<Lua_RenderWindow*>( luaL_checkudata(L, 1, LUA_RENDERWINDOW_METATABLENAME) );
    renderWindowPtr->display();
    return 0;
}

int RenderWindowExporter::clear(lua_State *L)
{
    Lua_RenderWindow* renderWindowPtr = static_cast<Lua_RenderWindow*>( luaL_checkudata(L, 1, LUA_RENDERWINDOW_METATABLENAME) );
    Lua_Color clearColor(0, 0, 0, 255);
    clearColor = *static_cast<Lua_Color*>( luaL_checkudata(L, 2, LUA_COLOR_METATABLENAME) );
    renderWindowPtr->clear(clearColor);

    return 0;
}

int RenderWindowExporter::setView(lua_State *L)
{
    Lua_RenderWindow* renderWindowPtr = static_cast<Lua_RenderWindow*>( luaL_checkudata(L, 1, LUA_RENDERWINDOW_METATABLENAME) );
    Lua_View* viewPtr = static_cast<Lua_View*>( luaL_checkudata(L, 2, LUA_VIEW_METATABLENAME) );
    renderWindowPtr->setView(*viewPtr);

    return 0;
}

int RenderWindowExporter::getView(lua_State *L)
{
    Lua_RenderWindow* renderWindowPtr = static_cast<Lua_RenderWindow*>( luaL_checkudata(L, 1, LUA_RENDERWINDOW_METATABLENAME) );
    ViewExporter::createView(L, renderWindowPtr->getView());
    
    return 1;
}

int RenderWindowExporter::getDefaultView(lua_State *L)
{
    Lua_RenderWindow* renderWindowPtr = static_cast<Lua_RenderWindow*>( luaL_checkudata(L, 1, LUA_RENDERWINDOW_METATABLENAME) );
    ViewExporter::createView(L, renderWindowPtr->getDefaultView());
    
    return 1;
}

int RenderWindowExporter::getViewPort(lua_State *L)
{
    Lua_RenderWindow* renderWindowPtr = static_cast<Lua_RenderWindow*>( luaL_checkudata(L, 1, LUA_RENDERWINDOW_METATABLENAME) );
    Lua_View* viewPtr = static_cast<Lua_View*>( luaL_checkudata(L, 2, LUA_VIEW_METATABLENAME) );
    IntRectExporter::createIntRect(L, renderWindowPtr->getViewport(*viewPtr));
    
    return 1;
}

int RenderWindowExporter::mapPixelToCoords(lua_State *L)
{
    int arg_count = lua_gettop(L);
    Lua_RenderWindow* renderWindowPtr = static_cast<Lua_RenderWindow*>( luaL_checkudata(L, 1, LUA_RENDERWINDOW_METATABLENAME) );
    Lua_Vector2* pointPtr = static_cast<Lua_Vector2*>( luaL_checkudata(L, 2, LUA_VECTOR2_METATABLENAME) );

    if(arg_count == 2)
    {
        Vector2Exporter::createVector(L, renderWindowPtr->mapPixelToCoords(*pointPtr));
        return 1;
    }

    Lua_View* viewPtr = static_cast<Lua_View*>( luaL_checkudata(L, 3, LUA_VIEW_METATABLENAME) );
    Vector2Exporter::createVector(L, renderWindowPtr->mapPixelToCoords(*pointPtr, *viewPtr));

    return 1;
}

int RenderWindowExporter::mapCoordsToPixel(lua_State *L)
{
    int arg_count = lua_gettop(L);
    Lua_RenderWindow* renderWindowPtr = static_cast<Lua_RenderWindow*>( luaL_checkudata(L, 1, LUA_RENDERWINDOW_METATABLENAME) );
    Lua_Vector2* pointPtr = static_cast<Lua_Vector2*>( luaL_checkudata(L, 2, LUA_VECTOR2_METATABLENAME) );

    if(arg_count == 2)
    {
        Vector2Exporter::createVector(L, renderWindowPtr->mapCoordsToPixel(*pointPtr));
        return 1;
    }

    Lua_View* viewPtr = static_cast<Lua_View*>( luaL_checkudata(L, 3, LUA_VIEW_METATABLENAME) );
    Vector2Exporter::createVector(L, renderWindowPtr->mapCoordsToPixel(*pointPtr, *viewPtr));

    return 1;
}

int RenderWindowExporter::draw(lua_State *L)
{
    Lua_RenderWindow* renderWindowPtr = static_cast<Lua_RenderWindow*>( luaL_checkudata(L, 1, LUA_RENDERWINDOW_METATABLENAME) );
    sf::Drawable* drawablePtr = static_cast<sf::Drawable*>( lua_touserdata(L, 2) );

    renderWindowPtr->draw(*drawablePtr);
    return 0;
}

int RenderWindowExporter::pushGLStates(lua_State *L)
{
    Lua_RenderWindow* renderWindowPtr = static_cast<Lua_RenderWindow*>( luaL_checkudata(L, 1, LUA_RENDERWINDOW_METATABLENAME) );
    renderWindowPtr->pushGLStates();
    return 0;
}

int RenderWindowExporter::popGLStates(lua_State *L)
{
    Lua_RenderWindow* renderWindowPtr = static_cast<Lua_RenderWindow*>( luaL_checkudata(L, 1, LUA_RENDERWINDOW_METATABLENAME) );
    renderWindowPtr->popGLStates();
    return 0;
}

int RenderWindowExporter::resetGLStates(lua_State *L)
{
    Lua_RenderWindow* renderWindowPtr = static_cast<Lua_RenderWindow*>( luaL_checkudata(L, 1, LUA_RENDERWINDOW_METATABLENAME) );
    renderWindowPtr->resetGLStates();
    return 0;
}

LuaExporter RenderWindowExporter::toLuaExporter()
{
    LuaExporter exporter(
        LUA_RENDERWINDOW_CLASSNAME,
        nullptr,
        {
            {"getSize", RenderWindowExporter::getSize},
            {"setActive", RenderWindowExporter::setActive},
            {"close", RenderWindowExporter::close},
            {"isOpen", RenderWindowExporter::isOpen},
            {"getPosition", RenderWindowExporter::getPosition},
            {"setPosition", RenderWindowExporter::setPosition},
            {"setSize", RenderWindowExporter::setSize},
            {"setTitle", RenderWindowExporter::setTitle},
            {"setIcon", RenderWindowExporter::setIcon},
            {"setVisible", RenderWindowExporter::setVisible},
            {"setVerticalSyncEnabled", RenderWindowExporter::setVerticalSyncEnabled},
            {"setMouseCursorVisible", RenderWindowExporter::setMouseCursorVisible},
            {"setMouseCursorGrabbed", RenderWindowExporter::setMouseCursorGrabbed},
            {"setMouseCursor", RenderWindowExporter::setMouseCursor},
            {"setKeyRepeatEnabled", RenderWindowExporter::setKeyRepeatEnabled},
            {"setFramerateLimit", RenderWindowExporter::setFramerateLimit},
            {"setJoystickTreshold", RenderWindowExporter::setJoystickTreshold},
            {"requestFocus", RenderWindowExporter::requestFocus},
            {"hasFocus", RenderWindowExporter::hasFocus},
            {"display", RenderWindowExporter::display},
            {"clear", RenderWindowExporter::clear},
            {"setView", RenderWindowExporter::setView},
            {"getView", RenderWindowExporter::getView},
            {"getDefaultView", RenderWindowExporter::getDefaultView},
            {"getViewPort", RenderWindowExporter::getViewPort},
            {"mapPixelToCoords", RenderWindowExporter::mapPixelToCoords},
            {"mapCoordsToPixel", RenderWindowExporter::mapCoordsToPixel},
            {"draw", RenderWindowExporter::draw},
            {"pushGLStates", RenderWindowExporter::pushGLStates},
            {"popGLStates", RenderWindowExporter::popGLStates},
            {"resetGLStates", RenderWindowExporter::resetGLStates},
        },
        {
            {"__index", RenderWindowExporter::__index},
            {"__destroy", RenderWindowExporter::__destroy},
        }
    );

    exporter.addInteger("StyleNone", sf::Style::None);
    exporter.addInteger("StyleTitlebar", sf::Style::Titlebar);
    exporter.addInteger("StyleResize", sf::Style::Resize);
    exporter.addInteger("StyleClose", sf::Style::Close);
    exporter.addInteger("StyleFullscreen", sf::Style::Fullscreen);
    exporter.addInteger("StyleDefault", sf::Style::Default);

    return exporter;
}