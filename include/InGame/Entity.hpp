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
    Entity(Game* parent, const std::string& modname, const std::string& name);
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
    [[nodiscard]] float getHealth() const;

    virtual void setPosition(const sfex::Vec2& newPos);
    virtual void move(const sfex::Vec2& delta);
    [[nodiscard]] sfex::Vec2 getPosition() const;

    Game* getParent();

    virtual bool isPlayer();

    virtual void onCollisionEnter(Entity* other) {};
    virtual void onCollisionStay(Entity* other) {};
    virtual void onCollisionExit(Entity* other) {};

    void setCollider(const Collider& collider);
    Collider& getCollider();

    [[nodiscard]] std::string getName() const;
    [[nodiscard]] std::string getModName() const;
    [[nodiscard]] std::string getFullName() const;

    void setMetadata(const std::string& newMetadata);
    [[nodiscard]] std::string getMetadata() const;

protected:
    float m_health;
    sfex::Vec2 m_position;

    Collider m_collider;

    Game* m_parent;
    std::string m_modName;
    std::string m_name;
    std::string m_metadata;
};