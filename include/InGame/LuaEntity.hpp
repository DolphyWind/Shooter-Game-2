#pragma once
#include <InGame/Entity.hpp>
#include <Modding/LuaFunction.hpp>
#include <boost/filesystem.hpp>

struct lua_State;
class LuaEntity : public Entity
{
public:
    LuaEntity(Game* parent, const std::string& filename, const boost::filesystem::path& assetsFolderPath);
    virtual ~LuaEntity();

    virtual void start() override;
    virtual void update(const sf::Time& deltaTime) override;
    virtual void lateUpdate(const sf::Time& deltaTime) override;
    virtual void onDestroy() override;
    virtual void render(sf::RenderTarget& target) override;

    virtual void onCollisionEnter(Entity* other) override;
    virtual void onCollisionStay(Entity* other) override;
    virtual void onCollisionExit(Entity* other) override;

private:
    lua_State* m_entityLuaState;
    LuaFunction m_startFunction;
    LuaFunction m_updateFunction;
    LuaFunction m_lateUpdateFunction;
    LuaFunction m_onDestroyFunction;
    LuaFunction m_renderFunction;
    LuaFunction m_onCollisionEnterFunction;
    LuaFunction m_onCollisionStayFunction;
    LuaFunction m_onCollisionExitFunction;

    boost::filesystem::path m_assetsFolderPath;
};
