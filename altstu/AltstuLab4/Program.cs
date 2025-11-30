using AltstuLab4.Domain;
using System;
using System.IO;

namespace AltstuLab4
{
    internal class Program
    {
        private static void Main()
        {
            Console.WriteLine("=== Демонстрация работы C# версии лабораторной 5 ===\n");

            Console.WriteLine("1. Статическая инициализация объектов:");
            DemonstrateStaticInitialization();
            Console.WriteLine();

            Console.WriteLine("2. Динамическая инициализация объектов:");
            DemonstrateDynamicInitialization();
            Console.WriteLine();

            Console.WriteLine("3. Работа по ссылкам:");
            DemonstrateReferences();
            Console.WriteLine();

            Console.WriteLine("4. Динамический массив объектов класса:");
            DemonstrateDynamicArrayOfObjects();
            Console.WriteLine();

            Console.WriteLine("5. Массив динамических объектов класса:");
            DemonstrateArrayOfDynamicObjects();
            Console.WriteLine();

            Console.WriteLine("6. Использование оператора this:");
            DemonstrateThisOperator();
            Console.WriteLine();

            Console.WriteLine("7. Статические поля и методы:");
            DemonstrateStaticMembers();
            Console.WriteLine();

            Console.WriteLine("8. Свойства с валидацией (get/set):");
            DemonstrateProperties();
            Console.WriteLine();

            Console.WriteLine("9. Обработка исключений (try-catch-throw):");
            DemonstrateExceptionHandling();
            Console.WriteLine();

            Console.WriteLine("10. Использование using statement (IDisposable):");
            DemonstrateUsingStatement();
            Console.WriteLine();
        }

        private static void DemonstrateStaticInitialization()
        {
            var athlete = new AthleteAccount("acc001", "Иван Иванов", GoalCode.Bulk)
            {
                ExperienceBand = 1
            };
            athlete.AddGear("barbell");
            athlete.AddGear("dumbbells");

            Console.WriteLine($"  Создан спортсмен: {athlete.DisplayName} с целью {(int)athlete.PrimaryGoal}");

            var metrics = new BodyMetrics("acc001", 75.5, 180);
            metrics.RestingHeartRate = 65;
            metrics.RecalculateDerived();

            Console.WriteLine($"  Метрики: вес {metrics.WeightKg} кг, рост {metrics.StatureCm} см, BMI {metrics.Bmi:F2}");

            var movement = new Movement("squat_001", "Приседания", "strength")
            {
                DifficultyBand = 1
            };
            movement.AddTarget("quads");
            movement.AddTarget("glutes");
            movement.AddGearNeed("barbell");

            Console.WriteLine($"  Движение: {movement.Title} (код: {movement.Code})");
        }

        private static void DemonstrateDynamicInitialization()
        {
            var athlete = new AthleteAccount("acc002", "Петр Петров", GoalCode.Cut)
            {
                ExperienceBand = 2
            };
            athlete.AddGear("kettlebell");
            athlete.AddGear("resistance_bands");

            Console.WriteLine($"  Создан спортсмен (динамически): {athlete.DisplayName}");
            athlete.UpdateGoal(GoalCode.Shape);
            Console.WriteLine($"  Новая цель: {(int)athlete.PrimaryGoal}");

            var session = new TrainingSession("sess_001", "FullBody A");
            session.PlannedAt = DateTime.Parse("2025-11-05 10:00");
            session.Start();

            Console.WriteLine($"  Сессия создана: {session.Title}");

            var telemetry = new SessionTelemetry
            {
                Duration = 45,
                Calories = 350
            };
            session.Finalize(telemetry);

            Console.WriteLine("  Сессия завершена");
        }

        private static void DemonstrateReferences()
        {
            var athlete = new AthleteAccount("acc003", "Анна Смирнова", GoalCode.Health);
            var athleteRef = athlete;

            athleteRef.AddGear("yoga_mat");
            athleteRef.ExperienceBand = 0;

            Console.WriteLine($"  Работа по ссылке: {athleteRef.DisplayName} имеет инвентарь: {string.Join(", ", athleteRef.AllowedGear)}");

            var metrics = new BodyMetrics("acc003", 60.0, 165)
            {
                SleepHours = 7.5
            };
            metrics.RecalculateDerived();

            Console.WriteLine($"  Работа по ссылке: BMI = {metrics.Bmi:F2}, BMR = {metrics.BmrKcal} ккал");
            Console.WriteLine($"  TDEE (коэффициент 1.5): {metrics.Tdee(1.5)} ккал");

            var newerMetrics = new BodyMetrics("acc003", 61.0, 165);
            var merged = metrics.MergeWith(newerMetrics);
            Console.WriteLine($"  Объединенные метрики: вес {merged.WeightKg} кг");
        }

