//
//  movement.hpp
//  altstu
//
//  Created by Stepan Bondarenko on 04.11.2025.
//

#ifndef movement_hpp
#define movement_hpp

#include <string>
#include <vector>
#include <set>

class AthleteAccount;

class Movement
{
public:
    using TargetsType = std::set<std::string>;
    using GearNeedsType = std::set<std::string>;
    using ContraFlagsType = std::set<std::string>;
    using AlternativesType = std::vector<std::string>;
    
    static const int MAX_DIFFICULTY_BAND = 2;
    
private:
    static constexpr const char* TAG_FOR_LOG = "Movement";
    
    std::string m_code;
    std::string m_title;
    TargetsType m_targets;
    GearNeedsType m_gearNeeds;
    std::string m_impact;
    int m_difficultyBand;
    ContraFlagsType m_contraFlags;
    AlternativesType m_alternatives;
    
public:
    Movement() = default;
    Movement(const std::string& code, const std::string& title, const std::string& impact);
    ~Movement() = default;
    
    bool isDoable(const AthleteAccount& athlete) const;
    Movement* closestAlternative(const std::set<std::string>& withGear) const;
    
    std::string getCode() const { return m_code; }
    std::string getTitle() const { return m_title; }
    std::string getImpact() const { return m_impact; }
    int getDifficultyBand() const { return m_difficultyBand; }
    TargetsType getTargets() const { return m_targets; }
    GearNeedsType getGearNeeds() const { return m_gearNeeds; }
    ContraFlagsType getContraFlags() const { return m_contraFlags; }
    void setDifficultyBand(int band) { m_difficultyBand = band; }
    void addTarget(const std::string& target) { m_targets.insert(target); }
    void addGearNeed(const std::string& gear) { m_gearNeeds.insert(gear); }
    void addContraFlag(const std::string& flag) { m_contraFlags.insert(flag); }
    void addAlternative(const std::string& alt) { m_alternatives.push_back(alt); }
};

#endif /* movement_hpp */

