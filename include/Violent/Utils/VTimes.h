#pragma once

#include <stdint.h>


namespace At0::Violent
{
	enum class TimeType : uint8_t
	{
		YearType, MonthType, WeekType, DayType,
		HourType, MinuteType, SecondType,
		MillisecondType, MicrosecondType, NanosecondType
	};

	class Year
	{
	public:
		Year() = default;

	private:
		static constexpr TimeType m_Type = TimeType::YearType;
	};

	class Month
	{
	public:
		Month() = default;

	private:
		static constexpr TimeType m_Type = TimeType::MonthType;
	};

	class Week
	{
	public:
		Week() = default;

	private:
		static constexpr TimeType m_Type = TimeType::WeekType;
	};

	class Day
	{
	public:
		Day() = default;

	private:
		static constexpr TimeType m_Type = TimeType::DayType;
	};

	class Hour
	{
	public:
		Hour() = default;

	private:
		static constexpr TimeType m_Type = TimeType::HourType;
	};

	class Minute
	{
	public:
		Minute() = default;

	private:
		static constexpr TimeType m_Type = TimeType::MinuteType;
	};

	class Second
	{
	public:
		Second() = default;

	private:
		static constexpr TimeType m_Type = TimeType::SecondType;
	};

	class Millisecond
	{
	public:
		Millisecond(uint8_t precision)
			: m_Precision(precision)
		{
		}

	private:
		static constexpr TimeType m_Type = TimeType::MillisecondType;
		uint8_t m_Precision;
	};

	class Microsecond
	{
	public:
		Microsecond(uint8_t precision)
			: m_Precision(precision)
		{
		}

	private:
		static constexpr TimeType m_Type = TimeType::MicrosecondType;
		uint8_t m_Precision;
	};

	class Nanosecond
	{
	public:
		Nanosecond(uint8_t precision)
			: m_Precision(precision)
		{
		}

	private:
		static constexpr TimeType m_Type = TimeType::NanosecondType;
		uint8_t m_Precision;
	};
}