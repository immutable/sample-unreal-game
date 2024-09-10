// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ItemWidget.generated.h"

/**
 * 
 */
UCLASS(Abstract, BlueprintType)
class SAMPLEGAME426_API UItemWidget : public UUserWidget
{
	GENERATED_BODY()

public:

	virtual void SetTextureNFT(TSoftObjectPtr<UTexture2D> Texture);
	virtual void SetName(FName Name);
	virtual void SetPrice(float Price);

protected:

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	class UTextBlock* NameNFT = nullptr;
	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	class UImage* TextureNFT  = nullptr;
	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	class UTextBlock* PriceNFT = nullptr;

};
