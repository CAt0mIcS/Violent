#pragma once

#include <string>
#include <sstream>
#include <type_traits>

#include <locale>
#include <codecvt>


namespace At0::Violent
{
	inline std::string ConvertUtf8(std::wstring_view wstr)
	{
		static std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;
		return converter.to_bytes(wstr.data());
	}
}  // namespace At0::Violent
