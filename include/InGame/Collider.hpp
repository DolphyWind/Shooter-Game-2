#pragma once
#include <SFEX/SFEX.hpp>
#include <SFML/Graphics.hpp>
#include <numeric>

class Collider
{
public:
    Collider();
    Collider(const std::vector<sfex::Vec2>& points, bool isStatic=false);

    void setCollider(const std::vector<sfex::Vec2>& points);

    sfex::Vec2 getColliderCenter() const;
    const std::vector<sfex::Vec2>& getPoints() const;
    const std::vector<sf::VertexArray>& getInnerLines() const;
    const std::vector<sf::VertexArray>& getOuterLines() const;

    void setStatic(bool isStatic);
    bool isStatic() const;

private:
    bool m_isStatic;

    sfex::Vec2 m_colliderCenter;
    std::vector<sfex::Vec2> m_points;
    std::vector<sf::VertexArray> m_innerLines;
    std::vector<sf::VertexArray> m_outerLines;
};