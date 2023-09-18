#pragma once
#include <InGame/Entity.hpp>
#include <Modding/LuaFunction.hpp>
#include <filesystem>

struct lua_State;
class LuaEntity : public Entity
{
public:
    LuaEntity(Game* parent, const std::string& filename, const std::filesystem::path& assetsFolderPath);
    virtual ~LuaEntity();

    virtual void start() override;
    virtual void handleEvent(const sf::Event& e) override;
    virtual void update(const sf::Time& deltaTime) override;
    virtual void lateUpdate(const sf::Time& deltaTime) override;
    virtual void onDestroy() override;
    virtual void render(sf::RenderTarget& target) override;
    virtual void onDeath() override;

    virtual void onCollisionEnter(Entity* other) override;
    virtual void onCollisionStay(Entity* other) override;
    virtual void onCollisionExit(Entity* other) override;

    lua_State* getLuaState() const;

private:
    lua_State* m_entityLuaState;
    LuaFunction m_startFunction;
    LuaFunction m_handleEventFunction;
    LuaFunction m_updateFunction;
    LuaFunction m_lateUpdateFunction;
    LuaFunction m_onDestroyFunction;
    LuaFunction m_renderFunction;
    LuaFunction m_onDeathFunction;
    LuaFunction m_onCollisionEnterFunction;
    LuaFunction m_onCollisionStayFunction;
    LuaFunction m_onCollisionExitFunction;

    std::filesystem::path m_assetsFolderPath;
    LuaEntity** thisPtr;
};
