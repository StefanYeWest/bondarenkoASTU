//
//  bodymetrics.cpp
//  altstu
//
//  Created by Stepan Bondarenko on 04.11.2025.
//

#include "bodymetrics.hpp"
#include <cmath>

BodyMetrics::BodyMetrics(const std::string& athleteId, double weightKg, int statureCm)
    : m_athleteId(athleteId), m_weightKg(weightKg), m_statureCm(statureCm), m_bmi(DEFAULT_BMI), m_bmrKcal(DEFAULT_BMR)
{
    recalculateDerived();
}

void BodyMetrics::recalculateDerived()
{
    if (m_statureCm > 0)
    {
        double heightM = m_statureCm / 100.0;
        m_bmi = m_weightKg / (heightM * heightM);
    }
    
    // Упрощенный расчет BMR (формула Харриса-Бенедикта для мужчин)
    if (m_statureCm > 0 && m_weightKg > 0)
    {
        m_bmrKcal = static_cast<int>(88.362 + (13.397 * m_weightKg) + (4.799 * m_statureCm) - (5.677 * 30)); // 30 - примерный возраст
    }
}

int BodyMetrics::tdee(double activityFactor) const
{
    return static_cast<int>(m_bmrKcal * activityFactor);
}

BodyMetrics BodyMetrics::mergeWith(const BodyMetrics& newer) const
{
    BodyMetrics result = newer;
    if (newer.m_weightKg == 0.0) result.m_weightKg = m_weightKg;
    if (newer.m_statureCm == 0) result.m_statureCm = m_statureCm;
    if (!newer.m_restingHR.has_value()) result.m_restingHR = m_restingHR;
    if (!newer.m_sleepHours.has_value()) result.m_sleepHours = m_sleepHours;
    result.recalculateDerived();
    return result;
}


