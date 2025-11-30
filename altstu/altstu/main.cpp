//
//  main.cpp
//  altstu
//
//  Created by Stepan Bondarenko on 04.11.2025.
//

#include <iostream>
#include <memory>
#include <vector>
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
#include "baseentity.hpp"

void demonstrateStaticInitialization();
void demonstrateSmartPointers();
void demonstrateReferencesAndPointers();
void demonstrateDynamicArrayOfObjects();
void demonstrateArrayOfDynamicObjects();
void demonstrateOperators();
void demonstrateCopyConstructors();
void demonstrateInheritance();
void demonstrateStringOperations();

int main(int argc, const char * argv[])
{
    std::cout << "=== Демонстрация работы классов (Лабораторная 5) ===\n\n";
    
    std::cout << "1. Статическая инициализация объектов:\n";
    demonstrateStaticInitialization();
    std::cout << "\n";
    
    std::cout << "2. Smart pointers (unique_ptr, shared_ptr):\n";
    demonstrateSmartPointers();
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
    
    std::cout << "6. Перегрузка операторов:\n";
    demonstrateOperators();
    std::cout << "\n";
    
    std::cout << "7. Конструкторы копирования:\n";
    demonstrateCopyConstructors();
    std::cout << "\n";
    
    std::cout << "8. Наследование и вызов конструктора базового класса:\n";
    demonstrateInheritance();
    std::cout << "\n";
    
    std::cout << "9. Работа со std::string:\n";
    demonstrateStringOperations();
    std::cout << "\n";
    
    std::cout << "10. Статические поля и методы:\n";
    std::cout << "  Всего создано аккаунтов: " << AthleteAccount::getAccountCount() << std::endl;
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

void demonstrateSmartPointers()
{
    // Использование unique_ptr для единоличного владения
    std::unique_ptr<AthleteAccount> athletePtr = std::make_unique<AthleteAccount>("acc002", "Петр Петров", GoalCode::eCut);
    athletePtr->setExperienceBand(2);
    athletePtr->addGear("kettlebell");
    athletePtr->addGear("resistance_bands");
    
    std::cout << "  Создан спортсмен (unique_ptr): " << athletePtr->getDisplayName() << std::endl;
    
    // Работа с объектом через smart pointer
    athletePtr->updateGoal(GoalCode::eShape);
    std::cout << "  Новая цель: " << static_cast<int>(athletePtr->getPrimaryGoal()) << std::endl;
    
    // unique_ptr автоматически освобождает память при выходе из области видимости
    std::cout << "  Память будет автоматически освобождена" << std::endl;
    
    // Использование shared_ptr для разделяемого владения
    std::shared_ptr<Movement> movement1 = std::make_shared<Movement>("bench_001", "Жим лежа", "strength");
    std::shared_ptr<Movement> movement2 = movement1; // Копирование shared_ptr
    
    std::cout << "  Создано shared_ptr движений, счетчик ссылок: " << movement1.use_count() << std::endl;
    
    // Использование unique_ptr для TrainingSession
    auto session = std::make_unique<TrainingSession>("sess_001", "FullBody A");
    session->setPlannedAt("2025-11-05 10:00");
    session->start();
    
    std::cout << "  Сессия создана: " << session->getTitle() << std::endl;
    
    SessionTelemetry telemetry;
    telemetry.setDuration(45);
    telemetry.setCalories(350);
    session->finalize(telemetry);
    
    std::cout << "  Сессия завершена (unique_ptr автоматически освободит память)" << std::endl;
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
    // Массив автоматически освободится при выходе из области видимости
    std::cout << "  Массив будет автоматически удален" << std::endl;
}

void demonstrateArrayOfDynamicObjects()
{
    // Массив shared_ptr на динамические объекты
    const int arraySize = 3;
    std::vector<std::shared_ptr<BodyMetrics>> metricsArray;
    
    // Создание динамических объектов через shared_ptr
    metricsArray.push_back(std::make_shared<BodyMetrics>("acc004", 70.0, 175));
    metricsArray[0]->setRestingHR(70);
    metricsArray[0]->recalculateDerived();
    
    metricsArray.push_back(std::make_shared<BodyMetrics>("acc005", 80.0, 185));
    metricsArray[1]->setRestingHR(65);
    metricsArray[1]->setSleepHours(8.0);
    metricsArray[1]->recalculateDerived();
    
    metricsArray.push_back(std::make_shared<BodyMetrics>("acc006", 65.0, 170));
    metricsArray[2]->setRestingHR(72);
    metricsArray[2]->recalculateDerived();
    
    std::cout << "  Массив динамических объектов BodyMetrics (" << arraySize << " элементов):" << std::endl;
    for (size_t i = 0; i < metricsArray.size(); i++)
    {
        std::cout << "    [" << i << "] ID: " << metricsArray[i]->getAthleteId()
                  << ", вес: " << metricsArray[i]->getWeightKg() 
                  << " кг, BMI: " << metricsArray[i]->getBmi() 
                  << ", BMR: " << metricsArray[i]->getBmrKcal() << " ккал" << std::endl;
    }
    
    std::cout << "  Память автоматически освободится при выходе из области видимости" << std::endl;
    
    // Дополнительная демонстрация с MovementLibrary
    auto library = std::make_unique<MovementLibrary>(1);
    Movement m1("deadlift_001", "Становая тяга", "strength");
    Movement m2("bench_001", "Жим лежа", "strength");
    Movement m3("row_001", "Тяга в наклоне", "strength");
    
    *library += m1; // Использование оператора +=
    library->addMovement(m2);
    library->addMovement(m3);
    
    std::cout << "  Библиотека движений создана, версия: " << library->getRev() << std::endl;
    auto found = library->find("жим");
    std::cout << "  Найдено движений по запросу 'жим': " << found.size() << std::endl;
    
    // Демонстрация оператора []
    if (library->getItems().size() > 0)
    {
        std::cout << "  Первое движение через operator[]: " << (*library)[0].getTitle() << std::endl;
    }
}

void demonstrateOperators()
{
    // Демонстрация перегрузки операторов для BodyMetrics
    BodyMetrics metrics1("acc007", 75.0, 180);
    metrics1.setRestingHR(70);
    metrics1.recalculateDerived();
    
    BodyMetrics metrics2("acc007", 76.0, 180);
    metrics2.setRestingHR(68);
    metrics2.recalculateDerived();
    
    std::cout << "  Оператор == : " << (metrics1 == metrics2 ? "равны" : "не равны") << std::endl;
    std::cout << "  Оператор != : " << (metrics1 != metrics2 ? "не равны" : "равны") << std::endl;
    
    // Оператор + для объединения метрик
    BodyMetrics merged = metrics1 + metrics2;
    std::cout << "  Оператор + (объединение): вес " << merged.getWeightKg() << " кг" << std::endl;
    
    // Оператор << для вывода (дружественная функция)
    std::cout << "  Оператор << : " << metrics1 << std::endl;
    
    // Оператор << для TrainingSession
    TrainingSession session("sess_002", "Push Day");
    session.start();
    SessionTelemetry tel;
    tel.setDuration(60);
    tel.setCalories(400);
    session.finalize(tel);
    std::cout << "  Оператор << для TrainingSession: " << session << std::endl;
    
    // Оператор [] для MovementLibrary
    MovementLibrary library(1);
    Movement m1("squat_001", "Приседания", "strength");
    Movement m2("deadlift_001", "Становая тяга", "strength");
    library += m1; // Оператор +=
    library += m2;
    
    std::cout << "  Оператор [] : " << library[0].getTitle() << std::endl;
    std::cout << "  Оператор += : добавлено " << library.getItems().size() << " движений" << std::endl;
}

void demonstrateCopyConstructors()
{
    // Демонстрация конструктора копирования для BodyMetrics
    BodyMetrics original("acc008", 70.0, 175);
    original.setRestingHR(65);
    original.recalculateDerived();
    
    BodyMetrics copy = original; // Использование конструктора копирования
    std::cout << "  Оригинал: " << original << std::endl;
    std::cout << "  Копия: " << copy << std::endl;
    std::cout << "  Копия равна оригиналу: " << (original == copy ? "да" : "нет") << std::endl;
    
    // Демонстрация конструктора копирования для Movement
    Movement mov1("bench_001", "Жим лежа", "strength");
    mov1.setDifficultyBand(1);
    mov1.addTarget("chest");
    
    Movement mov2 = mov1; // Конструктор копирования
    std::cout << "  Оригинальное движение: " << mov1.getTitle() << std::endl;
    std::cout << "  Скопированное движение: " << mov2.getTitle() << std::endl;
    
    // Демонстрация конструктора копирования для AthleteAccount
    AthleteAccount acc1("acc009", "Тестовый аккаунт", GoalCode::eBulk);
    acc1.addGear("barbell");
    
    AthleteAccount acc2 = acc1; // Конструктор копирования
    std::cout << "  Оригинальный аккаунт: " << acc1.getDisplayName() << std::endl;
    std::cout << "  Скопированный аккаунт: " << acc2.getDisplayName() << std::endl;
}

void demonstrateInheritance()
{
    // Демонстрация наследования: Movement наследуется от BaseEntity
    Movement movement("squat_002", "Глубокие приседания", "strength");
    movement.setDifficultyBand(2);
    
    // Использование методов базового класса
    std::cout << "  ID из базового класса: " << movement.getId() << std::endl;
    std::cout << "  Name из базового класса: " << movement.getName() << std::endl;
    
    // Переопределенный метод
    std::cout << "  Описание (переопределенный метод): " << movement.getDescription() << std::endl;
    
    // Демонстрация вызова конструктора базового класса
    BaseEntity* entity = &movement; // Полиморфизм
    std::cout << "  Полиморфизм: " << entity->getDescription() << std::endl;
}

void demonstrateStringOperations()
{
    // Демонстрация работы со std::string
    std::string str1 = "Приседания";
    std::string str2 = " со штангой";
    
    // Конкатенация
    std::string result = str1 + str2;
    std::cout << "  Конкатенация: " << result << std::endl;
    
    // Поиск подстроки
    size_t pos = result.find("штангой");
    if (pos != std::string::npos)
    {
        std::cout << "  Найдено 'штангой' на позиции: " << pos << std::endl;
    }
    
    // Извлечение подстроки
    std::string substr = result.substr(0, 10);
    std::cout << "  Подстрока (первые 10 символов): " << substr << std::endl;
    
    // Длина строки
    std::cout << "  Длина строки: " << result.length() << " символов" << std::endl;
    
    // Поиск и замена (демонстрация)
    std::string code = "movement_001";
    std::string prefix = "movement_";
    if (code.find(prefix) == 0)
    {
        std::string number = code.substr(prefix.length());
        std::cout << "  Извлеченный номер из кода: " << number << std::endl;
    }
}

