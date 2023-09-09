#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <SFEX/SFEX.hpp>
#include <Global.hpp>
#include <InGame/Collider.hpp>

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
    virtual void onDeath() {}
    void debugRender(sf::RenderTarget& target);
    
    void setHealth(float newHealth);
    void changeHealth(float delta);
    float getHealth() const;

    virtual void setPosition(const sfex::Vec2& newPos);
    virtual void move(const sfex::Vec2& delta);
    sfex::Vec2 getPosition() const;

    Game* getParent();

    virtual bool isPlayer();

    virtual void onCollisionEnter(Entity* other) {};
    virtual void onCollisionStay(Entity* other) {};
    virtual void onCollisionExit(Entity* other) {};

    void setCollider(const Collider& collider);
    Collider& getCollider();

    void setName(const std::string& newName);
    std::string getName() const;

    void setMetadata(const std::string& newMetadata);
    std::string getMetadata() const;

protected:
    float m_health;
    sfex::Vec2 m_position;

    Collider m_collider;

    Game* m_parent;
    std::string m_name;
    std::string m_metadata;
};