#pragma once

#include "VTimes.h"


namespace At0::Violent
{
	/**
	* Describes the output format for a log message, e.g. YYYY:MM:DD
	*/
	class FormatDescriptor
	{
	public:
		constexpr FormatDescriptor() = default;

		template<typename... Args>
		constexpr void Append(Args&&... args)
		{

		}

	private:

	};
}