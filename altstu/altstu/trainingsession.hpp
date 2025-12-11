//
//  trainingsession.hpp
//  altstu
//
//  Created by Stepan Bondarenko on 04.11.2025.
//

#ifndef trainingsession_hpp
#define trainingsession_hpp

#include <string>
#include <vector>
#include <memory>
#include <iostream>
#include "workblock.hpp"
#include "sessiontelemetry.hpp"

class SessionTelemetry;

class TrainingSession
{
public:
    using BlocksType = std::vector<WorkBlock>;
    
    enum class State
    {
        ePlanned = 0,
        eRunning = 1,
        eDone = 2,
        eMissed = 3
    };
    
    static constexpr const char* STATE_PLANNED = "planned";
    static constexpr const char* STATE_RUNNING = "running";
    static constexpr const char* STATE_DONE = "done";
    static constexpr const char* STATE_MISSED = "missed";
    
private:
    static constexpr const char* TAG_FOR_LOG = "TrainingSession";
    
    std::string m_sessionId;
    std::string m_plannedAt;
    std::string m_title;
    BlocksType m_blocks;
    State m_state;
    std::unique_ptr<SessionTelemetry> m_telemetry;
    
public:
    TrainingSession() = default;
    TrainingSession(const std::string& sessionId, const std::string& title);
    TrainingSession(const TrainingSession& other);
    TrainingSession(TrainingSession&& other) noexcept = default;
    virtual ~TrainingSession(); // Виртуальный деструктор
    
    TrainingSession& operator=(const TrainingSession& other);
    TrainingSession& operator=(TrainingSession&& other) noexcept = default;
    
    void start();
    void finalize(const SessionTelemetry& telemetry);
    void shift(const std::string& to);
    
    std::string getSessionId() const { return m_sessionId; }
    std::string getTitle() const { return m_title; }
    State getState() const { return m_state; }
    BlocksType getBlocks() const { return m_blocks; }
    void addBlock(const WorkBlock& block);
    void setPlannedAt(const std::string& date) { m_plannedAt = date; }
    
    // Дружественная функция для вывода в поток
    friend std::ostream& operator<<(std::ostream& os, const TrainingSession& session);
    
private:
    std::string stateToString(State state) const;
};

#endif /* trainingsession_hpp */


