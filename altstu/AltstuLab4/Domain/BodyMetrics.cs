using System;

namespace AltstuLab4.Domain
{
    public sealed class BodyMetrics
    {
        public const double DefaultBmi = 20.0;
        public const int DefaultBmr = 2000;

        public BodyMetrics(string athleteId, double weightKg, int statureCm)
        {
            // Использование this и валидация
            this.AthleteId = athleteId ?? throw new ArgumentNullException(nameof(athleteId));
            
            if (weightKg <= 0)
            {
                throw new ArgumentOutOfRangeException(nameof(weightKg), "Weight must be positive");
            }
            if (statureCm <= 0)
            {
                throw new ArgumentOutOfRangeException(nameof(statureCm), "Stature must be positive");
            }
            
            this.WeightKg = weightKg;
            this.StatureCm = statureCm;
            this.Bmi = DefaultBmi;
            this.BmrKcal = DefaultBmr;
            this.RecalculateDerived();
        }

        public string AthleteId { get; }
        public DateTime CapturedAt { get; private set; } = DateTime.UtcNow;
        
        // Свойство с валидацией
        private double _weightKg;
        public double WeightKg
        {
            get => _weightKg;
            set
            {
                if (value <= 0)
                {
                    throw new ArgumentOutOfRangeException(nameof(value), "Weight must be positive");
                }
                _weightKg = value;
                RecalculateDerived();
            }
        }
        
        // Свойство с валидацией
        private int _statureCm;
        public int StatureCm
        {
            get => _statureCm;
            set
            {
                if (value <= 0)
                {
                    throw new ArgumentOutOfRangeException(nameof(value), "Stature must be positive");
                }
                _statureCm = value;
                RecalculateDerived();
            }
        }
        public int? RestingHeartRate { get; set; }
        public double? SleepHours { get; set; }
        public double Bmi { get; private set; }
        public int BmrKcal { get; private set; }

        public void RecalculateDerived()
        {
            // Использование this для доступа к свойствам
            if (this.StatureCm > 0)
            {
                var heightM = this.StatureCm / 100.0;
                this.Bmi = this.WeightKg / (heightM * heightM);
            }

            if (this.StatureCm > 0 && this.WeightKg > 0)
            {
                this.BmrKcal = (int)(88.362 + (13.397 * this.WeightKg) + (4.799 * this.StatureCm) - (5.677 * 30));
            }
        }

        public int Tdee(double activityFactor) => (int)(BmrKcal * activityFactor);

        public BodyMetrics MergeWith(BodyMetrics newer)
        {
            return new BodyMetrics(newer.AthleteId, newer.WeightKg == 0 ? WeightKg : newer.WeightKg, newer.StatureCm == 0 ? StatureCm : newer.StatureCm)
            {
                RestingHeartRate = newer.RestingHeartRate ?? RestingHeartRate,
                SleepHours = newer.SleepHours ?? SleepHours
            };
        }
    }
}



