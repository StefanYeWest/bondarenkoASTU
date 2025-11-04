//
//  movementlibrary.cpp
//  altstu
//
//  Created by Stepan Bondarenko on 04.11.2025.
//

#include "movementlibrary.hpp"
#include "slotspec.hpp"
#include "athleteaccount.hpp"
#include <algorithm>
#include <cctype>

MovementLibrary::MovementLibrary(int rev)
    : m_rev(rev)
{
}

void MovementLibrary::addMovement(const Movement& movement)
{
    m_items.push_back(movement);
}

std::vector<Movement> MovementLibrary::find(const std::string& text) const
{
    std::vector<Movement> results;
    for (const auto& item : m_items)
    {
        if (matchesText(item, text))
        {
            results.push_back(item);
        }
    }
    return results;
}

std::vector<Movement> MovementLibrary::filter(const std::string* impact, const std::set<std::string>* gear, const int* band) const
{
    std::vector<Movement> results;
    for (const auto& item : m_items)
    {
        bool matches = true;
        
        if (impact != nullptr && item.getImpact() != *impact)
        {
            matches = false;
        }
        
        if (gear != nullptr)
        {
            auto itemGear = item.getGearNeeds();
            for (const auto& g : *gear)
            {
                if (itemGear.find(g) == itemGear.end())
                {
                    matches = false;
                    break;
                }
            }
        }
        
        if (band != nullptr && item.getDifficultyBand() != *band)
        {
            matches = false;
        }
        
        if (matches)
        {
            results.push_back(item);
        }
    }
    return results;
}

std::vector<Movement> MovementLibrary::rankForSlot(const SlotSpec& slot, const AthleteAccount& athlete) const
{
    std::vector<Movement> results;
    for (const auto& item : m_items)
    {
        if (item.isDoable(athlete))
        {
            results.push_back(item);
        }
    }
    return results;
}

bool MovementLibrary::matchesText(const Movement& movement, const std::string& text) const
{
    std::string lowerText = text;
    std::transform(lowerText.begin(), lowerText.end(), lowerText.begin(), ::tolower);
    
    std::string lowerTitle = movement.getTitle();
    std::transform(lowerTitle.begin(), lowerTitle.end(), lowerTitle.begin(), ::tolower);
    
    std::string lowerCode = movement.getCode();
    std::transform(lowerCode.begin(), lowerCode.end(), lowerCode.begin(), ::tolower);
    
    return lowerTitle.find(lowerText) != std::string::npos || 
           lowerCode.find(lowerText) != std::string::npos;
}

