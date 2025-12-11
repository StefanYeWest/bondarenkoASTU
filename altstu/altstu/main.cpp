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
#include "exercisable.hpp"
#include "strengthmovement.hpp"
#include "cardiomovement.hpp"
#include "noncopyable.hpp"
#include "cloneable.hpp"
#include "advancedsession.hpp"

void demonstrateStaticInitialization();
void demonstrateSmartPointers();
void demonstrateReferencesAndPointers();
void demonstrateDynamicArrayOfObjects();
void demonstrateArrayOfDynamicObjects();
void demonstrateOperators();
void demonstrateCopyConstructors();
void demonstrateInheritance();
void demonstrateStringOperations();
void demonstrateLab6Inheritance();
void demonstrateProtectedMembers();
void demonstrateMethodOverriding();
void demonstrateVirtualFunctions();
void demonstrateCloning();
void demonstrateAbstractClass();
void demonstrateVirtualDestructor();
void demonstrateNonCopyable();
void demonstrateDerivedAssignment();

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
    
    std::cout << "=== Лабораторная работа №6 ===\n\n";
    
    std::cout << "11. Наследование и производные классы:\n";
    demonstrateLab6Inheritance();
    std::cout << "\n";
    
    std::cout << "12. Модификатор protected:\n";
    demonstrateProtectedMembers();
    std::cout << "\n";
    
    std::cout << "13. Перегрузка методов (с вызовом базового и без):\n";
    demonstrateMethodOverriding();
    std::cout << "\n";
    
    std::cout << "14. Виртуальные функции и полиморфизм:\n";
    demonstrateVirtualFunctions();
    std::cout << "\n";
    
    std::cout << "15. Клонирование (поверхностное и глубокое):\n";
    demonstrateCloning();
    std::cout << "\n";
    
    std::cout << "16. Абстрактный класс:\n";
    demonstrateAbstractClass();
    std::cout << "\n";
    
    std::cout << "17. Виртуальный деструктор:\n";
    demonstrateVirtualDestructor();
    std::cout << "\n";
    
    std::cout << "18. Запрет конструктора копирования:\n";
    demonstrateNonCopyable();
    std::cout << "\n";
    
    std::cout << "19. Оператор присваивания производного класса:\n";
    demonstrateDerivedAssignment();
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

void demonstrateLab6Inheritance()
{
    // Демонстрация производных классов
    AthleteAccount athlete("acc021", "Тестовый спортсмен", GoalCode::eBulk);
    athlete.addGear("barbell");
    
    StrengthMovement strength("str_001", "Приседания со штангой", 3, 10, 100.0);
    strength.addGearNeed("barbell");
    
    std::cout << "  StrengthMovement создан: " << strength.getTitle() << std::endl;
    std::cout << "  Код (из базового класса Movement): " << strength.getCode() << std::endl;
    std::cout << "  Подходы: " << strength.getSets() << ", повторения: " << strength.getReps() << std::endl;
    
    CardioMovement cardio("card_001", "Бег", 5.0, 10.0);
    
    std::cout << "  CardioMovement создан: " << cardio.getTitle() << std::endl;
    std::cout << "  Дистанция: " << cardio.getDistanceKm() << " км, скорость: " 
              << cardio.getSpeedKmh() << " км/ч" << std::endl;
    std::cout << "  Длительность (из Exercisable): " << cardio.getDuration() << " минут" << std::endl;
}

void demonstrateProtectedMembers()
{
    // Демонстрация использования protected членов
    StrengthMovement strength("str_002", "Жим гантелей", 4, 12, 25.0);
    
    // Доступ к protected полю базового класса BaseEntity через метод производного класса
    std::cout << "  Имя (из protected поля BaseEntity::m_name): " << strength.getTitle() << std::endl;
    std::cout << "  ID (из protected поля BaseEntity::m_id): " << strength.getCode() << std::endl;
    
    // Использование метода, который работает с protected полями
    strength.updateName("Жим гантелей (обновлено)");
    std::cout << "  После updateName (использует protected поля): " << strength.getTitle() << std::endl;
    
    // Доступ к protected полям Exercisable
    std::cout << "  Длительность (из protected поля Exercisable::m_durationMinutes): " 
              << strength.getDuration() << " минут" << std::endl;
}

