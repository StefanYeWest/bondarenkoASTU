namespace AltstuLab4.Domain
{
    public sealed class ProgressionPolicy
    {
        public ProgressionPolicy(string strategy = "default")
        {
            Strategy = strategy;
        }

        public string Strategy { get; }
    }
}




