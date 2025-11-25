//
//  movement.cpp
//  altstu
//
//  Created by Stepan Bondarenko on 04.11.2025.
//

#include "movement.hpp"
#include "athleteaccount.hpp"

Movement::Movement(const std::string& code, const std::string& title, const std::string& impact)
    : m_code(code), m_title(title), m_impact(impact), m_difficultyBand(0)
{
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

Movement* Movement::closestAlternative(const std::set<std::string>& withGear) const
{
    // Упрощенная реализация - возвращаем nullptr
    // В реальной реализации здесь был бы поиск по alternatives
    return nullptr;
}


