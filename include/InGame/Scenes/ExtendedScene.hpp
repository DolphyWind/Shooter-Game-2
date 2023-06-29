#pragma once
#include <SFEX/SFEX.hpp>

namespace sg
{


class ExtendedScene : public sfex::Scene
{
private:
public:

    virtual void pollEvent(const sf::Event &e);
    virtual void start();

    virtual void update();
    virtual void lateUpdate();

    virtual void draw(sf::RenderTarget &target);
    virtual void destroy();
};


}