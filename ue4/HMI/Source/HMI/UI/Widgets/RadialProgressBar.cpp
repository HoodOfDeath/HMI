// Fill out your copyright notice in the Description page of Project Settings.


#include "RadialProgressBar.h"
#include "Components/Image.h"

URadialProgressBar::URadialProgressBar(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
}

void URadialProgressBar::NativeTick(const FGeometry& MovieSceneBlends, float InDeltaTime)
{
	Super::NativeTick(MovieSceneBlends, InDeltaTime);

	static float Time = 0;
	Time+=(InDeltaTime / 5);

	Percent = FMath::Abs(FMath::Sin(Time));
	
	if (MaterialInstanceDynamic.IsValid())
	{
		MaterialInstanceDynamic->SetScalarParameterValue("Percent", Percent);
	}
}

void URadialProgressBar::NativePreConstruct()
{
	Super::NativePreConstruct();

	if (IsValid(Image_Base))
	{
		if (MaterialInstance)
		{
			MaterialInstanceDynamic = UMaterialInstanceDynamic::Create(MaterialInstance, this);
			MaterialInstanceDynamic->SetScalarParameterValue("Percent", Percent);

			Image_Base->SetBrushFromMaterial(MaterialInstanceDynamic.Get());
		}
	}
}
