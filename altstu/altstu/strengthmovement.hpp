//
//  strengthmovement.hpp
//  altstu
//
//  Created by Stepan Bondarenko on 04.11.2025.
//

#ifndef strengthmovement_hpp
#define strengthmovement_hpp

#include "movement.hpp"
#include "exercisable.hpp"

class AthleteAccount;

// Производный класс от Movement и Exercisable (множественное наследование через интерфейс)
class StrengthMovement : public Movement, public Exercisable
{
protected:
    int m_sets;
    int m_reps;
    double m_weightKg;
    
public:
    StrengthMovement(const std::string& code, const std::string& title, 
                     int sets, int reps, double weightKg);
    StrengthMovement(const StrengthMovement& other); // Конструктор копирования
    virtual ~StrengthMovement() = default;
    
    // Перегрузка оператора присваивания
    StrengthMovement& operator=(const StrengthMovement& other);
    StrengthMovement& operator=(const Movement& base); // Присваивание от базового класса
    
    // Переопределение виртуальных методов Exercisable
    bool canPerform(const AthleteAccount& athlete) const override;
    std::string getInstructions() const override;
    int getEstimatedCalories() const override; // Переопределение с вызовом базового
    
    // Переопределение метода базового класса Movement
    std::string getDescription() const override; // С вызовом базового метода
    
    // Новый метод без вызова базового
    std::string getWorkoutDetails() const;
    
    // Доступ к protected полям базового класса
    void updateName(const std::string& newName);
    
    int getSets() const { return m_sets; }
    int getReps() const { return m_reps; }
    double getWeightKg() const { return m_weightKg; }
};

#endif /* strengthmovement_hpp */
