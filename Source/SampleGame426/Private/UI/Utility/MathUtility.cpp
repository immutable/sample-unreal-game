#include "UI/Utility/MathUtility.h"

#include <string>
#include <sstream>

// Undefine to avoid conflicts
#pragma push_macro("check")
#undef check

#include <boost/multiprecision/cpp_int.hpp>
#include <boost/multiprecision/cpp_bin_float.hpp>

// Redefine check macro
#pragma pop_macro("check")

using BigInt = boost::multiprecision::cpp_int;// boost::multiprecision::int128_t;
using BigFloat = boost::multiprecision::cpp_bin_float_quad;

FString FMathUtility::ConvertWeiStringToFloatValueString(int32 Decimals, const FString &Value)
{
	std::string StringNumber = TCHAR_TO_ANSI(*Value);

	BigInt x(StringNumber);
	BigInt y(10);

	y = boost::multiprecision::pow(y, Decimals);
	
	BigFloat Result = BigFloat(x) / BigFloat(y);

	std::stringstream StringStream;

	StringStream << std::setprecision(7) << Result;

	return StringStream.str().c_str();
}

FString FMathUtility::ConvertFloatValueStringToWeiString(int32 Decimals, const FString& Value)
{
	std::string StringNumber = TCHAR_TO_ANSI(*Value);

	BigFloat x(StringNumber);
	BigInt y(10);

	y = boost::multiprecision::pow(y, Decimals);
	x *= BigFloat(y);

	std::stringstream StringStream;

	StringStream << BigInt(x);

	return StringStream.str().c_str();
}
