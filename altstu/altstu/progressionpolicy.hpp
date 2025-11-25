//
//  progressionpolicy.hpp
//  altstu
//
//  Created by Stepan Bondarenko on 04.11.2025.
//

#ifndef progressionpolicy_hpp
#define progressionpolicy_hpp

#include <string>

class ProgressionPolicy
{
public:
    ProgressionPolicy() = default;
    ProgressionPolicy(const std::string& strategy);
    ~ProgressionPolicy() = default;
    
    std::string getStrategy() const { return m_strategy; }
    
private:
    std::string m_strategy;
};

#endif /* progressionpolicy_hpp */


