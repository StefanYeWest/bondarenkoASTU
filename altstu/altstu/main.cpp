//
//  main.cpp
//  altstu
//
//  Created by Stepan Bondarenko on 04.11.2025.
//

#include <iostream>
#include "athleteaccount.hpp"
#include "bodymetrics.hpp"
#include "movement.hpp"
#include "movementlibrary.hpp"
#include "sessionblueprint.hpp"
#include "trainingsession.hpp"
#include "microcycleplan.hpp"
#include "timewindow.hpp"
#include "slotspec.hpp"
#include "workblock.hpp"
#include "sessiontelemetry.hpp"
#include "progressionpolicy.hpp"
#include "readinessindex.hpp"

void demonstrateStaticInitialization();
void demonstrateDynamicInitialization();
void demonstrateReferencesAndPointers();
void demonstrateDynamicArrayOfObjects();
void demonstrateArrayOfDynamicObjects();

int main(int argc, const char * argv[])
{
    std::cout << "=== Демонстрация работы классов ===\n\n";
    
    std::cout << "1. Статическая инициализация объектов:\n";
    demonstrateStaticInitialization();
    std::cout << "\n";
    
    std::cout << "2. Динамическая инициализация объектов (new/delete):\n";
    demonstrateDynamicInitialization();
    std::cout << "\n";
    
    std::cout << "3. Работа по ссылкам и указателям:\n";
    demonstrateReferencesAndPointers();
    std::cout << "\n";
    
    std::cout << "4. Динамический массив объектов класса:\n";
    demonstrateDynamicArrayOfObjects();
    std::cout << "\n";
    
    std::cout << "5. Массив динамических объектов класса:\n";
    demonstrateArrayOfDynamicObjects();
    std::cout << "\n";
    
    return 0;
}

void demonstrateStaticInitialization()
{
    // Статическая инициализация AthleteAccount
    AthleteAccount athlete1("acc001", "Иван Иванов", GoalCode::eBulk);
    athlete1.setExperienceBand(1);
    athlete1.addGear("barbell");
    athlete1.addGear("dumbbells");
    
    std::cout << "  Создан спортсмен: " << athlete1.getDisplayName() 
              << " с целью " << static_cast<int>(athlete1.getPrimaryGoal()) << std::endl;
    
    // Статическая инициализация BodyMetrics
    BodyMetrics metrics1("acc001", 75.5, 180);
    metrics1.setRestingHR(65);
    metrics1.recalculateDerived();
    
    std::cout << "  Метрики: вес " << metrics1.getWeightKg() 
              << " кг, рост " << metrics1.getStatureCm() 
              << " см, BMI " << metrics1.getBmi() << std::endl;
    
    // Статическая инициализация Movement
    Movement movement1("squat_001", "Приседания", "strength");
    movement1.setDifficultyBand(1);
    movement1.addTarget("quads");
    movement1.addTarget("glutes");
    movement1.addGearNeed("barbell");
    
    std::cout << "  Движение: " << movement1.getTitle() 
              << " (код: " << movement1.getCode() << ")" << std::endl;
}

void demonstrateDynamicInitialization()
{
    // Динамическая инициализация с new
    AthleteAccount* athletePtr = new AthleteAccount("acc002", "Петр Петров", GoalCode::eCut);
    athletePtr->setExperienceBand(2);
    athletePtr->addGear("kettlebell");
    athletePtr->addGear("resistance_bands");
    
    std::cout << "  Создан спортсмен (динамически): " << athletePtr->getDisplayName() << std::endl;
    
    // Работа с динамическим объектом
    athletePtr->updateGoal(GoalCode::eShape);
    std::cout << "  Новая цель: " << static_cast<int>(athletePtr->getPrimaryGoal()) << std::endl;
    
    // Освобождение памяти с delete
    delete athletePtr;
    athletePtr = nullptr;
    std::cout << "  Память освобождена" << std::endl;
    
    // Динамическая инициализация TrainingSession
    TrainingSession* session = new TrainingSession("sess_001", "FullBody A");
    session->setPlannedAt("2025-11-05 10:00");
    session->start();
    
    std::cout << "  Сессия создана: " << session->getTitle() << std::endl;
    
    SessionTelemetry telemetry;
    telemetry.setDuration(45);
    telemetry.setCalories(350);
    session->finalize(telemetry);
    
    delete session;
    session = nullptr;
    std::cout << "  Сессия завершена и удалена" << std::endl;
}

