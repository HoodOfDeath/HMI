// Fill out your copyright notice in the Description page of Project Settings.


#include "HMIPlayerController.h"

void AHMIPlayerController::BeginPlay()
{
	Super::BeginPlay();

	FInputModeUIOnly ModeUIOnly;
	SetInputMode(ModeUIOnly);

	bShowMouseCursor = true;
}
