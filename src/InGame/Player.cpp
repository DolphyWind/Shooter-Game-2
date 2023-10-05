#include <InGame/Player.hpp>
#include <InGame/Game.hpp>

Player::Player(Game* parent, bool isCurrentPlayer):
    Entity(parent, "", "Player"), m_playerRadius(25.0f), m_gunSize(43.0f, 18.0f), m_playerVelocity(200.0f),
    m_isCurrentPlayer(isCurrentPlayer)
{
    m_playerCircle.setRadius(m_playerRadius);
    m_playerCircle.setOrigin(m_playerRadius, m_playerRadius);
    m_playerCircle.setFillColor(sfex::Color::Red);
    m_playerCircle.setOutlineThickness(1.0f);
    m_playerCircle.setOutlineColor(sfex::Color::Black);

    m_gunRectangle.setSize(m_gunSize);
    m_gunRectangle.setOrigin(0, m_gunSize.y / 2);
    m_gunRectangle.setFillColor(sfex::Color::Gray);
    m_gunRectangle.setOutlineThickness(1.0f);
    m_gunRectangle.setOutlineColor(sfex::Color::Black);
    setPosition(m_position);
    start();
}

Player::~Player() noexcept
{
    onDestroy();
}

void Player::start()
{
    std::vector<sfex::Vec2> points;
    points.reserve(m_playerCircle.getPointCount());

    for(std::size_t i = 0; i < m_playerCircle.getPointCount(); ++i)
    {
        points.push_back(m_playerCircle.getPoint(i) - m_playerRadius*sfex::Vec2::one);
    }
    setCollider(Collider(points, true, this));
}

void Player::update(const sf::Time& deltaTime)
{
    if(!m_isCurrentPlayer) return;

    sfex::Vec2 mousePos = (sfex::Vec2)sfex::Mouse::getPosition(&getParent()->getRenderWindow());
    sfex::Vec2 mousePosInGame = getParent()->getRenderWindow().mapPixelToCoords(mousePos);

    if(sfex::Keyboard::getKey(sfex::Keyboard::Key::W))
    {
        move(sfex::Vec2::down * m_playerVelocity * deltaTime.asSeconds());
    }
    if(sfex::Keyboard::getKey(sfex::Keyboard::Key::A))
    {
        move(sfex::Vec2::left * m_playerVelocity * deltaTime.asSeconds());
    }
    if(sfex::Keyboard::getKey(sfex::Keyboard::Key::S))
    {
        move(sfex::Vec2::up * m_playerVelocity * deltaTime.asSeconds());
    }
    if(sfex::Keyboard::getKey(sfex::Keyboard::Key::D))
    {
        move(sfex::Vec2::right * m_playerVelocity * deltaTime.asSeconds());
    }

    sfex::Vec2 differenceVector = mousePosInGame - m_position;
    float angle = sfex::Math::arctan2(differenceVector.y, differenceVector.x);
    m_gunRectangle.setRotation(sfex::AngleSystem::radians.convertTo(sfex::AngleSystem::degrees, angle));

    sfex::Keyboard::update();
    sfex::Mouse::update();
}

void Player::lateUpdate(const sf::Time& deltaTime)
{
    if(!m_isCurrentPlayer) return;
}

void Player::onDestroy()
{

}

void Player::handleEvent(const sf::Event& e)
{

}

void Player::render(sf::RenderTarget& target)
{
    target.draw(m_gunRectangle);
    target.draw(m_playerCircle);
}

void Player::onDeath()
{

}

void Player::setPosition(const sfex::Vec2& newPos)
{
    Entity::setPosition(newPos);
    m_playerCircle.setPosition(newPos);
    m_gunRectangle.setPosition(newPos);
}

void Player::move(const sfex::Vec2& delta)
{
    Entity::move(delta);
    m_playerCircle.move(delta);
    m_gunRectangle.move(delta);
}

bool Player::isPlayer()
{
    return true;
}

void Player::onCollisionEnter(Entity* other)
{

}

void Player::onCollisionStay(Entity* other)
{

}

void Player::onCollisionExit(Entity* other)
{

}