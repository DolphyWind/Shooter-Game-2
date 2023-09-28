#pragma once
#include <SFEX/SFEX.hpp>


class Game;
class ExtendedScene : public sfex::Scene
{
private:
    sfex::Color m_backgroundColor;
    Game* m_parent;
public:
    ExtendedScene(Game* parent);
    virtual ~ExtendedScene() = default;

    virtual void handleEvent(const sf::Event &e) override;
    virtual void start() override;

    virtual void update(const sf::Time& deltaTime) override;
    virtual void lateUpdate(const sf::Time& deltaTime);

    virtual void render(sf::RenderTarget &target) override;
    virtual void destroy() override;

    void setBackgroundColor(const sfex::Color& color);
    sfex::Color getBackgroundColor();
    Game* getParent();
};
