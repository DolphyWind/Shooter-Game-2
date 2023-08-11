#include <Global.hpp>

const sfex::Color Global::menuButtonColor = sfex::Color::fromHex(0x232CFFFF);
const sf::RenderWindow* Global::mainWindow = nullptr;

std::optional<sfex::Vec2> Global::getIntersectionPoint(const Line &firstLine, const Line &secondLine)
{
    // Source: https://www.youtube.com/watch?v=5FkOO1Wwb8w

    sfex::Vec2 AB = firstLine.endPoint - firstLine.beginPoint; // B - A
    sfex::Vec2 CD = secondLine.endPoint - secondLine.beginPoint; // D - C
    sfex::Vec2 AC = secondLine.beginPoint - firstLine.beginPoint; // C - A

    float determinant = AB.cross(CD);
    if(determinant == 0) return std::nullopt;

    float t1 = (CD.y * AC.x - CD.x * AC.y) / determinant;
    float t2 = (AB.y * AC.x - AB.x * AC.y) / determinant;

    if((t1 >= 0 && t1 <= 1) && (t2 >= 0 && t2 <= 1))
    {
        return sfex::Math::lerp(firstLine.beginPoint, firstLine.endPoint, t1);
    }
    
    return std::nullopt;
}