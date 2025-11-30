using System;
using System.IO;

namespace AltstuLab4.Domain
{
    /// <summary>
    /// Класс для демонстрации using statement - реализует IDisposable
    /// </summary>
    public class MetricsLogger : IDisposable
    {
        private readonly StreamWriter _writer;
        private bool _disposed = false;

        public MetricsLogger(string filePath)
        {
            // Использование this для инициализации
            this._writer = new StreamWriter(filePath);
            this._writer.WriteLine($"=== Metrics Log Started at {DateTime.Now} ===");
        }

        public void LogMetrics(BodyMetrics metrics)
        {
            if (_disposed)
            {
                throw new ObjectDisposedException(nameof(MetricsLogger));
            }

            // Использование this для доступа к полю
            this._writer.WriteLine($"Athlete: {metrics.AthleteId}, Weight: {metrics.WeightKg} kg, BMI: {metrics.Bmi:F2}");
        }

        public void LogMessage(string message)
        {
            if (_disposed)
            {
                throw new ObjectDisposedException(nameof(MetricsLogger));
            }

            this._writer.WriteLine($"[{DateTime.Now:HH:mm:ss}] {message}");
        }

        public void Dispose()
        {
            Dispose(true);
            GC.SuppressFinalize(this);
        }

        protected virtual void Dispose(bool disposing)
        {
            if (!_disposed)
            {
                if (disposing)
                {
                    // Использование this для доступа к полю
                    this._writer?.Dispose();
                }
                _disposed = true;
            }
        }

        ~MetricsLogger()
        {
            Dispose(false);
        }
    }
}
