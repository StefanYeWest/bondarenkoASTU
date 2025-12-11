# Описание программы (Лабораторная работа №6 - C++)

## Код программы

Программа представляет собой систему управления тренировками и прогрессом спортсмена, реализованную на C++ с использованием наследования и полиморфизма. В данной работе функционал расширен созданием производных классов, использованием виртуальных функций, абстрактных классов и различных техник наследования.

### Основные изменения в лабораторной работе №6:

#### 1. Производные классы

**Созданы производные классы от базовых:**

- `StrengthMovement` - наследуется от `Movement` и `Exercisable` (множественное наследование)
  - Добавлены поля: `m_sets`, `m_reps`, `m_weightKg` (protected)
  - Специализированные методы для силовых упражнений
  
- `CardioMovement` - наследуется от `Movement` и `Exercisable`
  - Добавлены поля: `m_distanceKm`, `m_speedKmh` (protected)
  - Специализированные методы для кардио упражнений

- `AdvancedTrainingSession` - наследуется от `TrainingSession`
  - Добавлены поля: `m_notes`, `m_coachName`
  - Демонстрация виртуального деструктора

**Пример использования:**
```cpp
StrengthMovement strength("str_001", "Приседания", 3, 10, 100.0);
CardioMovement cardio("card_001", "Бег", 5.0, 10.0);
```

#### 2. Модификатор protected

**Демонстрация использования protected:**

- В базовом классе `BaseEntity`: поля `m_id` и `m_name` объявлены как `protected`
- В базовом классе `Exercisable`: поля `m_name` и `m_durationMinutes` объявлены как `protected`
- Производные классы имеют доступ к protected полям базовых классов
- Метод `StrengthMovement::updateName()` демонстрирует доступ к protected полям

**Пример:**
```cpp
void StrengthMovement::updateName(const std::string& newName)
{
    this->m_name = newName; // Доступ к protected полю BaseEntity
    this->Exercisable::m_name = newName; // Доступ к protected полю Exercisable
}
```

#### 3. Перегрузка методов базового класса

**Переопределение методов с вызовом базового и без:**

- `StrengthMovement::getDescription()` - переопределен С вызовом базового метода `Movement::getDescription()`
- `CardioMovement::getDescription()` - переопределен БЕЗ вызова базового метода
- `StrengthMovement::getEstimatedCalories()` - переопределен С вызовом `Exercisable::getEstimatedCalories()`
- `CardioMovement::getEstimatedCalories()` - переопределен БЕЗ вызова базового

**Примеры:**
```cpp
// С вызовом базового
std::string StrengthMovement::getDescription() const
{
    std::string baseDesc = Movement::getDescription(); // Вызов базового
    return baseDesc + " [Strength: ...]";
}

// Без вызова базового
std::string CardioMovement::getDescription() const
{
    return "Cardio: " + this->getName() + " - ..."; // Без вызова базового
}
```

#### 4. Виртуальные функции и полиморфизм

**Реализованы виртуальные функции:**

- `BaseEntity::getDescription()` - виртуальный метод
- `Movement::getDescription()` - переопределен с `override`
- `Exercisable::canPerform()` - чисто виртуальный метод
- `Exercisable::getInstructions()` - чисто виртуальный метод
- `Exercisable::getEstimatedCalories()` - виртуальный метод с реализацией

**Демонстрация полиморфизма:**

1. Вызов через указатель на базовый класс:
```cpp
Exercisable* ex1 = &strength;
ex1->canPerform(athlete); // Вызывается StrengthMovement::canPerform
```

2. Вызов через невиртуальную функцию базового класса (полиморфизм все равно работает)

3. Присваивание указателя:
```cpp
Exercisable* ex3 = ex1; // Полиморфизм сохраняется
```

**Разница с невиртуальными функциями:**
- Если метод не виртуальный, вызывается метод базового класса
- Виртуальный метод вызывает метод производного класса через указатель на базовый

#### 5. Клонирование (поверхностное и глубокое)

**Реализован класс `ClonableMovementWrapper`:**

- Интерфейс `CloneableMovement` с методами `clone()` и `shallowClone()`
- Глубокое клонирование (`clone()`) - создает новый объект `Movement` через конструктор копирования
- Поверхностное клонирование (`shallowClone()`) - разделяет `shared_ptr`, оба указывают на один объект

