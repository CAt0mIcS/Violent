#include <Violent/Violent.h>

using namespace At0;



class Log
{
public:
	static void Open(const char* filepath)
	{
		Violent::FormatDescriptor format;
		format.Append(
			Violent::Format::Day,
			Violent::Format::Month
		);

		s_FileLogger.SetPath(filepath);
		s_FileLogger.SetFormat(format);
		s_ConsoleLogger.SetFormat(format);

		s_FileLogger.Open();
	}

	static void Close()
	{
		s_FileLogger.Close();
	}

	template<typename... Args>
	static void Trace(std::string_view msg, Args&&... args)
	{
		s_FileLogger.Trace(msg, std::forward<Args>(args)...);
		s_ConsoleLogger.Trace(msg, std::forward<Args>(args)...);
	}

	template<typename... Args>
	static void Debug(std::string_view msg, Args&&... args)
	{
		s_FileLogger.Debug(msg, std::forward<Args>(args)...);
		s_ConsoleLogger.Debug(msg, std::forward<Args>(args)...);
	}

	template<typename... Args>
	static void Info(std::string_view msg, Args&&... args)
	{
		s_FileLogger.Info(msg, std::forward<Args>(args)...);
		s_ConsoleLogger.Info(msg, std::forward<Args>(args)...);
	}

	template<typename... Args>
	static void Warn(std::string_view msg, Args&&... args)
	{
		s_FileLogger.Warn(msg, std::forward<Args>(args)...);
		s_ConsoleLogger.Warn(msg, std::forward<Args>(args)...);
	}

	template<typename... Args>
	static void Error(std::string_view msg, Args&&... args)
	{
		s_FileLogger.Error(msg, std::forward<Args>(args)...);
		s_ConsoleLogger.Error(msg, std::forward<Args>(args)...);
	}

	template<typename... Args>
	static void Critical(std::string_view msg, Args&&... args)
	{
		s_FileLogger.Critical(msg, std::forward<Args>(args)...);
		s_ConsoleLogger.Critical(msg, std::forward<Args>(args)...);
	}

private:
	inline static Violent::FileLogger s_FileLogger;
	inline static Violent::ConsoleLogger s_ConsoleLogger;
};



int main()
{
	Log::Open("Test.log");

	Log::Trace("Hello WO{0}ld", "r");
	Log::Debug("Hello WO{0}ld", "r");
	Log::Info("Hello WO{0}ld", "r");
	Log::Warn("Hello WO{0}ld", "r");
	Log::Error("Hello WO{0}ld", "r");
	Log::Critical("Hello WO{0}ld", "r");

	Log::Close();
}