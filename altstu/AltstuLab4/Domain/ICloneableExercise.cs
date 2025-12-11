namespace AltstuLab4.Domain
{
    /// <summary>
    /// Интерфейс для клонирования упражнений
    /// </summary>
    public interface ICloneableExercise
    {
        IExercisable Clone();
        IExercisable ShallowClone();
    }
}

