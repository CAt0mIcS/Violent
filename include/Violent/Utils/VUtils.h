#pragma once

#include <string>
#include <sstream>
#include <type_traits>

#include <locale>
#include <codecvt>


namespace At0::Violent
{
	std::string ConvertUtf8(const std::wstring& wstr)
	{
		static std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;
		return converter.to_bytes(wstr);
	}

#include "VSerialize.inl"

	template<typename... Args>
	inline std::string SerializeString(std::string serializedStr, Args&&... args)
	{
		int argCount = 0;
		(SerializeStringArg(serializedStr, args, argCount), ...);
		return serializedStr;
	}
}  // namespace At0::Violent
