using AltstuLab4.Domain;

namespace AltstuLab4
{
    internal class Program
    {
        private static void Main()
        {
            Console.WriteLine("=== Демонстрация работы C# версии лабораторной 4 ===\n");

            Console.WriteLine("1. Статическая инициализация объектов:");
            DemonstrateStaticInitialization();
            Console.WriteLine();

            Console.WriteLine("2. Динамическая инициализация объектов (new/delete):");
            DemonstrateDynamicInitialization();
            Console.WriteLine();

            Console.WriteLine("3. Работа по ссылкам и указателям (references):");
            DemonstrateReferences();
            Console.WriteLine();

            Console.WriteLine("4. Динамический массив объектов класса:");
            DemonstrateDynamicArrayOfObjects();
            Console.WriteLine();

            Console.WriteLine("5. Массив динамических объектов класса:");
            DemonstrateArrayOfDynamicObjects();
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
    }
}

