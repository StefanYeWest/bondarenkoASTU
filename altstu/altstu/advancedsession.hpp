//
//  advancedsession.hpp
//  altstu
//
//  Created by Stepan Bondarenko on 04.11.2025.
//

#ifndef advancedsession_hpp
#define advancedsession_hpp

#include "trainingsession.hpp"
#include <vector>
#include <string>

// Производный класс для демонстрации виртуального деструктора
class AdvancedTrainingSession : public TrainingSession
{
private:
    std::vector<std::string> m_notes;
    std::string m_coachName;
    
public:
    AdvancedTrainingSession(const std::string& sessionId, const std::string& title,
                            const std::string& coachName);
    AdvancedTrainingSession(const AdvancedTrainingSession& other);
    ~AdvancedTrainingSession() override; // Виртуальный деструктор
    
    AdvancedTrainingSession& operator=(const AdvancedTrainingSession& other);
    
    void addNote(const std::string& note);
    std::vector<std::string> getNotes() const { return m_notes; }
    std::string getCoachName() const { return m_coachName; }
};

#endif /* advancedsession_hpp */

