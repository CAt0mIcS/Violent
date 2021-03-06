#pragma once

#include <string>
#include <mutex>
#include <vector>
#include <sstream>

#include "../Formatters/VBracketFormatter.h"
#include "../Formatters/VLogLevelFormatter.h"
#include "../Formatters/VDateTimeFormatter.h"
#include "../Formatters/VNullTerminatorFormatter.h"

#include "../VLogLevel.h"
#include "../Utils/VUtils.h"


namespace At0::Violent
{
	using LogMessageType = LogLevel;

	class BaseLogger
	{
	public:
		void SetLogLevel(LogLevel level) { m_LogLevel = level; }

		LogLevel GetLogLevel() const { return m_LogLevel; }

		/**
		 * Opens the output stream for writing
		 */
		virtual void Open(const char* filepath) {}

		/**
		 * Flushes the output stream
		 */
		virtual void Flush() = 0;

		/**
		 * Closes the output stream
		 */
		virtual void Close() {}

		template<typename... Args>
		void Trace(std::string_view str, Args&&... args)
		{
			if (!ShouldLog(LogMessageType::Trace))
				return;

			Log(FormatMessage(str, LogMessageType::Trace, std::forward<Args>(args)...),
				LogMessageType::Trace);
		}

		template<typename... Args>
		void Debug(std::string_view str, Args&&... args)
		{
			if (!ShouldLog(LogMessageType::Debug))
				return;

			Log(FormatMessage(str, LogMessageType::Debug, std::forward<Args>(args)...),
				LogMessageType::Debug);
		}

		template<typename... Args>
		void Info(std::string_view str, Args&&... args)
		{
			if (!ShouldLog(LogMessageType::Information))
				return;

			Log(FormatMessage(str, LogMessageType::Information, std::forward<Args>(args)...),
				LogMessageType::Information);
		}

		template<typename... Args>
		void Warn(std::string_view str, Args&&... args)
		{
			if (!ShouldLog(LogMessageType::Warning))
				return;

			Log(FormatMessage(str, LogMessageType::Warning, std::forward<Args>(args)...),
				LogMessageType::Warning);
		}

		template<typename... Args>
		void Error(std::string_view str, Args&&... args)
		{
			if (!ShouldLog(LogMessageType::Error))
				return;

			Log(FormatMessage(str, LogMessageType::Error, std::forward<Args>(args)...),
				LogMessageType::Error);
		}

		template<typename... Args>
		void Critical(std::string_view str, Args&&... args)
		{
			if (!ShouldLog(LogMessageType::Critical))
				return;

			Log(FormatMessage(str, LogMessageType::Critical, std::forward<Args>(args)...),
				LogMessageType::Critical);
		}


		template<typename... Args>
		void Trace(const std::wstring_view str, Args&&... args)
		{
			if (!ShouldLog(LogMessageType::Trace))
				return;

			Log(FormatMessage(ConvertUtf8(str), LogMessageType::Trace, std::forward<Args>(args)...),
				LogMessageType::Trace);
		}

		template<typename... Args>
		void Debug(const std::wstring_view str, Args&&... args)
		{
			if (!ShouldLog(LogMessageType::Debug))
				return;

			Log(FormatMessage(ConvertUtf8(str), LogMessageType::Debug, std::forward<Args>(args)...),
				LogMessageType::Debug);
		}

		template<typename... Args>
		void Info(const std::wstring_view str, Args&&... args)
		{
			if (!ShouldLog(LogMessageType::Information))
				return;

			Log(FormatMessage(
					ConvertUtf8(str), LogMessageType::Information, std::forward<Args>(args)...),
				LogMessageType::Information);
		}

		template<typename... Args>
		void Warn(const std::wstring_view str, Args&&... args)
		{
			if (!ShouldLog(LogMessageType::Warning))
				return;

			Log(FormatMessage(
					ConvertUtf8(str), LogMessageType::Warning, std::forward<Args>(args)...),
				LogMessageType::Warning);
		}

		template<typename... Args>
		void Error(const std::wstring_view str, Args&&... args)
		{
			if (!ShouldLog(LogMessageType::Error))
				return;

			Log(FormatMessage(ConvertUtf8(str), LogMessageType::Error, std::forward<Args>(args)...),
				LogMessageType::Error);
		}

		template<typename... Args>
		void Critical(const std::wstring_view str, Args&&... args)
		{
			if (!ShouldLog(LogMessageType::Critical))
				return;

			Log(FormatMessage(
					ConvertUtf8(str), LogMessageType::Critical, std::forward<Args>(args)...),
				LogMessageType::Critical);
		}

	protected:
		/**
		 * Writes message to output buffer
		 * @param message The message to write
		 * @param type The type of message
		 */
		virtual void Log(std::string_view message, LogMessageType type) = 0;

		BaseLogger() : m_LogLevel(LogLevel::None)
		{
			BracketFormatter* pBracketFormatter = new BracketFormatter();
			m_Formatters.push_back(pBracketFormatter);

			LogLevelFormatter* pLogLevelFormatter = new LogLevelFormatter();
			m_Formatters.push_back(pLogLevelFormatter);

			DateTimeFormatter* pDateFormatter = new DateTimeFormatter();
			m_Formatters.push_back(pDateFormatter);

			NullTerminatorFormatter* pNullTerminatorFormatter = new NullTerminatorFormatter();
			m_Formatters.push_back(pNullTerminatorFormatter);
		}

		virtual ~BaseLogger()
		{
			for (auto* formatter : m_Formatters)
			{
				if (formatter)
					delete formatter;
			}
		}

		/**
		 * @returns If a message with msgType should be logged
		 */
		bool ShouldLog(LogMessageType msgType) { return msgType >= m_LogLevel; }

	private:
		/**
		 * Formats the message, inserts all arguments and calls the formatters
		 * @param str The base string to insert the arguments into
		 * @param args The arguments to insert
		 * @returns The formatted string ready for logging
		 */
		template<typename... Args>
		std::string FormatMessage(std::string_view str, LogMessageType msgLvl, Args&&... args)
		{
			std::string msg = SerializeString(str.data(), args...);

			for (auto formatter : m_Formatters)
			{
				formatter->Format(msg, msgLvl);
			}
			return msg;
		}

	protected:
		LogLevel m_LogLevel;

	private:
		std::vector<Formatter*> m_Formatters;
	};
}  // namespace At0::Violent
