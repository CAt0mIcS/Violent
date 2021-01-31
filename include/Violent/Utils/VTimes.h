#pragma once

#include <stdint.h>


namespace At0::Violent
{
	enum class Format : uint8_t
	{
		Year, Month, Week, Day,
		Hour, Minute, Second,
		Millisecond, Microsecond, Nanosecond
	};
}