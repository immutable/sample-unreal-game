#include "UI/Utility/MathUtility.h"

#include <sstream>

#include "LogSampleGame.h"
#include "UI/Utility/BigFloat/BigFloat.h"


FString FMathUtility::ConvertWeiStringToFloatValueString(int32 Decimals, const FString &Value)
{
	if (Decimals > 18)
	{
		UE_LOG(LogSampleGame, Error, TEXT("We need to rework calculation with big numbers"));

		return FString();
	}

	BigFloat BigValue(TCHAR_TO_ANSI(*Value));
	BigFloat BigDecimals(10);

	for (int32 i = 0; i < Decimals; ++i, BigDecimals *= 10);
	
	BigValue /= BigDecimals;
	
	std::stringstream ss;

	ss << BigValue;
	//return FString::SanitizeFloat(, GetDefault<USampleGameSettings>()->NumberFractionalDigits);

	return FString(ss.str().c_str());
}

FString FMathUtility::ConvertFloatValueStringToWeiString(int32 Decimals, const FString& Value)
{
	BigFloat BigValue(std::string(TCHAR_TO_UTF8(*Value)));
	BigFloat BigDecimals(10);

	for (int32 i = 0; i < Decimals; ++i, BigDecimals *= 10);

	BigValue *= BigDecimals;

	std::stringstream ss;
	
	ss << BigValue;

	return FString(ss.str().c_str());
}
