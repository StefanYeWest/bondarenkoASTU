//
//  exercisable.cpp
//  altstu
//
//  Created by Stepan Bondarenko on 04.11.2025.
//

#include "exercisable.hpp"

Exercisable::Exercisable(const std::string& name, int durationMinutes)
    : m_name(name), m_durationMinutes(durationMinutes)
{
}

int Exercisable::getEstimatedCalories() const
{
    // Базовая реализация - 5 ккал в минуту
    return m_durationMinutes * 5;
}
