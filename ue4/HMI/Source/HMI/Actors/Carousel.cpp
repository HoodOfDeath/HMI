// Fill out your copyright notice in the Description page of Project Settings.


#include "Carousel.h"

#include "WorldSpaceImage.h"
#include "Components/SceneCaptureComponent2D.h"
#include "Engine/TextureRenderTarget2D.h"

ACarousel::ACarousel()
{
	PrimaryActorTick.bCanEverTick = true;
	
	USceneComponent* DefaultPlatformRoot = CreateDefaultSubobject<USceneComponent>(TEXT("Carousel root"));
	RootComponent = DefaultPlatformRoot;

	RenderCamera = CreateDefaultSubobject<USceneCaptureComponent2D>(TEXT("RenderCamera"));
	RenderCamera->SetupAttachment(RootComponent);
}

void ACarousel::MoveNext()
{
	if (MovementState != EMovementState::Idle)
	{
		return;
	}
	
	++FrontItemIndex;
	FrontItemIndex = FrontItemIndex % ELEMENTS_IN_CAROUSEL;
	
	++FrontPlayerItemIndex;
	FrontPlayerItemIndex = FrontPlayerItemIndex % PlayerItems.Num();

	MovementState = EMovementState::MovingRight;

	int SwapCarouselItemIndex = (FrontItemIndex + 3) % ELEMENTS_IN_CAROUSEL;
	int SwapPlayerItemIndex = (FrontPlayerItemIndex + 3) % PlayerItems.Num();
	
	CarouselItems[SwapCarouselItemIndex]->SetImage(PlayerItems[SwapPlayerItemIndex].Cover);
	
	MovementTimeline.SetPlayRate(MovementRate);
	MovementTimeline.PlayFromStart();
}

void ACarousel::MovePrevious()
{
	if (MovementState != EMovementState::Idle)
	{
		return;
	}
	
	--FrontItemIndex;
	FrontItemIndex = (FrontItemIndex + ELEMENTS_IN_CAROUSEL) % ELEMENTS_IN_CAROUSEL;

	int PlayerItemsCount = PlayerItems.Num();
	
	--FrontPlayerItemIndex;
	FrontPlayerItemIndex = (FrontPlayerItemIndex + PlayerItemsCount) % PlayerItemsCount;

	MovementState = EMovementState::MovingLeft;

	int SwapCarouselItemIndex = (FrontItemIndex + 4) % ELEMENTS_IN_CAROUSEL;
	int SwapPlayerItemIndex = (FrontPlayerItemIndex - 3 + PlayerItemsCount) % PlayerItemsCount;

	CarouselItems[SwapCarouselItemIndex]->SetImage(PlayerItems[SwapPlayerItemIndex].Cover);

	MovementTimeline.SetPlayRate(MovementRate);
	MovementTimeline.PlayFromStart();
}

void ACarousel::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	MovementTimeline.TickTimeline(DeltaTime);
}

void ACarousel::BeginPlay()
{
	Super::BeginPlay();

	checkf(AnchorPoints.Num() == ELEMENTS_IN_CAROUSEL, TEXT("There must be %d anchor to ACarousel works properly"), ELEMENTS_IN_CAROUSEL)
	
	RenderTarget->ClearColor = FLinearColor::Transparent;
	
	if (IsValid(CarouselItemClass))
	{
		UWorld* World = GetWorld();

		const FVector ActorLocation = GetActorLocation();
		const FVector CameraLocation = RenderCamera->GetComponentLocation();
		
		for (int i = 0; i < ELEMENTS_IN_CAROUSEL; ++i)
		{
			AnchorPoints[i] = AnchorPoints[i] + ActorLocation;
			
			AWorldSpaceImage* Billboard = World->SpawnActor<AWorldSpaceImage>(CarouselItemClass, AnchorPoints[i], (CameraLocation - AnchorPoints[i]).Rotation());
			CarouselItems.Add(Billboard);
		}

		for (int i = 0; i < 4; ++i)
		{
			CarouselItems[i]->SetImage(PlayerItems[i].Cover);
		}

		for (int i = -1; i > -4; --i)
		{
			int CarouselItemIndex = ELEMENTS_IN_CAROUSEL + i;
			int PlayerItemIndex = PlayerItems.Num() + i;
			CarouselItems[CarouselItemIndex]->SetImage(PlayerItems[PlayerItemIndex].Cover);
		}
	}

	if (IsValid(MovementCurve))
	{
		FOnTimelineEvent OnEnd;
		OnEnd.BindUFunction(this, FName("OnStopCarousel"));
		MovementTimeline.SetTimelineFinishedFunc(OnEnd);

		FOnTimelineFloat TimelineCallback;
		TimelineCallback.BindUFunction(this, FName("UpdateCarouselMovement"));
		
		MovementTimeline.AddInterpFloat(MovementCurve, TimelineCallback);
	}


#if TESTING
	GetWorld()->GetTimerManager().SetTimer(CallMovementTimer,this, &ACarousel::MoveRandom, MovementCallDelay, true);
#endif
}

void ACarousel::UpdateCarouselMovement(float Value)
{
	int MovementShift = 0;
	
	switch (MovementState)
	{
		case EMovementState::MovingRight:
			MovementShift = -1;
			break;
		case EMovementState::MovingLeft:
			MovementShift = 1;
			break;
	}
	
	const FVector CameraLocation = RenderCamera->GetComponentLocation();

	for (int i = 0; i < ELEMENTS_IN_CAROUSEL; ++i)
	{
		FVector StartPos = AnchorPoints[i];
		FVector EndPos = AnchorPoints[(i + MovementShift + ELEMENTS_IN_CAROUSEL)%ELEMENTS_IN_CAROUSEL];

		const FVector NewItemLocation = FMath::Lerp(StartPos, EndPos, Value);
		const FRotator NewItemRotation = (CameraLocation - NewItemLocation).Rotation();

		const int ItemIndex = (FrontItemIndex + MovementShift + i + ELEMENTS_IN_CAROUSEL) % ELEMENTS_IN_CAROUSEL;
		CarouselItems[ItemIndex]->SetActorLocationAndRotation(NewItemLocation, NewItemRotation);
	}
}


void ACarousel::OnStopCarousel()
{
	MovementState = EMovementState::Idle;
}

#if TESTING

void ACarousel::MoveRandom()
{
	bool bMoveRight = FMath::RandBool();
	if (bMoveRight)
	{
		MoveNext();
	}
	else
	{
		MovePrevious();
	}
}

#endif
