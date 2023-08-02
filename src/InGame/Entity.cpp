#include <InGame/Entity.hpp>

Entity::Entity(Game* parent):
    m_health(100), m_colliderPoints(), m_parent(parent)
{
    start();
}

Entity::~Entity()
{
    onDestroy();
}

void Entity::setHealth(float newHealth)
{
    m_health = newHealth;
    if(m_health <= 0)
    {
        this->onDestroy();
        // Destroy the object here
    }
}

void Entity::changeHealth(float delta)
{
    setHealth(getHealth() + delta);
}

float Entity::getHealth() const
{
    return m_health;
}

void Entity::setCollider(const std::vector<sfex::Vec2>& points)
{
    m_colliderPoints = points;
}

std::vector<sfex::Vec2> Entity::getCollider() const
{
    return m_colliderPoints;
}

bool Entity::isPlayer()
{
    return false;
}

void Entity::setPosition(const sfex::Vec2& newPos)
{
    m_position = newPos;
}

void Entity::move(const sfex::Vec2& delta)
{
    m_position += delta;
}

sfex::Vec2 Entity::getPosition() const
{
    return m_position;
}

Game* Entity::getParent()
{
    return m_parent;
}