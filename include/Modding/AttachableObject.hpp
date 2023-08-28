#pragma once
#include <InGame/Entity.hpp>

/// Represents an object that is attachable to an entity
/// \tparam T The type of the object. Has to have an empty constructor
template<typename T>
class AttachableObject : public sf::Drawable
{
public:
    AttachableObject(Entity* entity);
    template<typename... Args>
    AttachableObject(Entity* entity, Args&&... args);
    ~AttachableObject();

    void attachTo(Entity* entity);
    T* getUnderlyingObject();
    Entity* getEntity();

    sfex::Vec2 getPosition() const;
    sf::FloatRect getGlobalBounds() const;
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
    T* operator->();
private:
    Entity* m_entity;
    T* m_object;
};

#include <Modding/AttachableObject.inl>