// Fill out your copyright notice in the Description page of Project Settings.


#include "WorldSpaceImage.h"
#include "Components/WidgetComponent.h"
#include "UI/Widgets/Billboard.h"

// Sets default values
AWorldSpaceImage::AWorldSpaceImage()
{
	PrimaryActorTick.bCanEverTick = false;

	USceneComponent* DefaultPlatformRoot = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	RootComponent = DefaultPlatformRoot;
	
	WidgetComponent = CreateDefaultSubobject<UWidgetComponent>(TEXT("Widget component"));
	WidgetComponent->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
}

void AWorldSpaceImage::SetImage(TAssetPtr<UTexture2D> NewTexture)
{
	ImageWidget->SetImage(NewTexture);
}

void AWorldSpaceImage::BeginPlay()
{
	Super::BeginPlay();
	
	ImageWidget = Cast<UBillboard>(WidgetComponent->GetUserWidgetObject());
}
