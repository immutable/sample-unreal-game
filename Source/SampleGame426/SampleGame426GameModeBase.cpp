#include "SampleGame426GameModeBase.h"

#include "LogSampleGame.h"
#include "OpenAPISearchStacksResult.h"

#include "Misc/AutomationTest.h"

void ASampleGame426GameModeBase::InitGame(const FString& MapName, const FString& Options, FString& ErrorMessage)
{
	
}

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FJsonParserTest, "JsonParserTest", EAutomationTestFlags::EditorContext | EAutomationTestFlags::ProductFilter)

bool FJsonParserTest::RunTest(const FString& Parameters)
{
	FString FileLocation = FPaths::Combine(*FPaths::ProjectDir(), TEXT("test.json"));

	if (!FPaths::FileExists(FileLocation))
	{
		return false;
	}
	FString Content;

	FFileHelper::LoadFileToString(Content, *FileLocation);

	TSharedPtr<FJsonValue> RootJsonObject;
	UE_LOG(LogSampleGame, Log, TEXT("%s"), *Content);
	// Parse the JSON
	const TSharedRef<TJsonReader<>> JsonReader = TJsonReaderFactory<>::Create(Content);
		
	if (FJsonSerializer::Deserialize(JsonReader, RootJsonObject))
	{
		OpenAPI::OpenAPISearchStacksResult SearchStacksReesult;
		
		SearchStacksReesult.FromJson(RootJsonObject);

		UE_LOG(LogSampleGame, Log, TEXT("%s"), *SearchStacksReesult.Page.PreviousCursor.GetValue());
	}
	
	// TSharedPtr<FJsonObject> RootJsonObject;
	// const TSharedRef<TJsonReader<>> JsonReader = TJsonReaderFactory<>::Create(Content);
	//
	// if (FJsonSerializer::Deserialize(JsonReader, RootJsonObject))
	// {
	// 	const TSharedPtr<FJsonObject>& PageObject = RootJsonObject->GetObjectField(TEXT("Page"));
	//
	// 	const TArray<TSharedPtr<FJsonValue>>* ResultArray;
	// 	if (RootJsonObject->TryGetArrayField(TEXT("result"), ResultArray))
	// 	{
	// 		for (TSharedPtr<FJsonValue> ResultItem : *ResultArray)
	// 		{
	// 			const TSharedPtr<FJsonObject> ResultItemObject = ResultItem->AsObject();
	//
	// 			const FJsonObject& Stack = *ResultItemObject->GetObjectField(TEXT("stack"));
	//
	// 			FString ImageURL = Stack.GetStringField(TEXT("image"));
	// 			
	// 			
	// 			UE_LOG(LogSampleGame, Log, TEXT("%s"), *ImageURL);		
	// 		}
	// 	}
	//
	// 	UE_LOG(LogSampleGame, Log, TEXT("%s"), *PageObject->GetStringField(TEXT("next_cursor")));
	// }

	return true;
}