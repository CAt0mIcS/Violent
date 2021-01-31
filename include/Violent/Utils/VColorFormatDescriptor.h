#pragma once


namespace At0::Violent
{
	/**
	* Describes the different colors for the console to output
	*/
	struct Color
	{
		static constexpr const char* Default = "\033[39m";
		static constexpr const char* Black = "\033[30m";
		static constexpr const char* Red = "\033[31m";
		static constexpr const char* Green = "\033[32m";
		static constexpr const char* Yellow = "\033[33m";
		static constexpr const char* Blue = "\033[34m";
		static constexpr const char* Magenta = "\033[35m";
		static constexpr const char* Cyan = "\033[36m";
		static constexpr const char* LightGrey = "\033[37m";
		static constexpr const char* DarkGrey = "\033[90m";
		static constexpr const char* LightRed = "\033[91m";
		static constexpr const char* LightGreen = "\033[92m";
		static constexpr const char* LightYellow = "\033[93m";
		static constexpr const char* LightBlue = "\033[94m";
		static constexpr const char* LightMagenta = "\033[95m";
		static constexpr const char* LightCyan = "\033[96m";
		static constexpr const char* White = "\033[97m";
	};

	/**
	* Describes different styles for the console output
	*/
	struct Style
	{
		static constexpr const char* Default = "\033[0m";
		static constexpr const char* Bold = "\033[1m";
		static constexpr const char* Dim = "\033[2m";
		static constexpr const char* Underlined = "\033[4m";
		static constexpr const char* Blink = "\033[5m";
		static constexpr const char* Reverse = "\033[7m";
		static constexpr const char* Hidden = "\033[8m";
	};

	/**
	* Describes the colors for each log message
	*/
	struct ConsoleColorFormatDescriptor
	{
		const char* Trace = Color::Default;
		const char* Debug = Color::LightGreen;
		const char* Information = Color::Green;
		const char* Warning = Color::Yellow;
		const char* Error = Color::LightRed;
		const char* Critical = Color::Red;
	};

	/**
	* Describes the console style for each log message
	*/
	struct ConsoleStyleFormatDescriptor
	{
		const char* Trace = Style::Default;
		const char* Debug = Style::Default;
		const char* Information = Style::Default;
		const char* Warning = Style::Default;
		const char* Error = Style::Default;
		const char* Critical = Style::Default;
	};
}