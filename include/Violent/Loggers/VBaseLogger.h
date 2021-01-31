#pragma once

#include "../Utils/VFormatDescriptor.h"
#include "../Utils/VSerialize.h"

#include <utility>
#include <string>
#include <string_view>

#define VIOLENT_INSERT_LOG(logLvl)  if (!ShouldLog(LogLevel::logLvl))									\
										return;															\
									auto formattedStr = Format(msg, std::forward<Args>(args)...);		\
									AfterFormat(formattedStr, LogLevel::logLvl);											\
									InternalLog(formattedStr)


namespace At0::Violent
{
	/**
	* Describes some base functions that are the same for all sub loggers
	*/
	class BaseLogger
	{
	public:
		virtual ~BaseLogger() = default;

		/**
		* Sets the format for the log message
		* @param descriptor The descriptor struct that describes the output format
		*/
		void SetFormat(FormatDescriptor descriptor)
		{
			m_Descriptor = std::move(descriptor);
		}

		template<typename... Args>
		void Trace(std::string_view msg, Args&&... args)
		{
			VIOLENT_INSERT_LOG(Trace);
		}

		template<typename... Args>
		void Debug(std::string_view msg, Args&&... args)
		{
			VIOLENT_INSERT_LOG(Debug);
		}

		template<typename... Args>
		void Info(std::string_view msg, Args&&... args)
		{
			VIOLENT_INSERT_LOG(Information);
		}

		template<typename... Args>
		void Warn(std::string_view msg, Args&&... args)
		{
			VIOLENT_INSERT_LOG(Warning);
		}

		template<typename... Args>
		void Error(std::string_view msg, Args&&... args)
		{
			VIOLENT_INSERT_LOG(Error);
		}

		template<typename... Args>
		void Critical(std::string_view msg, Args&&... args)
		{
			VIOLENT_INSERT_LOG(Critical);
		}

		/**
		* Checks if a message should be logged with the current log level
		* @param msgType The type of message (Trace, Debug, Warning, ...)
		*/
		bool ShouldLog(LogLevel msgType) { return msgType >= m_LogLevel; }

	protected:
		/**
		* @param descriptor Describes the look of the output
		*/
		BaseLogger(FormatDescriptor descriptor)
			: m_Descriptor(std::move(descriptor))
		{
		}

		BaseLogger() = default;

		/**
		* Called after initial formatting is done
		*/
		virtual void AfterFormat(std::string& msg, LogLevel logLvl) {}

		/**
		* Logs the fully formatted message to the stream
		* @param msg The message ready for logging
		*/
		virtual void InternalLog(std::string_view msg) = 0;

	private:
		template<typename... Args>
		std::string Format(std::string_view msg, Args&&... args)
		{
			std::string formattedStr = InsertArguments(msg.data(), std::forward<Args>(args)...);
			return formattedStr;
		}

	protected:
		FormatDescriptor m_Descriptor;
		LogLevel m_LogLevel = LogLevel::Trace;
	};
}

#undef VIOLENT_INSERT_LOG