//
//  cardiomovement.cpp
//  altstu
//
//  Created by Stepan Bondarenko on 04.11.2025.
//

#include "cardiomovement.hpp"
#include "athleteaccount.hpp"
#include <sstream>
#include <cmath>

CardioMovement::CardioMovement(const std::string& code, const std::string& title,
                               double distanceKm, double speedKmh)
    : Movement(code, title, "cardio"), // Вызов конструктора базового класса
      Exercisable(title, static_cast<int>(distanceKm / speedKmh * 60)), // Расчет времени
      m_distanceKm(distanceKm), m_speedKmh(speedKmh)
{
}

CardioMovement::CardioMovement(const CardioMovement& other)
    : Movement(other),
      Exercisable(other.Exercisable::m_name, other.m_durationMinutes), // Явное указание области видимости
      m_distanceKm(other.m_distanceKm), m_speedKmh(other.m_speedKmh)
{
}

CardioMovement& CardioMovement::operator=(const CardioMovement& other)
{
    if (this != &other)
    {
        Movement::operator=(other);
        Exercisable::m_name = other.Exercisable::m_name; // Явное указание области видимости
        m_durationMinutes = other.m_durationMinutes;
        m_distanceKm = other.m_distanceKm;
        m_speedKmh = other.m_speedKmh;
    }
    return *this;
}

CardioMovement& CardioMovement::operator=(const Movement& base)
{
    Movement::operator=(base);
    return *this;
}

bool CardioMovement::canPerform(const AthleteAccount& athlete) const
{
    return this->isDoable(athlete);
}

std::string CardioMovement::getInstructions() const
{
    std::ostringstream oss;
    oss << "Пробегите " << m_distanceKm << " км со скоростью " 
        << m_speedKmh << " км/ч";
    return oss.str();
}

int CardioMovement::getEstimatedCalories() const
{
    // Переопределение БЕЗ вызова базового метода
    // Для кардио: примерно 10 ккал на км для бега
    return static_cast<int>(m_distanceKm * 10);
}

std::string CardioMovement::getDescription() const
{
    // Переопределение БЕЗ вызова базового метода
    std::ostringstream oss;
    oss << "Cardio: " << this->Exercisable::getName() << " - " << m_distanceKm 
        << " км @ " << m_speedKmh << " км/ч";
    return oss.str();
}
