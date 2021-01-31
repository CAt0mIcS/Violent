#pragma once

#include <type_traits>
#include <string>
#include <sstream>


namespace At0::Violent
{
	namespace Internal
	{
		template<typename T>
		using BaseType = typename std::remove_cv<typename std::remove_reference<T>::type>::type;

		template<typename, typename = void>
		struct HasOstreamOutputOperator : std::false_type {};

		template<typename T>
		struct HasOstreamOutputOperator<T, std::void_t<decltype(std::declval<std::ofstream>() << std::declval<T>())>> : std::true_type {};

		template<typename, typename = void>
		struct HasWOstreamOutputOperator : std::false_type {};

		template<typename T>
		struct HasWOstreamOutputOperator<T, std::void_t<decltype(std::declval<std::wofstream>() << std::declval<T>())>> : std::true_type {};
	}


	template<typename T>
	void SerializeStringArg(std::string& message, T&& arg, int& argCount)
	{
		if (argCount == -1)
			return;

		const std::string toFind = "{" + std::to_string(argCount) + "}";
		size_t foundIdx = message.find(toFind);


		if constexpr (Internal::HasOstreamOutputOperator<Internal::BaseType<T>>::value)
		{
			std::ostringstream oss;
			oss << arg;

			message.replace(
				message.begin() + foundIdx, message.begin() + foundIdx + std::size(toFind), oss.str());
			++argCount;
		}
		//else if constexpr (Internal::HasWOstreamOutputOperator<Internal::BaseType<T>>::value)
		//{
		//	std::wostringstream oss;
		//	oss << arg;


		//	message.replace(
		//		message.begin() + foundIdx, message.begin() + foundIdx + std::size(toFind), str);
		//	++argCount;
		//}
	}

	/**
	 * Takes a correct string possibly containing "{0}", "{1}", ... and fills these in with the
	 * corresponding argument
	 * @tparam Args Any list of arguments that have a output operator defined
	 * @param serializedStr The string which should be serialized
	 * @param args... The arguments to insert into the string
	 * @returns The serialized string
	 */
	template<typename... Args>
	std::string InsertArguments(std::string serializedStr, Args&&... args)
	{
		int argCount = 0;
		(SerializeStringArg(serializedStr, args, argCount), ...);
		return serializedStr;
	}
}