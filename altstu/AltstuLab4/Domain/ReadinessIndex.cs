namespace AltstuLab4.Domain
{
    public sealed class ReadinessIndex
    {
        public ReadinessIndex(double value = 1.0)
        {
            Value = value;
        }

        public double Value { get; }
    }
}



