//
//  exercisable.hpp
//  altstu
//
//  Created by Stepan Bondarenko on 04.11.2025.
//

#ifndef exercisable_hpp
#define exercisable_hpp

#include <string>

class AthleteAccount;

// Абстрактный класс для демонстрации
class Exercisable
{
protected:
    std::string m_name;
    int m_durationMinutes;
    
public:
    Exercisable(const std::string& name, int durationMinutes);
    virtual ~Exercisable() = default;
    
    // Чисто виртуальные методы (делают класс абстрактным)
    virtual bool canPerform(const AthleteAccount& athlete) const = 0;
    virtual std::string getInstructions() const = 0;
    
    // Виртуальный метод с реализацией по умолчанию
    virtual int getEstimatedCalories() const;
    
    // Невиртуальный метод для демонстрации разницы
    std::string getName() const { return m_name; }
    int getDuration() const { return m_durationMinutes; }
};

#endif /* exercisable_hpp */
