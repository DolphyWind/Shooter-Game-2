#pragma once
#include <SFEX/SFEX.hpp>
#include <SFML/Graphics.hpp>
#include <numeric>

class Entity;
class Collider
{
public:
    struct Line
    {
        sfex::Vec2 beginPoint;
        sfex::Vec2 endPoint;
    };

    Collider(Entity* entity=nullptr);
    Collider(const std::vector<sfex::Vec2>& points, bool isStatic=false, Entity* entity=nullptr);

    void setPoints(const std::vector<sfex::Vec2>& points);
    void setStatic(bool isStatic);
    void setImmovable(bool immovable);
    void setEntity(Entity* entity);

    sfex::Vec2 getColliderCenter() const;
    const std::vector<sfex::Vec2>& getPoints() const;
    const std::vector<sf::VertexArray>& getInnerLines() const;
    const std::vector<sf::VertexArray>& getOuterLines() const;

    bool isStatic() const;
    bool isImmovable() const;
    Entity* getEntity() const;

    /// Checks the collision between two lines, returns a pair of normalized floats that can be used to find the point of intersection. Returns std::nullopt if there is no intersection.
    /// @param firstLine First line
    /// @param secondLine Second line
    /// @return A pair of normalized floats that can be used to find the point of intersection
    static std::optional<std::pair<float, float>> getIntersectionParams(const Line& firstLine, const Line& secondLine);

    /// Checks the collisions with another collider. Returns true if there is at least one collision. Displaces current collider automatically if there is a collision.
    /// \param other Other collider
    /// \return True if there is at least one collision
    bool checkCollisions(const Collider& other) const;


    bool operator==(const Collider& collider) const;
    bool operator!=(const Collider& collider) const;
private:
    bool m_isStatic;
    bool m_isImmovable;
    Entity* m_entityPtr;

    sfex::Vec2 m_colliderCenter;
    std::vector<sfex::Vec2> m_points;
    std::vector<sf::VertexArray> m_innerLines;
    std::vector<sf::VertexArray> m_outerLines;
};