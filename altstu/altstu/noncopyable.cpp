//
//  noncopyable.cpp
//  altstu
//
//  Created by Stepan Bondarenko on 04.11.2025.
//

#include "noncopyable.hpp"

NonCopyableSession::NonCopyableSession(const std::string& sessionId, const std::string& title)
    : m_sessionId(sessionId), m_title(title)
{
}
