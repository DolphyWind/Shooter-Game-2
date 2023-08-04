#include <InGame/Entity.hpp>
#include <InGame/Game.hpp>

Entity::Entity(Game* parent):
    m_health(100), m_collider(), m_parent(parent), m_innerLines(), m_outerLines()
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

    for(std::size_t i = 0; i < points.size(); ++i)
    {
        m_innerLines[i] = sf::VertexArray(sf::LinesStrip, 2);
        m_innerLines[i][0].position = sfex::Vec2::zero;
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