#pragma once
#include <InGame/Entity.hpp>

class Player : public Entity
{
public:
    Player(Game* parent, bool isCurrentPlayer);
    virtual ~Player() = default;

    virtual void start() override;
    virtual void update(const sf::Time& deltaTime) override;
    virtual void lateUpdate(const sf::Time& deltaTime) override;
    virtual void onDestroy() override;
    virtual void handleEvent(const sf::Event& e) override;
    virtual void render(sf::RenderTarget& target) override;

    virtual void setPosition(const sfex::Vec2& newPos) override;
    virtual void move(const sfex::Vec2& delta) override;

    virtual bool isPlayer() override;
    virtual void onCollisionEnter(Entity* other) override;
    virtual void onCollisionStay(Entity* other) override;
    virtual void onCollisionExit(Entity* other) override;
private:
    sf::CircleShape m_playerCircle;
    sf::RectangleShape m_gunRectangle;

    const float m_playerRadius;
    const sfex::Vec2 m_gunSize;
    const float m_playerVelocity;
    bool m_isCurrentPlayer;
};