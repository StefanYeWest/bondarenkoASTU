//
//  trainingsession.cpp
//  altstu
//
//  Created by Stepan Bondarenko on 04.11.2025.
//

#include "trainingsession.hpp"
#include <iostream>

TrainingSession::TrainingSession(const std::string& sessionId, const std::string& title)
    : m_sessionId(sessionId), m_title(title), m_state(State::ePlanned), m_telemetry(nullptr)
{
}

TrainingSession::~TrainingSession()
{
    if (m_telemetry != nullptr)
    {
        delete m_telemetry;
        m_telemetry = nullptr;
    }
}

void TrainingSession::start()
{
    m_state = State::eRunning;
    std::cout << TAG_FOR_LOG << ": Session " << m_sessionId << " started" << std::endl;
}

void TrainingSession::finalize(const SessionTelemetry& telemetry)
{
    m_state = State::eDone;
    if (m_telemetry != nullptr)
    {
        delete m_telemetry;
    }
    m_telemetry = new SessionTelemetry(telemetry);
    std::cout << TAG_FOR_LOG << ": Session " << m_sessionId << " finalized" << std::endl;
}

void TrainingSession::shift(const std::string& to)
{
    m_plannedAt = to;
    std::cout << TAG_FOR_LOG << ": Session " << m_sessionId << " shifted to " << to << std::endl;
}

void TrainingSession::addBlock(const WorkBlock& block)
{
    m_blocks.push_back(block);
}

std::string TrainingSession::stateToString(State state) const
{
    switch (state)
    {
        case State::ePlanned: return STATE_PLANNED;
        case State::eRunning: return STATE_RUNNING;
        case State::eDone: return STATE_DONE;
        case State::eMissed: return STATE_MISSED;
        default: return "unknown";
    }
}


