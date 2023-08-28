#include <InGame/Entity.hpp>
#include <InGame/Game.hpp>

Entity::Entity(Game* parent):
    m_health(100), m_position(), m_colliderCenter(), m_collider(), m_innerLines(), m_outerLines(), m_parent(parent), m_name(), m_metadata()
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

void Entity::setCollider(const std::vector<sfex::Vec2>& points)
{
    m_collider = points;

    m_innerLines.resize(points.size());
    m_outerLines.resize(points.size());

    if(points.empty())
    {
        m_colliderCenter = sfex::Vec2::zero;
    }
    else
    {
        m_colliderCenter = std::accumulate(points.begin(), points.end(), sfex::Vec2::zero) / (float)points.size();
    }

    for(std::size_t i = 0; i < points.size(); ++i)
    {
        m_innerLines[i] = sf::VertexArray(sf::LinesStrip, 2);
        m_innerLines[i][0].position = m_colliderCenter;
        m_innerLines[i][1].position = m_collider[i];
        m_innerLines[i][0].color = m_innerLines[i][1].color = sfex::Color::Blue;

        if(i != points.size() - 1)
        {
            m_outerLines[i] = sf::VertexArray(sf::LinesStrip, 2);
            m_outerLines[i][0].position = m_collider[i];
            m_outerLines[i][1].position = m_collider[i + 1];
            m_outerLines[i][0].color = m_outerLines[i][1].color = sfex::Color::Yellow;
        }
    }
    m_outerLines[points.size() - 1] = sf::VertexArray(sf::LinesStrip, 2);
    m_outerLines[points.size() - 1][0] = m_collider[points.size() - 1];
    m_outerLines[points.size() - 1][1] = m_collider[0];
    m_outerLines[points.size() - 1][0].color = m_outerLines[points.size() - 1][1].color = sfex::Color::Yellow;

}

std::vector<sfex::Vec2> Entity::getCollider() const
{
    return m_collider;
}

const std::vector<sf::VertexArray>& Entity::getColliderLines() const
{
    return m_innerLines;
}

const std::vector<sf::VertexArray>& Entity::getOuterLines() const
{
    return m_outerLines;
}

sfex::Vec2  Entity::getColliderCenter() const
{
    return m_colliderCenter;
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

void Entity::debugRender(sf::RenderTarget& target)
{
    sf::Transform playerTransform;
    playerTransform.translate(getPosition());
    for(std::size_t i = 0; i < m_collider.size(); ++i)
    {
        target.draw(m_innerLines[i], playerTransform);
        target.draw(m_outerLines[i], playerTransform);
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
