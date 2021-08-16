// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "HMIPlayerController.generated.h"

/**
 * 
 */
class UHMIMainHUD;

UCLASS()
class HMI_API AHMIPlayerController : public APlayerController
{
	GENERATED_BODY()
public:
	virtual void BeginPlay() override;
};
