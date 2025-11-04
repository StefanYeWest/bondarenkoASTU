//
//  bodymetrics.hpp
//  altstu
//
//  Created by Stepan Bondarenko on 04.11.2025.
//

#ifndef bodymetrics_hpp
#define bodymetrics_hpp

#include <string>
#include <optional>

class BodyMetrics
{
public:
    static constexpr double DEFAULT_BMI = 20.0;
    static constexpr int DEFAULT_BMR = 2000;
    
private:
    static constexpr const char* TAG_FOR_LOG = "BodyMetrics";
    
    std::string m_athleteId;
    std::string m_capturedAt;
    double m_weightKg;
    int m_statureCm;
    std::optional<int> m_restingHR;
    std::optional<double> m_sleepHours;
    double m_bmi;
    int m_bmrKcal;
    
public:
    BodyMetrics() = default;
    BodyMetrics(const std::string& athleteId, double weightKg, int statureCm);
    ~BodyMetrics() = default;
    
    void recalculateDerived();
    int tdee(double activityFactor) const;
    BodyMetrics mergeWith(const BodyMetrics& newer) const;
    
    std::string getAthleteId() const { return m_athleteId; }
    double getWeightKg() const { return m_weightKg; }
    int getStatureCm() const { return m_statureCm; }
    double getBmi() const { return m_bmi; }
    int getBmrKcal() const { return m_bmrKcal; }
    void setWeightKg(double weight) { m_weightKg = weight; }
    void setStatureCm(int stature) { m_statureCm = stature; }
    void setRestingHR(int hr) { m_restingHR = hr; }
    void setSleepHours(double hours) { m_sleepHours = hours; }
    void setCapturedAt(const std::string& time) { m_capturedAt = time; }
};

#endif /* bodymetrics_hpp */

