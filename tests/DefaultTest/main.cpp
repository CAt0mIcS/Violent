#include <Violent/Violent.h>

using namespace At0;



class Log
{
public:
	static void Open(const char* filepath)
	{
		Violent::FormatDescriptor format;
		format.Append(
			Violent::Day(),
			Violent::Month(),
			Violent::Year(),
			Violent::Hour(),
			Violent::Minute(),
			Violent::Second(),
			Violent::Millisecond(4)
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

private:
	inline static Violent::FileLogger s_FileLogger;
	inline static Violent::ConsoleLogger s_ConsoleLogger;
};



int main()
{
	Log::Open("Test.log");
	Log::Trace("Hello WOrld {0}, {1}", 1, std::wstring(L"d"));
}