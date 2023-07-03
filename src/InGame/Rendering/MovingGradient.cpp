#include <InGame/Rendering/MovingGradient.hpp>

namespace sg
{

MovingGradient::MovingGradient(float gradientPeriod):
    m_gradient(), m_gradientPeriod(gradientPeriod), m_gradientTimer(0)
{
    m_gradient.setKey(0, Random::getRandomColor());
    m_gradient.setKey(m_gradientPeriod, Random::getRandomColor());
}

void MovingGradient::update(float deltaTime)
{
    m_gradientTimer += deltaTime;
    if(m_gradientTimer >= m_gradientPeriod)
    {
        m_gradientTimer = 0;
        m_gradient.setKey(0, m_gradient(m_gradientPeriod));
        m_gradient.setKey(m_gradientPeriod, Random::getRandomColor());
    }
}

sfex::Color MovingGradient::getCurrentColor()
{
    return m_gradient(m_gradientTimer);
}

}