// Fill out your copyright notice in the Description page of Project Settings.


#include "RadialProgressBar.h"
#include "Components/Image.h"

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


void URadialProgressBar::NativeTick(const FGeometry& MovieSceneBlends, float InDeltaTime)
{
	Super::NativeTick(MovieSceneBlends, InDeltaTime);
	
#if TESTING
	static float Time = Percent;
	Time+=(InDeltaTime / 5);

	Percent = FMath::Abs(FMath::Sin(Time));
#endif
	
	if (MaterialInstanceDynamic.IsValid())
	{
		MaterialInstanceDynamic->SetScalarParameterValue("Percent", Percent);
	}
}

