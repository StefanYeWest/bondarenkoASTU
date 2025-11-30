//
//  baseentity.cpp
//  altstu
//
//  Created by Stepan Bondarenko on 04.11.2025.
//

#include "baseentity.hpp"

BaseEntity::BaseEntity(const std::string& id, const std::string& name)
    : m_id(id), m_name(name)
{
}

BaseEntity::BaseEntity(const BaseEntity& other)
    : m_id(other.m_id), m_name(other.m_name)
{
}

BaseEntity& BaseEntity::operator=(const BaseEntity& other)
{
    if (this != &other)
    {
        m_id = other.m_id;
        m_name = other.m_name;
    }
    return *this;
}

std::string BaseEntity::getDescription() const
{
    return "Entity: " + m_id + " - " + m_name;
}

