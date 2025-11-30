using System.Collections.Generic;
using System.Linq;

namespace AltstuLab4.Domain
{
    public sealed class Movement
    {
        public const int MaxDifficultyBand = 2;

        private readonly HashSet<string> _targets = new();
        private readonly HashSet<string> _gearNeeds = new();
        private readonly HashSet<string> _contraFlags = new();
        private readonly List<string> _alternatives = new();

        public Movement(string code, string title, string impact)
        {
            Code = code;
            Title = title;
            Impact = impact;
        }

        public string Code { get; }
        public string Title { get; }
        public string Impact { get; }
        public int DifficultyBand { get; set; }
        public IReadOnlyCollection<string> Targets => _targets;
        public IReadOnlyCollection<string> GearNeeds => _gearNeeds;
        public IReadOnlyCollection<string> ContraFlags => _contraFlags;
        public IReadOnlyCollection<string> Alternatives => _alternatives;

        public void AddTarget(string target) => _targets.Add(target);
        public void AddGearNeed(string gear) => _gearNeeds.Add(gear);
        public void AddContraFlag(string flag) => _contraFlags.Add(flag);
        public void AddAlternative(string alt) => _alternatives.Add(alt);

        public bool IsDoable(AthleteAccount athlete)
        {
            return _gearNeeds.All(athlete.Prefers);
        }

        public Movement? ClosestAlternative(IEnumerable<Movement> catalog, HashSet<string> withGear)
        {
            foreach (var altCode in _alternatives)
            {
                var candidate = catalog.FirstOrDefault(m => m.Code == altCode);
                if (candidate is null)
                {
                    continue;
                }

                if (candidate.GearNeeds.All(withGear.Contains))
                {
                    return candidate;
                }
            }

            return null;
        }
    }
}



