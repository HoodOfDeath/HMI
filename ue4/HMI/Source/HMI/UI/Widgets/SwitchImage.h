// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "SwitchImage.generated.h"


UENUM()
enum class EIndicatorState : uint8
{
	Off = 0,
	On = 1,
	Blinking = 2 
};

UCLASS(Abstract)
class HMI_API USwitchImage : public UUserWidget
{
	GENERATED_BODY()

public:
	UPROPERTY(meta = ( BindWidget ))
	class UImage* ImageEnabled;

	UPROPERTY(meta = ( BindWidget ))
	class UImage* ImageDisabled;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UTexture2D* TextureEnabled = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UTexture2D* TextureDisabled = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EIndicatorState CurrentState = EIndicatorState::Off;

	void SetState(EIndicatorState NewState);

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (ClampMin = 0.0f, ClampMax = 10.0f, UIMin = 0.0f, UIMax = 10.0f))
	float BlinkPeriod = 0.5f;

	void Switch(bool bNewState);
	
private:
	FTimerHandle BlinkTimer;
	
	bool bIsOn = false;
	
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

	virtual void NativePreConstruct() override;
};
