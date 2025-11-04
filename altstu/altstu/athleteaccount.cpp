//
//  athleteaccount.cpp
//  altstu
//
//  Created by Stepan Bondarenko on 04.11.2025.
//

#include "athleteaccount.hpp"
#include <iostream>

AthleteAccount::AthleteAccount(const std::string& accountId, const std::string& displayName, GoalCode primaryGoal)
    : m_accountId(accountId), m_displayName(displayName), m_primaryGoal(primaryGoal), m_experienceBand(0)
{
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

