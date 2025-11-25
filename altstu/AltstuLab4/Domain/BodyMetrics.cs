using System;

namespace AltstuLab4.Domain
{
    public sealed class BodyMetrics
    {
        public const double DefaultBmi = 20.0;
        public const int DefaultBmr = 2000;

        public BodyMetrics(string athleteId, double weightKg, int statureCm)
        {
            AthleteId = athleteId;
            WeightKg = weightKg;
            StatureCm = statureCm;
            Bmi = DefaultBmi;
            BmrKcal = DefaultBmr;
            RecalculateDerived();
        }

        public string AthleteId { get; }
        public DateTime CapturedAt { get; private set; } = DateTime.UtcNow;
        public double WeightKg { get; set; }
        public int StatureCm { get; set; }
        public int? RestingHeartRate { get; set; }
        public double? SleepHours { get; set; }
        public double Bmi { get; private set; }
        public int BmrKcal { get; private set; }

        public void RecalculateDerived()
        {
            if (StatureCm > 0)
            {
                var heightM = StatureCm / 100.0;
                Bmi = WeightKg / (heightM * heightM);
            }

            if (StatureCm > 0 && WeightKg > 0)
            {
                BmrKcal = (int)(88.362 + (13.397 * WeightKg) + (4.799 * StatureCm) - (5.677 * 30));
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

