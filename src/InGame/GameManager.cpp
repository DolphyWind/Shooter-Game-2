#include <InGame/GameManager.hpp>

GameManager::GameManager():
    m_entities()
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
}

void GameManager::destroy()
{
    // This will call entity->onDestroy()
    m_entities.clear();
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
            bool collided = false;
            std::optional<sfex::Vec2> intersectionPoint;

            for(auto& line1 : e1->getColliderLines())
            {
                for(auto& line2 : e2->getOuterLines())
                {
                    intersectionPoint = Global::getIntersectionPoint({
                                                                         line1[0].position + e1->getPosition(),
                                                                         line1[1].position + e1->getPosition()
                                                                     }, {
                                                                         line2[0].position + e2->getPosition(),
                                                                         line2[1].position + e2->getPosition()
                                                                     });

                    if(intersectionPoint.has_value())
                    {
                        collided = true;
                        break;
                    }
                }
                if(collided) break;
            }

            if(collided)
            {
                if(!m_collisionTable.contains(e1.get()) || !m_collisionTable[e1.get()].contains(e2.get()))
                {
                    m_collisionTable[e1.get()].insert(e2.get());
                    e1->onCollisionEnter(e2.get(), intersectionPoint.value());
                }
                else
                {
                    e1->onCollisionStay(e2.get(), intersectionPoint.value());
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
