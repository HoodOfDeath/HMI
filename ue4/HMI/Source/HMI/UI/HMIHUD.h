// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "HMIHUD.generated.h"

/**
 * 
 */
UCLASS()
class HMI_API AHMIHUD : public AHUD
{
	GENERATED_BODY()

public:
	void CreateUI();

protected:
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<class UUserWidget> MainWidgetClass;

	TWeakObjectPtr<UUserWidget> MainWidget;
};
