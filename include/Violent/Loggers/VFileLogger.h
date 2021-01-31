#pragma once

#include "VBaseLogger.h"

#include <fstream>
#include <string>


namespace At0::Violent
{
	/**
	* Describes a logger that writes to a file
	*/
	class FileLogger : public BaseLogger
	{
	public:
		FileLogger(FormatDescriptor descriptor)
			: BaseLogger(std::move(descriptor))
		{
		}

		FileLogger() = default;

		/**
		* Set the path for the log file
		* @param filepath The path to the log file
		*/
		void SetPath(const char* filepath)
		{
			m_Filepath = filepath;
		}

		/**
		* Closes the streams
		*/
		void Close()
		{
			m_OWriter.close();
			m_WOWriter.close();
		}

		/**
		* Opens the streams
		*/
		void Open()
		{
			m_OWriter.open(m_Filepath);
			m_WOWriter.open(m_Filepath);
		}

	private:
		void InternalLog(std::string_view msg) override
		{
			m_OWriter << msg;
		}

		void InternalLog(std::wstring_view msg) override
		{
			m_WOWriter << msg;
		}

	private:
		std::string m_Filepath;
		std::ofstream m_OWriter;
		std::wofstream m_WOWriter;
	};
}