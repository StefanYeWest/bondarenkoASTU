//
//  movementlibrary.hpp
//  altstu
//
//  Created by Stepan Bondarenko on 04.11.2025.
//

#ifndef movementlibrary_hpp
#define movementlibrary_hpp

#include <string>
#include <vector>
#include <set>
#include "movement.hpp"

class SlotSpec;
class AthleteAccount;

class MovementLibrary
{
public:
    using ItemsType = std::vector<Movement>;
    
    static const int INITIAL_REV = 1;
    
private:
    static constexpr const char* TAG_FOR_LOG = "MovementLibrary";
    
    ItemsType m_items;
    int m_rev;
    
public:
    MovementLibrary() = default;
    MovementLibrary(int rev);
    ~MovementLibrary() = default;
    
    std::vector<Movement> find(const std::string& text) const;
    std::vector<Movement> filter(const std::string* impact, const std::set<std::string>* gear, const int* band) const;
    std::vector<Movement> rankForSlot(const SlotSpec& slot, const AthleteAccount& athlete) const;
    
    void addMovement(const Movement& movement);
    MovementLibrary& operator+=(const Movement& movement); // Добавление движения
    const Movement& operator[](size_t index) const; // Доступ по индексу
    Movement& operator[](size_t index);
    ItemsType getItems() const { return m_items; }
    int getRev() const { return m_rev; }
    
private:
    bool matchesText(const Movement& movement, const std::string& text) const;
};

#endif /* movementlibrary_hpp */


