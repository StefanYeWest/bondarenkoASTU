using System;
using System.Collections.Generic;

namespace AltstuLab4.Domain
{
    public sealed class AthleteAccount
    {
        public const int MaxExperienceBand = 2;

        // Статическое поле - счетчик созданных аккаунтов
        private static int _accountCount = 0;

        // Статический метод для получения количества аккаунтов
        public static int GetAccountCount() => _accountCount;

        private readonly List<TimeWindow> _timeWindows = new();
        private readonly HashSet<string> _allowedGear = new(StringComparer.OrdinalIgnoreCase);

        public AthleteAccount(string accountId, string displayName, GoalCode primaryGoal)
        {
            // Использование this для явного указания на поля класса
            this.AccountId = accountId ?? throw new ArgumentNullException(nameof(accountId));
            this.DisplayName = displayName ?? throw new ArgumentNullException(nameof(displayName));
            this.PrimaryGoal = primaryGoal;
            
            // Увеличение статического счетчика
            _accountCount++;
        }

        public string AccountId { get; }
        public string DisplayName { get; }
        public GoalCode PrimaryGoal { get; private set; }
        
        // Свойство с валидацией в set
        private int _experienceBand;
        public int ExperienceBand
        {
            get => _experienceBand;
            set
            {
                if (value < 0 || value > MaxExperienceBand)
                {
                    throw new ArgumentOutOfRangeException(nameof(value), 
                        $"ExperienceBand must be between 0 and {MaxExperienceBand}");
                }
                _experienceBand = value;
            }
        }
        
        public string DietStyleCode { get; set; } = string.Empty;
        public IReadOnlyCollection<TimeWindow> TimeWindows => _timeWindows.AsReadOnly();
        public IReadOnlyCollection<string> AllowedGear => _allowedGear;

        public void UpdateGoal(GoalCode newGoal)
        {
            // Использование this для доступа к свойству
            var oldGoal = this.PrimaryGoal;
            this.PrimaryGoal = newGoal;
            LogGoalChange(oldGoal, newGoal);
        }

        public void SetTimeWindows(IEnumerable<TimeWindow> windows)
        {
            _timeWindows.Clear();
            _timeWindows.AddRange(windows);
        }

        public bool Prefers(string gear)
        {
            // Использование this для доступа к приватному полю
            return this._allowedGear.Contains(gear);
        }

        public void AddGear(string gear)
        {
            if (string.IsNullOrWhiteSpace(gear))
            {
                throw new ArgumentException("Gear cannot be null or empty", nameof(gear));
            }
            
            // Использование this
            this._allowedGear.Add(gear);
        }
        
        // Деструктор для уменьшения счетчика
        ~AthleteAccount()
        {
            _accountCount--;
        }

        private static void LogGoalChange(GoalCode oldGoal, GoalCode newGoal)
        {
            Console.WriteLine($"    [AthleteAccount] Goal changed from {(int)oldGoal} to {(int)newGoal}");
        }
    }
}



