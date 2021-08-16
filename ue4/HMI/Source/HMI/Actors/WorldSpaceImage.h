// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "UI/Widgets/Billboard.h"
#include "WorldSpaceImage.generated.h"

UCLASS(Abstract)
class HMI_API AWorldSpaceImage : public AActor
{
	GENERATED_BODY()
	
public:
	AWorldSpaceImage();

	void SetImage(TAssetPtr<UTexture2D> NewTexture);

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	class UWidgetComponent* WidgetComponent;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TSubclassOf<UBillboard> BillboardClass;
	
	TWeakObjectPtr<UBillboard> ImageWidget;
	
	virtual void BeginPlay() override;
};
