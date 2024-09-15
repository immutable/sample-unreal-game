#pragma once
#include "OpenAPISearchStacksResult.h"

namespace OpenAPI
{
	class Model;
}

DECLARE_DELEGATE_TwoParams(FOnImmutableQueryComplete, bool /*bWasSuccessful*/, TSharedPtr<OpenAPI::Model> /*ResultData*/);

namespace ImmutableQuery
{
	struct FImmutableQueryRequestData
	{};
	
	struct FMP_SearchStacksRequestTraitData
	{
		FString TraitType;
		FString Value;
	};
	
	struct FMP_SearchStacksRequestData : public FImmutableQueryRequestData
	{
		TArray<FString> ContactAddress; // required
		FString AccountAddress;
		FString Keyword;
		bool OnlyIncludeOwnerListings = false;
		FString PageCursor;
		int32 PageSize = 0;
		TArray<FMP_SearchStacksRequestTraitData> Trait;
	};

	template<typename TQueryData = FImmutableQueryRequestData>
	static void ExecuteQuery(TSharedPtr<TQueryData> Data, const FOnImmutableQueryComplete& OnMarketplaceQueryComplete)
	// static void ExecuteQuery(TSharedPtr<TQueryData> Data, TFunction<bool /*bWasSuccessful*/, TSharedPtr<OpenAPI::Model> /*ResultData*/>(void) OnMarketplaceQueryComplete)
	{
		// Use the template type here to stop the compiler generating the code unless it's actually used
		static_assert(!TIsSame<OpenAPI::Model, TQueryData>::Value, "This function must be specialized to use with the specified type");
	}


	template<> inline void ExecuteQuery(TSharedPtr<FMP_SearchStacksRequestData> Data, const FOnImmutableQueryComplete& OnMarketplaceQueryComplete)
	{
		FString FileLocation = FPaths::Combine(*FPaths::ProjectDir(), TEXT("test.json"));

		if (!FPaths::FileExists(FileLocation))
		{
			OnMarketplaceQueryComplete.Execute(true, nullptr);
		}
		FString Content;

		FFileHelper::LoadFileToString(Content, *FileLocation);

		TSharedPtr<FJsonValue> RootJsonObject;
		const TSharedRef<TJsonReader<>> JsonReader = TJsonReaderFactory<>::Create(Content);
		
		if (FJsonSerializer::Deserialize(JsonReader, RootJsonObject))
		{
			TSharedPtr<OpenAPI::OpenAPISearchStacksResult> SearchStacksResult = MakeShareable(new OpenAPI::OpenAPISearchStacksResult());
		
			SearchStacksResult->FromJson(RootJsonObject);
			OnMarketplaceQueryComplete.Execute(true, SearchStacksResult);
		}
	}
	
};