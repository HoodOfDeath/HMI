// Fill out your copyright notice in the Description page of Project Settings.


#include "SwitchImage.h"
#include "Components/Image.h"

void USwitchImage::Switch(bool bNewState)
{
	if (bNewState == bIsOn || !IsValid(ImageDisabled) || !IsValid(ImageEnabled))
	{
		return;
	}

	bIsOn = bNewState;

	if (bIsOn)
	{
		ImageEnabled->SetVisibility(ESlateVisibility::Visible);
		ImageDisabled->SetVisibility(ESlateVisibility::Hidden);
	}
	else
	{
		ImageEnabled->SetVisibility(ESlateVisibility::Hidden);
		ImageDisabled->SetVisibility(ESlateVisibility::Visible);
	}
}

void USwitchImage::SetState(EIndicatorState NewState)
{
	if (NewState == CurrentState)
	{
		return;
	}
	
	switch (NewState)
	{
		case EIndicatorState::On:
			{
				Switch(true);
				break;
			}
		case EIndicatorState::Blinking:
			{
				if (IsValid(ImageDisabled) && IsValid(ImageEnabled))
				{
					FTimerDelegate TimerCallback;
					TimerCallback.BindLambda([=](){Switch(!bIsOn);});
					GetWorld()->GetTimerManager().SetTimer(BlinkTimer, TimerCallback, BlinkPeriod, true);
				}
				break;
			}
		case EIndicatorState::Off:
		default:
			{
				Switch(false);
			}
	}

	CurrentState = NewState;
}

void USwitchImage::NativePreConstruct()
{
	Super::NativePreConstruct();

	bIsOn = false;

	EIndicatorState CachedState = CurrentState;
	CurrentState = EIndicatorState::Off;

	if (IsValid(ImageDisabled))
	{
		ImageDisabled->SetVisibility(ESlateVisibility::Visible);
		ImageDisabled->SetBrushFromTexture(TextureDisabled);
	}

	if (IsValid(ImageEnabled))
	{
		ImageEnabled->SetVisibility(ESlateVisibility::Hidden);
		ImageEnabled->SetBrushFromTexture(TextureEnabled);
	}

	SetState(CachedState);
}

#if TESTING
void USwitchImage::NativeConstruct()
{
	Super::NativeConstruct();
	
	SwitchToRandomState();
	GetWorld()->GetTimerManager().SetTimer(CallSwitchTimer,this, &USwitchImage::SwitchToRandomState, SwitchCallDelay, true);
}

void USwitchImage::SwitchToRandomState()
{
	int State = FMath::RandHelper(3);
	SetState((EIndicatorState)State);
}
#endif