void demonstrateMethodOverriding()
{
    AthleteAccount athlete("acc022", "Тестовый", GoalCode::eBulk);
    athlete.addGear("barbell");
    
    StrengthMovement strength("str_003", "Становая тяга", 5, 5, 120.0);
    strength.addGearNeed("barbell");
    
    CardioMovement cardio("card_002", "Велотренажер", 10.0, 20.0);
    
    // Демонстрация переопределения getEstimatedCalories - С вызовом базового
    std::cout << "  StrengthMovement::getEstimatedCalories() (с вызовом базового Exercisable::getEstimatedCalories):" << std::endl;
    std::cout << "    " << strength.getEstimatedCalories() << " ккал" << std::endl;
    
    // Демонстрация переопределения getEstimatedCalories - БЕЗ вызова базового
    std::cout << "  CardioMovement::getEstimatedCalories() (без вызова базового):" << std::endl;
    std::cout << "    " << cardio.getEstimatedCalories() << " ккал" << std::endl;
    
    // Демонстрация getDescription - С вызовом базового
    std::cout << "  StrengthMovement::getDescription() (с вызовом базового Movement::getDescription):" << std::endl;
    std::cout << "    " << strength.getDescription() << std::endl;
    
    // Демонстрация getDescription - БЕЗ вызова базового
    std::cout << "  CardioMovement::getDescription() (без вызова базового):" << std::endl;
    std::cout << "    " << cardio.getDescription() << std::endl;
    
    // Новый метод без вызова базового
    std::cout << "  StrengthMovement::getWorkoutDetails() (новый метод, без базового):" << std::endl;
    std::cout << "    " << strength.getWorkoutDetails() << std::endl;
}

void demonstrateVirtualFunctions()
{
    AthleteAccount athlete("acc020", "Тестовый спортсмен", GoalCode::eBulk);
    athlete.addGear("barbell");
    athlete.addGear("dumbbells");
    
    StrengthMovement strength("str_004", "Жим лежа", 3, 8, 80.0);
    strength.addGearNeed("barbell");
    
    CardioMovement cardio("card_003", "Плавание", 1.5, 3.0);
    
    // Демонстрация полиморфизма через указатели на базовый класс
    std::cout << "  Полиморфизм через указатели на базовый класс Exercisable:" << std::endl;
    Exercisable* ex1 = &strength;
    Exercisable* ex2 = &cardio;
    
    std::cout << "    StrengthMovement через Exercisable*::canPerform(): " 
              << (ex1->canPerform(athlete) ? "можно выполнить" : "нельзя выполнить") << std::endl;
    std::cout << "    CardioMovement через Exercisable*::canPerform(): " 
              << (ex2->canPerform(athlete) ? "можно выполнить" : "нельзя выполнить") << std::endl;
    
    // Демонстрация виртуальной функции getInstructions
    std::cout << "    Инструкции через Exercisable* (виртуальная функция):" << std::endl;
    std::cout << "      Strength: " << ex1->getInstructions() << std::endl;
    std::cout << "      Cardio: " << ex2->getInstructions() << std::endl;
    
    // Демонстрация виртуальной функции getEstimatedCalories
    std::cout << "    Калории через Exercisable* (виртуальная функция):" << std::endl;
    std::cout << "      Strength: " << ex1->getEstimatedCalories() << " ккал" << std::endl;
    std::cout << "      Cardio: " << ex2->getEstimatedCalories() << " ккал" << std::endl;
    
    // Демонстрация присваивания указателя
    Exercisable* ex3 = ex1;
    std::cout << "    После присваивания указателя: " << ex3->getInstructions() << std::endl;
    
    // Демонстрация через указатель на Movement (базовый класс Movement)
    std::cout << "  Полиморфизм через указатели на базовый класс Movement:" << std::endl;
    Movement* mov1 = &strength;
    Movement* mov2 = &cardio;
    
    std::cout << "    StrengthMovement через Movement*::getDescription(): " 
              << mov1->getDescription() << std::endl;
    std::cout << "    CardioMovement через Movement*::getDescription(): " 
              << mov2->getDescription() << std::endl;
    
    // Демонстрация разницы: если бы getDescription не был виртуальным
    std::cout << "  Если бы getDescription не был виртуальным, вызывался бы метод базового класса" << std::endl;
}

