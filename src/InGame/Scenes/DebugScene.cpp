#include <InGame/Scenes/DebugScene.hpp>
#include <InGame/Game.hpp>
#include <InGame/Entity.hpp>
#include <InGame/Player.hpp>
#include <InGame/LuaEntity.hpp>


DebugScene::DebugScene(Game* parent):
    ExtendedScene(parent), m_collisionTable()
{
    setBackgroundColor(sfex::Color::Cyan);
    m_welcomeLabel = tgui::Label::create("Welcome to the debug menu!\n"
    "Various test will go here\n"
    );
    m_welcomeLabel->getRenderer()->setTextColor(sfex::Color::Black);

    m_drawCollidersToggle = tgui::ToggleButton::create("Draw colliders", false);
    m_drawCollidersToggle->setPosition(0, "100% - height");
}

void DebugScene::handleEvent(const sf::Event &e)
{
    if(e.type == sf::Event::Resized)
    {
        // Scale text accordingly when the size changes
        float scale_percentage = getParent()->getScalePercentage();
        m_welcomeLabel->setTextSize(18 * scale_percentage);
    }

    for(auto& entity : m_entities)
    {
        entity->handleEvent(e);
    }
}

void DebugScene::start()
{
    m_f3Clock.restart();
    tgui::GuiSFML* gui = getParent()->getGUI();
    gui->add(m_welcomeLabel);
    gui->add(m_drawCollidersToggle);

    m_entities.push_back(std::make_unique<Player>(getParent(), true));
    m_entities.push_back(std::make_unique<Player>(getParent(), false));

    m_entities[0]->setPosition({100, 100});
    m_entities[1]->setPosition({300, 300});
}

void DebugScene::update(const sf::Time& deltaTime)
{
    if(!sfex::Keyboard::getKey(sfex::Keyboard::Key::F3))
    {
        m_f3Clock.restart();
    }
    if(sfex::Keyboard::getKey(sfex::Keyboard::Key::F3) && m_f3Clock.getElapsedTime().asSeconds() > Global::f3Time)
    {
        getParent()->switchScene("main_menu");
    }

    for(auto& entity : m_entities)
    {
        entity->update(deltaTime);
    }

    checkCollisions();
}

void DebugScene::lateUpdate(const sf::Time& deltaTime)
{
    for(auto& entity : m_entities)
    {
        entity->lateUpdate(deltaTime);
    }
}

void DebugScene::draw(sf::RenderTarget &target)
{
    for(auto& entity : m_entities)
    {
        entity->render(target);
        if(m_drawCollidersToggle->isDown()) entity->debugRender(target);
    }
}

void DebugScene::destroy()
{
    getParent()->getGUI()->removeAllWidgets();
    m_entities.clear();
}

void DebugScene::checkCollisions()
{
    for(std::size_t i = 0; i < m_entities.size(); ++i)
    {
        for(std::size_t j = 0; j < m_entities.size(); ++j)
        {
            if(i == j) continue;

            auto& e1 = m_entities[i];
            auto& e2 = m_entities[j];
            bool collided = false;
            std::optional<sfex::Vec2> intersectionPoint;

            for(auto& line1 : e1->getColliderLines())
            {
                for(auto& line2 : e2->getOuterLines())
                {
                    intersectionPoint = Global::getIntersectionPoint({
                        line1[0].position + e1->getPosition(),
                        line1[1].position + e1->getPosition()
                    }, {
                        line2[0].position + e2->getPosition(),
                        line2[1].position + e2->getPosition()
                    });

                    if(intersectionPoint.has_value())
                    {
                        collided = true;
                        break;
                    }
                }
                if(collided) break;
            }

            if(collided)
            {
                if(!m_collisionTable.contains(e1.get()) || !m_collisionTable[e1.get()].contains(e2.get()))
                {
                    m_collisionTable[e1.get()].insert(e2.get());
                    e1->onCollisionEnter(e2.get(), intersectionPoint.value());
                    // e2->onCollisionEnter(e1.get(), intersectionPoint.value());
                }
                else
                {
                    e1->onCollisionStay(e2.get(), intersectionPoint.value());
                    // e2->onCollisionStay(e1.get(), intersectionPoint.value());
                }
            }
            else
            {
                if(m_collisionTable.contains(e1.get()) && m_collisionTable.at(e1.get()).contains(e2.get()))
                {
                    m_collisionTable[e1.get()].erase(e2.get());
                    e1->onCollisionExit(e2.get());
                    // e2->onCollisionExit(e1.get());
                }
            }
        }
    }
}