//
//  athleteaccount.cpp
//  altstu
//
//  Created by Stepan Bondarenko on 04.11.2025.
//

#include "athleteaccount.hpp"
#include <iostream>

// Инициализация статического поля
int AthleteAccount::s_accountCount = 0;

AthleteAccount::AthleteAccount(const std::string& accountId, const std::string& displayName, GoalCode primaryGoal)
    : m_accountId(accountId), m_displayName(displayName), m_primaryGoal(primaryGoal), m_experienceBand(0)
{
    // Использование this для доступа к полям
    this->m_accountId = accountId;
    this->m_displayName = displayName;
    s_accountCount++; // Увеличение статического счетчика
}

AthleteAccount::AthleteAccount(const AthleteAccount& other)
    : m_accountId(other.m_accountId),
      m_displayName(other.m_displayName),
      m_primaryGoal(other.m_primaryGoal),
      m_experienceBand(other.m_experienceBand),
      m_timeWindows(other.m_timeWindows),
      m_dietStyleCode(other.m_dietStyleCode),
      m_allowedGear(other.m_allowedGear)
{
    s_accountCount++; // Увеличение статического счетчика при копировании
}

AthleteAccount::~AthleteAccount()
{
    s_accountCount--; // Уменьшение статического счетчика
}

void AthleteAccount::updateGoal(GoalCode newGoal)
{
    GoalCode oldGoal = m_primaryGoal;
    m_primaryGoal = newGoal;
    logGoalChange(oldGoal, newGoal);
}

void AthleteAccount::setTimeWindows(const TimeWindowsType& windows)
{
    m_timeWindows = windows;
}

bool AthleteAccount::prefers(const std::string& gear) const
{
    return m_allowedGear.find(gear) != m_allowedGear.end();
}

void AthleteAccount::logGoalChange(GoalCode oldGoal, GoalCode newGoal)
{
    std::cout << TAG_FOR_LOG << ": Goal changed from " << static_cast<int>(oldGoal) 
              << " to " << static_cast<int>(newGoal) << std::endl;
}