**Пример:**
```cpp
ClonableMovementWrapper original(movement);
auto deepClone = original.clone(); // Новый объект
auto shallowClone = original.shallowClone(); // Разделяет shared_ptr
```

#### 6. Вызов конструктора базового класса

**Демонстрация в конструкторах производных классов:**

- `StrengthMovement::StrengthMovement()` вызывает:
  - `Movement(code, title, "strength")` - конструктор базового класса Movement
  - `Exercisable(title, 30)` - конструктор Exercisable
  
- `CardioMovement::CardioMovement()` вызывает:
  - `Movement(code, title, "cardio")`
  - `Exercisable(title, calculatedDuration)`

**Пример:**
```cpp
StrengthMovement::StrengthMovement(...)
    : Movement(code, title, "strength"), // Вызов конструктора базового класса
      Exercisable(title, 30),            // Вызов конструктора Exercisable
      m_sets(sets), m_reps(reps), m_weightKg(weightKg)
{
}
```

#### 7. Абстрактный класс

**Создан абстрактный класс `Exercisable`:**

- Содержит чисто виртуальные методы: `canPerform()` и `getInstructions()`
- Нельзя создать объект абстрактного класса напрямую
- Можно использовать только через производные классы
- Виртуальный метод `getEstimatedCalories()` с реализацией по умолчанию

**Пример использования:**
```cpp
// Exercisable ex("test", 10); // Ошибка компиляции - класс абстрактный

Exercisable* exercises[] = {&strength, &cardio}; // Использование через указатели
for (auto ex : exercises) {
    ex->getInstructions(); // Вызывается метод производного класса
}
```

#### 8. Перегрузка оператора присваивания для производного класса

**Реализован оператор присваивания от базового класса:**

- `StrengthMovement& operator=(const Movement& base)` - присваивание от базового класса Movement
- `CardioMovement& operator=(const Movement& base)` - присваивание от базового класса Movement

**Пример:**
```cpp
Movement base("base_001", "Базовое упражнение", "general");
StrengthMovement strength("str_001", "Жим", 3, 8, 80.0);
strength = base; // Использует operator=(const Movement&)
```

#### 9. Запрет конструктора копирования

**Создан класс `NonCopyableSession`:**

- Конструктор копирования удален: `NonCopyableSession(const NonCopyableSession&) = delete;`
- Оператор присваивания удален: `operator=(const NonCopyableSession&) = delete;`
- Перемещение разрешено: конструктор и оператор перемещения = default

**Пример:**
```cpp
NonCopyableSession session1("sess_001", "Сессия 1");
// NonCopyableSession session2 = session1; // Ошибка компиляции
NonCopyableSession session3 = std::move(session1); // Разрешено
```

#### 10. Виртуальный деструктор

**Виртуальный деструктор в базовых классах:**

- `BaseEntity::~BaseEntity()` - виртуальный деструктор
- `Exercisable::~Exercisable()` - виртуальный деструктор
- `TrainingSession::~TrainingSession()` - виртуальный деструктор

**Демонстрация:**
```cpp
TrainingSession* session = new AdvancedTrainingSession("adv_001", "Сессия", "Тренер");
delete session; // Вызывается AdvancedTrainingSession::~AdvancedTrainingSession(),
                // затем TrainingSession::~TrainingSession()
```

**Разница с невиртуальным деструктором:**
- Без виртуального деструктора вызывался бы только деструктор базового класса
- С виртуальным деструктором вызываются деструкторы в правильном порядке (производный → базовый)

## Тест программы

Запуск программы через Xcode или компилятор выводит результаты всех демонстраций:

1. **Наследование и производные классы** - создание StrengthMovement и CardioMovement
2. **Модификатор protected** - доступ к protected полям базовых классов
3. **Перегрузка методов** - методы с вызовом базового и без
4. **Виртуальные функции** - полиморфизм через указатели на базовый класс
5. **Клонирование** - поверхностное и глубокое клонирование объектов
6. **Абстрактный класс** - использование Exercisable через производные классы
7. **Виртуальный деструктор** - правильное освобождение ресурсов при удалении через указатель на базовый класс
8. **Запрет копирования** - демонстрация NonCopyableSession
9. **Оператор присваивания** - присваивание объекта базового класса производному

Все демонстрации показывают корректную работу механизмов наследования и полиморфизма: виртуальные функции вызывают правильные методы производных классов, виртуальный деструктор гарантирует правильное освобождение ресурсов, абстрактный класс обеспечивает интерфейс для производных классов.

