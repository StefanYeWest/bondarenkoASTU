//
//  workblock.hpp
//  altstu
//
//  Created by Stepan Bondarenko on 04.11.2025.
//

#ifndef workblock_hpp
#define workblock_hpp

#include <string>

class Movement;

class WorkBlock
{
public:
    WorkBlock() = default;
    ~WorkBlock() = default;
    
    void setMovement(Movement* movement) { m_movement = movement; }
    Movement* getMovement() const { return m_movement; }
    void setVolume(const std::string& volume) { m_volume = volume; }
    std::string getVolume() const { return m_volume; }
    
private:
    Movement* m_movement = nullptr;
    std::string m_volume;
};

#endif /* workblock_hpp */

