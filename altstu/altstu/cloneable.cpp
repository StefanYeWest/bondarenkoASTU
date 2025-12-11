//
//  cloneable.cpp
//  altstu
//
//  Created by Stepan Bondarenko on 04.11.2025.
//

#include "cloneable.hpp"
#include <memory>

ClonableMovementWrapper::ClonableMovementWrapper(std::shared_ptr<Movement> movement)
    : m_movement(movement)
{
}

ClonableMovementWrapper::ClonableMovementWrapper(const ClonableMovementWrapper& other)
    : m_movement(other.m_movement) // Поверхностное копирование shared_ptr
{
}

std::unique_ptr<CloneableMovement> ClonableMovementWrapper::clone() const
{
    // Глубокое клонирование - создаем новый объект Movement
    if (m_movement)
    {
        auto newMovement = std::make_shared<Movement>(*m_movement); // Конструктор копирования
        return std::make_unique<ClonableMovementWrapper>(newMovement);
    }
    return nullptr;
}

CloneableMovement* ClonableMovementWrapper::shallowClone() const
{
    // Поверхностное клонирование - разделяем shared_ptr
    return new ClonableMovementWrapper(m_movement);
}

