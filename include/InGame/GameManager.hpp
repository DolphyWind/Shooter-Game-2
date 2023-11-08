#pragma once
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <memory>
#include <random>

#include <SFML/Graphics.hpp>
#include <InGame/Entity.hpp>
#include <InGame/Player.hpp>
#include <Modding/Mod.hpp>

struct EntityDataHasher
{
    std::size_t operator()(const EntityData& ed) const
    {
        return std::hash<std::string>()(ed.name);
    }
};

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

    void destroyEntity(Entity* entityPtr);
private:
    void destroyEntities();

    std::vector<std::unique_ptr<Entity>> m_entities;
    std::vector<std::unique_ptr<Entity>> m_newEntities;
    std::vector<Entity*> m_destroyedEntities;
    std::vector<unsigned> m_usedPlayerIds;

    std::unordered_map<Entity*, std::unordered_set<Entity*>> m_collisionTable;
    std::unordered_set<EntityData, EntityDataHasher> m_spawnedSingleInstanceEntities;
    Game* m_parent;
    bool ranStart = false;
};

template<class T, typename... Args>
T* GameManager::addEntity(Args&& ... args)
{
    std::unique_ptr<T> newEntity = std::make_unique<T>(std::forward<Args>(args)...);
    if(std::is_same_v<T, Player>)
    {
        unsigned id = 0;
        do
        {
            id = StaticRandom::get<unsigned>();
        }while(std::find(m_usedPlayerIds.begin(), m_usedPlayerIds.end(), id) != m_usedPlayerIds.end());

        m_usedPlayerIds.push_back(id);
        auto player = dynamic_cast<Player*>(newEntity.get());
        player->setPlayerId(id);
    }

    m_newEntities.emplace_back( std::move(newEntity) );
    return static_cast<T*>(m_newEntities[m_newEntities.size() - 1].get());
}

