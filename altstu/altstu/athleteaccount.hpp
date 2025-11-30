//
//  athleteaccount.hpp
//  altstu
//
//  Created by Stepan Bondarenko on 04.11.2025.
//

#ifndef athleteaccount_hpp
#define athleteaccount_hpp

#include <string>
#include <vector>
#include <set>
#include "goalcode.hpp"
#include "timewindow.hpp"

class AthleteAccount
{
public:
    using TimeWindowsType = std::vector<TimeWindow>;
    using AllowedGearType = std::set<std::string>;
    
    static const int MAX_EXPERIENCE_BAND = 2;
    
    // Статическое поле - счетчик созданных аккаунтов
    static int s_accountCount;
    
    // Статический метод для получения количества аккаунтов
    static int getAccountCount() { return s_accountCount; }
    
private:
    static constexpr const char* TAG_FOR_LOG = "AthleteAccount";
    
    std::string m_accountId;
    std::string m_displayName;
    GoalCode m_primaryGoal;
    int m_experienceBand;
    TimeWindowsType m_timeWindows;
    std::string m_dietStyleCode;
    AllowedGearType m_allowedGear;
    
public:
    AthleteAccount() = default;
    AthleteAccount(const std::string& accountId, const std::string& displayName, GoalCode primaryGoal);
    AthleteAccount(const AthleteAccount& other); // Конструктор копирования
    ~AthleteAccount();
    
    void updateGoal(GoalCode newGoal);
    void setTimeWindows(const TimeWindowsType& windows);
    bool prefers(const std::string& gear) const;
    
    std::string getAccountId() const { return m_accountId; }
    std::string getDisplayName() const { return m_displayName; }
    GoalCode getPrimaryGoal() const { return m_primaryGoal; }
    int getExperienceBand() const { return m_experienceBand; }
    AllowedGearType getAllowedGear() const { return m_allowedGear; }
    void setExperienceBand(int band) { m_experienceBand = band; }
    void setDietStyleCode(const std::string& code) { m_dietStyleCode = code; }
    void addGear(const std::string& gear) { m_allowedGear.insert(gear); }
    
private:
    void logGoalChange(GoalCode oldGoal, GoalCode newGoal);
};

#endif /* athleteaccount_hpp */

