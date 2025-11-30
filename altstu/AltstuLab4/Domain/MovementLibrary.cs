using System;
using System.Collections.Generic;
using System.Linq;

namespace AltstuLab4.Domain
{
    public sealed class MovementLibrary
    {
        private readonly List<Movement> _items = new();

        public MovementLibrary(int rev = 1)
        {
            Rev = rev;
        }

        public int Rev { get; }
        public IReadOnlyCollection<Movement> Items => _items.AsReadOnly();

        public void AddMovement(Movement movement)
        {
            // Использование this и валидация
            if (movement == null)
            {
                throw new ArgumentNullException(nameof(movement));
            }
            
            // Использование this для доступа к приватному полю
            this._items.Add(movement);
        }

        public List<Movement> Find(string text)
        {
            return _items.Where(m => MatchesText(m, text)).ToList();
        }

        public List<Movement> Filter(string? impact, HashSet<string>? gear, int? band)
        {
            return _items.Where(item =>
                (impact is null || item.Impact.Equals(impact, StringComparison.OrdinalIgnoreCase)) &&
                (gear is null || gear.All(g => item.GearNeeds.Contains(g))) &&
                (band is null || item.DifficultyBand == band)).ToList();
        }

        public List<Movement> RankForSlot(SlotSpec slot, AthleteAccount athlete)
        {
            return _items.Where(item => item.IsDoable(athlete)).ToList();
        }

        private static bool MatchesText(Movement movement, string text)
        {
            var lower = text.ToLowerInvariant();
            return movement.Title.ToLowerInvariant().Contains(lower) ||
                   movement.Code.ToLowerInvariant().Contains(lower);
        }
    }
}



