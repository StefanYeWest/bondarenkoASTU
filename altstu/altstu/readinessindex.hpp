//
//  readinessindex.hpp
//  altstu
//
//  Created by Stepan Bondarenko on 04.11.2025.
//

#ifndef readinessindex_hpp
#define readinessindex_hpp

class ReadinessIndex
{
public:
    ReadinessIndex() = default;
    ReadinessIndex(double value);
    ~ReadinessIndex() = default;
    
    double getValue() const { return m_value; }
    
private:
    double m_value = 1.0;
};

#endif /* readinessindex_hpp */

