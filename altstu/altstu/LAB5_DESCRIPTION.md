# Описание программы (Лабораторная работа №5 - C++)

## Код программы

Программа представляет собой систему управления тренировками и прогрессом спортсмена, реализованную на C++ с использованием современных возможностей языка. В данной работе функционал расширен использованием умных указателей, перегрузки операторов, конструкторов копирования, наследования и работы со строками.

### Основные изменения в лабораторной работе №5:

#### 1. Умные указатели (Smart Pointers)

**Заменили обычные указатели на `std::unique_ptr` и `std::shared_ptr`:**

- `TrainingSession::m_telemetry` - изменен с `SessionTelemetry*` на `std::unique_ptr<SessionTelemetry>` для автоматического управления памятью
- `WorkBlock::m_movement` - изменен с `Movement*` на `std::shared_ptr<Movement>` для разделяемого владения
- `SessionBlueprint::instantiate()` - возвращает `std::unique_ptr<TrainingSession>` вместо сырого указателя
- `Movement::closestAlternative()` - возвращает `std::shared_ptr<Movement>`

**Пример использования:**
```cpp
// unique_ptr для единоличного владения
auto session = std::make_unique<TrainingSession>("sess_001", "FullBody A");
session->start();

// shared_ptr для разделяемого владения
std::shared_ptr<Movement> movement1 = std::make_shared<Movement>("bench_001", "Жим лежа", "strength");
std::shared_ptr<Movement> movement2 = movement1; // Копирование shared_ptr
```

#### 2. Дружественные функции

**Реализованы две дружественные функции:**

- `friend std::ostream& operator<<(std::ostream&, const TrainingSession&)` - для вывода информации о тренировочной сессии в поток
- `friend std::ostream& operator<<(std::ostream&, const BodyMetrics&)` - для вывода метрик тела в поток

**Пример:**
```cpp
TrainingSession session("sess_001", "Push Day");
std::cout << session << std::endl; // Использует дружественную функцию
```

#### 3. Перегрузка операторов (6 примеров)

**Реализованы следующие операторы:**

1. `BodyMetrics::operator==` - сравнение метрик на равенство
2. `BodyMetrics::operator!=` - сравнение метрик на неравенство
3. `BodyMetrics::operator+` - объединение метрик (аналог mergeWith)
4. `BodyMetrics::operator<<` - вывод в поток (дружественная функция)
5. `TrainingSession::operator<<` - вывод в поток (дружественная функция)
6. `MovementLibrary::operator[]` - доступ к движению по индексу
7. `MovementLibrary::operator+=` - добавление движения в библиотеку

**Примеры:**
```cpp
BodyMetrics m1("acc001", 75.0, 180);
BodyMetrics m2("acc001", 76.0, 180);
bool equal = (m1 == m2); // Оператор ==
BodyMetrics merged = m1 + m2; // Оператор +
std::cout << m1 << std::endl; // Оператор <<

MovementLibrary lib(1);
lib += Movement("squat_001", "Приседания", "strength"); // Оператор +=
Movement& mov = lib[0]; // Оператор []
```

#### 4. Работа со std::string

**Использованы различные операции со строками:**

- Конкатенация: `std::string result = str1 + str2;`
- Поиск подстроки: `size_t pos = result.find("штангой");`
- Извлечение подстроки: `std::string substr = result.substr(0, 10);`
- Получение длины: `result.length()`
- Преобразование регистра в `MovementLibrary::matchesText()`

**Пример:**
```cpp
std::string str1 = "Приседания";
std::string str2 = " со штангой";
std::string result = str1 + str2; // Конкатенация
size_t pos = result.find("штангой"); // Поиск
std::string substr = result.substr(0, 10); // Подстрока
```

#### 5. Конструкторы копирования

**Реализованы конструкторы копирования для основных классов:**

- `BodyMetrics::BodyMetrics(const BodyMetrics&)` - копирование всех полей включая optional
- `Movement::Movement(const Movement&)` - копирование с вызовом конструктора базового класса
- `AthleteAccount::AthleteAccount(const AthleteAccount&)` - копирование с увеличением статического счетчика
- `TrainingSession::TrainingSession(const TrainingSession&)` - глубокое копирование unique_ptr

**Пример:**
```cpp
BodyMetrics original("acc001", 70.0, 175);
BodyMetrics copy = original; // Использование конструктора копирования
```

#### 6. Наследование и вызов конструктора базового класса

**Создан базовый класс `BaseEntity`:**

- Поля: `m_id`, `m_name` (protected для доступа в производных классах)
- Виртуальный метод `getDescription()` для демонстрации полиморфизма
- Конструктор с параметрами: `BaseEntity(const std::string& id, const std::string& name)`

**Класс `Movement` наследуется от `BaseEntity`:**

- Конструктор вызывает конструктор базового класса: `BaseEntity(code, title)`
- Переопределен виртуальный метод `getDescription()`
- Демонстрация полиморфизма через указатель на базовый класс

**Пример:**
```cpp
Movement movement("squat_001", "Приседания", "strength");
// Вызов конструктора базового класса
BaseEntity* entity = &movement; // Полиморфизм
std::cout << entity->getDescription() << std::endl;
```

#### 7. Использование оператора this

**Демонстрация использования `this` в различных контекстах:**

- В конструкторах для явной инициализации полей
- В методах для доступа к полям класса
- В методах базового класса для вызова методов производного класса

**Пример:**
```cpp
std::string getCode() const { return this->getId(); } // Использование this
std::string getTitle() const { return this->getName(); } // Использование this
```

#### 8. Статические поля и методы

**В классе `AthleteAccount`:**

- Статическое поле `s_accountCount` - счетчик созданных аккаунтов
- Статический метод `getAccountCount()` - возвращает количество аккаунтов
- Счетчик увеличивается в конструкторе и уменьшается в деструкторе

**Пример:**
```cpp
AthleteAccount acc1("acc001", "Иван", GoalCode::eBulk);
std::cout << AthleteAccount::getAccountCount() << std::endl; // Статический метод
```

## Тест программы

Запуск программы через `./build.sh` или `make` выводит результаты всех демонстраций:

1. **Статическая инициализация** - создание объектов на стеке
2. **Smart pointers** - демонстрация unique_ptr и shared_ptr
3. **Работа по ссылкам и указателям** - использование ссылок и указателей
4. **Динамические массивы** - массивы объектов и указателей
5. **Перегрузка операторов** - все реализованные операторы
6. **Конструкторы копирования** - копирование различных объектов
7. **Наследование** - вызов конструктора базового класса и полиморфизм
8. **Работа со строками** - конкатенация, поиск, извлечение подстрок
9. **Статические члены** - вывод количества созданных аккаунтов

Все демонстрации показывают корректную работу реализованных механизмов: умные указатели автоматически освобождают память, операторы работают интуитивно, конструкторы копирования создают независимые копии объектов, наследование позволяет использовать полиморфизм.

