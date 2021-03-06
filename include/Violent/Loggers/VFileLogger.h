#pragma once

#include <fstream>
#include "VBaseLogger.h"


namespace At0::Violent
{
	class FileLogger : public BaseLogger
	{
	public:
		FileLogger() = default;

		FileLogger(const char* filepath) { Open(filepath); }

		~FileLogger() { Close(); }

		bool IsOpen() const { return m_Writer.is_open(); }

		virtual void Open(const char* filepath) override
		{
#ifndef ZL_LOG_NON_THREAD_SAVE

			std::scoped_lock lock(m_StreamMutex);

#endif
			if (!m_Writer.is_open())
				m_Writer.open(filepath);
		}

		virtual void Flush() override
		{
#ifndef ZL_LOG_NON_THREAD_SAVE

			std::scoped_lock lock(m_StreamMutex);

#endif
			if (m_Writer.is_open())
				m_Writer.flush();
		}

		virtual void Close() override
		{
#ifndef ZL_LOG_NON_THREAD_SAVE

			std::scoped_lock lock(m_StreamMutex);

#endif
			if (m_Writer.is_open())
				m_Writer.close();
		}

	private:
		virtual void Log(std::string_view message, LogMessageType type) override
		{
#ifndef ZL_LOG_NON_THREAD_SAVE

			std::scoped_lock lock(m_StreamMutex);

#endif
			m_Writer << message << '\n';
		}

	private:
		std::ofstream m_Writer;

#ifndef ZL_LOG_NON_THREAD_SAVE

		std::mutex m_StreamMutex;

#endif
	};
}  // namespace At0::Violent
