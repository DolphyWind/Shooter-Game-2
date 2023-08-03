#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <SFEX/SFEX.hpp>
#include <Global.hpp>

class Game;
class Entity
{
public:
    Entity(Game* parent);
    virtual ~Entity();

    virtual void start() {};
    virtual void update(const sf::Time& deltaTime) {};
    virtual void lateUpdate(const sf::Time& deltaTime) {};
    virtual void onDestroy() {};
    virtual void handleEvent(const sf::Event& e) {};
    virtual void render(sf::RenderTarget& target) {};
    void debugRender(sf::RenderTarget& target);
    
    void setHealth(float newHealth);
    void changeHealth(float delta);
    float getHealth() const;

    virtual void setPosition(const sfex::Vec2& newPos);
    virtual void move(const sfex::Vec2& delta);
    sfex::Vec2 getPosition() const;

    Game* getParent();

    virtual bool isPlayer();

    virtual void onCollisionEnter(Entity* other, sfex::Vec2 intersectionPoint) {};
    virtual void onCollisionStay(Entity* other, sfex::Vec2 intersectionPoint) {};
    virtual void onCollisionExit(Entity* other) {};

    void setCollider(const std::vector<sfex::Vec2>& points);
    std::vector<sfex::Vec2> getCollider() const;
    const std::vector<sf::VertexArray>& getColliderLines() const;
    const std::vector<sf::VertexArray>& getOuterLines() const;

protected:
    float m_health;
    sfex::Vec2 m_position;
    std::vector<sfex::Vec2> m_collider;
    std::vector<sf::VertexArray> m_innerLines;
    std::vector<sf::VertexArray> m_outerLines;
    Game* m_parent;
};