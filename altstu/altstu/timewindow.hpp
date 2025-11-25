//
//  timewindow.hpp
//  altstu
//
//  Created by Stepan Bondarenko on 04.11.2025.
//

#ifndef timewindow_hpp
#define timewindow_hpp

#include <string>

class TimeWindow
{
public:
    TimeWindow() = default;
    TimeWindow(const std::string& start, const std::string& end);
    ~TimeWindow() = default;
    
    std::string getStart() const { return m_start; }
    std::string getEnd() const { return m_end; }
    
private:
    std::string m_start;
    std::string m_end;
};

#endif /* timewindow_hpp */


