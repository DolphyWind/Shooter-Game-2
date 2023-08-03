#pragma once
#include <InGame/Scenes/ExtendedScene.hpp>
#include <TGUI/TGUI.hpp>
#include <InGame/Rendering/MessageBoxWindow.hpp>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <InGame/Entity.hpp>

class Game;
class DebugScene : public ExtendedScene
{
public:
    DebugScene(Game* parent);

    virtual void handleEvent(const sf::Event &e) override;
    virtual void start() override;

    virtual void update(const sf::Time& deltaTime) override;
    virtual void lateUpdate(const sf::Time& deltaTime) override;

    virtual void draw(sf::RenderTarget &target) override;
    virtual void destroy() override;
    
    void checkCollisions();
private:
    tgui::Label::Ptr m_welcomeLabel;
    tgui::ToggleButton::Ptr m_drawCollidersToggle; 

    sf::Clock m_f3Clock;
    std::vector<std::unique_ptr<Entity>> m_entities;
    std::unordered_map<Entity*, std::unordered_set<Entity*>> m_collisionTable;
};
