namespace AltstuLab4.Domain
{
    public sealed class TimeWindow
    {
        public TimeWindow(string start, string end)
        {
            Start = start;
            End = end;
        }

        public string Start { get; }
        public string End { get; }
    }
}

