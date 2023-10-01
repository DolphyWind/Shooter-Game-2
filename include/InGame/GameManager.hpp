#pragma once
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <SFML/Graphics.hpp>
#include <memory>

#include <InGame/Entity.hpp>
#include <Modding/Mod.hpp>

class Entity;
class LuaEntity;
class Game;
class GameManager
{
public:
    GameManager() = default;
    GameManager(Game* parent);
    ~GameManager();

    void start();
    void handleEvent(const sf::Event& e);
    void update(const sf::Time& deltaTime);
    void lateUpdate(const sf::Time& deltaTime);
    void render(sf::RenderTarget& target, bool debugRender = false);
    void destroy();

    void setParent(Game* parent);
    Game* getParent();

    template<class T, typename... Args>
    T* addEntity(Args&&... args);
    void checkCollisions();
    std::vector<std::unique_ptr<Entity>>& getEntities();
    Entity* spawnEntity(const std::pair<Mod, EntityData>& entityData);
    void moveNewEntities();
private:
    std::vector<std::unique_ptr<Entity>> m_entities;
    std::vector<std::unique_ptr<Entity>> m_newEntities;

    std::unordered_map<Entity*, std::unordered_set<Entity*>> m_collisionTable;
    Game* m_parent;
};

template<class T, typename... Args>
T* GameManager::addEntity(Args&& ... args)
{
    m_newEntities.push_back( std::make_unique<T>(std::forward<Args>(args)...) );
    return static_cast<T*>(m_newEntities[m_newEntities.size() - 1].get());
}