        private static void DemonstrateDynamicArrayOfObjects()
        {
            var movements = new[]
            {
                new Movement("push_001", "Отжимания", "strength")
                {
                    DifficultyBand = 0
                },
                new Movement("pull_001", "Подтягивания", "strength")
                {
                    DifficultyBand = 1
                },
                new Movement("run_001", "Бег", "cardio")
                {
                    DifficultyBand = 0
                }
            };

            movements[0].AddTarget("chest");
            movements[0].AddTarget("triceps");

            movements[1].AddTarget("lats");
            movements[1].AddTarget("biceps");
            movements[1].AddGearNeed("pullup_bar");

            movements[2].AddTarget("legs");

            Console.WriteLine("  Динамический массив движений:");
            for (var i = 0; i < movements.Length; i++)
            {
                Console.WriteLine($"    [{i}] {movements[i].Title} (сложность: {movements[i].DifficultyBand})");
            }
        }

        private static void DemonstrateArrayOfDynamicObjects()
        {
            var metricsArray = new BodyMetrics[3];

            metricsArray[0] = new BodyMetrics("acc004", 70.0, 175) { RestingHeartRate = 70 };
            metricsArray[1] = new BodyMetrics("acc005", 80.0, 185) { RestingHeartRate = 65, SleepHours = 8.0 };
            metricsArray[2] = new BodyMetrics("acc006", 65.0, 170) { RestingHeartRate = 72 };

            foreach (var metrics in metricsArray)
            {
                metrics.RecalculateDerived();
            }

            Console.WriteLine("  Массив динамических объектов BodyMetrics:");
            for (var i = 0; i < metricsArray.Length; i++)
            {
                var metrics = metricsArray[i];
                Console.WriteLine($"    [{i}] ID: {metrics.AthleteId}, вес: {metrics.WeightKg} кг, BMI: {metrics.Bmi:F2}, BMR: {metrics.BmrKcal} ккал");
            }

            var library = new MovementLibrary(1);
            library.AddMovement(new Movement("deadlift_001", "Становая тяга", "strength"));
            library.AddMovement(new Movement("bench_001", "Жим лежа", "strength"));
            library.AddMovement(new Movement("row_001", "Тяга в наклоне", "strength"));

            Console.WriteLine($"  Библиотека движений создана, версия: {library.Rev}");
            var found = library.Find("жим");
            Console.WriteLine($"  Найдено движений по запросу 'жим': {found.Count}");
        }

        private static void DemonstrateThisOperator()
        {
            // Демонстрация использования this в конструкторах и методах
            var athlete = new AthleteAccount("acc007", "Тестовый спортсмен", GoalCode.Bulk);
            
            Console.WriteLine($"  Создан аккаунт через конструктор с this: {athlete.DisplayName}");
            Console.WriteLine($"  AccountId (установлен через this): {athlete.AccountId}");
            
            // this используется внутри методов класса для явного доступа к полям
            athlete.AddGear("barbell");
            athlete.AddGear("dumbbells");
            
            Console.WriteLine($"  Инвентарь добавлен через метод с использованием this: {string.Join(", ", athlete.AllowedGear)}");
            
            // Демонстрация this в BodyMetrics
            var metrics = new BodyMetrics("acc007", 75.0, 180);
            Console.WriteLine($"  Метрики созданы, BMI рассчитан с использованием this: {metrics.Bmi:F2}");
        }

        private static void DemonstrateStaticMembers()
        {
            // Демонстрация статического поля и метода
            Console.WriteLine($"  Количество созданных аккаунтов (до создания): {AthleteAccount.GetAccountCount()}");
            
            var athlete1 = new AthleteAccount("acc008", "Первый спортсмен", GoalCode.Bulk);
            Console.WriteLine($"  После создания первого: {AthleteAccount.GetAccountCount()}");
            
            var athlete2 = new AthleteAccount("acc009", "Второй спортсмен", GoalCode.Cut);
            Console.WriteLine($"  После создания второго: {AthleteAccount.GetAccountCount()}");
            
            // Статический метод можно вызвать без создания экземпляра
            Console.WriteLine($"  Текущее количество аккаунтов (статический метод): {AthleteAccount.GetAccountCount()}");
            
            // Освобождение объектов (счетчик уменьшится в финализаторах)
            athlete1 = null;
            athlete2 = null;
            GC.Collect();
            GC.WaitForPendingFinalizers();
        }

        private static void DemonstrateProperties()
        {
            // Демонстрация свойств с get/set и валидацией
            var athlete = new AthleteAccount("acc010", "Тест свойств", GoalCode.Health);
            
            // Установка свойства с валидацией
            try
            {
                athlete.ExperienceBand = 1; // Валидное значение
                Console.WriteLine($"  ExperienceBand установлен: {athlete.ExperienceBand}");
                
                // Попытка установить невалидное значение
                athlete.ExperienceBand = 5; // Должно выбросить исключение
            }
            catch (ArgumentOutOfRangeException ex)
            {
                Console.WriteLine($"  Валидация свойства сработала: {ex.Message}");
            }
            
            // Демонстрация свойств с автоматической валидацией в BodyMetrics
            var metrics = new BodyMetrics("acc010", 70.0, 175);
            Console.WriteLine($"  Исходный вес: {metrics.WeightKg} кг");
            
            // Изменение свойства вызывает автоматический пересчет
            metrics.WeightKg = 72.0;
            Console.WriteLine($"  Новый вес: {metrics.WeightKg} кг, BMI пересчитан: {metrics.Bmi:F2}");
            
            // Попытка установить невалидное значение
            try
            {
                metrics.WeightKg = -10.0; // Должно выбросить исключение
            }
            catch (ArgumentOutOfRangeException ex)
            {
                Console.WriteLine($"  Валидация свойства WeightKg: {ex.Message}");
            }
        }

