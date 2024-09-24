#include "Marketplace/MarketplaceUtility.h"

#include <sstream>

#include "LogSampleGame.h"
#include "Settings/SampleGameSettings.h"
#include "BigFloat/BigFloat.h"


FString FMarketplaceUtility::ConvertMarketplaceTokenValue(int32 Decimals, const FString &Value)
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
	std::string str;
	std::stringstream ss;

	ss << BigValue;
	//return FString::SanitizeFloat(, GetDefault<USampleGameSettings>()->NumberFractionalDigits);

	return FString(ss.str().c_str());
}
