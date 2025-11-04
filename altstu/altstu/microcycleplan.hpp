//
//  microcycleplan.hpp
//  altstu
//
//  Created by Stepan Bondarenko on 04.11.2025.
//

#ifndef microcycleplan_hpp
#define microcycleplan_hpp

#include <string>
#include <vector>
#include "trainingsession.hpp"
#include "progressionpolicy.hpp"
#include "readinessindex.hpp"

class SessionBlueprint;
class MovementLibrary;
class AthleteAccount;

class MicrocyclePlan
{
public:
    using SessionsType = std::vector<TrainingSession>;
    
    static const int DEFAULT_WEEK_INDEX = 0;
    
private:
    static constexpr const char* TAG_FOR_LOG = "MicrocyclePlan";
    
    std::string m_planId;
    std::string m_ownerId;
    int m_weekIndex;
    SessionsType m_sessions;
    ProgressionPolicy m_policy;
    
public:
    MicrocyclePlan() = default;
    MicrocyclePlan(const std::string& planId, const std::string& ownerId);
    ~MicrocyclePlan() = default;
    
    void compose(const std::vector<SessionBlueprint>& blueprints, const MovementLibrary& library, const AthleteAccount& athlete);
    void adapt(const ReadinessIndex& readiness);
    std::vector<TrainingSession> upcoming(int limit) const;
    
    std::string getPlanId() const { return m_planId; }
    std::string getOwnerId() const { return m_ownerId; }
    int getWeekIndex() const { return m_weekIndex; }
    SessionsType getSessions() const { return m_sessions; }
    void setWeekIndex(int index) { m_weekIndex = index; }
    void addSession(const TrainingSession& session);
};

#endif /* microcycleplan_hpp */