        private static void DemonstrateExceptionHandling()
        {
            // Демонстрация try-catch-throw
            Console.WriteLine("  Демонстрация обработки исключений:");
            
            // 1. Try-catch для перехвата исключений
            try
            {
                string? nullId = null;
                var athlete = new AthleteAccount(nullId!, "Тест", GoalCode.Bulk); // Должно выбросить ArgumentNullException
            }
            catch (ArgumentNullException ex)
            {
                Console.WriteLine($"    Перехвачено ArgumentNullException: {ex.ParamName}");
            }
            
            // 2. Try-catch для валидации данных
            try
            {
                var metrics = new BodyMetrics("acc011", -10.0, 180); // Невалидный вес
            }
            catch (ArgumentOutOfRangeException ex)
            {
                Console.WriteLine($"    Перехвачено ArgumentOutOfRangeException: {ex.Message}");
            }
            
            // 3. Try-catch-finally
            AthleteAccount? athlete2 = null;
            try
            {
                athlete2 = new AthleteAccount("acc012", "Тест finally", GoalCode.Bulk);
                athlete2.ExperienceBand = 10; // Вызовет исключение
            }
            catch (ArgumentOutOfRangeException ex)
            {
                Console.WriteLine($"    В блоке catch: {ex.Message}");
            }
            finally
            {
                Console.WriteLine("    Блок finally выполнен (очистка ресурсов)");
            }
            
            // 4. Демонстрация throw для создания собственных исключений
            try
            {
                var library = new MovementLibrary(1);
                Movement? nullMovement = null;
                library.AddMovement(nullMovement!); // Должно выбросить ArgumentNullException
            }
            catch (ArgumentNullException ex)
            {
                Console.WriteLine($"    Исключение выброшено в AddMovement: {ex.ParamName}");
            }
            
            // 5. Вложенные try-catch
            try
            {
                try
                {
                    var metrics2 = new BodyMetrics("acc013", 0, 0); // Двойная ошибка
                }
                catch (ArgumentOutOfRangeException ex) when (ex.ParamName == "weightKg")
                {
                    Console.WriteLine($"    Внутренний catch (weightKg): {ex.Message}");
                    throw; // Повторное выбрасывание исключения
                }
            }
            catch (ArgumentOutOfRangeException ex)
            {
                Console.WriteLine($"    Внешний catch: {ex.ParamName}");
            }
        }

        private static void DemonstrateUsingStatement()
        {
            // Демонстрация using statement для автоматического вызова Dispose
            Console.WriteLine("  Демонстрация using statement:");
            
            // 1. Базовое использование using
            var tempFile = Path.GetTempFileName();
            try
            {
                using (var logger = new MetricsLogger(tempFile))
                {
                    var metrics = new BodyMetrics("acc014", 75.0, 180);
                    logger.LogMetrics(metrics);
                    logger.LogMessage("Тестовое сообщение");
                    Console.WriteLine("    Данные записаны в лог (внутри using)");
                } // Dispose вызывается автоматически здесь
                
                Console.WriteLine("    Using блок завершен, ресурсы освобождены");
                
                // Проверка, что файл создан
                if (File.Exists(tempFile))
                {
                    var content = File.ReadAllText(tempFile);
                    Console.WriteLine($"    Содержимое лога ({content.Length} символов) прочитано");
                }
            }
            finally
            {
                // Очистка временного файла
                if (File.Exists(tempFile))
                {
                    File.Delete(tempFile);
                }
            }
            
            // 2. Using с несколькими ресурсами (C# 8.0+)
            var tempFile2 = Path.GetTempFileName();
            {
                using var logger1 = new MetricsLogger(tempFile2);
                var metrics1 = new BodyMetrics("acc015", 80.0, 185);
                logger1.LogMetrics(metrics1);
                Console.WriteLine("    Using declaration (автоматический Dispose в конце области видимости)");
            } // Dispose вызывается здесь
            
            // 3. Демонстрация, что Dispose действительно вызывается
            var tempFile3 = Path.GetTempFileName();
            try
            {
                using (var logger = new MetricsLogger(tempFile3))
                {
                    logger.LogMessage("Тест 1");
                    logger.LogMessage("Тест 2");
                }
                
                // Попытка использовать после Dispose должна выбросить исключение
                var logger2 = new MetricsLogger(tempFile3);
                logger2.Dispose();
                
                try
                {
                    logger2.LogMessage("Это должно вызвать исключение");
                }
                catch (ObjectDisposedException)
                {
                    Console.WriteLine("    ObjectDisposedException перехвачен - ресурс действительно освобожден");
                }
            }
            finally
            {
                if (File.Exists(tempFile2)) File.Delete(tempFile2);
                if (File.Exists(tempFile3)) File.Delete(tempFile3);
            }
        }
    }
}



