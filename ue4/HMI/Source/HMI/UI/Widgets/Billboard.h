// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Image.h"
#include "Billboard.generated.h"

/**
 * 
 */
UCLASS(Abstract)
class HMI_API UBillboard : public UUserWidget
{
	GENERATED_BODY()

public:
	void SetImage(TAssetPtr<UTexture2D> NewTexture);
	
protected:
	UPROPERTY(meta = ( BindWidget ))
	UImage* MainImage;

	TAssetPtr<UTexture2D> Texture;
};
