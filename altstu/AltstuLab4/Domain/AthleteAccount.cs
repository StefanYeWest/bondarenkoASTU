using System;
using System.Collections.Generic;

namespace AltstuLab4.Domain
{
    public sealed class AthleteAccount
    {
        public const int MaxExperienceBand = 2;

        private readonly List<TimeWindow> _timeWindows = new();
        private readonly HashSet<string> _allowedGear = new(StringComparer.OrdinalIgnoreCase);

        public AthleteAccount(string accountId, string displayName, GoalCode primaryGoal)
        {
            AccountId = accountId;
            DisplayName = displayName;
            PrimaryGoal = primaryGoal;
        }

        public string AccountId { get; }
        public string DisplayName { get; }
        public GoalCode PrimaryGoal { get; private set; }
        public int ExperienceBand { get; set; }
        public string DietStyleCode { get; set; } = string.Empty;
        public IReadOnlyCollection<TimeWindow> TimeWindows => _timeWindows.AsReadOnly();
        public IReadOnlyCollection<string> AllowedGear => _allowedGear;

        public void UpdateGoal(GoalCode newGoal)
        {
            var oldGoal = PrimaryGoal;
            PrimaryGoal = newGoal;
            LogGoalChange(oldGoal, newGoal);
        }

        public void SetTimeWindows(IEnumerable<TimeWindow> windows)
        {
            _timeWindows.Clear();
            _timeWindows.AddRange(windows);
        }

        public bool Prefers(string gear) => _allowedGear.Contains(gear);

        public void AddGear(string gear)
        {
            if (!string.IsNullOrWhiteSpace(gear))
            {
                _allowedGear.Add(gear);
            }
        }

        private static void LogGoalChange(GoalCode oldGoal, GoalCode newGoal)
        {
            Console.WriteLine($"    [AthleteAccount] Goal changed from {(int)oldGoal} to {(int)newGoal}");
        }
    }
}

