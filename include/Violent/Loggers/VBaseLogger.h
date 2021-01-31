#pragma once

#include "../Utils/VFormatDescriptor.h"
#include "../Utils/VSerialize.h"

#include <utility>
#include <string>
#include <string_view>


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
			if (!ShouldLog(LogLevel::Trace))
				return;

			std::string formattedStr = Format(msg, std::forward<Args>(args)...);
			AfterFormat(formattedStr);
			InternalLog(formattedStr);
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
		virtual void AfterFormat(std::string& msg) {}

		/**
		* Called after initial formatting is done
		*/
		virtual void AfterFormat(std::wstring& msg) {}

		/**
		* Logs the fully formatted message to the stream
		* @param msg The message ready for logging
		*/
		virtual void InternalLog(std::string_view msg) = 0;

		/**
		* Logs the fully formatted message to the stream
		* @param msg The message ready for logging
		*/
		virtual void InternalLog(std::wstring_view msg) = 0;

	private:
		template<typename... Args>
		std::string Format(std::string_view msg, Args&&... args)
		{
			std::string formattedStr = InsertArguments(msg.data(), std::forward<Args>(args)...);
			return formattedStr;
		}

		template<typename... Args>
		std::wstring Format(std::wstring_view msg, Args&&... args)
		{
			std::string formattedStr = InsertArguments(msg.data(), std::forward<Args>(args)...);
			return formattedStr;
		}

	protected:
		FormatDescriptor m_Descriptor;
		LogLevel m_LogLevel = LogLevel::Trace;
	};
}