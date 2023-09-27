#include <lua.hpp>
#include <InGame/LuaEntity.hpp>
#include <InGame/Game.hpp>
#include <Modding/ShooterGameExporter.hpp>
#include <Modding/Exporters/EntityExporter.hpp>
#include <Modding/Exporters/EventExporter.hpp>
#include <Modding/Exporters/RenderWindowExporter.hpp>
#include <Modding/Exporters/Vector2Exporter.hpp>

LuaEntity::LuaEntity(Game* parent, const std::string& filename, const std::filesystem::path& assetsFolderPath):
    Entity(parent), m_assetsFolderPath(assetsFolderPath)
{
    m_entityLuaState = luaL_newstate();
    luaL_openlibs(m_entityLuaState);
    ShooterGameExporter::exportTo(m_entityLuaState);

    lua_pushstring(m_entityLuaState, assetsFolderPath.string().c_str());
    lua_setglobal(m_entityLuaState, ASSETSPATH_VARNAME);

    LuaHelper::push(m_entityLuaState, &Global::mainWindow, sizeof(sf::RenderWindow**), LUA_RENDERWINDOW_METATABLENAME);
    lua_setglobal(m_entityLuaState, "main_window");

    thisPtr = new LuaEntity*(this);
    LuaHelper::push(m_entityLuaState, thisPtr, sizeof(LuaEntity*), LUA_ENTITY_METATABLENAME);
    lua_setglobal(m_entityLuaState, "this");
    lua_pushcfunction(m_entityLuaState, LuaHelper::InterpretLUdataAs);
    lua_setglobal(m_entityLuaState, "InterpretLUdataAs");

    int status = luaL_dofile(m_entityLuaState, filename.c_str());
    if(status != LUA_OK)
    {
        throw std::runtime_error( lua_tostring(m_entityLuaState, -1) );
    }

    m_startFunction.load(m_entityLuaState, "start", 0, 0);
    m_handleEventFunction.load(m_entityLuaState, "handleEvent", 1, 0);
    m_updateFunction.load(m_entityLuaState, "update", 1, 0);
    m_lateUpdateFunction.load(m_entityLuaState, "lateUpdate", 1, 0);
    m_onDestroyFunction.load(m_entityLuaState, "onDestroy", 0, 0);
    m_renderFunction.load(m_entityLuaState, "render", 0, 0);
    m_onCollisionEnterFunction.load(m_entityLuaState, "onCollisionEnter", 1, 0);
    m_onCollisionStayFunction.load(m_entityLuaState, "onCollisionStay", 1, 0);
    m_onCollisionExitFunction.load(m_entityLuaState, "onCollisionExit", 1, 0);
    m_onDeathFunction.load(m_entityLuaState, "onDeath", 0, 0);

    start();
}

LuaEntity::~LuaEntity()
{
    m_onDestroyFunction();
    lua_close(m_entityLuaState);
    delete thisPtr;
}

void LuaEntity::start()
{
    m_startFunction();
}

void LuaEntity::handleEvent(const sf::Event& e)
{
    m_handleEventFunction((void*)&e);
}

void LuaEntity::update(const sf::Time& deltaTime)
{
    m_updateFunction(deltaTime.asSeconds());
}

void LuaEntity::lateUpdate(const sf::Time& deltaTime)
{
    m_lateUpdateFunction(deltaTime.asSeconds());
}

void LuaEntity::onDestroy()
{
    m_onDestroyFunction();
}

void LuaEntity::render(sf::RenderTarget& target)
{
    m_renderFunction();
}

void LuaEntity::onDeath()
{
    m_onDeathFunction();
}

void LuaEntity::onCollisionEnter(Entity* other)
{
    m_onCollisionEnterFunction((void*)other);
}

void LuaEntity::onCollisionStay(Entity* other)
{
    m_onCollisionStayFunction((void*)other);
}

void LuaEntity::onCollisionExit(Entity* other)
{
    m_onCollisionExitFunction((void*)other);
}

lua_State* LuaEntity::getLuaState() const
{
    return m_entityLuaState;
}
