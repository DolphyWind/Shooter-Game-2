#pragma once
#include <Global.hpp>
#include <SFEX/Numeric/Gradient.hpp>
#include <SFEX/Graphics/Color.hpp>
#include <Random/Random.hpp>


class MovingGradient
{
private:
    sfex::Gradient<sfex::Color> m_gradient;
    float m_gradientPeriod;
    float m_gradientTimer;
public:
    MovingGradient(float gradientPeriod);

    sfex::Color getCurrentColor();
    void update(float deltaTime);
};
