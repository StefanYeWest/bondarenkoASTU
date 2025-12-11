//
//  noncopyable.hpp
//  altstu
//
//  Created by Stepan Bondarenko on 04.11.2025.
//

#ifndef noncopyable_hpp
#define noncopyable_hpp

#include <string>

// Класс с запретом конструктора копирования по умолчанию
class NonCopyableSession
{
private:
    std::string m_sessionId;
    std::string m_title;
    
    // Запрещаем конструктор копирования и оператор присваивания
    NonCopyableSession(const NonCopyableSession&) = delete;
    NonCopyableSession& operator=(const NonCopyableSession&) = delete;
    
public:
    NonCopyableSession(const std::string& sessionId, const std::string& title);
    ~NonCopyableSession() = default;
    
    // Разрешаем перемещение
    NonCopyableSession(NonCopyableSession&&) noexcept = default;
    NonCopyableSession& operator=(NonCopyableSession&&) noexcept = default;
    
    std::string getSessionId() const { return m_sessionId; }
    std::string getTitle() const { return m_title; }
};

#endif /* noncopyable_hpp */
