#pragma once
#include <InGame/Scenes/ExtendedScene.hpp>


namespace sg
{

class Game;
class AboutScene : public ExtendedScene
{
private:
public:
    AboutScene(Game* parent);
    ~AboutScene();

    virtual void pollEvent(const sf::Event &e) override;
    virtual void start() override;

    virtual void update() override;
    virtual void lateUpdate() override;

    virtual void draw(sf::RenderTarget &target) override;
    virtual void destroy() override;
};


}