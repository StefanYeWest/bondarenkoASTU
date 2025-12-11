//
//  advancedsession.cpp
//  altstu
//
//  Created by Stepan Bondarenko on 04.11.2025.
//

#include "advancedsession.hpp"
#include <iostream>

AdvancedTrainingSession::AdvancedTrainingSession(const std::string& sessionId, 
                                                 const std::string& title,
                                                 const std::string& coachName)
    : TrainingSession(sessionId, title), // Вызов конструктора базового класса
      m_coachName(coachName)
{
}

AdvancedTrainingSession::AdvancedTrainingSession(const AdvancedTrainingSession& other)
    : TrainingSession(other), // Вызов конструктора копирования базового класса
      m_notes(other.m_notes),
      m_coachName(other.m_coachName)
{
}

AdvancedTrainingSession::~AdvancedTrainingSession()
{
    // Виртуальный деструктор - вызывается при удалении через указатель на базовый класс
    std::cout << "AdvancedTrainingSession destructor called" << std::endl;
}

AdvancedTrainingSession& AdvancedTrainingSession::operator=(const AdvancedTrainingSession& other)
{
    if (this != &other)
    {
        TrainingSession::operator=(other); // Вызов оператора присваивания базового класса
        m_notes = other.m_notes;
        m_coachName = other.m_coachName;
    }
    return *this;
}

void AdvancedTrainingSession::addNote(const std::string& note)
{
    m_notes.push_back(note);
}