void demonstrateCloning()
{
    // Создаем Movement для обертки
    auto originalMovement = std::make_shared<Movement>("str_005", "Приседания", "strength");
    originalMovement->setDifficultyBand(1);
    originalMovement->addTarget("quads");
    
    ClonableMovementWrapper original(originalMovement);
    
    std::cout << "  Оригинальный объект:" << std::endl;
    std::cout << "    " << original.getMovement()->getTitle() << std::endl;
    std::cout << "    Сложность: " << original.getMovement()->getDifficultyBand() << std::endl;
    
    // Глубокое клонирование - создает новый объект Movement
    auto deepClone = original.clone();
    std::cout << "  Глубокое клонирование (через clone()):" << std::endl;
    auto deepWrapper = dynamic_cast<ClonableMovementWrapper*>(deepClone.get());
    if (deepWrapper)
    {
        std::cout << "    " << deepWrapper->getMovement()->getTitle() << std::endl;
        // Изменение клона не влияет на оригинал
        deepWrapper->getMovement()->setDifficultyBand(2);
        std::cout << "    После изменения клона - оригинал: " 
                  << original.getMovement()->getDifficultyBand() 
                  << ", клон: " << deepWrapper->getMovement()->getDifficultyBand() << std::endl;
    }
    
    // Поверхностное клонирование - разделяет shared_ptr
    auto shallowClone = original.shallowClone();
    std::cout << "  Поверхностное клонирование (через shallowClone()):" << std::endl;
    auto shallowWrapper = dynamic_cast<ClonableMovementWrapper*>(shallowClone);
    if (shallowWrapper)
    {
        std::cout << "    " << shallowWrapper->getMovement()->getTitle() << std::endl;
        // Изменение клона влияет на оригинал (разделяют один объект)
        shallowWrapper->getMovement()->setDifficultyBand(3);
        std::cout << "    После изменения клона - оригинал: " 
                  << original.getMovement()->getDifficultyBand() 
                  << ", клон: " << shallowWrapper->getMovement()->getDifficultyBand() << std::endl;
        std::cout << "    (Оба указывают на один объект - поверхностное копирование)" << std::endl;
    }
    
    delete shallowClone;
}

void demonstrateAbstractClass()
{
    // Нельзя создать объект абстрактного класса напрямую
    // Exercisable ex("test", 10); // Ошибка компиляции - класс абстрактный
    
    std::cout << "  Абстрактный класс Exercisable нельзя инстанцировать напрямую" << std::endl;
    std::cout << "  (содержит чисто виртуальные методы canPerform и getInstructions)" << std::endl;
    std::cout << "  Можно использовать только через производные классы:" << std::endl;
    
    AthleteAccount athlete("acc023", "Тестовый", GoalCode::eBulk);
    athlete.addGear("pullup_bar");
    
    StrengthMovement strength("str_006", "Подтягивания", 3, 10, 0.0);
    strength.addGearNeed("pullup_bar");
    
    CardioMovement cardio("card_004", "Бег на дорожке", 5.0, 12.0);
    
    // Использование через указатель на абстрактный класс
    Exercisable* exercises[] = {&strength, &cardio};
    
    for (int i = 0; i < 2; i++)
    {
        std::cout << "    Упражнение " << (i + 1) << ": " << exercises[i]->getName() << std::endl;
        std::cout << "      Инструкции (чисто виртуальный метод): " 
                  << exercises[i]->getInstructions() << std::endl;
        std::cout << "      Можно выполнить: " 
                  << (exercises[i]->canPerform(athlete) ? "да" : "нет") << std::endl;
        std::cout << "      Калории (виртуальный метод): " 
                  << exercises[i]->getEstimatedCalories() << " ккал" << std::endl;
    }
}

