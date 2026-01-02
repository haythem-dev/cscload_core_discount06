using System;

namespace Phoenix
{
    public static class CscDateTimeConverter
    {
        /// <summary>
        /// Converts System.DateTime to Csc.Base.DateTime.
        /// </summary>
        public static Csc.Base.DateTime toCscDateTime(this DateTime dt)
        {
            return new Csc.Base.DateTime
            {
                Year = (short)dt.Year,
                Month = (short)dt.Month,
                Day = (short)dt.Day,
                Hour = (short)dt.Hour,
                Minute = (short)dt.Minute,
                Second = (short)dt.Second
            };
        }

        /// <summary>
        /// Converts Csc.Base.DateTime to System.DateTime. Empty parts are set to System.DateTime.MinValue.
        /// </summary>
        public static DateTime fromCscDateTime(this DateTime dt, Csc.Base.DateTime cscDt)
        {
            int year;
            int month;
            int day;
            removeNullableFromDate(cscDt.Year, cscDt.Month, cscDt.Day, out year, out month, out day);
            int hour;
            int minute;
            int second;
            removeNullableFromTime(cscDt.Hour, cscDt.Minute, cscDt.Second, out hour, out minute, out second);
            return new DateTime(year, month, day, hour, minute, second);
        }

        /// <summary>
        /// Converts System.DateTime to Csc.Base.Date.
        /// </summary>
        public static Csc.Base.Date toCscDate(this DateTime dt)
        {
            return new Csc.Base.Date
            {
                Year = (short)dt.Year,
                Month = (short)dt.Month,
                Day = (short)dt.Day
            };
        }

        /// <summary>
        /// Converts Csc.Base.Date to System.DateTime. The time part is set to System.DateTime.MinValue.
        /// </summary>
        public static DateTime fromCscDate(this DateTime dt, Csc.Base.Date cscDate)
        {
            int year;
            int month;
            int day;
            removeNullableFromDate(cscDate.Year, cscDate.Month, cscDate.Day, out year, out month, out day);
            return new DateTime(year, month, day);
        }

        /// <summary>
        /// Converts System.DateTime to Csc.Base.Time.
        /// </summary>
        public static Csc.Base.Time toCscTime(this DateTime dt)
        {
            return new Csc.Base.Time
            {
                Hour = (short)dt.Hour,
                Minute = (short)dt.Minute,
                Second = (short)dt.Second
            };
        }

        /// <summary>
        /// Converts Csc.Base.Time to System.DateTime. The date part is set to System.DateTime.MinValue.
        /// </summary>
        public static DateTime fromCscTime(this DateTime dt, Csc.Base.Time cscTime)
        {
            int hour;
            int minute;
            int second;
            removeNullableFromTime(cscTime.Hour, cscTime.Minute, cscTime.Second, out hour, out minute, out second);
            return new DateTime(DateTime.MinValue.Year, DateTime.MinValue.Month, DateTime.MinValue.Day, hour, minute, second);
        }

        private static void removeNullableFromDate(short? cscYear, short? cscMonth, short? cscDay, out int year, out int month, out int day)
        {
            year = cscYear.HasValue ? cscYear.Value : DateTime.MinValue.Year;
            month = cscMonth.HasValue ? cscMonth.Value : DateTime.MinValue.Month;
            day = cscDay.HasValue ? cscDay.Value : DateTime.MinValue.Day;
        }

        private static void removeNullableFromTime(short? cscHour, short? cscMinute, short? cscSecond, out int hour, out int minute, out int second)
        {
            hour = cscHour.HasValue ? cscHour.Value : DateTime.MinValue.Hour;
            minute = cscMinute.HasValue ? cscMinute.Value : DateTime.MinValue.Minute;
            second = cscSecond.HasValue ? cscSecond.Value : DateTime.MinValue.Second;
        }
    }
}
