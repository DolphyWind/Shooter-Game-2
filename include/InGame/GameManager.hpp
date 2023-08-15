#pragma once
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <memory>

#include <InGame/Entity.hpp>

class GameManager
{
public:
    GameManager();
    ~GameManager() = default;

    void start();
    void handleEvent(const sf::Event& e);
    void update(const sf::Time& deltaTime);
    void lateUpdate(const sf::Time& deltaTime);
    void render(sf::RenderTarget& target, bool debugRender = false);
    void destroy();

    template<class T, typename... Args>
    void addEntity(Args&&... args);
    void checkCollisions();
    std::vector<std::unique_ptr<Entity>>& getEntities();
private:
    std::vector<std::unique_ptr<Entity>> m_entities;
    std::unordered_map<Entity*, std::unordered_set<Entity*>> m_collisionTable;
};

template<class T, typename... Args>
void GameManager::addEntity(Args&& ... args)
{
    m_entities.push_back( std::make_unique<T>(std::forward<Args>(args)...) );
}
