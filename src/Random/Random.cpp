#include <Random/Random.hpp>

sfex::Color Random::getRandomColor(bool randomAlpha)
{
    sfex::Color out;
    sf::Uint8 rangeMin = std::numeric_limits<sf::Uint8>::min();
    sf::Uint8 rangeMax = std::numeric_limits<sf::Uint8>::max();

    out.r = RandomGenerator::get<sf::Uint8>(rangeMin, rangeMax);
    out.g = RandomGenerator::get<sf::Uint8>(rangeMin, rangeMax);
    out.b = RandomGenerator::get<sf::Uint8>(rangeMin, rangeMax);
    out.a = rangeMax;

    if(randomAlpha)
    {
        out.a = RandomGenerator::get<sf::Uint8>(rangeMin, rangeMax);
    }

    return out;
}
