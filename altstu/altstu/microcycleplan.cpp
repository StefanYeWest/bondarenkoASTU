//
//  microcycleplan.cpp
//  altstu
//
//  Created by Stepan Bondarenko on 04.11.2025.
//

#include "microcycleplan.hpp"
#include "sessionblueprint.hpp"
#include "movementlibrary.hpp"
#include "athleteaccount.hpp"
#include <algorithm>

MicrocyclePlan::MicrocyclePlan(const std::string& planId, const std::string& ownerId)
    : m_planId(planId), m_ownerId(ownerId), m_weekIndex(DEFAULT_WEEK_INDEX)
{
}

void MicrocyclePlan::compose(const std::vector<SessionBlueprint>& blueprints, const MovementLibrary& library, const AthleteAccount& athlete)
{
    m_sessions.clear();
    for (const auto& blueprint : blueprints)
    {
        if (blueprint.validateAgainst(athlete))
        {
            TrainingSession* session = blueprint.instantiate(library, athlete);
            if (session != nullptr)
            {
                m_sessions.push_back(*session);
                delete session;
            }
        }
    }
}

void MicrocyclePlan::adapt(const ReadinessIndex& readiness)
{
    double factor = readiness.getValue();
    // Упрощенная адаптация - в реальной реализации здесь изменялись бы объемы/интенсивность
    std::cout << TAG_FOR_LOG << ": Plan adapted with readiness factor " << factor << std::endl;
}

std::vector<TrainingSession> MicrocyclePlan::upcoming(int limit) const
{
    std::vector<TrainingSession> result;
    int count = 0;
    for (const auto& session : m_sessions)
    {
        if (count >= limit) break;
        if (session.getState() == TrainingSession::State::ePlanned)
        {
            result.push_back(session);
            count++;
        }
    }
    return result;
}

void MicrocyclePlan::addSession(const TrainingSession& session)
{
    m_sessions.push_back(session);
}

