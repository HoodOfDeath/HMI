// Fill out your copyright notice in the Description page of Project Settings.


#include "HMIHUD.h"
#include "Blueprint/UserWidget.h"

void AHMIHUD::CreateUI()
{
	// Make widget owned by our PlayerController
	APlayerController* PC = Cast<APlayerController>( GetOwner() );
	MainWidget = CreateWidget<UUserWidget>( PC, MainWidgetClass );

	MainWidget->AddToViewport();
}
