using System.Collections.Generic;

namespace AltstuLab4.Domain
{
    public sealed class SessionBlueprint
    {
        public const int DefaultTimeCap = 60;

        private readonly List<SlotSpec> _slots = new();

        public SessionBlueprint(string blueprintId, string label)
        {
            BlueprintId = blueprintId;
            Label = label;
            TimeCapMinutes = DefaultTimeCap;
        }

        public string BlueprintId { get; }
        public string Label { get; }
        public int TimeCapMinutes { get; set; }
        public IReadOnlyCollection<SlotSpec> Slots => _slots.AsReadOnly();

        public void AddSlot(SlotSpec slot) => _slots.Add(slot);

        public bool ValidateAgainst(AthleteAccount athlete) => true;

        public TrainingSession Instantiate(MovementLibrary library, AthleteAccount athlete)
        {
            var session = new TrainingSession($"session_{BlueprintId}", Label);
            foreach (var slot in _slots)
            {
                var movements = library.RankForSlot(slot, athlete);
                if (movements.Count == 0)
                {
                    continue;
                }

                var block = new WorkBlock
                {
                    Movement = movements[0],
                    Volume = "3x10"
                };
                session.AddBlock(block);
            }

            return session;
        }
    }
}



