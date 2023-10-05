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
    for(std::size_t i = 0; i < m_entities.size(); ++i)
    {
        for(std::size_t j = 0; j < m_entities.size(); ++j)
        {
            if(i == j) continue;

            auto& e1 = m_entities[i];
            auto& e2 = m_entities[j];
            bool collidedAtLeastOnce = e1->getCollider().checkCollisions(e2->getCollider());

            if(collidedAtLeastOnce)
            {
                if(!m_collisionTable.contains(e1.get()) || !m_collisionTable[e1.get()].contains(e2.get()))
                {
                    m_collisionTable[e1.get()].insert(e2.get());
                    e1->onCollisionEnter(e2.get());
                }
                else
                {
                    e1->onCollisionStay(e2.get());
                }
            }
            else
            {
                if(m_collisionTable.contains(e1.get()) && m_collisionTable.at(e1.get()).contains(e2.get()))
                {
                    m_collisionTable[e1.get()].erase(e2.get());
                    e1->onCollisionExit(e2.get());
                }
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
        m_entities.push_back(std::move(e));
    }
    m_newEntities.clear();
}