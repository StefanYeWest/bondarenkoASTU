//
//  baseentity.hpp
//  altstu
//
//  Created by Stepan Bondarenko on 04.11.2025.
//

#ifndef baseentity_hpp
#define baseentity_hpp

#include <string>

class BaseEntity
{
protected:
    std::string m_id;
    std::string m_name;
    
public:
    BaseEntity() = default;
    BaseEntity(const std::string& id, const std::string& name);
    BaseEntity(const BaseEntity& other); // Конструктор копирования
    BaseEntity(BaseEntity&& other) noexcept = default;
    virtual ~BaseEntity() = default;
    
    BaseEntity& operator=(const BaseEntity& other);
    BaseEntity& operator=(BaseEntity&& other) noexcept = default;
    
    std::string getId() const { return m_id; }
    std::string getName() const { return m_name; }
    void setName(const std::string& name) { m_name = name; }
    
    // Виртуальный метод для демонстрации полиморфизма
    virtual std::string getDescription() const;
};

#endif /* baseentity_hpp */

