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

TrainingSession::TrainingSession(const TrainingSession& other)
    : m_sessionId(other.m_sessionId),
      m_plannedAt(other.m_plannedAt),
      m_title(other.m_title),
      m_blocks(other.m_blocks),
      m_state(other.m_state),
      m_telemetry(other.m_telemetry ? std::make_unique<SessionTelemetry>(*other.m_telemetry) : nullptr)
{
}

TrainingSession& TrainingSession::operator=(const TrainingSession& other)
{
    if (this != &other)
    {
        m_sessionId = other.m_sessionId;
        m_plannedAt = other.m_plannedAt;
        m_title = other.m_title;
        m_blocks = other.m_blocks;
        m_state = other.m_state;
        m_telemetry = other.m_telemetry ? std::make_unique<SessionTelemetry>(*other.m_telemetry) : nullptr;
    }
    return *this;
}

TrainingSession::~TrainingSession() = default;

void TrainingSession::start()
{
    m_state = State::eRunning;
    std::cout << TAG_FOR_LOG << ": Session " << m_sessionId << " started" << std::endl;
}

void TrainingSession::finalize(const SessionTelemetry& telemetry)
{
    m_state = State::eDone;
    m_telemetry = std::make_unique<SessionTelemetry>(telemetry);
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

// Дружественная функция для вывода в поток
std::ostream& operator<<(std::ostream& os, const TrainingSession& session)
{
    os << "TrainingSession{id: " << session.m_sessionId 
       << ", title: " << session.m_title
       << ", state: " << session.stateToString(session.m_state);
    if (session.m_telemetry)
    {
        os << ", duration: " << session.m_telemetry->getDuration() 
           << " min, calories: " << session.m_telemetry->getCalories();
    }
    os << "}";
    return os;
}


