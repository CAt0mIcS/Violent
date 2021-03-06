#pragma once

#include "VFormatter.h"


namespace At0::Violent
{
	class BracketFormatter : public Formatter
	{
	public:
		BracketFormatter() = default;

		virtual void Format(std::string& str, LogLevel logLvl) override
		{
#ifndef ZL_NO_BRACKETS

			str.insert(0, "[] ");

#endif	// !ZL_NO_BRACKETS
		}
	};
}  // namespace At0::Violent
