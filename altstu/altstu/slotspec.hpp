//
//  slotspec.hpp
//  altstu
//
//  Created by Stepan Bondarenko on 04.11.2025.
//

#ifndef slotspec_hpp
#define slotspec_hpp

#include <string>
#include <set>

class SlotSpec
{
public:
    SlotSpec() = default;
    SlotSpec(const std::string& pattern, const std::string& target, const std::set<std::string>& restrictions);
    ~SlotSpec() = default;
    
    std::string getPattern() const { return m_pattern; }
    std::string getTarget() const { return m_target; }
    std::set<std::string> getRestrictions() const { return m_restrictions; }
    
private:
    std::string m_pattern;
    std::string m_target;
    std::set<std::string> m_restrictions;
};

#endif /* slotspec_hpp */

