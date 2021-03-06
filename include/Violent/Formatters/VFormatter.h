#pragma once

#include <string>

#include "../VLogLevel.h"


namespace At0::Violent
{
	class Formatter
	{
	public:
		/**
		 * Adds specific formatting to the string
		 * @param str The string which will be modified
		 * @param logLvl The current log level
		 */
		virtual void Format(std::string& str, LogLevel logLvl) = 0;

		virtual ~Formatter() = default;

	protected:
		Formatter() = default;
	};
}  // namespace At0::Violent