void demonstrateVirtualDestructor()
{
    std::cout << "  Демонстрация виртуального деструктора:" << std::endl;
    
    // Создание объектов через указатели на базовый класс
    Exercisable* ex1 = new StrengthMovement("str_007", "Жим", 3, 8, 80.0);
    Exercisable* ex2 = new CardioMovement("card_005", "Прыжки", 2.0, 8.0);
    
    std::cout << "    Созданы объекты через Exercisable*" << std::endl;
    std::cout << "    " << ex1->getName() << std::endl;
    std::cout << "    " << ex2->getName() << std::endl;
    
    // Удаление через указатель на базовый класс
    // Благодаря виртуальному деструктору вызываются правильные деструкторы
    std::cout << "    Удаление через указатель на базовый класс..." << std::endl;
    delete ex1; // Вызовется деструктор StrengthMovement, затем Exercisable
    delete ex2; // Вызовется деструктор CardioMovement, затем Exercisable
    
    // Демонстрация с TrainingSession (виртуальный деструктор)
    std::cout << "  Демонстрация виртуального деструктора для TrainingSession:" << std::endl;
    TrainingSession* session = new AdvancedTrainingSession("adv_001", "Продвинутая сессия", "Тренер Иван");
    std::cout << "    Создан AdvancedTrainingSession через TrainingSession*" << std::endl;
    std::cout << "    Удаление через указатель на базовый класс..." << std::endl;
    delete session; // Вызовется деструктор AdvancedTrainingSession, затем TrainingSession
    std::cout << "    Виртуальный деструктор гарантирует правильное освобождение ресурсов" << std::endl;
}

void demonstrateNonCopyable()
{
    std::cout << "  Класс с запрещенным конструктором копирования:" << std::endl;
    
    NonCopyableSession session1("sess_nc_001", "Уникальная сессия 1");
    std::cout << "    Создан объект: " << session1.getTitle() 
              << " (ID: " << session1.getSessionId() << ")" << std::endl;
    
    NonCopyableSession session2("sess_nc_002", "Уникальная сессия 2");
    std::cout << "    Создан объект: " << session2.getTitle() 
              << " (ID: " << session2.getSessionId() << ")" << std::endl;
    
    // Попытка копирования вызовет ошибку компиляции
    // NonCopyableSession session3 = session1; // Ошибка: конструктор копирования удален
    // session3 = session1; // Ошибка: оператор присваивания удален
    
    std::cout << "    Конструктор копирования запрещен (удален)" << std::endl;
    std::cout << "    Оператор присваивания запрещен (удален)" << std::endl;
    
    // Но перемещение разрешено
    NonCopyableSession session4 = std::move(session1);
    std::cout << "    Перемещение разрешено: " << session4.getTitle() 
              << " (ID: " << session4.getSessionId() << ")" << std::endl;
}

void demonstrateDerivedAssignment()
{
    std::cout << "  Перегрузка оператора присваивания для производного класса:" << std::endl;
    
    StrengthMovement strength("str_008", "Жим лежа", 3, 8, 90.0);
    
    std::cout << "    Оригинальный StrengthMovement:" << std::endl;
    std::cout << "      " << strength.getTitle() << std::endl;
    std::cout << "      Подходы: " << strength.getSets() 
              << ", повторения: " << strength.getReps() << std::endl;
    
    // Создание объекта базового класса Movement
    Movement base("base_001", "Базовое упражнение", "general");
    base.setDifficultyBand(2);
    
    std::cout << "    Объект базового класса Movement:" << std::endl;
    std::cout << "      " << base.getTitle() << ", сложность: " << base.getDifficultyBand() << std::endl;
    
    // Присваивание объекта базового класса производному классу
    strength = base; // Использует operator=(const Movement&)
    
    std::cout << "    После присваивания Movement -> StrengthMovement:" << std::endl;
    std::cout << "      " << strength.getTitle() << std::endl;
    std::cout << "      Подходы (остались прежними): " << strength.getSets() << std::endl;
    std::cout << "      Сложность (из базового класса): " << strength.getDifficultyBand() << std::endl;
}

