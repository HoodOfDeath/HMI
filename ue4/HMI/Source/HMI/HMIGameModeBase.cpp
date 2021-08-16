// Copyright Epic Games, Inc. All Rights Reserved.


#include "HMIGameModeBase.h"
#include "Kismet/GameplayStatics.h"
#include "UI/HMIHUD.h"

void AHMIGameModeBase::BeginPlay()
{
	Super::BeginPlay();

	APlayerController* PC = UGameplayStatics::GetPlayerController( GetWorld(), 0);
	AHMIHUD* HUD = PC->GetHUD<AHMIHUD>();
	HUD->CreateUI();
}
