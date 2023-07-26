#pragma once
#include <thirdparty/effolkronium/random.hpp>
#include <SFEX/General/StaticClass.hpp>
#include <SFEX/Graphics/Color.hpp>
#include <limits>
#include <Global.hpp>

using RandomGenerator = StaticRandom;


class Random : public sfex::StaticClass
{
public:
    static sfex::Color getRandomColor(bool randomAlpha=false);
};
