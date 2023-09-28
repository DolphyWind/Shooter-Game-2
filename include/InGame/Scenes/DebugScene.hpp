#pragma once
#include <memory>
#include <unordered_map>
#include <unordered_set>

#include <TGUI/TGUI.hpp>
#include <InGame/Rendering/MessageBoxWindow.hpp>
#include <InGame/Scenes/ExtendedScene.hpp>
#include <InGame/Entity.hpp>
#include <InGame/GameManager.hpp>
#include <Modding/Mod.hpp>
#include <Modding/ModManager.hpp>

class Game;
class DebugScene final : public ExtendedScene
{
public:
    DebugScene(Game* parent);

    virtual void handleEvent(const sf::Event &e) override;
    virtual void start() override;

    virtual void update(const sf::Time& deltaTime) override;
    virtual void lateUpdate(const sf::Time& deltaTime) override;

    virtual void render(sf::RenderTarget &target) override;
    virtual void destroy() override;
private:
    tgui::Label::Ptr m_welcomeLabel;
    tgui::ToggleButton::Ptr m_drawCollidersToggle; 

    sf::Clock m_f3Clock;
};
