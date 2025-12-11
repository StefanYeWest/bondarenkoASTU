using AltstuLab4.Domain;

namespace AltstuLab4.Domain
{
    /// <summary>
    /// Интерфейс для упражнений
    /// </summary>
    public interface IExercisable
    {
        string Code { get; }
        string Title { get; }
        bool CanPerform(AthleteAccount athlete);
        string GetInstructions();
    }
}

