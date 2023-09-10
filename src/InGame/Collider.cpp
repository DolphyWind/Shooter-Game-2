#include <InGame/Collider.hpp>
#include <InGame/Entity.hpp>

Collider::Collider(Entity* entity):
    m_isStatic(false), m_colliderCenter(), m_points(), m_innerLines(), m_outerLines()
{
    setEntity(entity);
}

Collider::Collider(const std::vector<sfex::Vec2>& points, bool isStatic, Entity* entity):
    m_points(), m_innerLines(), m_outerLines()
{
    setEntity(entity);
    setPoints(points);
    setStatic(isStatic);
}

void Collider::setPoints(const std::vector<sfex::Vec2>& points)
{
    m_points = points;

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
        m_innerLines[i][1].position = m_points[i];
        m_innerLines[i][0].color = m_innerLines[i][1].color = sfex::Color::Blue;

        if(i != points.size() - 1)
        {
            m_outerLines[i] = sf::VertexArray(sf::LinesStrip, 2);
            m_outerLines[i][0].position = m_points[i];
            m_outerLines[i][1].position = m_points[i + 1];
            m_outerLines[i][0].color = m_outerLines[i][1].color = sfex::Color::Yellow;
        }
    }
    m_outerLines[points.size() - 1] = sf::VertexArray(sf::LinesStrip, 2);
    m_outerLines[points.size() - 1][0] = m_points[points.size() - 1];
    m_outerLines[points.size() - 1][1] = m_points[0];
    m_outerLines[points.size() - 1][0].color = m_outerLines[points.size() - 1][1].color = sfex::Color::Yellow;
}

void Collider::setStatic(bool isStatic)
{
    m_isStatic = isStatic;
}

void Collider::setImmovable(bool immovable)
{
    m_isImmovable = immovable;
}

void Collider::setEntity(Entity* entity)
{
    m_entityPtr = entity;
    if(!entity) return;

    if(entity->getCollider() != *this)
    {
        entity->setCollider(*this);
    }
}

sfex::Vec2 Collider::getColliderCenter() const
{
    return m_colliderCenter;
}

const std::vector<sfex::Vec2>& Collider::getPoints() const
{
    return m_points;
}

const std::vector<sf::VertexArray>& Collider::getInnerLines() const
{
    return m_innerLines;
}

const std::vector<sf::VertexArray>& Collider::getOuterLines() const
{
    return m_outerLines;
}


bool Collider::isStatic() const
{
    return m_isStatic;
}

bool Collider::isImmovable() const
{
    return m_isImmovable;
}

Entity* Collider::getEntity() const
{
    return m_entityPtr;
}

std::optional<std::pair<float, float>> Collider::getIntersectionParams(const Line &firstLine, const Line &secondLine)
{
    // Source: https://www.youtube.com/watch?v=5FkOO1Wwb8w

    sfex::Vec2 AB = firstLine.endPoint - firstLine.beginPoint; // B - A
    sfex::Vec2 CD = secondLine.endPoint - secondLine.beginPoint; // D - C
    sfex::Vec2 AC = secondLine.beginPoint - firstLine.beginPoint; // C - A

    float determinant = AB.cross(CD);
    if(determinant == 0) return std::nullopt;

    float t1 = (CD.y * AC.x - CD.x * AC.y) / determinant;
    float t2 = (AB.y * AC.x - AB.x * AC.y) / determinant;

    if((t1 >= 0 && t1 <= 1) && (t2 >= 0 && t2 <= 1))
    {
        return std::pair{t1, t2};
    }

    return std::nullopt;
}

bool Collider::checkCollisions(const Collider& other) const
{
    bool collidedAtLeastOnce = false;
    sfex::Vec2 intersectionPoint;
    sfex::Vec2 displacementVector;
    std::optional<std::pair<float, float>> parametersOfCollision;

    for(auto& line1 : this->getInnerLines())
    {
        bool collided = false;
        sfex::Vec2 entityPos = sfex::Vec2::zero;
        if(getEntity())
        {
            entityPos = getEntity()->getPosition();
        }

        Collider::Line firstLine = {
            line1[0].position + entityPos,
            line1[1].position + entityPos
        };
        for(auto& line2 : other.getOuterLines())
        {
            sfex::Vec2 othersEntityPos = sfex::Vec2::zero;
            if(other.getEntity())
            {
                othersEntityPos = other.getEntity()->getPosition();
            }

            Collider::Line secondLine = {
                line2[0].position + othersEntityPos,
                line2[1].position + othersEntityPos
            };
            parametersOfCollision = Collider::getIntersectionParams(firstLine, secondLine);

            if(parametersOfCollision.has_value())
            {
                intersectionPoint = sfex::Math::lerp(
                    firstLine.beginPoint,
                    firstLine.endPoint,
                    parametersOfCollision->first
                );
                collided = true;
                collidedAtLeastOnce = true;
                break;
            }
        }
        if(collided)
        {
            displacementVector -= (1 - parametersOfCollision->first) * (firstLine.endPoint - firstLine.beginPoint);
        }
    }

    if(isStatic() && other.isStatic() && !isImmovable() && getEntity())
    {
        getEntity()->move(displacementVector);
    }
    return collidedAtLeastOnce;
}

bool Collider::operator==(const Collider& collider)
{
    return collider.getPoints() == this->getPoints() &&
           collider.isStatic() == this->isStatic() &&
           collider.isImmovable() == this->isImmovable();
}

bool Collider::operator!=(const Collider& collider)
{
    return !this->operator==(collider);
}