#pragma once
#include <thirdparty/effolkronium/random.hpp>
#include <SFEX/General/StaticClass.hpp>
#include <SFEX/SFEX.hpp>

using StaticRandom = effolkronium::random_static;
using LocalRandom = effolkronium::random_local;
using ThreadLocalRandom = effolkronium::random_thread_local;


class Global : public sfex::StaticClass
{
public:
    static constexpr float f3Time = 2.0;
    static const sfex::Color menuButtonColor;
    static constexpr unsigned int menuButtonTextSize = 22;
    static constexpr unsigned int menuButtonBorderRadius = 5;
    static constexpr unsigned int titleTextSize = 42;

    struct Line
    {
        sfex::Vec2 beginPoint;
        sfex::Vec2 endPoint;
    };
    static bool doLinesCollide(const Line& firstLine, const Line& secondLine)
    {
        // Check by seperating axis theorem
        float min_x = std::min(
            std::min(firstLine.beginPoint.x, firstLine.endPoint.x),
            std::min(secondLine.beginPoint.x, secondLine.endPoint.x)
        );
        float min_y = std::min(
            std::min(firstLine.beginPoint.y, firstLine.endPoint.y),
            std::min(secondLine.beginPoint.y, secondLine.endPoint.y)
        );

        float max_x = std::max(
            std::max(firstLine.beginPoint.x, firstLine.endPoint.x),
            std::max(secondLine.beginPoint.x, secondLine.endPoint.x)
        );
        float max_y = std::max(
            std::max(firstLine.beginPoint.y, firstLine.endPoint.y),
            std::max(secondLine.beginPoint.y, secondLine.endPoint.y)
        );

        if((max_x - min_x) > std::abs(firstLine.beginPoint.x - firstLine.endPoint.x) + std::abs(secondLine.beginPoint.x - secondLine.endPoint.x))
        {
            return false;
        }
        if((max_y - min_y) > std::abs(firstLine.beginPoint.y - firstLine.endPoint.y) + std::abs(secondLine.beginPoint.y - secondLine.endPoint.y))
        {
            return false;
        }

        return true;
    }
};
