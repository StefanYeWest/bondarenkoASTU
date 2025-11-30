//
//  movement.cpp
//  altstu
//
//  Created by Stepan Bondarenko on 04.11.2025.
//

#include "movement.hpp"
#include "athleteaccount.hpp"

Movement::Movement(const std::string& code, const std::string& title, const std::string& impact)
    : BaseEntity(code, title), // Вызов конструктора базового класса
      m_impact(impact), m_difficultyBand(0)
{
}

Movement::Movement(const Movement& other)
    : BaseEntity(other), // Вызов конструктора копирования базового класса
      m_targets(other.m_targets),
      m_gearNeeds(other.m_gearNeeds),
      m_impact(other.m_impact),
      m_difficultyBand(other.m_difficultyBand),
      m_contraFlags(other.m_contraFlags),
      m_alternatives(other.m_alternatives)
{
}

Movement& Movement::operator=(const Movement& other)
{
    if (this != &other)
    {
        BaseEntity::operator=(other); // Вызов оператора присваивания базового класса
        m_targets = other.m_targets;
        m_gearNeeds = other.m_gearNeeds;
        m_impact = other.m_impact;
        m_difficultyBand = other.m_difficultyBand;
        m_contraFlags = other.m_contraFlags;
        m_alternatives = other.m_alternatives;
    }
    return *this;
}

std::string Movement::getDescription() const
{
    // Использование this для доступа к методам
    return BaseEntity::getDescription() + " [Impact: " + this->m_impact + ", Band: " + std::to_string(this->m_difficultyBand) + "]";
}

bool Movement::isDoable(const AthleteAccount& athlete) const
{
    // Проверка наличия необходимого инвентаря
    for (const auto& gear : m_gearNeeds)
    {
        if (!athlete.prefers(gear))
        {
            return false;
        }
    }
    
    // Здесь можно добавить проверку противопоказаний
    // Для упрощения возвращаем true если есть инвентарь
    return true;
}

std::shared_ptr<Movement> Movement::closestAlternative(const std::set<std::string>& withGear) const
{
    // Упрощенная реализация - возвращаем nullptr
    // В реальной реализации здесь был бы поиск по alternatives
    return nullptr;
}


