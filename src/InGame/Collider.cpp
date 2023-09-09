#include <InGame/Collider.hpp>

Collider::Collider():
    m_isStatic(false), m_colliderCenter(), m_points(), m_innerLines(), m_outerLines()
{}

Collider::Collider(const std::vector<sfex::Vec2>& points, bool isStatic)
{
    setCollider(points);
    setStatic(isStatic);
}

void Collider::setCollider(const std::vector<sfex::Vec2>& points)
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

void Collider::setStatic(bool isStatic)
{
    m_isStatic = isStatic;
}

bool Collider::isStatic() const
{
    return m_isStatic;
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
