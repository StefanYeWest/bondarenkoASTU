//
//  sessionblueprint.hpp
//  altstu
//
//  Created by Stepan Bondarenko on 04.11.2025.
//

#ifndef sessionblueprint_hpp
#define sessionblueprint_hpp

#include <string>
#include <vector>
#include <memory>
#include "slotspec.hpp"

class AthleteAccount;
class MovementLibrary;
class TrainingSession;

class SessionBlueprint
{
public:
    using SlotsType = std::vector<SlotSpec>;
    
    static const int DEFAULT_TIME_CAP = 60;
    
private:
    static constexpr const char* TAG_FOR_LOG = "SessionBlueprint";
    
    std::string m_blueprintId;
    std::string m_label;
    SlotsType m_slots;
    int m_timeCapMin;
    
public:
    SessionBlueprint() = default;
    SessionBlueprint(const std::string& blueprintId, const std::string& label);
    ~SessionBlueprint() = default;
    
    bool validateAgainst(const AthleteAccount& athlete) const;
    std::unique_ptr<TrainingSession> instantiate(const MovementLibrary& library, const AthleteAccount& athlete) const;
    
    std::string getBlueprintId() const { return m_blueprintId; }
    std::string getLabel() const { return m_label; }
    SlotsType getSlots() const { return m_slots; }
    int getTimeCapMin() const { return m_timeCapMin; }
    void addSlot(const SlotSpec& slot);
    void setTimeCapMin(int cap) { m_timeCapMin = cap; }
    
private:
    bool hasRequiredGear(const AthleteAccount& athlete) const;
};

#endif /* sessionblueprint_hpp */