void demonstrateReferencesAndPointers()
{
    // Работа по ссылке
    AthleteAccount athlete("acc003", "Анна Смирнова", GoalCode::eHealth);
    AthleteAccount& athleteRef = athlete;
    
    athleteRef.addGear("yoga_mat");
    athleteRef.setExperienceBand(0);
    
    std::cout << "  Работа по ссылке: " << athleteRef.getDisplayName() 
              << " имеет инвентарь: ";
    auto gear = athleteRef.getAllowedGear();
    for (const auto& g : gear)
    {
        std::cout << g << " ";
    }
    std::cout << std::endl;
    
    // Работа по указателю
    BodyMetrics* metricsPtr = new BodyMetrics("acc003", 60.0, 165);
    metricsPtr->setSleepHours(7.5);
    metricsPtr->recalculateDerived();
    
    std::cout << "  Работа по указателю: BMI = " << metricsPtr->getBmi() 
              << ", BMR = " << metricsPtr->getBmrKcal() << " ккал" << std::endl;
    std::cout << "  TDEE (коэффициент 1.5): " << metricsPtr->tdee(1.5) << " ккал" << std::endl;
    
    // Объединение метрик
    BodyMetrics newerMetrics("acc003", 61.0, 165);
    BodyMetrics merged = metricsPtr->mergeWith(newerMetrics);
    std::cout << "  Объединенные метрики: вес " << merged.getWeightKg() << " кг" << std::endl;
    
    delete metricsPtr;
    metricsPtr = nullptr;
}

void demonstrateDynamicArrayOfObjects()
{
    // Динамический массив объектов класса Movement
    const int arraySize = 3;
    Movement* movementsArray = new Movement[arraySize];
    
    movementsArray[0] = Movement("push_001", "Отжимания", "strength");
    movementsArray[0].setDifficultyBand(0);
    movementsArray[0].addTarget("chest");
    movementsArray[0].addTarget("triceps");
    
    movementsArray[1] = Movement("pull_001", "Подтягивания", "strength");
    movementsArray[1].setDifficultyBand(1);
    movementsArray[1].addTarget("lats");
    movementsArray[1].addTarget("biceps");
    movementsArray[1].addGearNeed("pullup_bar");
    
    movementsArray[2] = Movement("run_001", "Бег", "cardio");
    movementsArray[2].setDifficultyBand(0);
    movementsArray[2].addTarget("legs");
    movementsArray[2].setDifficultyBand(0);
    
    std::cout << "  Динамический массив движений (" << arraySize << " элементов):" << std::endl;
    for (int i = 0; i < arraySize; i++)
    {
        std::cout << "    [" << i << "] " << movementsArray[i].getTitle() 
                  << " (сложность: " << movementsArray[i].getDifficultyBand() << ")" << std::endl;
    }
    
    // Освобождение памяти
    delete[] movementsArray;
    movementsArray = nullptr;
    std::cout << "  Массив удален" << std::endl;
}

void demonstrateArrayOfDynamicObjects()
{
    // Массив указателей на динамические объекты
    const int arraySize = 3;
    BodyMetrics** metricsArray = new BodyMetrics*[arraySize];
    
    // Создание динамических объектов
    metricsArray[0] = new BodyMetrics("acc004", 70.0, 175);
    metricsArray[0]->setRestingHR(70);
    metricsArray[0]->recalculateDerived();
    
    metricsArray[1] = new BodyMetrics("acc005", 80.0, 185);
    metricsArray[1]->setRestingHR(65);
    metricsArray[1]->setSleepHours(8.0);
    metricsArray[1]->recalculateDerived();
    
    metricsArray[2] = new BodyMetrics("acc006", 65.0, 170);
    metricsArray[2]->setRestingHR(72);
    metricsArray[2]->recalculateDerived();
    
    std::cout << "  Массив динамических объектов BodyMetrics (" << arraySize << " элементов):" << std::endl;
    for (int i = 0; i < arraySize; i++)
    {
        std::cout << "    [" << i << "] ID: " << metricsArray[i]->getAthleteId()
                  << ", вес: " << metricsArray[i]->getWeightKg() 
                  << " кг, BMI: " << metricsArray[i]->getBmi() 
                  << ", BMR: " << metricsArray[i]->getBmrKcal() << " ккал" << std::endl;
    }
    
    // Освобождение памяти: сначала удаляем объекты, затем массив указателей
    for (int i = 0; i < arraySize; i++)
    {
        delete metricsArray[i];
        metricsArray[i] = nullptr;
    }
    delete[] metricsArray;
    metricsArray = nullptr;
    std::cout << "  Все динамические объекты и массив удалены" << std::endl;
    
    // Дополнительная демонстрация с MovementLibrary
    MovementLibrary* library = new MovementLibrary(1);
    Movement m1("deadlift_001", "Становая тяга", "strength");
    Movement m2("bench_001", "Жим лежа", "strength");
    Movement m3("row_001", "Тяга в наклоне", "strength");
    
    library->addMovement(m1);
    library->addMovement(m2);
    library->addMovement(m3);
    
    std::cout << "  Библиотека движений создана, версия: " << library->getRev() << std::endl;
    auto found = library->find("жим");
    std::cout << "  Найдено движений по запросу 'жим': " << found.size() << std::endl;
    
    delete library;
    library = nullptr;
}
