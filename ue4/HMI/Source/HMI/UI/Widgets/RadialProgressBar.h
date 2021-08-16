// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "RadialProgressBar.generated.h"

#define TESTING false

UCLASS(Abstract)
class HMI_API URadialProgressBar : public UUserWidget
{
	GENERATED_BODY()

public:
	UPROPERTY(meta = ( BindWidget ))
	class UImage* Image_Base;

	UPROPERTY(EditAnywhere, Category="Progress bar")
	UMaterialInstance* MaterialInstance;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Progress bar", meta=(UIMin = 0.0f, ClampMin = 0.0f, UIMax = 1.0f, ClampMax = 1.0f))
	float Percent;

	UFUNCTION(BlueprintCallable)
	void SetPercent(float NewPercent) {Percent = NewPercent;}

private:
	TWeakObjectPtr<UMaterialInstanceDynamic> MaterialInstanceDynamic;

	virtual void NativePreConstruct() override;

	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;
	
};
