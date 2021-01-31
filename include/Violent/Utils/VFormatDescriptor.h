#pragma once

#include "VTimes.h"

#include <vector>
#include <chrono>
#include <time.h>
#include <string>


namespace At0::Violent
{
	class FormatView
	{
	public:
		FormatView(const char* startIdx)
			: m_StartAddr(startIdx)
		{
		}

	private:
		const char* m_StartAddr;
	};

	/**
	* Describes the output format for a log message, e.g. YYYY-MM-DD
	*/
	class FormatDescriptor
	{
		static constexpr uint8_t NumberOfTimeConfigurations = 10;

	public:
		FormatDescriptor() = default;

		template<typename... Args>
		constexpr void Append(Args&&... args)
		{
			(m_Data.emplace_back(args), ...);
		}

		auto begin() const
		{
			return m_Data.begin();
		}

		auto end() const
		{
			return m_Data.end();
		}

		uint8_t Size() const
		{
			return (uint8_t)m_Data.size();
		}

		std::string AsString(uint8_t idx) const
		{
			return "";
		}

	private:
		std::vector<Format> m_Data;
	};
}