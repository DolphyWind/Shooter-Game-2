#pragma once
#include <SFEX/SFEX.hpp>

namespace sg
{

class Game;
class ExtendedScene : public sfex::Scene
{
private:
    sfex::Color m_backgroundColor;
    Game* m_parent;
public:
    ExtendedScene(Game* parent);

    virtual void pollEvent(const sf::Event &e) override;
    virtual void start() override;

    virtual void update() override;
    virtual void lateUpdate();

    virtual void draw(sf::RenderTarget &target) override;
    virtual void destroy() override;

    void setBackgroundColor(const sfex::Color& color);
    sfex::Color getBackgroundColor();
    Game* getParent();
};


}