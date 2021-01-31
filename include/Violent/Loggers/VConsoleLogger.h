#pragma once

#include "VBaseLogger.h"
#include "../Utils/VColorFormatDescriptor.h"

#include <iostream>


namespace At0::Violent
{
	class ConsoleLogger : public BaseLogger
	{
	public:
		ConsoleLogger(FormatDescriptor descriptor)
			: BaseLogger(descriptor)
		{
		}

		ConsoleLogger() = default;

		/**
		* Set the color format for the console output
		*/
		ConsoleColorFormatDescriptor& ColorFormat()
		{
			return m_ColorFormatDescriptor;
		}

	private:
		void AfterFormat(std::string& msg, LogLevel logLvl) override
		{
			msg.insert(0, m_ColorFormatDescriptor[logLvl]);
			msg.insert(msg.size() - 1, Color::Default);
		}

		void InternalLog(std::string_view msg) override
		{
			std::cout << msg;
		}

	private:
		ConsoleColorFormatDescriptor m_ColorFormatDescriptor{};
	};
}