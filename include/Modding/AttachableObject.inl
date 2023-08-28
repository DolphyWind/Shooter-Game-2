#pragma once
#include <Modding/AttachableObject.hpp>

template<typename T>
AttachableObject<T>::AttachableObject(Entity* entity): m_entity(entity), m_object(new T())
{
}

template<typename T>
template<typename... Args>
AttachableObject<T>::AttachableObject(Entity* entity, Args&& ...args): m_entity(entity), m_object(new T(std::forward<Args&&>(args)...))
{
}

template<typename T>
AttachableObject<T>::~AttachableObject()
{
    delete m_object;
}

template<typename T>
void AttachableObject<T>::attachTo(Entity* entity)
{
    m_entity = entity;
}

template<typename T>
T* AttachableObject<T>::getUnderlyingObject()
{
    return m_object;
}

template<typename T>
Entity* AttachableObject<T>::getEntity()
{
    return m_entity;
}

template<typename T>
sfex::Vec2 AttachableObject<T>::getPosition() const
{
    if(!m_entity)
    {
        return m_object->getPosition();
    }
    return m_entity->getPosition() + (sfex::Vec2)m_object->getPosition();
}

template<typename T>
sf::FloatRect AttachableObject<T>::getGlobalBounds() const
{
    if(!m_entity)
    {
        return m_object->getGlobalBounds();
    }
    sf::FloatRect bounds = m_object->getGlobalBounds();
    bounds.left += m_entity->getPosition().x;
    bounds.top += m_entity->getPosition().y;

    return bounds;
}

template<typename T>
void AttachableObject<T>::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    if(m_entity)
    {
        sf::Transform entityTransform;
        entityTransform.translate(m_entity->getPosition());
        target.draw(*m_object, entityTransform);
        return;
    }
    target.draw(*m_object);
}

template<typename T>
T* AttachableObject<T>::operator->()
{
    return getUnderlyingObject();
}
