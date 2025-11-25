//
//  sessiontelemetry.hpp
//  altstu
//
//  Created by Stepan Bondarenko on 04.11.2025.
//

#ifndef sessiontelemetry_hpp
#define sessiontelemetry_hpp

#include <string>

class SessionTelemetry
{
public:
    SessionTelemetry() = default;
    ~SessionTelemetry() = default;
    
    void setDuration(int duration) { m_duration = duration; }
    int getDuration() const { return m_duration; }
    void setCalories(int calories) { m_calories = calories; }
    int getCalories() const { return m_calories; }
    
private:
    int m_duration = 0;
    int m_calories = 0;
};

#endif /* sessiontelemetry_hpp */


