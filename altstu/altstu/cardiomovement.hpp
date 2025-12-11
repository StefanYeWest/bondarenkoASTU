//
//  cardiomovement.hpp
//  altstu
//
//  Created by Stepan Bondarenko on 04.11.2025.
//

#ifndef cardiomovement_hpp
#define cardiomovement_hpp

#include "movement.hpp"
#include "exercisable.hpp"

class AthleteAccount;

// Еще один производный класс для демонстрации
class CardioMovement : public Movement, public Exercisable
{
protected:
    double m_distanceKm;
    double m_speedKmh;
    
public:
    CardioMovement(const std::string& code, const std::string& title,
                   double distanceKm, double speedKmh);
    CardioMovement(const CardioMovement& other);
    virtual ~CardioMovement() = default;
    
    CardioMovement& operator=(const CardioMovement& other);
    CardioMovement& operator=(const Movement& base);
    
    // Переопределение виртуальных методов
    bool canPerform(const AthleteAccount& athlete) const override;
    std::string getInstructions() const override;
    int getEstimatedCalories() const override; // Без вызова базового
    
    // Переопределение без вызова базового метода
    std::string getDescription() const override;
    
    double getDistanceKm() const { return m_distanceKm; }
    double getSpeedKmh() const { return m_speedKmh; }
};

#endif /* cardiomovement_hpp */
