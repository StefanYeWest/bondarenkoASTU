//
//  strengthmovement.cpp
//  altstu
//
//  Created by Stepan Bondarenko on 04.11.2025.
//

#include "strengthmovement.hpp"
#include "athleteaccount.hpp"
#include <sstream>

StrengthMovement::StrengthMovement(const std::string& code, const std::string& title,
                                   int sets, int reps, double weightKg)
    : Movement(code, title, "strength"), // Вызов конструктора базового класса Movement
      Exercisable(title, 30), // Вызов конструктора Exercisable
      m_sets(sets), m_reps(reps), m_weightKg(weightKg)
{
}

StrengthMovement::StrengthMovement(const StrengthMovement& other)
    : Movement(other), // Вызов конструктора копирования базового класса
      Exercisable(other.Exercisable::m_name, other.m_durationMinutes), // Явное указание области видимости
      m_sets(other.m_sets), m_reps(other.m_reps), m_weightKg(other.m_weightKg)
{
}

StrengthMovement& StrengthMovement::operator=(const StrengthMovement& other)
{
    if (this != &other)
    {
        Movement::operator=(other); // Вызов оператора присваивания базового класса
        Exercisable::m_name = other.Exercisable::m_name; // Явное указание области видимости
        m_durationMinutes = other.m_durationMinutes;
        m_sets = other.m_sets;
        m_reps = other.m_reps;
        m_weightKg = other.m_weightKg;
    }
    return *this;
}

StrengthMovement& StrengthMovement::operator=(const Movement& base)
{
    // Присваивание от базового класса Movement
    Movement::operator=(base);
    // Остальные поля Exercisable остаются без изменений
    return *this;
}

bool StrengthMovement::canPerform(const AthleteAccount& athlete) const
{
    // Использование метода базового класса Movement
    return this->isDoable(athlete);
}

std::string StrengthMovement::getInstructions() const
{
    std::ostringstream oss;
    oss << "Выполните " << m_sets << " подходов по " << m_reps 
        << " повторений с весом " << m_weightKg << " кг";
    return oss.str();
}

int StrengthMovement::getEstimatedCalories() const
{
    // Переопределение с вызовом базового метода
    int baseCalories = Exercisable::getEstimatedCalories();
    // Для силовых упражнений добавляем больше калорий
    return baseCalories + (m_sets * m_reps * 2);
}

std::string StrengthMovement::getDescription() const
{
    // Переопределение с вызовом базового метода
    std::string baseDesc = Movement::getDescription();
    return baseDesc + " [Strength: " + std::to_string(m_sets) + "x" + 
           std::to_string(m_reps) + " @ " + std::to_string(m_weightKg) + "kg]";
}

std::string StrengthMovement::getWorkoutDetails() const
{
    // Новый метод без вызова базового
    std::ostringstream oss;
    oss << "Силовое упражнение: " << this->getTitle() 
        << ", подходы: " << m_sets << ", повторения: " << m_reps;
    return oss.str();
}

void StrengthMovement::updateName(const std::string& newName)
{
    // Доступ к protected полю базового класса BaseEntity через Movement
    // Movement наследуется от BaseEntity, поэтому имеет доступ к protected полям
    // Прямой доступ к protected полю BaseEntity::m_name через Movement
    this->setName(newName); // Используем публичный метод для BaseEntity::m_name
    // Прямой доступ к protected полю Exercisable::m_name
    this->Exercisable::m_name = newName; // Прямой доступ к protected полю Exercisable
}
