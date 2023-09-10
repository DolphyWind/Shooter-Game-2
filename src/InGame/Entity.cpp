#include <InGame/Entity.hpp>
#include <InGame/Game.hpp>

Entity::Entity(Game* parent):
    m_health(100), m_position(), m_collider(this), m_parent(parent), m_name(), m_metadata()
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
        this->onDeath();
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

bool Entity::isPlayer()
{
    return false;
}

void Entity::setCollider(const Collider& collider)
{
    m_collider = collider;
    if(m_collider.getEntity() != this)
    {
        m_collider.setEntity(this);
    }
}

Collider& Entity::getCollider()
{
    return m_collider;
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

void Entity::debugRender(sf::RenderTarget& target)
{
    sf::Transform playerTransform;
    playerTransform.translate(getPosition());

    for(std::size_t i = 0; i < m_collider.getPoints().size(); ++i)
    {
        target.draw(m_collider.getInnerLines()[i], playerTransform);
        target.draw(m_collider.getOuterLines()[i], playerTransform);
    }
}

void Entity::setName(const std::string& newName)
{
    m_name = newName;
}

std::string Entity::getName() const
{
    return m_name;
}

void Entity::setMetadata(const std::string& newMetadata)
{
    m_metadata = newMetadata;
}

std::string Entity::getMetadata() const
{
    return m_metadata;
}
