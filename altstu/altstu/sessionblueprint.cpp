//
//  sessionblueprint.cpp
//  altstu
//
//  Created by Stepan Bondarenko on 04.11.2025.
//

#include "sessionblueprint.hpp"
#include "athleteaccount.hpp"
#include "movementlibrary.hpp"
#include "trainingsession.hpp"
#include "slotspec.hpp"

SessionBlueprint::SessionBlueprint(const std::string& blueprintId, const std::string& label)
    : m_blueprintId(blueprintId), m_label(label), m_timeCapMin(DEFAULT_TIME_CAP)
{
}

void SessionBlueprint::addSlot(const SlotSpec& slot)
{
    m_slots.push_back(slot);
}

bool SessionBlueprint::validateAgainst(const AthleteAccount& athlete) const
{
    return hasRequiredGear(athlete);
}

TrainingSession* SessionBlueprint::instantiate(const MovementLibrary& library, const AthleteAccount& athlete) const
{
    TrainingSession* session = new TrainingSession("session_" + m_blueprintId, m_label);
    
    for (const auto& slot : m_slots)
    {
        auto movements = library.rankForSlot(slot, athlete);
        if (!movements.empty())
        {
            // Упрощенная реализация - берем первое движение
            // В реальной реализации здесь был бы выбор лучшего движения
        }
    }
    
    return session;
}

bool SessionBlueprint::hasRequiredGear(const AthleteAccount& athlete) const
{
    // Упрощенная проверка - возвращаем true
    // В реальной реализации проверяли бы все слоты
    return true;
}

