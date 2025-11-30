using System;
using System.Collections.Generic;

namespace AltstuLab4.Domain
{
    public sealed class MicrocyclePlan
    {
        public const int DefaultWeekIndex = 0;

        private readonly List<TrainingSession> _sessions = new();

        public MicrocyclePlan(string planId, string ownerId, ProgressionPolicy? policy = null)
        {
            PlanId = planId;
            OwnerId = ownerId;
            Policy = policy ?? new ProgressionPolicy();
            WeekIndex = DefaultWeekIndex;
        }

        public string PlanId { get; }
        public string OwnerId { get; }
        public int WeekIndex { get; set; }
        public ProgressionPolicy Policy { get; }
        public IReadOnlyCollection<TrainingSession> Sessions => _sessions.AsReadOnly();

        public void Compose(IEnumerable<SessionBlueprint> blueprints, MovementLibrary library, AthleteAccount athlete)
        {
            _sessions.Clear();
            foreach (var blueprint in blueprints)
            {
                if (!blueprint.ValidateAgainst(athlete))
                {
                    continue;
                }

                var session = blueprint.Instantiate(library, athlete);
                _sessions.Add(session);
            }
        }

        public void Adapt(ReadinessIndex readiness)
        {
            Console.WriteLine($"    [MicrocyclePlan] Adapted with readiness factor {readiness.Value:F2}");
        }

        public List<TrainingSession> Upcoming(int limit)
        {
            var result = new List<TrainingSession>();
            foreach (var session in _sessions)
            {
                if (result.Count >= limit)
                {
                    break;
                }

                if (session.State == TrainingSession.SessionState.Planned)
                {
                    result.Add(session);
                }
            }

            return result;
        }
    }
}



