//
//  cloneable.hpp
//  altstu
//
//  Created by Stepan Bondarenko on 04.11.2025.
//

#ifndef cloneable_hpp
#define cloneable_hpp

#include <memory>
#include "movement.hpp"

// Интерфейс для клонирования
class CloneableMovement
{
public:
    virtual ~CloneableMovement() = default;
    virtual std::unique_ptr<CloneableMovement> clone() const = 0; // Глубокое клонирование
    virtual CloneableMovement* shallowClone() const = 0; // Поверхностное клонирование
};

// Класс-обертка для демонстрации клонирования
class ClonableMovementWrapper : public CloneableMovement
{
private:
    std::shared_ptr<Movement> m_movement; // Разделяемое владение для поверхностного клонирования
    
public:
    ClonableMovementWrapper(std::shared_ptr<Movement> movement);
    ClonableMovementWrapper(const ClonableMovementWrapper& other);
    
    // Глубокое клонирование - создает новый объект Movement
    std::unique_ptr<CloneableMovement> clone() const override;
    
    // Поверхностное клонирование - разделяет shared_ptr
    CloneableMovement* shallowClone() const override;
    
    Movement* getMovement() const { return m_movement.get(); }
    std::shared_ptr<Movement> getSharedMovement() const { return m_movement; }
};

#endif /* cloneable_hpp */

