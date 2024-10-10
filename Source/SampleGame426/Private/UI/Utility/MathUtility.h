#pragma once

class FMathUtility
{
public:
	// !NOTE: VERY VERY VERY IMPORTANT
	// !NOTE: HAS TO BE REDESIGNED AND CONFIRMDE THAT THESE METHOD CALCULATE AND CONVERT VALUES CORRECTLY

	static FString ConvertWeiStringToFloatValueString(int32 Decimals, const FString &Value);
	static FString ConvertFloatValueStringToWeiString(int32 Decimals, const FString& Value);
};