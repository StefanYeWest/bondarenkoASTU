using System;
using System.Collections.Generic;

namespace AltstuLab4.Domain
{
    public sealed class TrainingSession
    {
        public enum SessionState
        {
            Planned = 0,
            Running = 1,
            Done = 2,
            Missed = 3
        }

        private readonly List<WorkBlock> _blocks = new();

        public TrainingSession(string sessionId, string title)
        {
            SessionId = sessionId;
            Title = title;
            State = SessionState.Planned;
        }

        public string SessionId { get; }
        public DateTime PlannedAt { get; set; } = DateTime.UtcNow;
        public string Title { get; }
        public SessionState State { get; private set; }
        public SessionTelemetry? Telemetry { get; private set; }
        public IReadOnlyCollection<WorkBlock> Blocks => _blocks.AsReadOnly();

        public void Start()
        {
            State = SessionState.Running;
            Console.WriteLine($"    [TrainingSession] Session {SessionId} started");
        }

        public void Finalize(SessionTelemetry telemetry)
        {
            State = SessionState.Done;
            Telemetry = new SessionTelemetry
            {
                Duration = telemetry.Duration,
                Calories = telemetry.Calories
            };
            Console.WriteLine($"    [TrainingSession] Session {SessionId} finalized");
        }

        public void Shift(DateTime newTime)
        {
            PlannedAt = newTime;
            Console.WriteLine($"    [TrainingSession] Session {SessionId} shifted to {newTime:yyyy-MM-dd HH:mm}");
        }

        public void AddBlock(WorkBlock block)
        {
            _blocks.Add(block);
        }
    }
}



