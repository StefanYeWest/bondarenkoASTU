using System;

namespace AltstuLab4.Domain
{
    /// <summary>
    /// Абстрактный базовый класс для упражнений
    /// </summary>
    public abstract class BaseExercise
    {
        // Protected поле для демонстрации protected
        protected string Category { get; set; }
        protected int DifficultyLevel { get; set; }
        
        // Protected метод для демонстрации protected
        protected virtual void ValidateDifficulty()
        {
            if (DifficultyLevel < 0 || DifficultyLevel > 10)
            {
                throw new ArgumentOutOfRangeException(nameof(DifficultyLevel),
                    "Difficulty level must be between 0 and 10");
            }
        }
        
        protected BaseExercise(string id, string name, string category)
        {
            // Использование this
            this.Id = id ?? throw new ArgumentNullException(nameof(id));
            this.Name = name ?? throw new ArgumentNullException(nameof(name));
            this.Category = category ?? throw new ArgumentNullException(nameof(category));
            this.DifficultyLevel = 0;
        }
        
        // Защищенный конструктор копирования
        protected BaseExercise(BaseExercise other)
        {
            if (other == null) throw new ArgumentNullException(nameof(other));
            this.Id = other.Id;
            this.Name = other.Name;
            this.Category = other.Category;
            this.DifficultyLevel = other.DifficultyLevel;
        }
        
        public string Id { get; }
        public string Name { get; }
        
        // Абстрактный метод - делает класс абстрактным
        public abstract bool CanPerform(AthleteAccount athlete);
        
        // Виртуальный метод с реализацией по умолчанию
        public virtual string GetInstructions()
        {
            return $"General exercise instructions for {this.Name}";
        }
        
        // Невиртуальный метод для демонстрации вызова виртуальной функции
        public string PerformCheck(AthleteAccount athlete)
        {
            // Невиртуальная функция вызывает виртуальную функцию
            bool canDo = this.CanPerform(athlete);
            return canDo ? $"Can perform: {this.GetInstructions()}" : "Cannot perform this exercise";
        }
        
        // Виртуальный метод для получения описания
        public virtual string GetDescription()
        {
            return $"Exercise: {this.Id} - {this.Name} [Category: {this.Category}, Difficulty: {this.DifficultyLevel}]";
        }
        
        public void SetDifficultyLevel(int level)
        {
            this.DifficultyLevel = level;
            this.ValidateDifficulty(); // Использование protected метода
        }
        
        public int GetDifficultyLevel() => this.DifficultyLevel;
        public string GetCategory() => this.Category;
    }
}

