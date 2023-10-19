#include <InGame/Entity.hpp>
#include <InGame/Game.hpp>

Entity::Entity(Game* parent, const std::string& modName, const std::string& name):
    m_health(100), m_position(), m_collider(this), m_parent(parent), m_modName(modName), m_name(name), m_metadata()
{
}

Entity::~Entity()
{
}

void Entity::setHealth(float newHealth)
{
    m_health = newHealth;
    if(m_health <= 0)
    {
        this->onDeath();
        Global::defaultGameManager.destroyEntity(this);
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

std::string Entity::getName() const
{
    return m_name;
}

std::string Entity::getModName() const
{
    return m_modName;
}

std::string Entity::getFullName() const
{
    return m_modName + "/" + m_name;
}

void Entity::setMetadata(const std::string& newMetadata)
{
    m_metadata = newMetadata;
}

std::string Entity::getMetadata() const
{
    return m_metadata;
}

