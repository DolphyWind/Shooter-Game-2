#include <InGame/GameManager.hpp>
#include <InGame/Entity.hpp>
#include <InGame/LuaEntity.hpp>
#include <InGame/Game.hpp>

GameManager::GameManager(Game* game):
    m_entities(), m_parent(game)
{

}

GameManager::~GameManager()
{

}

void GameManager::start()
{
    for(auto& e : m_entities)
    {
        e->start();
    }
}

void GameManager::update(const sf::Time& deltaTime)
{
    for(auto& e : m_entities)
    {
        e->update(deltaTime);
    }
}

void GameManager::lateUpdate(const sf::Time& deltaTime)
{
    for(auto& e : m_entities)
    {
        e->lateUpdate(deltaTime);
    }

    checkCollisions();
}

void GameManager::render(sf::RenderTarget& target, bool debugRender)
{
    for(auto& e : m_entities)
    {
        e->render(target);
        if(debugRender) e->debugRender(target);
    }

    moveNewEntities();
    destroyEntities();
}

void GameManager::destroy()
{
    m_entities.clear();
    m_collisionTable.clear();
    m_parent = nullptr;
}

void GameManager::setParent(Game* parent)
{
    m_parent = parent;
}

Game* GameManager::getParent()
{
    return m_parent;
}

void GameManager::checkCollisions()
{
    enum CollisionState
    {
        COLLISION_ENTER,
        COLLISION_STAY,
        COLLISION_EXIT
    };

    std::vector<std::tuple<Entity*, Entity*, CollisionState>> collidedEntities;

    for(std::size_t i = 0; i < m_entities.size(); ++i)
    {
        for(std::size_t j = i + 1; j < m_entities.size(); ++j)
        {
            if(i == j) continue;

            auto& e1 = m_entities[i];
            auto& e2 = m_entities[j];
            bool collidedAtLeastOnce = e1->getCollider().checkCollisions(e2->getCollider());

            if(collidedAtLeastOnce)
            {
                if(!m_collisionTable.contains(e1.get()) || !m_collisionTable[e1.get()].contains(e2.get()))
                {
                    collidedEntities.emplace_back(e1.get(), e2.get(), COLLISION_ENTER);
                }
                else
                {
                    collidedEntities.emplace_back(e1.get(), e2.get(), COLLISION_STAY);
                }
            }
            else
            {
                if(m_collisionTable.contains(e1.get()) && m_collisionTable.at(e1.get()).contains(e2.get()))
                {
                    collidedEntities.emplace_back(e1.get(), e2.get(), COLLISION_EXIT);
                }
            }
        }
    }

    for(auto& collisionInfo : collidedEntities)
    {
        Entity* e1 = std::get<0>(collisionInfo);
        Entity* e2 = std::get<1>(collisionInfo);
        CollisionState collisionState = std::get<2>(collisionInfo);

        switch (collisionState)
        {
            case COLLISION_ENTER:
            {
                m_collisionTable[e1].insert(e2);
                e1->onCollisionEnter(e2);
                e2->onCollisionEnter(e1);
                break;
            }
            case COLLISION_STAY:
            {
                e1->onCollisionStay(e2);
                e2->onCollisionStay(e1);
                break;
            }
            case COLLISION_EXIT:
            {
                m_collisionTable[e1].erase(e2);
                e1->onCollisionExit(e2);
                e2->onCollisionExit(e1);
                break;
            }
        }
    }
}

void GameManager::handleEvent(const sf::Event& e)
{
    for(auto& entity : m_entities)
    {
        entity->handleEvent(e);
    }
}

std::vector<std::unique_ptr<Entity>>& GameManager::getEntities()
{
    return m_entities;
}

Entity* GameManager::spawnEntity(const std::pair<Mod, EntityData>& entityData)
{
    Mod mod = entityData.first;
    EntityData data = entityData.second;

    return addEntity<LuaEntity>(m_parent, mod.config.getModName(), data.name, mod.entitiesFolderPath / data.file, mod.assetsFolderPath);
}

void GameManager::moveNewEntities()
{
    for(auto& e : m_newEntities)
    {
        e->start();
        m_entities.push_back(std::move(e));
    }
    m_newEntities.clear();
}

void GameManager::destroyEntity(Entity* entityPtr)
{
    m_destroyedEntities.emplace_back(entityPtr);
}

void GameManager::destroyEntities()
{
    for(auto& e : m_destroyedEntities)
    {
        auto it = std::find_if(
            m_entities.begin(),
            m_entities.end(),
            [e](auto& item){
                return item.get() == e;
            }
        );

        if(it != m_entities.end())
        {
            m_entities.erase(it);
        }
    }

    m_destroyedEntities.clear();
}
