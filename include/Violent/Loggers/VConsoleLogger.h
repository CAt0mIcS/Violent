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
		void AfterFormat(std::string& msg) override
		{

		}

		void AfterFormat(std::wstring& msg) override
		{

		}

		void InternalLog(std::string_view msg) override
		{
			std::cout << msg;
		}

		void InternalLog(std::wstring_view msg) override
		{
			std::wcout << msg;
		}

	private:
		ConsoleColorFormatDescriptor m_ColorFormatDescriptor{};
	};
}