// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/TimelineComponent.h"
#include "Carousel.generated.h"

class AWorldSpaceImage;

#define ELEMENTS_IN_CAROUSEL 7
#define TESTING true

UENUM()
enum class EMovementState : uint8
{
	Idle = 0,
	MovingRight = 1,
	MovingLeft = 2 
};

USTRUCT(BlueprintType)
struct FPlayerItem
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TAssetPtr<UTexture2D> Cover;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FText SongName;
};

UCLASS(Abstract)
class HMI_API ACarousel : public AActor
{
	GENERATED_BODY()
	
public:	
	ACarousel();

	UFUNCTION(BlueprintCallable)
	void MoveNext();

	UFUNCTION(BlueprintCallable)
	void MovePrevious();
	
	virtual void Tick(float DeltaTime) override;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TArray<FPlayerItem> PlayerItems;

	UPROPERTY(EditInstanceOnly, BlueprintReadOnly, meta = (MakeEditWidget))
	TArray<FVector> AnchorPoints;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TSubclassOf<AWorldSpaceImage> CarouselItemClass;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	UTextureRenderTarget2D* RenderTarget;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	USceneCaptureComponent2D* RenderCamera;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	UCurveFloat* MovementCurve = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float MovementRate = 2;
	
private:
	int FrontItemIndex = 0;

	int FrontPlayerItemIndex = 0;

	EMovementState MovementState = EMovementState::Idle;
	
	FTimeline MovementTimeline;

	TArray<AWorldSpaceImage*, TInlineAllocator<ELEMENTS_IN_CAROUSEL>> CarouselItems;

	virtual void BeginPlay() override;

	UFUNCTION()
	void UpdateCarouselMovement(float Value);

	UFUNCTION()
	void OnStopCarousel();

#if TESTING
	//Testing functionality

	FTimerHandle CallMovementTimer;

	float MovementCallDelay = 1.5f;
	
	void MoveRandom();
#endif

};
