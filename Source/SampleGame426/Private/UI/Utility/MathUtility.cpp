#include "UI/Utility/MathUtility.h"



#include "LogSampleGame.h"
//#include "UI/Utility/BigFloat/BigFloat.h"
#include <string>
#include <sstream>

// Undefine to avoid conflicts
#pragma push_macro("check")
#undef check

#include <boost/multiprecision/cpp_int.hpp>
#include <boost/multiprecision/cpp_bin_float.hpp>

// Redefine check macro
#pragma pop_macro("check")

FString FMathUtility::ConvertWeiStringToFloatValueString(int32 Decimals, const FString &Value)
{
// 	if (Decimals > 18)
// 	{
// 		UE_LOG(LogSampleGame, Error, TEXT("We need to rework calculation with big numbers"));
//
// 		return FString();
// 	}
//
// 	BigFloat BigValue(TCHAR_TO_ANSI(*Value));
// 	BigFloat BigDecimals(10);
//
// 	for (int32 i = 0; i < Decimals; ++i, BigDecimals *= 10);
// 	
// 	BigValue /= BigDecimals;
// 	
// 	return FString(BigValue.ToString().c_str());

	using BigFloat = boost::multiprecision::cpp_bin_float_quad;

	std::string StringNumber = TCHAR_TO_ANSI(*Value);

	BigFloat x(StringNumber);
	BigFloat Decimal("1000000000000000000");
	x /= Decimal;

	std::stringstream StringStream;

	StringStream << std::setprecision(2) << x;

	return StringStream.str().c_str();
}

FString FMathUtility::ConvertFloatValueStringToWeiString(int32 Decimals, const FString& Value)
{
	// BigFloat BigValue(std::string(TCHAR_TO_UTF8(*Value)));
	// BigFloat BigDecimals(10);
	//
	// for (int32 i = 0; i < Decimals; ++i, BigDecimals *= 10);
	//
	// BigValue *= BigDecimals;
	// BigValue.SetPrecision(0);
	//
	// return FString(BigValue.ToString().c_str());


	using BigFloat = boost::multiprecision::cpp_bin_float_quad;

	std::string StringNumber = TCHAR_TO_ANSI(*Value);

	BigFloat x(StringNumber);
	BigFloat Decimal("1000000000000000000");
	x *= Decimal;

	const auto result = boost::multiprecision::int128_t(x);

	std::stringstream StringStream;

	StringStream << result;

	return StringStream.str().c_str();
}
