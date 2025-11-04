//
//  slotspec.cpp
//  altstu
//
//  Created by Stepan Bondarenko on 04.11.2025.
//

#include "slotspec.hpp"

SlotSpec::SlotSpec(const std::string& pattern, const std::string& target, const std::set<std::string>& restrictions)
    : m_pattern(pattern), m_target(target), m_restrictions(restrictions)
{
}

