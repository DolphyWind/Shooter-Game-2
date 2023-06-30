#pragma once
#include <thirdparty/effolkronium/random.hpp>
#include <SFEX/General/StaticClass.hpp>
#include <SFEX/Graphics/Color.hpp>
#include <limits>

using RandomGenerator = effolkronium::random_static;

namespace sg
{


class Random : public sfex::StaticClass
{
public:
    static sfex::Color getRandomColor(bool randomAlpha=false);
};


}