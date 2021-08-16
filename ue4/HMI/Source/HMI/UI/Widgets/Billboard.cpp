// Fill out your copyright notice in the Description page of Project Settings.


#include "Billboard.h"

void UBillboard::SetImage(TAssetPtr<UTexture2D> NewTexture)
{
	UTexture2D* LoadedTexture = NewTexture.LoadSynchronous();
	MainImage->SetBrushFromTexture(LoadedTexture);
}
