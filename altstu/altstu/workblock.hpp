//
//  workblock.hpp
//  altstu
//
//  Created by Stepan Bondarenko on 04.11.2025.
//

#ifndef workblock_hpp
#define workblock_hpp

#include <string>
#include <memory>

class Movement;

class WorkBlock
{
public:
    WorkBlock() = default;
    WorkBlock(const WorkBlock& other) = default;
    WorkBlock(WorkBlock&& other) noexcept = default;
    WorkBlock& operator=(const WorkBlock& other) = default;
    WorkBlock& operator=(WorkBlock&& other) noexcept = default;
    ~WorkBlock() = default;
    
    void setMovement(std::shared_ptr<Movement> movement) { m_movement = movement; }
    std::shared_ptr<Movement> getMovement() const { return m_movement; }
    void setVolume(const std::string& volume) { m_volume = volume; }
    std::string getVolume() const { return m_volume; }
    
private:
    std::shared_ptr<Movement> m_movement;
    std::string m_volume;
};

#endif /* workblock_hpp */


