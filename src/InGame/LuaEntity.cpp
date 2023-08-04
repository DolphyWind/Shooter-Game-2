#include <InGame/LuaEntity.hpp>
#include <Modding/ShooterGameExporter.hpp>

LuaEntity::LuaEntity(Game* parent, const std::string& filename, const boost::filesystem::path& assetsFolderPath):
    Entity(parent), m_assetsFolderPath(assetsFolderPath)
{
    m_entityLuaState = luaL_newstate();
    luaL_openlibs(m_entityLuaState);
    ShooterGameExporter::exportTo(m_entityLuaState);

    int status = luaL_dofile(m_entityLuaState, filename.c_str());
    if(status != LUA_OK)
    {
        throw std::runtime_error( lua_tostring(m_entityLuaState, -1) );
    }

    m_startFunction.load(m_entityLuaState, "start", 0, 0);
    m_updateFunction.load(m_entityLuaState, "update", 1, 0);
    m_lateUpdateFunction.load(m_entityLuaState, "lateUpdate", 1, 0);
    m_onDestroyFunction.load(m_entityLuaState, "onDestroy", 0, 0);
    m_renderFunction.load(m_entityLuaState, "render", 1, 0);
    m_onCollisionEnterFunction.load(m_entityLuaState, "onCollisionEnter", 2, 0);
    m_onCollisionStayFunction.load(m_entityLuaState, "onCollisionStay", 2, 0);
    m_onCollisionExitFunction.load(m_entityLuaState, "onCollisionExit", 1, 0);

    start();
}

LuaEntity::~LuaEntity()
{
    m_onDestroyFunction();
    lua_close(m_entityLuaState);
}

void LuaEntity::start()
{
    m_startFunction();
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
    m_renderFunction((void*)&target);
}

void LuaEntity::onCollisionEnter(Entity* other, sfex::Vec2 intersectionPoint)
{
    m_onCollisionEnterFunction((void*)other, (void*)&intersectionPoint);
}

void LuaEntity::onCollisionStay(Entity* other, sfex::Vec2 intersectionPoint)
{
    m_onCollisionStayFunction((void*)other, (void*)&intersectionPoint);
}

void LuaEntity::onCollisionExit(Entity* other)
{
    m_onCollisionExitFunction((void*)other);
}